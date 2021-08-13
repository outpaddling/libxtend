#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "file.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      get_home_dir() determines the full pathname of the process owner's
 *      home directory.  The information is retrieved using a call to
 *      getpwuid(3), and copied to the argument "dir".
 *   
 *      The name is stored in dir up to maxlen characters.
 *      Note that up to maxlen characters are stored, not including the 
 *      null terminator, hence the buffer should be at least maxlen+1
 *      bytes long.
 *  
 *  Arguments:
 *      dir:    Character buffer to receive home directory path
 *      maxlen: Max characters to copy to dir, not including null byte
 *
 *  Returns:
 *      A pointer to dir, or NULL upon failure.
 *
 *  See also:
 *      getuid(3), getpwuid(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char   *get_home_dir(char *dir, size_t maxlen)

{
    int     user;
    struct passwd *pwentry;

    /* Determine who the user is */
    user = getuid();

    /* Get password file entry */
    if ((pwentry = getpwuid(user)) == NULL)
	return (NULL);
 
    strlcpy(dir, pwentry->pw_dir,maxlen);
    return dir;
}

