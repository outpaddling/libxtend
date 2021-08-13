#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "file.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      rmkdir() recursively creates a directory from within a compiled
 *      program in the same way as "mkdir -r" from shell.
 *  
 *  Arguments:
 *      path:   Absolute or relative pathname of the directory to create
 *      mode:   Permissions and other bits passed to mkdir(2)
 *
 *  Returns:
 *      0 on success, -1 on failure
 *
 *  See also:
 *      mkdir(1), mkdir(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-10  Jason Bacon Begin
 ***************************************************************************/

int     rmkdir(const char *path, mode_t mode)

{
    char    *parent_end;
    
    /* First try given path */
    if ( mkdir(path,mode) == 0 )
	return 0;
    else
    {
	/* Recursively attempt to make parent directories */
	parent_end = strrchr(path,'/');
	if ( parent_end == NULL )
	{
	    /* Ran out of ancestors - give it up */
	    return -1;
	}
	else
	{
	    /* Try to make parent with recursive call */
	    *parent_end = '\0';
	    if ( rmkdir(path,mode) == 0 )
	    {
		/* If parent successfully made, try again to make current */
		*parent_end = '/';
		return mkdir(path,mode);
	    }
	    else
	    {
		*parent_end = '/';
		return -1;
	    }
	}
    }
}
