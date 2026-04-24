#include <fcntl.h>


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
 *      The mode argument represents permissions and other mode bits
 *      as described by chmod(1) and chmod(2);
 *  
 *  Arguments:
 *      path    Absolute or relative pathname
 *      options Bitwise flags for controlling behavior
 *      mode    Permissions for the file
 *
 *  Returns:
 *      0 on success, non-zero error codes otherwise
 *
 *  Examples:
 *      xt_touch("lockfile", 0, 0640);
 *
 *  See also:
 *      touch(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-10-05  Jason Bacon Begin
 ***************************************************************************/

int     xt_touch(const char *path, unsigned int options, unsigned int mode)

{
    int     fd, open_flags;
    
    open_flags = O_WRONLY|O_CREAT|O_SYNC;
    if ( ! (options & XT_TOUCH_NO_CREATE) )
        open_flags |= O_CREAT;
    
    if ( (fd = open(path, open_flags, mode)) == 0 )
    {
        close(fd);
        return EX_OK;
    }
    else
        return EX_CANTCREAT;
}
