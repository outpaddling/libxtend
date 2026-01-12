#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sysexits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "proc.h"

/***************************************************************************
 *  Name:
 *      xt_spawnvp() - Fork and exec a new process from an argv-style array
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      xt_spawnvp() and xt_spawnlp() are wrappers around fork(2) and exec(3)
 *      which make it easy to run a child process without an intermediate
 *      shell process as is used by system(3).  The xt_spawnlp() function
 *      spawns a child process using a variable argument list.  The 6th
 *      argument is passed to argv[0] of the child, the 7th to argv[1], etc.
 *
 *      The xt_spawnvp() function spawns a process using the command contained
 *      in an argv[] array constructed by the caller.  xt_spawnlp() automatically
 *      constructs such an argv[] array and calls xt_spawnvp().
 *
 *      The calling process waits for the child to complete if P_WAIT is
 *      passed to parent_action, or continues immediately if P_NOWAIT
 *      is passed.  If P_ECHO is passed as the echo argument, the command
 *      is echoed, the command is echoed to the parent's stdout.
 *
 *      If infile, outfile, or errfile are not NULL, then the corresponding
 *      file streams stdin, stdout, or stderr are redirected to the filename
 *      provided.
 *  
 *  Arguments:
 *      parent_action:  P_WAIT or P_NOWAIT
 *      echo:           P_ECHO or P_NOECHO
 *      infile:         File to which stdin of child is redirected or NULL
 *      outfile:        File to which stdout of child is redirected or NULL
 *      errfile:        File to which stderr of child is redirected or NULL
 *
 *  Returns:
 *      The exit status of the child process if P_WAIT is passed
 *      The PID of the child process if P_NOWAIT is passed
 *
 *  See also:
 *      xt_spawnlp(3), fork(2), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

// FIXME: Ugly stop-gap for now.  sig_t is not portable, so don't use it.
#if defined(__sun__)
typedef void (*sig_t)(int);
#endif

int     xt_spawnvp(int parent_action, int echo, char *argv[],
                const char *infile, const char *outfile, const char *errfile)

{
    int     stat = 0;
    pid_t   pid;
    char    **p;
    extern int  errno;
    sig_t   oldsig;
    
    switch(echo)
    {
        case    P_ECHO:     /* Echo command */
            for (p = argv; *p != NULL; ++p)
                printf("%s ",*p);
            putchar('\n');
            fflush(stdout);
        case    P_NOECHO:
            break;
        default:
            fprintf(stderr,
                "xt_spawnvp(): Invalid echo flag: must be ECHO or NO_ECHO.\n");
            exit(1);
    }
    
    /* If in child process, exec the new program */
    if ((pid = fork()) == 0)
    {
        xt_redirect(infile,outfile,errfile);
        signal(SIGINT,SIG_DFL); /* Allow child process to be interrupted */
        execvp(argv[0], argv);
        fprintf(stderr, "%s: %s: Cannot execute: %s\n", __FUNCTION__,
                argv[0], strerror(errno));
        exit(EX_UNAVAILABLE);   /* Return errno - all I could think of */
        // exit(errno|0x80);   /* Return errno - all I could think of */
    }
    else    /* If parent, wait for child to croak */
    {
        switch ( parent_action )
        {   
            case    P_WAIT:
                /* wait() may fail is SIGCHLD isn't SIG_DFL */
                oldsig = signal(SIGCHLD,SIG_DFL);
                waitpid(pid,&stat,0);
                signal(SIGCHLD,oldsig);
                return stat;
            case    P_NOWAIT:
                return pid;
            default:
                fprintf(stderr,"xt_spawnvp(): Invalid parent action.\n");
                exit(1);
        }
    }
    /* Dummy return for some compilers (IRIX) that think the code
       can actually get here */
    return 0;
}


/*************************************************************************
 * Name:
 *  xt_redirect() - Redirect stdin, stdout and stderr if corresponding argument isn't NULL
 *
 * Description: 
 *  This function redirects the stdin, stdout, and stderr of the current
 *  process to the files named by the corresponding arguments.  The original
 *  file streams are not preserved.  If you need to restore any of these
 *  streams to their original state, they must be saved (e.g. using dup(),
 *  dup2(), or ttyname()) prior to calling xt_redirect().
 * 
 * Author: 
 *  Jason W. Bacon
 ****************************************************************************/
 
void    xt_redirect(
    const char *infile,    /* If not NULL, stdin is redirected from this file */
    const char *outfile,   /* If not NULL, stdout is redirected to this file */
    const char *errfile    /* If not NULL, stderr is redirected to this file */
    )

{
    if (infile != NULL)
    {
        close(0);
        if ( open(infile, O_RDONLY) == -1 )
            fprintf(stderr,"%s(): Cannot open infile %s: %s.\n",
                    __FUNCTION__, infile, strerror(errno));
    }
    if (outfile != NULL)
    {
        close(1);
        if ( open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0600) == -1 )
            fprintf(stderr,"%s(): Cannot open outfile %s: %s.\n",
                    __FUNCTION__, outfile, strerror(errno));
    }
    if (errfile != NULL)
    {
        close(2);
        if ( strcmp(errfile,outfile) == 0 )
        {
            if ( dup(1) == -1 )
                fprintf(stderr,"%s(): Cannot open errfile %s: %s.\n",
                        __FUNCTION__, errfile, strerror(errno));
        }
        else
        {
            if ( open(errfile, O_WRONLY | O_CREAT | O_TRUNC, 0600) == -1 )
                fprintf(stderr,"%s(): Cannot open errfile %s: %s.\n",
                        __FUNCTION__, errfile, strerror(errno));
        }
    }
}

