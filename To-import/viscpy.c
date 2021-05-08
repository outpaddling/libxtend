#include <stdio.h>
#include <ctype.h>
#include "xtend.h"

/*
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Copy a string, making non-graphic characters visible as octal
 */

char    *viscpy(dest,src,maxlen)
unsigned char    dest[],src[];
size_t  maxlen;

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


