#include <stdio.h>
#include <ctype.h>
#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      strviscpy() copies a string from src to dest, converting invisible
 *      characters to a visible format much like the vis command or cat -v.
 *  
 *  Arguments:
 *      src:    Source string containing invisible characters
 *      dest:   Destination array to receive modified string
 *      maxlen: Maximum number of characters in dest, not including null byte
 *
 *  Returns:
 *      A pointer to dest
 *
 *  See also:
 *      vis(1), cat(1), strlcpy(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char    *strviscpy(unsigned char *dest, const unsigned char *src,
		size_t maxlen)

{
    char    *d = (char *)dest;

    if ( (src == NULL) || (dest == NULL) )
	return NULL;
    
    while ( (*src != '\0') && (maxlen > 0) )
    {
	if ( ((unsigned char)*src < 128) && isgraph(*src) )
	{
	    *d++ = *src++;
	    --maxlen;
	}
	else
	{
	    if ( maxlen > 4 )
	    {
		snprintf(d,maxlen,"\\%03o",(unsigned char)*src);
		++src;
		d+=4;
		maxlen-=4;
	    }
	}
    }
    *d = '\0';
    return (char *)dest;
}
