/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      Compute the binomial coefficient N choose K = N! / (K! * (N-K)!).
 *      This represents the number of ways to choose K items out of a
 *      pool of N, such that we don't care about order.  E.g., if
 *      choosing 2 letters from the set [A B C D E], [C D] is considered
 *      the same [D C].
 *
 *      This implementation avoids overflow by alternating multiply and
 *      divide operations (rather than try to compute factorials first,
 *      which will fail for relatively small values of N or K).
 *  
 *  Arguments:
 *      n   Number of items to choose from
 *      k   Number of items chosen
 *
 *  Returns:
 *      The number of ways to choose K items from N objects.
 *
 *  Examples:
 *      unsigned long   n = 5, k = 2;
 *
 *      printf("Ways to choose %lu items from %lu = %lu\n",
 *              k, n, xt_binomial(n, k));
 *
 *  See also:
 *      lgamma(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-12-09  Jason Bacon Begin
 ***************************************************************************/

#include "math.h"

unsigned long   xt_binomial(unsigned long n, unsigned long k)

{
    unsigned long   b, c;
    
    if ( k < 0 || k > n )
	return 0UL;
    if ( k == 0 || k == n )
	return 1UL;
    k = XT_MIN(k, n - k);
    for (b = 1, c = 0; c < k; ++c)
	b = b * (n - c) / (c + 1);
    return b;
}
