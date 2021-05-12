#include <stdlib.h>

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      xt_malloc() is a simple wrapper around malloc(3) that requires two
 *      arguments representing the number of objects to allocate and the
 *      size of an element.  This prevents the very common mistake with
 *      malloc(3) of forgetting to multiply by the size of an element.
 *      Specifying the size using sizeof(*variable) has the advantage of
 *      being type-independent.  I.e. if you change the type of the variable,
 *      this code need not be updated.
 *  
 *  Arguments:
 *      nelem:  Number of objects to allocate
 *      size:   Size of a single object
 *
 *  Examples:
 *      #define     MAX_WIDGETS 1000
 *      widget_t    *widgets;
 *
 *      widgets = xt_malloc(MAX_WIDGETS, sizeof(*widgets));
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
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      xt_realloc() is a simple wrapper around realloc(3) that requires three
 *      arguments representing the original array, the new number of objects
 *      to allocate and the size of an element.  This prevents the very
 *      common mistake with realloc(3) of forgetting to multiply by the size
 *      of an element.
 *      Specifying the size using sizeof(*variable) has the advantage of
 *      being type-independent.  I.e. if you change the type of the variable,
 *      this code need not be updated.
 *  
 *  Arguments:
 *      array:  Address of the previously allocated array
 *      nelem:  Number of objects to allocate
 *      size:   Size of a single object
 *
 *  Examples:
 *      #define     MAX_WIDGETS 1000
 *      widget_t    *widgets;
 *
 *      widgets = xt_malloc(MAX_WIDGETS, sizeof(*widgets));
 *      ...
 *      widgets = xt_realloc(widgets, new_widget_count, sizeof(*widgets));
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
