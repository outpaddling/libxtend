#include "math.h"

/***************************************************************************
 *  Name:
 *      xt_digits() - Compute the number of xt_digits in an integer in any base
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      xt_digits() computes the number of xt_digits in val, assuming the
 *      given base.
 *  
 *  Arguments:
 *      val:    The number for which xt_digits are to be counted
 *      base:   The number base, between 2 and 36
 *
 *  Returns:
 *      The number of base "base" xt_digits in val, or -1 if base is invalid
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     xt_digits(long val, unsigned base)

{
    int     d;
    
    if ( (base < 2) || (base > 36) )
	return -1;
    
    for (d=1; val != 0; ++d)
	val /= base;
    return d;
}
