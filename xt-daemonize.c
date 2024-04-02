#include <stdio.h>
#include <sysexits.h>   // EX_OK
#include <unistd.h>     // fork(), setsid()
#include <errno.h>
#include <string.h>     // strerror()
#include <stdlib.h>     // exit()
#include <fcntl.h>      // open()

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_daemonize() - Detach process from terminal
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      Daemonize a process, using the double-fork() method to ensure
 *      that it cannot attach to a controlling tty (terminal).  The
 *      interface is identical to the BSD daemon(3) function, but
 *      daemon(3) only performs a single fork, so there is a risk that
 *      the resulting process could attach to a termimal.
 *
 *      The double-fork() entails additional overhead compared to daemon(3),
 *      but ensures that the process cannot aquire a controlling terminal
 *      and be affected by signals from the keyboard.
 *
 *      daemon(3) is deprecated on macOS as of this writing.
 *  
 *  Arguments:
 *      nochdir:    If true (non-zero), do not chdir("/")
 *      noclose:    If true, do not redirect standard descriptors to /dev/null
 *
 *  Returns:
 *      0 on success, -1 on failure
 *
 *  Examples:
 *      xt_daemonize(0, 0);
 *
 *  See also:
 *      daemon(3), fork(2), setsid(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-25  Jason Bacon Begin
 ***************************************************************************/

int     xt_daemonize(int nochdir, int noclose)

{
    int     pid;
    
    #ifdef __TEST__
    fprintf(stderr, "Calling process:   PID = %d  PGID = %d  SID = %d\n",
	    getpid(), getpgrp(), getsid(getpid()));
    #endif
    
    /*
     *  Fork and terminate parent so process becomes a child of init
     */
    
    if ((pid = fork()) < 0)
    {
	fprintf(stderr, "xt_daemonize(): fork() failed: %s.\n", strerror(errno));
	return -1;  // Consistent with daemon(3)
    }
    
    if (pid != 0)
	exit(EX_OK);

    #ifdef __TEST__
    fprintf(stderr, "First child:       PID = %d  PGID = %d  SID = %d\n",
	    getpid(), getpgrp(), getsid(getpid()));
    #endif
    
    /*
     *  Create a new session, dissociating from the controlling terminal.
     *  This process is the session leader and process group leader,
     *  and the only process in the session and group at this point.
     */
    
    setsid();

    #ifdef __TEST__
    fprintf(stderr, "New session:       PID = %d  PGID = %d  SID = %d\n",
	    getpid(), getpgrp(), getsid(getpid()));
    #endif
    
    /*
     *  Fork and terminate parent again, so that remaining process is
     *  not the session leader.  This prevents it from aquiring a
     *  controlling terminal under SYSV rules.
     */
    
    if ((pid = fork()) < 0)
    {
	fprintf(stderr, "xt_daemonize(): fork() failed: %s.\n", strerror(errno));
	return -1;  // Consistent with daemon(3)
    }
    
    if (pid != 0)
	exit(EX_OK);

    #ifdef __TEST__
    fputs("PID should differ from SID below.\n", stderr);
    fprintf(stderr, "Second child:      PID = %d  PGID = %d  SID = %d\n",
	    getpid(), getpgrp(), getsid(getpid()));
    #endif

    /*
     *  Set CWD to / unless told not to
     *  This should never fail, but modern GCC warns about ignoring RV
     */
    
    if ( ! nochdir )
	if ( chdir("/") != 0 )
	    return -1;
    
    /*
     *  Redirect standard streams to /dev/null unless told not to
     */
    
    if ( ! noclose )
    {
	close(0);
	close(1);
	close(2);
	open("/dev/null", O_RDONLY);
	// O_NONBLOCK should eliminate delays?
	open("/dev/null", O_WRONLY|O_APPEND|O_NONBLOCK);
	open("/dev/null", O_WRONLY|O_APPEND|O_NONBLOCK);
    }
    
    return 0;   // Consistent with daemon(2)
}


#ifdef __TEST__

#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>

int     main(int argc,char *argv[])

{
    xt_daemonize(0, 0);
    
    return EX_OK;
}
#endif
