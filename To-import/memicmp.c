/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Return values:
 *      Like memcmp(), strcmp(), etc.
 *          str1 < str2, < 0
 *          str1 > str2, > 0
 *          str1 == str2, 0
 * Description:
 *      Fast case-insensitive fixed-length string comparison
 *      Works for ASCII or EBCDIC, so don't change the 'a' - 'A'
 *      construct
 *********************************************************************/

#include <ctype.h>
#include "xtend.h"

int     memicmp(str1, str2, len)
char   *str1, *str2;
int     len;

{
    /* Don't make static or register - compiler can register cache autos */
    int     c1, c2, diff = 'a' - 'A';

    do
    {
	/* Convert c1 and c2 to lower case before compare */
	if ( isupper(c1 = *str1++) )
	    c1 += diff;
	if ( isupper(c2 = *str2++) )
	    c2 += diff;
    } while ((c1 == c2) && (--len));    /* Go until diff or len */
    return (c1 - c2);   /* Return >0, 0, or <0 */
}

