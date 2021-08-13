#include <stdio.h>
#include <ctype.h>
#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      strblank() returns true if the null-terminated string contains only
 *      whitespace or nothing at all.  It is the null-terminated string
 *      equivalent of isblank(3), which tests a single character.
 *  
 *  Arguments:
 *      string: A null-terminated string
 *
 *  Returns:
 *      true is string contains only whitespace, or nothing
 *      false if any non-whitespace characters are present
 *
 *  See also:
 *      isblank(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     strblank(const char *string)

{
    while ( *string != '\0' )
    {
	if ( !isspace((size_t)(*string)) )   /* Not blank? */
	    return 0;
	++string;
    }
    return 1;
}
