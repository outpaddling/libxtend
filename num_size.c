/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      num_size() computes the number of digits in val, assuming the
 *      given base.
 *  
 *  Arguments:
 *      val:    The number for which digits are to be counted
 *      base:   The number base, between 2 and 36
 *
 *  Returns:
 *      The number of base "base" digits in val, or -1 if base is invalid
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     num_size(long val, unsigned base)

{
    int     digits;
    
    if ( (base < 2) || (base > 36) )
	return -1;
    
    for (digits=1; val != 0; ++digits)
	val /= base;
    return digits;
}
