#include <stdlib.h>
#include "mem.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/mem.h>
 *      -lxtend
 *
 *  Description:
 *      xt_malloc() is a simple wrapper around malloc(3) that requires two
 *      arguments representing the number of objects to allocate and the
 *      size of an element.  This prevents the very common mistake with
 *      malloc(3) of forgetting to multiply by the size of an element.
 *
 *      Specifying the size using sizeof(*variable) has the advantage of
 *      being type-independent.  I.e. if you change the type of the variable,
 *      this code need not be updated.  Simply add one * to whatever
 *      the return value is assigned to.
 *  
 *  Arguments:
 *      nelem:  Number of objects to allocate
 *      size:   Size of a single object
 *
 *  Examples:
 *      size_t      widget_list_size = 1024;
 *      widget_t    *widgets;
 *
 *      widgets = xt_malloc(widget_list_size, sizeof(*widgets));
 *
 *  Returns:
 *      Address of the newly allocated array, or NULL if allocation failed
 *
 *  See also:
 *      malloc(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

void    *xt_malloc(size_t nelem, size_t size)

{
    return  malloc(nelem * size);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/mem.h>
 *      -lxtend
 *
 *  Description:
 *      xt_realloc() is a simple wrapper around realloc(3) that requires three
 *      arguments representing the original array, the new number of objects
 *      to allocate and the size of an element.  This prevents the very
 *      common mistake with realloc(3) of forgetting to multiply by the size
 *      of an element.
 *
 *      Specifying the size using sizeof(*variable) has the advantage of
 *      being type-independent.  I.e. if you change the type of the variable,
 *      this code need not be updated.  Simply add one * to whatever
 *      the return value is assigned to.
 *  
 *  Arguments:
 *      array:  Address of the previously allocated array
 *      nelem:  Number of objects to allocate
 *      size:   Size of a single object
 *
 *  Examples:
 *      size_t      widget_list_size = 1024;
 *      widget_t    *widgets;
 *
 *      widgets = xt_malloc(widget_list_size, sizeof(*widgets));
 *      ...
 *      widget_list_size *= 2;
 *      widgets = xt_realloc(widgets, widget_list_size, sizeof(*widgets));
 *
 *  Returns:
 *      Address of the newly allocated array, or NULL if allocation failed
 *
 *  See also:
 *      realloc(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

void    *xt_realloc(void *array, size_t nelem, size_t size)

{
    return  realloc(array, nelem * size);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/mem.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_free_strings(3)
 *      frees all memory for an argv-style pointer array of strings,
 *      such as those allocated by xt_inhale_strings(3).  The pointer
 *      array itself and each string it points to must have been
 *      dynamically allocated with malloc(3), strdup(3), or similar.
 *  
 *  Arguments:
 *      list    A dynamically allocated char ** array
 *
 *  Examples:
 *      FILE    *instream;
 *      char    **strings;
 *      ssize_t string_count;
 *
 *      string_count = xt_inhale_strings(instream, &strings);
 *      ...
 *      xt_free_strings(strings);
 *
 *  See also:
 *      xt_inhale_strings(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-21  Jason Bacon Begin
 ***************************************************************************/

void    xt_free_strings(char **list)

{
    size_t  c;
    
    for (c = 0; list[c] != NULL; ++c)
	free(list[c]);
    free(list);
}
