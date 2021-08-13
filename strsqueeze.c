#include <string.h>
#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Copy string src to dest, reducing to a maximum length of dstsize if
 *      necessary by replacing the center portion of the string with "...".
 *  
 *  Arguments:
 *      dest:   Pointer to a character array of at least len dstsize, where
 *              the possibly modified string is stored.
 *      src:    Point to a character array containing the string to compact
 *      dstsize: Length of the dest array
 *
 *  Returns:
 *      The length of the original string (like strlcpy(3))
 *
 *  Examples:
 *      #define MAXLEN  127
 *      char    limited_str[MAXLEN + 1],
 *              original_str[SOME_OTHER_LEN + 1];
 *      
 *      strsqueeze(limited_str, original_str, MAXLEN + 1);
 *
 *  See also:
 *      strlcpy(3), strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-29  Jason Bacon Begin
 ***************************************************************************/

size_t  strsqueeze(char *dest, const char *src, size_t dstsize)

{
    size_t  len = strlen(src),
	    left_len,
	    right_len;
    
    if ( len <= dstsize )
	strlcpy(dest, src, dstsize);
    else
    {
	left_len = (dstsize - 3) / 2;
	right_len = dstsize - left_len - 3;
	memcpy(dest, src, left_len);
	strlcat(dest, "...", dstsize);
	strlcat(dest, src + len - right_len + 1, dstsize);
    }
    return len;
}



