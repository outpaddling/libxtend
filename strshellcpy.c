#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "string.h"
#include "file.h"
#include "ctype.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      strshellcpy() expands a string containing shell meta-characters,
 *      usually a shell command, as a Unix shell would do before execution.
 *      This is useful if you want to avoid spawning an unnecessary shell
 *      process, such as when using fork(2) and exec(3) directly instead
 *      of using system(3).
 *
 *      Currently supports:
 *          ~/: process owner's home directory
 *          $: environment variable
 *  
 *  Arguments:
 *      src:        String containing meta-characters
 *      dest:       Expanded string
 *      dest_len:   Size of destination array
 *
 *  Returns:
 *      0 on success, -1 if expansion did not fit in dest_len
 *
 *  See also:
 *      sh(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     strshellcpy(char *dest, const char *src, size_t dest_len)

{
    char    home[PATH_MAX + 1],*p,*val,var[PATH_MAX + 1];
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
		for (p=var, c=0; (c<PATH_MAX) && ISIDENT((size_t)(*src)); ++c)
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
    if ( (dest_len == 0) && (*src != '\0') )
	return -1;
    else
	return 0;
}
