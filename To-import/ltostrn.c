#include <stdio.h>

/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Arguments:
 *      string: char array to receive ascii text
 *      val:    value to convert to ascii
 *      base:   number base for conversion, must be between 2 and 36
 *      maxlen: size of 'string' array
 * Return values:   Pointer to string
 * Description:
 *      This is a small, fast integer to string converter meant as
 *      an alternative to snprintf(), which is big and slow
 ****************************************************************************/
 

char    *ltostrn(string,val,base,maxlen)
char    string[];
long    val;
unsigned    base,maxlen;

{
    char    temp[33], *p, *s = string;
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
    return string;
}

