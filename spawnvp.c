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
 *      .B xt_spawnvp()
 *      is a wrapper around fork(2) and exec(3)
 *      which makes it easy to run a child process without an intermediate
 *      shell process as is used by system(3).
 *
 *      The xt_spawnvp() function spawns a process using the command contained
 *      in an argv[] array constructed by the caller.
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
 *      .B xt_spawnvp(3)
 *      is a wrapper that
 *      calls xt_spawnvp10(3) using default values O_RDONLY for infile_flags,
 *      O_WRONLY|O_CREAT|O_TRUNC for outfile_flags and errfile_flags,
 *      and 0755 for mode.
 *  
 *  Arguments:
 *      parent_action   P_WAIT or P_NOWAIT
 *      echo            P_ECHO or P_NOECHO
 *      infile          File to which stdin of child is redirected or NULL
 *      outfile         File to which stdout of child is redirected or NULL
 *      errfile         File to which stderr of child is redirected or NULL
 *
 *  Returns:
 *      The exit status of the child process if P_WAIT is passed
 *      The PID of the child process if P_NOWAIT is passed
 *
 *  See also:
 *      xt_spawnlp(3), xt_redirect(3),
 *      xt_spawnlp10(3), xt_spawnvp10(3), xt_redirect7(3),
 *      fork(2), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

// FIXME: Ugly stop-gap for now.  sig_t is not portable, so don't use it.
#if defined(__sun__)
typedef void (*sig_t)(int);
#endif

int     xt_spawnvp(int parent_action, int echo, const char *argv[],
                   const char *infile, const char *outfile, const char *errfile)

{
    int     in_flags = O_RDONLY,
            out_flags = O_WRONLY|O_CREAT|O_TRUNC;
            
    return xt_spawnvp10(parent_action, echo, argv,
                       infile, outfile, errfile, in_flags, out_flags, out_flags,
                       0755);
}


/***************************************************************************
 *  Name:
 *      xt_spawnvp10() - Fork and exec a new process from an argv-style array
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      xt_spawnvp10() is a wrapper around fork(2) and exec(3)
 *      which makes it easy to run a child process without an intermediate
 *      shell process as is used by system(3).
 *
 *      The xt_spawnvp10() function spawns a process using the command contained
 *      in an argv[] array constructed by the caller.
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
 *      In contrast to xt_spawnvp(3), xt_spawnvp10(3) gives the caller
 *      full control over the open(2) mode of all redirect files and
 *      permissions (before umask is applied) of files that are created.
 *  
 *  Arguments:
 *      parent_action   P_WAIT or P_NOWAIT
 *      echo            P_ECHO or P_NOECHO
 *      infile          File to which stdin of child is redirected or NULL
 *      outfile         File to which stdout of child is redirected or NULL
 *      errfile         File to which stderr of child is redirected or NULL
 *      infile_flags    Open mode flags for infile
 *      outfile_flags   Open mode flags for outfile
 *      errfile_flags   Open mode flags for errfile
 *      mode            Permissions before applying umask(2) when creating outfile/errfile
 *
 *  Returns:
 *      The exit status of the child process if P_WAIT is passed
 *      The PID of the child process if P_NOWAIT is passed
 *
 *  See also:
 *      xt_spawnlp10(3), xt_redirect7(3),
 *      xt_spawnvp(3), xt_spawnlp(3), xt_redirect(3),
 *      fork(2), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2026-06-04  Jason Bacon Begin
 ***************************************************************************/

int     xt_spawnvp10(int parent_action, int echo, const char *argv[],
                   const char *infile, const char *outfile, const char *errfile,
                   int infile_flags, int outfile_flags, int errfile_flags,
                   int mode)

