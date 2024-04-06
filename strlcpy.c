#include "string.h"


/***************************************************************************
 *  Name:
 *      xt_strcpy() - Copy a string without risk of buffer overflow
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Copy string src to dest, truncating to a maximum length of dstsize if
 *      necessary.
 *  
 *  Arguments:
 *      dest:   Pointer to a character array of at least len dstsize, where
 *              the possibly modified string is stored.
 *      src:    Point to a character array containing the string to compact
 *      dstsize: Length of the dest array
 *
 *  Returns:
 *      The length of the source string.  If the return value is
 *      larger than the dstsize, then truncation has occurred.
 *
 *  Examples:
 *      #define MAXLEN  127
 *      char    limited_str[MAXLEN + 1],
 *              original_str[SOME_OTHER_LEN + 1];
 *      
 *      xt_strcpy(limited_str, original_str, MAXLEN + 1);
 *
 *  See also:
 *      xt_strlsqueeze(3), xt_strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strlcpy(char * restrict dest, const char * restrict src,
		   size_t dstsize)

{
    const char  *save_src;
    char        *end;

    save_src = src;
    end = (char *)src + dstsize;
    while ((*src != '\0') && (src < end))
	*dest++ = *src++;
    *dest = '\0';

    // Return length of string we tried to create
    while ( *src != '\0' )
	++src;
    return src - save_src;
}
