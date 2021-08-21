#include <string.h>
#include "string.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Translate characters in a string similar to tr(1), where each
 *      occurrence of from[i] is replaced with to[i] in string.
 *
 *      Currently only replacement is supported and flags is ignored.
 *      In the future, additional features such as deletion and
 *      compaction may be supported.
 *  
 *  Arguments:
 *      string  The string to be transformed
 *      from    Characters to be replaced with those in to
 *      to      Characters to replace those in from
 *      flags   Bit mask to enable optional features simlar to tr(1)
 *
 *  Examples:
 *      char    string[] = "Hello";
 *
 *      // Convert string to "HELLO"
 *      strtr(string, "elo", "ELO", 0);
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-08-10  Jason Bacon Begin
 ***************************************************************************/

void    strtr(char *string, const char *from, const char *to, int flags)

{
    char    *p,
	    *i;
    
    for (p = string; *p != '\0'; ++p)
    {
	i = strchr(from, *p);
	if ( i != NULL )
	{
	    //fprintf(stderr, "Replacing %c with %c\n", *p, to[i - from]);
	    //fflush(stderr);
	    *p = to[i - from];
	}
    }
}
