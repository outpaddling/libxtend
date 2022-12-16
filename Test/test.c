#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <inttypes.h>
#include "../math.h"
#include "../string.h"
#include "../stdlib.h"

int     main(int argc,char *argv[])

{
    char        string[100] = "  Aldred E. Neumann.",
		**array;
    unsigned    c;
    char        *rn[] =
		{
		    "I", "II", "III", "IIII", "IIIII", "XIV", "XIIV",
		    "XLIX", "VVI", "LLI", "DDI", "XXXXX", "CCCCC",
		    "MMMMM", "MMMMMM", NULL
		}, *endptr;
    
    for (c = 0; rn[c] != NULL; ++c)
	printf("%s = %d, *endptr = %d\n",
	    rn[c], romantoi(rn[c], &endptr), *endptr);
    
    strtrim(string, " .");
    puts("\nstrtrim: Should be 'Alfred E. Neumann'");
    printf("'%s'\n", string);
    
    puts("\nstrtrim: Should be ''");
    strlcpy(string, "       ", 100);
    strtrim(string, " .");
    printf("'%s'\n", string);

    puts("\nn choose k: Should be 6 45 0");
    printf("%lu %lu %lu\n", xt_n_choose_k(4,2), xt_n_choose_k(10,2),
	    xt_n_choose_k(1,2));
    
    puts("\nfactorials: Should be 1 ... 2432902008176640000");
    for (c = 0; c <= 20; ++c)
	printf("%u! = %" PRIu64 "\n", c, xt_factorial(c));
    
    puts("\nstrsplit(): Should be 1 2 3 4 5");
    strlcpy(string, "1,2,3,4,5", 100);
    if ( strsplit(string, &array, ",") != 5 )
	fprintf(stderr, "strsplit() did not return 5.\n");
    else
    {
	for (c = 0; c < 5; ++c)
	    printf("%s ", array[c]);
	putchar('\n');
    }
    
    return EX_OK;
}

