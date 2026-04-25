#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "file.h"

/***************************************************************************
 *  Name:
 *      xt_touch() - Create or update timestamp on a file
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_touch()
 *      creates or alters the access and/or modification time of a file.
 *      If options is non-zero, each bit controls behavior as follows:
 *
 *      XT_TOUCH_UPDATE_MOD_TIME - Set modification time of an existing
 *      file to the current time.
 *
 *      XT_TOUCH_UPDATE_ACCESS_TIME - Set access time of an existing
 *      file to the current time.
 *
 *      XT_TOUCH_NO_CREATE - Do not create the file if it does not exist.
 *
 *      The utimensat_flags argument is passed to utimensat(2) in order
 *      to control handling of the path argument, symbolic links, etc.
 *      See utimensat(2) for more information.
 *  
 *  Arguments:
 *      path            Absolute or relative pathname
 *      options         Bitwise flags for controlling behavior
 *      utimensat_flags Bitwise flags to pass to utimensat(2)
 *
 *  Returns:
 *      0 on success, non-zero error codes otherwise
 *
 *  Examples:
 *      xt_touch("lockfile", 0, 0640);
 *
 *  See also:
 *      touch(1), utimensat(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-10-05  Jason Bacon Begin
 ***************************************************************************/

int     xt_touch(const char *path, unsigned int options, int utimensat_flags)

{
    int             fd, open_flags;
    struct timespec times[2];
    struct stat     st;
    
    if ( stat(path, &st) == 0 )
    {
        // tv_sec values are ignored, no need to set them
        times[0].tv_nsec = times[1].tv_nsec = UTIME_OMIT;
        if ( options & XT_TOUCH_UPDATE_ACCESS_TIME )
            times[0].tv_nsec = UTIME_NOW;
        if ( options & XT_TOUCH_UPDATE_MOD_TIME )
            times[1].tv_nsec = UTIME_NOW;
        if ( utimensat(AT_FDCWD, path, times, 0) == 0 )
            return XT_OK;
        else
            return XT_FAIL;
    }
    else
    {
        open_flags = O_WRONLY|O_CREAT|O_SYNC;
        if ( ! (options & XT_TOUCH_NO_CREATE) )
            open_flags |= O_CREAT;
        if ( (fd = open(path, open_flags, 0777)) == 0 )
        {
            close(fd);
            return XT_OK;
        }
        else
            return XT_FAIL;
    }
}
