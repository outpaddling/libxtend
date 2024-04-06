#include "string.h"


/***************************************************************************
 *  Name:
 *      xt_strcat() - Concatenate strings without risk of buffer overflow
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Concatenate string src to dest, truncating if necessary to avoid
 *      overflowing the destination array.
 *  
 *  Arguments:
 *      dest:   Pointer to a character array of at least len dstsize, where
 *              the possibly modified string is stored.
 *      src:    Point to a character array containing the string to compact
 *      dstsize: Length of the dest array
 *
 *  Returns:
 *      The combined lengths of the two strings.  If the return value is
 *      larger than the dstsize, then truncation has occurred.
 *
 *  Examples:
 *      #define MAXLEN  127
 *      char    limited_str[MAXLEN + 1],
 *              original_str[SOME_OTHER_LEN + 1];
 *      
 *      xt_strlcat(limited_str, original_str, MAXLEN + 1);
 *
 *  See also:
 *      xt_strlcpy(3), xt_strlsqueeze(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strlcat(char *dest, const char *src, size_t dstsize)

{
    char        *dp;
    const char  *sp;
    
    /* Find end of first string */
    for (dp=dest; (*dp != '\0') && --dstsize; ++dp)
	;
    
    /* Concetanate second string */
    for (sp=src; (*sp != '\0') && --dstsize; )
	*dp++ = *sp++;
    
    /* Null terminate */
    *dp = '\0';
    
    // Return length of string we tried to create
    while ( *sp != '\0' )
	++sp;
    return (dp - dest) + (sp - src);
}
