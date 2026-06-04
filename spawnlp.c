#include <stdio.h>
#include <stdarg.h>
#include "proc.h"

/***************************************************************************
 *  Name:
 *      xt_spawnlp() - Fork and exec a process from a variable argument list
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_spawnlp()
 *      is a wrapper around xt_spawnvp(3) which
 *      makes it easy to run a child process without an intermediate
 *      shell process as is used by system(3).  The xt_spawnlp() function
 *      spawns a child process using a variable argument list.  The 6th
 *      argument is passed to argv[0] of the child, the 7th to argv[1], etc.
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
 *      arg0:           The name of the program to run
 *      arg1, ...       Command-line arguments
 *
 *      IMPORTANT:      The last argument must be NULL
 *
 *  Returns:
 *      The exit status of the child process if P_WAIT is passed
 *      The PID of the child process if P_NOWAIT is passed
 *
 *  See also:
 *      xt_redirect(3), xt_spawnvp(3),
 *      xt_spawnlp10(3), xt_spawnvp10(3), xt_redirect7(3),
 *      fork(2), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     xt_spawnlp(int parent_action, int echo,
                   const char *infile, const char *outfile, const char *errfile,
                   const char *arg0, ...)

{
    va_list list;
    const char *argv[100];
    int     c;
    
    va_start(list, arg0);
    argv[0] = arg0;
    for (c=1; (argv[c] = (char *)va_arg(list,char *)) != NULL; ++c)
        ;
    return(xt_spawnvp(parent_action,echo,argv,infile,outfile,errfile));
}


/***************************************************************************
 *  Name:
 *      xt_spawnlp10() - Fork and exec a process from a variable argument list
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_spawnlp10()
 *      is a wrapper around xt_spawnvp10(3) which
 *      makes it easy to run a child process without an intermediate
 *      shell process as is used by system(3).  The xt_spawnlp10() function
 *      spawns a child process using a variable argument list.  The 10th
 *      argument is passed to argv[0] of the child, the 11th to argv[1], etc.
 *
 *      The calling process waits for the child to complete if P_WAIT is
 *      passed to parent_action, or continues immediately if P_NOWAIT
 *      is passed.  If P_ECHO is passed as the echo argument, the command
 *      is echoed, the command is echoed to the parent's stdout.
 *
 *      If infile, outfile, or errfile are not NULL, then the corresponding
 *      file streams stdin, stdout, or stderr are redirected to the filename
 *      provided, opened using infile_flags, outfile_flags, errfile_flags,
 *      and/or mode as appropriate.
 *  
 *  Arguments:
 *      parent_action:  P_WAIT or P_NOWAIT
 *      echo:           P_ECHO or P_NOECHO
 *      infile:         File to which stdin of child is redirected or NULL
 *      outfile:        File to which stdout of child is redirected or NULL
 *      errfile:        File to which stderr of child is redirected or NULL
 *      infile_flags    Open mode flags for infile
 *      outfile_flags   Open mode flags for outfile
 *      errfile_flags   Open mode flags for errfile
 *      mode            Permissions before applying umask(2) when creating outfile/errfile

 *      arg0:           The name of the program to run
 *      arg1, ...       Command-line arguments
 *
 *      IMPORTANT:      The last argument must be NULL
 *
 *  Returns:
 *      The exit status of the child process if P_WAIT is passed
 *      The PID of the child process if P_NOWAIT is passed
 *
 *  See also:
 *      xt_spawnvp10(3), xt_redirect7(3),
 *      xt_spawnlp(3), xt_spawnvp(3), xt_redirect(3),
 *      fork(2), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2026-06-04  Jason Bacon Begin
 ***************************************************************************/

int     xt_spawnlp10(int parent_action, int echo,
                     const char *infile, const char *outfile, const char *errfile,
                     int infile_flags, int outfile_flags, int errfile_flags,
                     int mode, const char *arg0, ...)

{
    va_list list;
    const char *argv[100];
    int     c;
    
    va_start(list, arg0);
    argv[0] = arg0;
    for (c=1; (argv[c] = (char *)va_arg(list,char *)) != NULL; ++c)
        ;
    return xt_spawnvp10(parent_action,echo,argv,infile,outfile,errfile,
                        infile_flags, outfile_flags, errfile_flags, mode);
}
