#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "proc.h"
#include "string.h" // Linux strlcpy()


/***************************************************************************
 *  Name:
 *      xt_get_user_name() - Get username of process owner
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      xt_get_user_name() determines the user name of the process owner.
 *      The information is retrieved using a call to
 *      getpwuid(3), and copied to the argument "user_name".
 *   
 *      The name is stored in user_name up to buff_size characters.
 *      Note that up to buff_size characters are stored, including the 
 *      null terminator.
 *  
 *  Arguments:
 *      user_name:  Character buffer to receive home directory path
 *      buff_size:  Max characters to copy to user_name, including null byte
 *
 *  Returns:
 *      A pointer to user_name, or NULL upon failure.
 *
 *  See also:
 *      getuid(3), getpwuid(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-06-03  Jason Bacon Adapt from xt_get_user_name()
 ***************************************************************************/

char   *xt_get_user_name(char *user_name, size_t buff_size)

{
    uid_t           uid;
    struct passwd   *pwentry;

    /* Determine who the user is */
    uid = getuid();

    /* Get password file entry */
    if ((pwentry = getpwuid(uid)) == NULL)
        return (NULL);
 
    strlcpy(user_name, pwentry->pw_name, buff_size);
    return user_name;
}


/***************************************************************************
 *  Name:
 *      xt_get_primary_group_name() - Get primary group name of process owner
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      xt_get_primary_group_name() determines the primary group name of the process owner.
 *      The information is retrieved using a call to
 *      getpwuid(3), and copied to the argument "primary_group_name".
 *   
 *      The name is stored in primary_group_name up to buff_size characters.
 *      Note that up to buff_size characters are stored, including the 
 *      null terminator.
 *  
 *  Arguments:
 *      primary_group_name: Character buffer to receive home directory path
 *      buff_size:          Max characters to copy to primary_group_name, including null byte
 *
 *  Returns:
 *      A pointer to primary_group_name, or NULL upon failure.
 *
 *  See also:
 *      getuid(3), getpwuid(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-06-03  Jason Bacon Adapt from xt_get_primary_group_name()
 ***************************************************************************/

char   *xt_get_primary_group_name(char *primary_group_name, size_t buff_size)

{
    gid_t           gid;
    struct group    *grentry;

    /* Determine who the primary_group is */
    gid = getgid();

    /* Get password file entry */
    if ((grentry = getgrgid(gid)) == NULL)
        return (NULL);
 
    strlcpy(primary_group_name, grentry->gr_name, buff_size);
    return primary_group_name;
}
