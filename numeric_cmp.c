#include "math.h"

/***************************************************************************
 *  Name:
 *      double_cmp() - Compare two doubles for sort(3), bsearch(3), etc.
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      This is a function that compares two doubles as a service to
 *      polymorphic functions such as qsort(3), bsearch(3), etc.  The
 *      address of double_cmp() is passed as an argument to perform the
 *      data type specific comparison on behalf of the sort of search function.
 *  
 *  Arguments:
 *      n1, n2  Pointers to two double values
 *
 *  Returns:
 *      A value > 0 if *n1 is greater than *n2
 *      A value < 0 if *n1 is less than *n2
 *      0 if the values are equal
 *
 *  Examples:
 *      double  list[LIST_SIZE];
 *
 *      // sizeof(*list) will continue to work if we change the data type
 *      // We'll still need to change the cmp function, though
 *      qsort(list, LIST_SIZE, sizeof(*list),
 *            (int (*)(const void *, const void *))double_cmp);
 *      
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3), bsearch(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-10-07  Jason Bacon Begin
 ***************************************************************************/

int     double_cmp(const double *n1, const double *n2)

{
    /*
     *  Don't just return *n1 - *n2, since it will truncate to 0 in some
     *  cases where one is actually greater
     */
    
    if ( *n1 > *n2 )
	return 1;
    else if ( *n1 < *n2 )
	return -1;
    else
	return 0;
}


/***************************************************************************
 *  Name:
 *      float_cmp() - Compare two floats for sort(3), bsearch(3), etc.
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      This is a function that compares two floats as a service to
 *      polymorphic functions such as qsort(3), bsearch(3), etc.  The
 *      address of float_cmp() is passed as an argument to perform the
 *      data type specific comparison on behalf of the sort of search function.
 *  
 *  Arguments:
 *      n1, n2  Pointers to two float values
 *
 *  Returns:
 *      A value > 0 if *n1 is greater than *n2
 *      A value < 0 if *n1 is less than *n2
 *      0 if the values are equal
 *
 *  Examples:
 *      float  list[LIST_SIZE];
 *
 *      // sizeof(*list) will continue to work if we change the data type
 *      // We'll still need to change the cmp function, though
 *      qsort(list, LIST_SIZE, sizeof(*list),
 *            (int (*)(const void *, const void *))float_cmp);
 *      
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3), bsearch(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-10-07  Jason Bacon Begin
 ***************************************************************************/

int     float_cmp(const float *n1, const float *n2)

{
    /*
     *  Don't just return *n1 - *n2, since it will truncate to 0 in some
     *  cases where one is actually greater
     */
    
    if ( *n1 > *n2 )
	return 1;
    else if ( *n1 < *n2 )
	return -1;
    else
	return 0;
}


/***************************************************************************
 *  Name:
 *      long_long_cmp() - Compare two long longs for sort(3), bsearch(3), etc.
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      This is a function that compares two long longs as a service to
 *      polymorphic functions such as qsort(3), bsearch(3), etc.  The
 *      address of long_long_cmp() is passed as an argument to perform the
 *      data type specific comparison on behalf of the sort of search function.
 *  
 *  Arguments:
 *      n1, n2  Pointers to two long long values
 *
 *  Returns:
 *      A value > 0 if *n1 is greater than *n2
 *      A value < 0 if *n1 is less than *n2
 *      0 if the values are equal
 *
 *  Examples:
 *      long long  list[LIST_SIZE];
 *
 *      // sizeof(*list) will continue to work if we change the data type
 *      // We'll still need to change the cmp function, though
 *      qsort(list, LIST_SIZE, sizeof(*list),
 *            (int (*)(const void *, const void *))long_long_cmp);
 *      
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3), bsearch(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-10-07  Jason Bacon Begin
 ***************************************************************************/

int     long_long_cmp(const long long *n1, const long long *n2)

{
    /*
     *  Don't just return *n1 - *n2, since it might exceed the range of
     *  an int
     */
    
    if ( *n1 > *n2 )
	return 1;
    else if ( *n1 < *n2 )
	return -1;
    else
	return 0;
}


/***************************************************************************
 *  Name:
 *      long_cmp() - Compare two longs for sort(3), bsearch(3), etc.
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      This is a function that compares two longs as a service to
 *      polymorphic functions such as qsort(3), bsearch(3), etc.  The
 *      address of long_cmp() is passed as an argument to perform the
 *      data type specific comparison on behalf of the sort of search function.
 *  
 *  Arguments:
 *      n1, n2  Pointers to two long values
 *
 *  Returns:
 *      A value > 0 if *n1 is greater than *n2
 *      A value < 0 if *n1 is less than *n2
 *      0 if the values are equal
 *
 *  Examples:
 *      long  list[LIST_SIZE];
 *
 *      // sizeof(*list) will continue to work if we change the data type
 *      // We'll still need to change the cmp function, though
 *      qsort(list, LIST_SIZE, sizeof(*list),
 *            (int (*)(const void *, const void *))long_cmp);
 *      
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3), bsearch(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-10-07  Jason Bacon Begin
 ***************************************************************************/

int     long_cmp(const long *n1, const long *n2)

{
    /*
     *  Don't just return *n1 - *n2, since it might exceed the range of
     *  an int
     */
    
    if ( *n1 > *n2 )
	return 1;
    else if ( *n1 < *n2 )
	return -1;
    else
	return 0;
}


/***************************************************************************
 *  Name:
 *      int_cmp() - Compare two ints for sort(3), bsearch(3), etc.
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      This is a function that compares two ints as a service to
 *      polymorphic functions such as qsort(3), bsearch(3), etc.  The
 *      address of int_cmp() is passed as an argument to perform the
 *      data type specific comparison on behalf of the sort of search function.
 *  
 *  Arguments:
 *      n1, n2  Pointers to two int values
 *
 *  Returns:
 *      A value > 0 if *n1 is greater than *n2
 *      A value < 0 if *n1 is less than *n2
 *      0 if the values are equal
 *
 *  Examples:
 *      int  list[LIST_SIZE];
 *
 *      // sizeof(*list) will continue to work if we change the data type
 *      // We'll still need to change the cmp function, though
 *      qsort(list, LIST_SIZE, sizeof(*list),
 *            (int (*)(const void *, const void *))int_cmp);
 *      
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3), bsearch(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-10-07  Jason Bacon Begin
 ***************************************************************************/

int     int_cmp(const int *n1, const int *n2)

{
    return *n1 - *n2;
}


/***************************************************************************
 *  Name:
 *      short_cmp() - Compare two shorts for sort(3), bsearch(3), etc.
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      This is a function that compares two shorts as a service to
 *      polymorphic functions such as qsort(3), bsearch(3), etc.  The
 *      address of short_cmp() is passed as an argument to perform the
 *      data type specific comparison on behalf of the sort of search function.
 *  
 *  Arguments:
 *      n1, n2  Pointers to two short values
 *
 *  Returns:
 *      A value > 0 if *n1 is greater than *n2
 *      A value < 0 if *n1 is less than *n2
 *      0 if the values are equal
 *
 *  Examples:
 *      short  list[LIST_SIZE];
 *
 *      // sizeof(*list) will continue to work if we change the data type
 *      // We'll still need to change the cmp function, though
 *      qsort(list, LIST_SIZE, sizeof(*list),
 *            (int (*)(const void *, const void *))short_cmp);
 *      
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3), bsearch(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-10-07  Jason Bacon Begin
 ***************************************************************************/

int     short_cmp(const short *n1, const short *n2)

{
    return *n1 - *n2;
}
