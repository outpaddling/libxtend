#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include <ctype.h>


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/stdlib.h>
 *      -lxtend
 *
 *  Description:
 *      The 
 *      .B romantoi() function converts a string containing a valid
 *      Roman numeral to an integer, much like strtol().  It rejects
 *      non-normalized values, such as IIIII, XXXXX, or CCCCC, which
 *      should be written as V, L, and D, respectively.  IIII, XXXX, and
 *      CCCC are accepted in place of IV, XL, and CD.  Any number of
 *      consecutive Ms (1000s) are accepted, since there is no larger digit.
 *      Like strtol(), it returns the
 *      address of the first character not converted as part of the
 *      number.  This can be used to verify that the number ended as
 *      it should have, perhaps with a '\0' byte.
 *  
 *  Arguments:
 *      nptr:   Pointer to the first character of the Roman numeral
 *      endptr: Address of a pointer variable to receive the end of the string
 *
 *  Returns:
 *      The integer value of the Roman numeral if converted, or 0 if
 *      an invalid numeral is detected.
 *
 *  Examples:
 *      char    string[] = "XIV", *end;
 *      int     n;
 *
 *      n = romantoi(string, &end);
 *      if ( *end == '\0' )
 *          printf("%d\n", n);
 *      else
 *          fprintf(stderr, "Error converting %s.\n", string);
 *
 *  See also:
 *      strtol(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-12-14  Jason Bacon Begin
 ***************************************************************************/

int     romantoi(const char *nptr, char **endptr)

{
    int     digit, next_digit, previous_digit, val, consecutive;
    const char    *p;
    
    // Array of values using subscripts from 'C' to 'X'
    const static int  digits[] = 
    {
	// I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000
	100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0,
	0, 0, 0, 5, 0, 10
    };

    // FIXME: Check for more than 3 consecutive identical digits
    val = 0;
    previous_digit = 0;
    p = nptr;
    while ( isalpha(*p) )
    {
	digit = digits[toupper(*p) - 'C'];
	// fprintf(stderr, "digit = %d\n", digit);
	
	// Can't have more than 3 I's in a row
	if ( digit == previous_digit )
	{
	    ++consecutive;
	    
	    // IIIII should be V, XXXXX should be L, etc.
	    if ( ((consecutive > 4) && (digit != 1000)) ||
		 ((consecutive > 1) &&
		  ((digit == 5) || (digit == 50) || (digit == 500))) )
	    {
		fprintf(stderr, "romantoi(): Invalid Roman numeral: %s.\n",
			nptr);
		return 0;
	    }
	}
	else
	    consecutive = 1;
	
	if ( digit != 0 )
	{
	    if ( ! isalpha(p[1]) )
		next_digit = 0;
	    else
		next_digit = digits[toupper(*(p + 1)) - 'C'];
	    if ( next_digit > digit )
	    {
		// Only 1 lesser digit allowed before a greater one.
		// E.g. IV is valid, IIV is not.
		if ( consecutive > 1 )
		{
		    fprintf(stderr, "romantoi(): Invalid Roman numeral: %s.\n",
			    nptr);
		    return 0;
		}
		val += next_digit - digit;  // IV, IX, XL, XC, DC, CM
		++p;
	    }
	    else
		val += digit;
	}
	previous_digit = digit;
	++p;
    }
    
    *endptr = (char *)p;
    return val;
}

