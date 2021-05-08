/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Return values:   The number of decimal digits in val
 ****************************************************************************/

int     num_size(val)
long    val;

{
    int digits;
    
    for (digits=1; val != 0; ++digits)
	val /= 10;
    return digits;
}

