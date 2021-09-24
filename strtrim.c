#include <string.h>
#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Trim unwanted characters off both ends of a string.  Typically
 *      this is whitespace added to a comma-separated file or similar.
 *
 *  Arguments:
 *      string  The string to be trimmed
 *      fat     A string containing a list of characters to be removed
 *
 *  See also:
 *      strsep(3)
 *
 *  Examples:
 *      char    string[] = "  Alfred E. Neumann."
 *
 *      strtrim(string, " .");
 *      puts(string);
 *
 *      Output is "Aldred E. Neumann"
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-09-24  Jason Bacon Begin
 ***************************************************************************/

void    strtrim(char *string, const char *fat)

{
    char    *start, *end;
    
    for (start = string; (*start != '\0') && strchr(fat, *start); ++start)
	;
    for (end = start; *end != '\0'; ++end)
	;
    while ( (end >= string) && strchr(fat, *end) )
	--end;
    end[1] = '\0';
    if ( (start > string) && (end > start) )
	memmove(string, start, end - start + 2);
}
