#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "proc.h"
#include "string.h" // Linux strlcpy()

/***************************************************************************
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      xt_get_user_name() determines the user name of the process owner.
 *      The information is retrieved using a call to
 *      getpwuid(3), and copied to the argument "dir".
 *   
 *      The name is stored in user_name up to maxlen characters.
 *      Note that up to maxlen characters are stored, not including the 
 *      null terminator, hence the buffer should be at least maxlen+1
 *      bytes long.
 *  
 *  Arguments:
 *      user_name:  Character buffer to receive home directory path
 *      maxlen:     Max characters to copy to dir, not including null byte
 *
 *  Returns:
 *      A pointer to user_name, or NULL upon failure.
 *
 *  See also:
 *      getuid(3), getpwuid(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-06-03  Jason Bacon Adapt from xt_xt_get_user_name()
 ***************************************************************************/

char   *xt_get_user_name(char *user_name, size_t maxlen)

{
    int     user;
    struct passwd *pwentry;

    /* Determine who the user is */
    user = getuid();

    /* Get password file entry */
    if ((pwentry = getpwuid(user)) == NULL)
	return (NULL);
 
    strlcpy(user_name, pwentry->pw_name, maxlen);
    return user_name;
}
