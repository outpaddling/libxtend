#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "xtend.h"

/****************************************************************************
 Name:
    Return the name of the process owner's home directory.
 
 Description: 
    get_home_dir() determines the full pathname of the process owner's
    home directory.  The information is retrieved using a call to
    getpwuid(3), and copied to the argument "dir".
    
    The name is stored in dir up to maxlen characters.
    Note that up to maxlen characters are stored, not including the 
    null terminator, hence the buffer should be at least maxlen+1
    bytes long.
 
 Author: 
    Jason W. Bacon
 
 Returns: 
    A pointer to dir, or NULL upon failure.
 ****************************************************************************/

char   *get_home_dir(
	char    dir[],  /* buffer for directory name */
	int     maxlen  /* maximum name length */
	)

{
    int     user;
    struct passwd *pwentry;

    /* Determine who the user is */
    user = getuid();

    /* Get password file entry */
    if ((pwentry = getpwuid(user)) == NULL)
	return (NULL);
 
    strlcpy(dir, pwentry->pw_dir,maxlen);
    return (dir);
}

