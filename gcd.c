#include "math.h"

/***************************************************************************
 *  Name:
 *      gcd() - Greatest common divisor
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      Computes the greatest common divisor of two natural
 *      numbers a and b.
 *  
 *  Arguments:
 *      a, b: Numbers for which to find GCD
 *
 *  Returns:
 *      The greatest common divisor of a and b.
 *
 *  See also:
 *      lcm(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

unsigned long   gcd(unsigned long a, unsigned long b)

{
    if ( a == 0 ) return b;
    if ( b == 0 ) return a;
    if ( a < b )
	return gcd(b,a);
    else
	return gcd(b, a % b);
}


/***************************************************************************
 *  Name:
 *      lcm() - Least common multiple
 *
 *  Library:
 *      #include <xtend/math.h>
 *      -lxtend
 *
 *  Description:
 *      Computes the least common multiple of two natural
 *      numbers a and b.  Note that this function may fail for relatively
 *      small values, as their LCM may be beyond the range of a 32-bit
 *      integer.
 *  
 *  Arguments:
 *      a, b: Numbers for which to find LCM
 *
 *  Returns:
 *      The least common multiple of a and b.
 *
 *  See also:
 *      gcd(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

unsigned long   lcm(unsigned long a,unsigned long b)

{
    return a * b / gcd(a,b);
}
