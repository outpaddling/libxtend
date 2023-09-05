/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_n_choose_k() - Compute binomial coefficient N choose K
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
 *      #include <xtend/math.h>
 *
 *      unsigned long   n = 5, k = 2;
 *
 *      printf("Ways to choose %lu items from %lu = %lu\n",
 *              k, n, xt_n_choose_k(n, k));
 *
 *  See also:
 *      lgamma(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-12-09  Jason Bacon Begin
 ***************************************************************************/

#include <stdint.h>
#include "math.h"

unsigned long   xt_n_choose_k(unsigned long n, unsigned long k)

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


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_factorial() - Fast factorial function
 *
 *  Library:
 *      #include <inttypes.h>
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      Instantaneous factorial for n in [0,20] using a lookup table.
 *
 *      Note that 21! is beyond the range of uint64_t, so programs that
 *      need it should either use a multiple precision library or rearrange
 *      the computations to avoid repeated multiplication leading to overflow.
 *      xt_n_choose_k(3) uses the latter approach to avoid computing whole
 *      factorials before finally dividing.
 *  
 *  Arguments:
 *      n   Integer in the range [0,20] (inclusive) for which n! is returned.
 *
 *  Returns:
 *      n! if n is an element of [0,20], 0 otherwise
 *
 *  Examples:
 *      #include <inttypes.h>
 *      #include <xtend/math.h>
 *
 *      printf("20! = %" PRIu64 "\n", factorial(20));
 *
 *  Files:
 *
 *  Environment
 *
 *  See also:
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-12-11  Jason Bacon Begin
 ***************************************************************************/

uint64_t    xt_factorial(unsigned n)

{
    static uint64_t f[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320,
			    362880, 3628800, 39916800, 479001600,
			    6227020800, 87178291200, 1307674368000,
			    20922789888000, 355687428096000, 6402373705728000,
			    121645100408832000, 2432902008176640000 };
    
    return n <= 20 ? f[n] : 0;
}
