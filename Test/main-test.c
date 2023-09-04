#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>      // O_RDONLY
#include "../math.h"
#include "../string.h"
#include "../stdlib.h"
#include "../file.h"
#include "../dsv.h"
#include "../fast-file.h"

#define BUFF_SIZE   1024

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
		}, *endptr,
		field[BUFF_SIZE];
    size_t      len;
    FILE        *fp;
    
    puts("\nxt_fopen()...");
    if ( xt_fopen("/asdfasdfad/asdfasfadsf.gz", "r") != NULL )
    {
	fputs("xt_fopen(\"/asdfasdfad/asdfasfadsf.gz\", \"r\") should have failed.\n", stderr);
	return EX_SOFTWARE;
    }
    else
	puts("Nonexistent xt_fopen() failed as it should.");
    
    if ( xt_fopen("/asdfasdfad/asdfasfadsf.gz", "w") != NULL )
    {
	fputs("xt_fopen(\"/asdfasdfad/asdfasfadsf.gz\", \"w\") should have failed.\n", stderr);
	return EX_SOFTWARE;
    }
    else
	puts("Unwritable xt_fopen() failed as it should.");
    
    fputs("\nxt_romantoi()...\n", stderr);
    for (c = 0; rn[c] != NULL; ++c)
    {
	// On Alma8, calling xt_romantoi() inside printf() intermittently
	// leads to invalid endptr.  This should not happen.
	// The function call should complete before printf() processes
	// the return values.
	// printf("%s = %d, *endptr = %d\n", rn[c],
	//        xt_romantoi(rn[c], &endptr), *endptr);
	int n = xt_romantoi(rn[c], &endptr);
	printf("%s = %d, *endptr = %d\n", rn[c], n, *endptr);
    }
    
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

    puts("\ncsv_read()...");
    puts("Should be \"Builder, Bob\" | Builder | 40 | Male");
    fp = fopen("test.csv", "r");
    while ( csv_read_field(fp, field, BUFF_SIZE, &len) != '\n' )
	puts(field);
    fclose(fp);
    
    return EX_OK;
}