{
    int         status = 0;
    pid_t       pid;
    const char  **p;
    extern int  errno;
    sig_t       oldsig;
    
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
        xt_redirect7(infile, outfile, errfile,
                     infile_flags, outfile_flags, errfile_flags, mode);
        signal(SIGINT,SIG_DFL); /* Allow child process to be interrupted */
        // FIXME: Silencing warning due to execvp interface
        // char * const argv[]
        // Does execvp really need lvalues?
        execvp(argv[0], (char **)argv);
        fprintf(stderr, "%s(): %s: Cannot execute: %s\n", __FUNCTION__,
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
                waitpid(pid,&status,0);
                signal(SIGCHLD,oldsig);
                return status;
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
 *  Name:
 *      xt_redirect() - Redirect stdin, stdout and stderr if corresponding argument isn't NULL
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description: 
 *      This function redirects the stdin, stdout, and stderr of the current
 *      process to the files named by the corresponding arguments.  The original
 *      file streams are not preserved.  If you need to restore any of these
 *      streams to their original state, they must be saved (e.g. using dup(),
 *      dup2(), or ttyname()) prior to calling xt_redirect().
 *
 *      This function is a wrapper around xt_redirect7(3), which uses
 *      default values of O_RDONLY for infile_flags, O_WRONLY|O_CREAT|O_TRUNC
 *      for outfile_flags and errfile_flags, and 0755 for mode.
 *
 *  Arguments:
 *      infile          File to which stdin of child is redirected or NULL
 *      outfile         File to which stdout of child is redirected or NULL
 *      errfile         File to which stderr of child is redirected or NULL
 *
 *  Returns:
 *      void
 *
 *  See also:
 *      xt_redirect7(3),
 *      xt_spawnlp(3), xt_spawnvp(3)
 *      xt_spawnlp10(3), xt_spawnvp10(3)
 *
 *  Author: 
 *      Jason W. Bacon
 ****************************************************************************/
 
void    xt_redirect(
    const char *infile,    /* If not NULL, stdin is redirected from this file */
    const char *outfile,   /* If not NULL, stdout is redirected to this file */
    const char *errfile    /* If not NULL, stderr is redirected to this file */
    )

{
    int     in_flags = O_RDONLY,
            out_flags = O_WRONLY|O_CREAT|O_TRUNC;
    
    xt_redirect7(infile, outfile, errfile, in_flags, out_flags, out_flags, 0755);
}


/*************************************************************************
 *  Name:
 *      xt_redirect7() - Redirect stdin, stdout and stderr if corresponding argument isn't NULL
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description: 
 *      This function redirects the stdin, stdout, and stderr of the current
 *      process to the files named by the corresponding arguments.  The original
 *      file streams are not preserved.  If you need to restore any of these
 *      streams to their original state, they must be saved (e.g. using dup(),
 *      dup2(), or ttyname()) prior to calling xt_redirect().
 *
 *      Unlike xt_redirect(3), xt_redirect7(3) gives the caller full
 *      control over open(2) modes and file permissions (before umask is
 *      applied) when creating files.
 *
 *  Arguments:
 *      infile          File to which stdin of child is redirected or NULL
 *      outfile         File to which stdout of child is redirected or NULL
 *      errfile         File to which stderr of child is redirected or NULL
 *      infile_flags    Open mode flags for infile
 *      outfile_flags   Open mode flags for outfile
 *      errfile_flags   Open mode flags for errfile
 *      mode            Permissions before applying umask(2) when creating outfile/errfile
 *
 *  Returns:
 *      void
 *
 *  See also:
 *      xt_redirect(3),
 *      xt_spawnlp10(3), xt_spawnvp10(3),
 *      xt_spawnlp(3), xt_spawnvp(3)
 *
 *  Author: 
 *      Jason W. Bacon
 ****************************************************************************/

void    xt_redirect7(
    const char *infile,    /* If not NULL, stdin is redirected from this file */
    const char *outfile,   /* If not NULL, stdout is redirected to this file */
    const char *errfile,   /* If not NULL, stderr is redirected to this file */
    int   infile_flags,
    int   outfile_flags,
    int   errfile_flags,
    int   mode
    )

{
    if (infile != NULL)
    {
        close(0);
        if ( open(infile, infile_flags) == -1 )
            fprintf(stderr,"%s(): Cannot open infile %s: %s.\n",
                    __FUNCTION__, infile, strerror(errno));
    }
    if (outfile != NULL)
    {
        close(1);
        if ( open(outfile, outfile_flags, mode) == -1 )
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
            if ( open(errfile, errfile_flags, mode) == -1 )
                fprintf(stderr,"%s(): Cannot open errfile %s: %s.\n",
                        __FUNCTION__, errfile, strerror(errno));
        }
    }
}

