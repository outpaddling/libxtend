#include <string.h>

/***************************************************************************
 *  Library:
 *      #include <xtendc.h>
 *      -lxtendc
 *
 *  Description:
 *      Compare two strings via indirect pointers.  This can be used by
 *      qsort(), heapsort(), etc. to sort an argv-style pointer array,
 *      swapping only the pointers rather than the string contents.
 *
 *  Arguments:
 *      p1, p2: Pointers to pointers to the strings to compare
 *
 *  Returns:
 *      0 if the strings are the same, a value < 0 if the string at p1
 *      is lexically < that at p2, a value > 0 otherwise.
 *
 *  See also:
 *      strcmp(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-04  Jason Bacon Begin
 ***************************************************************************/

int     strptrcmp(const char **p1, const char **p2)

{
    return strcmp(*p1, *p2);
}
