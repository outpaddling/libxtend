/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      mv() - Library function equivalent of mv(1)
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      Move file from pathname src to pathname dest. First attempt to
 *      rename using rename(3).  This will fail if src and dest are
 *      in different filesystems.  Then attempt to copy the file using
 *      fast_cp(3), an optimized cross-filesystem file copy routine.
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
 *      if ( mv(old_name, new_name) != 0 )
 *      {
 *          fprintf(stderr, "Failed to move %s to %s.\n", old_name, new_name);
 *          ...
 *      }
 *
 *  See also:
 *      fast_cp(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-01-10  Jason Bacon Begin
 ***************************************************************************/

#include <unistd.h>
#include "file.h"

int     mv(const char *src, const char *dest)

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
