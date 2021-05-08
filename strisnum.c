#include <stdlib.h>

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      Determine whether a string is a valid integer by attempting to
 *      convert it using strtoll().
 *
 *  Arguments:
 *      string: The string to be tested
 *      base:   The expected base of the integer (usually 8, 10, or 16)
 *
 *  Returns:
 *      Non-zero value if the string represents an integer, zero otherwise
 *
 *  See also:
 *      strtoll(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-24  Jason Bacon Begin
 ***************************************************************************/

int     strisint(const char *string, int base)

{
    char    *end;
    
    strtoll(string, &end, base);
    return *end == '\0';
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      Determine whether a string is a valid real number by attempting to
 *      convert it using strtod().
 *
 *  Arguments:
 *      string: The string to be tested
 *
 *  Returns:
 *      Non-zero value if the string represents a real number, zero otherwise
 *
 *  See also:
 *      strtod(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-24  Jason Bacon Begin
 ***************************************************************************/

int     strisreal(const char *string)

{
    char    *end;
    
    strtod(string, &end);
    return *end == '\0';
}
