#include <string.h>
#include <unistd.h>
#include <stdlib.h>     // free()
#include <sys/stat.h>
#include <sys/types.h>
#include "file.h"

/***************************************************************************
 *  Name:
 *      xt_rmkdir() - Recursively create directories
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      xt_rmkdir() recursively creates a directory from within a compiled
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

int     xt_rmkdir(const char *path, mode_t mode)

{
    char    *parent,
	    *parent_end;
    struct stat st;
    
    if ( stat(path, &st) == 0 )
	return 0;
    
    /* First try given path */
    if ( mkdir(path, mode) == 0 )
	return 0;
    else
    {
	/* Recursively attempt to make parent directories */
	parent = strdup(path);            // path could be const in the caller
	parent_end = strrchr(parent, '/');
	if ( parent_end == NULL )
	{
	    /* Ran out of ancestors - give it up */
	    free(parent);
	    return -1;
	}
	else
	{
	    /* Try to make parent with recursive call */
	    *parent_end = '\0';
	    
	    if ( xt_rmkdir(parent, mode) == 0 )
	    {
		/* If parent successfully made, try again to make current */
		free(parent);
		return mkdir(path, mode);
	    }
	    else
	    {
		free(parent);
		return -1;
	    }
	}
    }
}
