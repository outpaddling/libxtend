/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_mv() - Library function equivalent of xt_mv(1)
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      Move file from pathname src to pathname dest. First attempt to
 *      rename using rename(3).  This will fail if src and dest are
 *      in different filesystems.  Then attempt to copy the file using
 *      xt_fast_cp(3), an optimized cross-filesystem file copy routine.
 *  
 *  Arguments:
 *      src     Original filename
 *      dest    New filename
 *
 *  Returns:
 *      0 on success, otherwise error code from fastcp(3)
 *
 *  Examples:
 *      char    *old_name, char *new_name;
 *
 *      if ( xt_mv(old_name, new_name) != 0 )
 *      {
 *          fprintf(stderr, "Failed to move %s to %s.\n", old_name, new_name);
 *          ...
 *      }
 *
 *  See also:
 *      xt_fast_cp(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-01-10  Jason Bacon Begin
 ***************************************************************************/

#include <unistd.h>
#include "file.h"

int     xt_mv(const char *src, const char *dest)

{
    int     status = 0;
    
    if ( rename(src,dest) != 0 )
    {
	if ( (status = xt_fast_cp(src,dest)) == 0 )
	    unlink(src);
	else
	    unlink(dest);
    }
    return status;
}
