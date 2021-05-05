#include <string.h>

/***************************************************************************
 *  Description:
 *      Compare two strings via indirect pointers.  This can be used by
 *      qsort(), heapsort(), etc. to sort an argv-style pointer array.
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-04  Jason Bacon Begin
 ***************************************************************************/

int     strptrcmp(const char **p1, const char **p2)

{
    return strcmp(*p1, *p2);
}
