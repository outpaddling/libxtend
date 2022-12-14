/***************************************************************************
 *  Description:
 *  
 *  Arguments:
 *
 *  Returns:
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-12-14  Jason Bacon Begin
 ***************************************************************************/

#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include <ctype.h>

long    romantol(const char * restrict str, char ** restrict end);

int     main(int argc,char *argv[])

{
    char    rn[100], *end;
    
    puts("Enter a Roman numeral:");
    fgets(rn, 100, stdin);
    printf("%ld\n", romantol(rn, &end));
    return EX_OK;
}


long    romantol(const char * restrict str, char ** restrict end)

{
    long    digit, next_digit, previous_digit, val, consecutive;
    
    const static long digits[] = 
    {
	// I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000
	0, 0, 100, 500, 0, 0, 0, 0, 1, 0, 0, 50, 1000, 0, 0, 0, 0, 0,
	0, 0, 0, 5, 0, 10
    };

    // FIXME: Check for more than 3 consecutive identical digits
    val = 0;
    previous_digit = 0;
    while ( isalpha(*str) )
    {
	digit = digits[toupper(*str) - 'A'];
	if ( digit == previous_digit )
	{
	    if ( ++consecutive > 3 )
	    {
		fprintf(stderr, "romantol(): Invalid Roman numeral.\n");
		return 0;
	    }
	}
	else
	    consecutive = 1;
	if ( digit != 0 )
	{
	    if ( ! isalpha(str[1]) )
		next_digit = 0;
	    else
		next_digit = digits[toupper(*(str + 1)) - 'A'];
	    if ( next_digit > digit )
	    {
		val += next_digit - digit;  // IV, IX, XL, XC, DC, CM
		++str;
	    }
	    else
		val += digit;
	}
	previous_digit = digit;
	++str;
    }
    return val;
}
