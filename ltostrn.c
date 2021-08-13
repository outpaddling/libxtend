#include <stdio.h>
#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      ltostrn() is a small, fast integer to string converter that can
 *      convert using any base from 2 to 36.  It is the converse of strtol(3).
 *      The size of the char buffer passed should be 1 more than maxlen to
 *      allow for a null byte.
 *  
 *  Arguments:
 *      string: char array to receive ascii text
 *      val:    value to convert to ascii
 *      base:   number base for conversion, must be between 2 and 36
 *      maxlen: size of 'string' array - 1 (to account for null byte)
 *
 *  Returns:
 *      A pointer to the converted string, or NULL if the string buffer was
 *      not big enough for all the digits
 *
 *  See also:
 *      strtol(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char    *ltostrn(char string[], long val, unsigned base, size_t maxlen)

{
    char    temp[maxlen+1], *p, *s = string;
    int     digit;
    
    if ( base > 36 )
	return NULL;
    
    /* Tack on - sign if negative */
    if ( val < 0 )
    {
	*s++ = '-';
	val = -val;
    }
    
    /* Convert val to ascii digits (in reverse order) */
    for (p=temp; (val > 0) && (maxlen > 0); val /= base, --maxlen)
    {
	digit = val % base;
	if ( digit < 10 )
	    *p++ = digit+'0';
	else
	    *p++ = digit-10+'a';
    }
    
    /* Reverse digits */
    while ( p > temp )
	*s++ = *(--p);
    *s = '\0';
    if ( val > 0 )
	return NULL;
    else
	return string;
}
