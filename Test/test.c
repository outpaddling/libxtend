#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <inttypes.h>
#include "../math.h"
#include "../string.h"

int     main(int argc,char *argv[])

{
    char    string[100] = "  Aldred E. Neumann.";
    unsigned    c;
    
    strtrim(string, " .");
    puts("\nstrtrim:\nShould be 'Alfred E. Neumann'");
    printf("'%s'\n", string);
    
    puts("\nstrtrim:\nShould be ''");
    strlcpy(string, "       ", 100);
    strtrim(string, " .");
    printf("'%s'\n", string);

    puts("\nn choose k:\nShould be 6 45 0");
    printf("%lu %lu %lu\n", xt_n_choose_k(4,2), xt_n_choose_k(10,2),
	    xt_n_choose_k(1,2));
    
    puts("\nfactorials:\nShould be 1 ... 2432902008176640000");
    for (c = 0; c <= 20; ++c)
	printf("%u! = %" PRIu64 "\n", c, xt_factorial(c));
    return EX_OK;
}

