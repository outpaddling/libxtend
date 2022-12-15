#include <string.h>
#include <stdlib.h>

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/stdlib.h>
 *      -lxtend
 *
 *  Description:
 *      Shuffle an array of objects using the Fisher-Yates method, which
 *      ensures equal probability of all arrangements.
 *  
 *  Arguments:
 *      base    Base address of the array (address of the first element)
 *      nelem   Number of elements in the array
 *      size    Size of one element
 *
 *  Examples:
 *      type_t  *list;
 *      size_t  list_size = 100;
 *
 *      if ( (list = xt_malloc(list_size, sizeof(*list))) == NULL)
 *      {
 *          fprintf(stderr, "xt_malloc() failed.\n");
 *          exit(EX_UNAVAILABLE);
 *      }
 *      ...
 *      xt_shuffle(list, list_size, sizeof(*list));
 *
 *  See also:
 *      qsort(3), heapsort(3), mergesort(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-10-23  Jason Bacon Begin
 ***************************************************************************/

void    xt_shuffle(void *base, size_t nelem, size_t size)

{
    size_t  c, c1;
    char    temp[size];
    
    // Fisher-Yates shuffle
    for (c = 0; c < nelem - 1; ++c)
    {
	// c <= c1 < pair_nelem
	// Yes, we want the possibility of swapping an element with itself
	// Leaving it in place should have the same probability as
	// every other possibility
	c1 = c + random() % (nelem - c);
	memcpy((void *)temp, base + c * size, size);
	memcpy(base + c * size, base + c1 * size, size);
	memcpy(base+ c1 * size, (void *)temp, size);
    }
}
