#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      strlbasecpy() is a convenience for copying a string to a non-zero
 *      starting position in another string.  The caller provides the address
 *      of the destination to which string should be copied, the base address
 *      of the array containing the destination, and the TOTAL length of the
 *      destination array.  strlbasecpy() then computes the distance from
 *      the destination address to the end of the array and like strlcpy(),
 *      prevents overrun from occurring.
 *  
 *  Arguments:
 *      dest:       Address to which src is copied
 *      dest_base:  Base address of the array containing dest address
 *      src:        Address of null-terminated string to be copied
 *      dstsize:    Size of the dest array
 *
 *  Returns:
 *      The original value of dest
 *
 *  See also:
 *      strlcpy(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char   *strlbasecpy(char *dest, const char *dest_base, const char *src,
		    size_t dstsize)

{
    char        *save_dest;
    const char  *end;

    save_dest = dest;
    dstsize -= dest-dest_base;
    end = src + dstsize;
    while ((*src != '\0') && (src < end - 1))
	*dest++ = *src++;
    *dest = '\0';
    return (save_dest);
}
