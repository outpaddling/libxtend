#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "xtend.h"

/**********************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 **********************************************************************/

int     rmkdir(char *path,mode_t mode)

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

