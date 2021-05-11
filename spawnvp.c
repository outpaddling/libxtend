#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "xtend.h"

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      spawnvp() and spawnlp() are wrappers around fork(2) and exec(3)
 *      which make it easy to run a child process without an intermediate
 *      shell process as is used by system(3).  The spawnlp() function
 *      spawns a child process using a variable argument list.  The 6th
 *      argument is passed to argv[0] of the child, the 7th to argv[1], etc.
 *
 *      The spawnvp() function spawns a process using the command contained
 *      in an argv[] array constructed by the caller.  spawnlp() automatically
 *      constructs such an argv[] array and calls spawnvp().
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
 *      spawnlp(3), fork(2), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     spawnvp(int parent_action, int echo, char *argv[],
		char *infile, char *outfile, char *errfile)

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
		"spawnvp(): Invalid echo flag: must be ECHO or NO_ECHO.\n");
	    exit(1);
    }
    
    /* If in child process, exec the new program */
    if ((pid = fork()) == 0)
    {
	redirect(infile,outfile,errfile);
	signal(SIGINT,SIG_DFL); /* Allow child process to be interrupted */
	execvp(argv[0], argv);
	exit(errno|0x80);   /* Return errno - all I could think of */
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
		fprintf(stderr,"spawnvp(): Invalid parent action.\n");
		exit(1);
	}
    }
    /* Dummy return for some compilers (IRIX) that think the code
       can actually get here */
    return 0;
}


/*************************************************************************
 * Name:
 *  Redirect stdin, stdout and stderr if corresponding argument isn't NULL
 *
 * Description: 
 *  This function redirects the stdin, stdout, and stderr of the current
 *  process to the files named by the corresponding arguments.  The original
 *  file streams are not preserved.  If you need to restore any of these
 *  streams to their original state, they must be saved (e.g. using dup(),
 *  dup2(), or ttyname()) prior to calling redirect().
 * 
 * Author: 
 *  Jason W. Bacon
 ****************************************************************************/
 
void    redirect(
    char    *infile,    /* If not NULL, stdin is redirected from this file */
    char    *outfile,   /* If not NULL, stdout is redirected to this file */
    char    *errfile    /* If not NULL, stderr is redirected to this file */
    )

{
    if (infile != NULL)
    {
	close(0);
	if ( open(infile, O_RDONLY) == -1 )
	    fprintf(stderr,"redirect(): Cannot open infile: %s.\n",infile);
    }
    if (outfile != NULL)
    {
	close(1);
	if ( open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0600) == -1 )
	    fprintf(stderr,"redirect(): Cannot open outfile: %s.\n",outfile);
    }
    if (errfile != NULL)
    {
	close(2);
	if ( strcmp(errfile,outfile) == 0 )
	{
	    if ( dup(1) == -1 )
		fprintf(stderr,"redirect(): Cannot open errfile: %s.\n",errfile);
	}
	else
	{
	    if ( open(errfile, O_WRONLY | O_CREAT | O_TRUNC, 0600) == -1 )
		fprintf(stderr,"redirect(): Cannot open errfile: %s.\n",errfile);
	}
    }
}

