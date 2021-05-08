/*
    Copyright (c) 1994-2003, Jason W. Bacon, Acadix Software Systems
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer. Redistributions
    in binary form must reproduce the above copyright notice, this list of
    conditions and the following disclaimer in the documentation and/or
    other materials provided with the distribution. 

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "bacon.h"


/****************************************************************************
 * Name:
 *  Fork and exec a new process.
 *
 * Description: 
 *  This function creates a new process using fork(3) and execvp(3),
 *  optionally echoing the command to execvp(), and optionally waiting
 *  for the child process to complete.
 * 
 * Author: 
 *  Jason W. Bacon
 *
 * Returns: 
 *  The return status of the child process if the parent waits
 *  for it to complete, otherwise the PID of the child process.
 ****************************************************************************/

int     spawnvp(
    int     parent_action,  /* P_WAIT or P_NOWAIT */
    int     echo,           /* P_ECHO or P_NOECHO */
    char    *argv[],        /* Arguments to be passed to execvp() */
    char    *infile,        /* If not NULL, the child process's
				stdin is redirected from this file */
    char    *outfile,       /* If not NULL, the child process's
				stdout is redirected to this file */
    char    *errfile)       /* If not NULL, the child process's 
				stderr is redirected to this file */

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
	    /*
	    if ( infile != NULL )
		printf("\n[stdin = %s]",infile);
	    if ( outfile != NULL )
		printf("\n[stdout = %s]",outfile);
	    if ( errfile != NULL )
		printf("\n[stderr = %s]",errfile);
	    */
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

