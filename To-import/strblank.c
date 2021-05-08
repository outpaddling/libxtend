#include <stdio.h>
#include <ctype.h>

int     strblank(str)
char    *str;

{
    while ( *str != '\0' )
    {
	if ( !isspace((size_t)(*str)) )   /* Not blank? */
	    return 0;
	++str;
    }
    return 1;
}
