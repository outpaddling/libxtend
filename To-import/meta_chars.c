#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "xtend.h"

#define NAME_LEN    128

/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Arguments:   src: String containing meta-characters
 *              dest: expanded string
 *              dest_len: size of destination array
 * Return values: 0 for success
 * Description:
 *      Expand a string containing shell meta-characters, usually a
 *      shell command using C-shell syntax.
 *      Currently supports:
 *          ~/: process owner's home directory
 *          $: environment variable
 ****************************************************************************/

int     meta_chars(dest,src,dest_len)
char    *dest,*src;
size_t  dest_len;

{
    char    home[PATH_MAX+1],*p,*val,var[NAME_LEN+1];
    int     c;
    
    while ( dest_len && (*src != '\0') )
    {
	switch(*src)
	{
	    case    '~':
		++src;
		if ( *src == '/' )  /* Process owner's home dir */
		{
		    get_home_dir(home,PATH_MAX);
		    for (p=home; dest_len-- && (*p != '\0'); )
			*dest++ = *p++;
		}
		else
		{
		    /* Get somebody else's home dir */
		}
		break;
	    case    '$':
		++src;
		/* Get ENV variable name */
		for (p=var, c=0; (c<NAME_LEN) && ISIDENT((size_t)(*src)); ++c)
		    *p++ = *src++;
		*p = '\0';
		
		/* Get value and copy to dest command */
		if ( (val = getenv(var)) != NULL )
		    while ( dest_len-- && (*val != '\0') )
			*dest++ = *val++;
		break;
	    default:
		*dest++ = *src++;
		--dest_len;
	}
    }
    *dest = '\0';
    return 0;
}

