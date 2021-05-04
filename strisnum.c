#include <stdlib.h>

/***************************************************************************
 *  Description:
 *      Determine whether a string is a valid number.
 *
 *  To-do:
 *      Support other bases and floating point.
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-24  Jason Bacon Begin
 ***************************************************************************/

int     strisnum(const char *string)

{
    char    *end;
    
    strtol(string, &end, 10);
    return *end == '\0';
}



