/***************************************************************************
 *  Description:
 *      Test fast-file higher level functions
 *
 *  Arguments:
 *
 *  Returns:
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-02-04  Jason Bacon Begin
 ***************************************************************************/

#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include "../../fast-file.h"

int     main(int argc,char *argv[])

{
    xt_ff_t *infile, *outfile;
    int     ch;
    
    // popen
    printf("\nTesting xt_ff_popen() read...  ");
    infile = xt_ff_popen("printf '%d + %d = %d\n' 1 2 $((1 + 2))\n", O_RDONLY);
    outfile = xt_ff_open("temp-output", O_WRONLY|O_CREAT);
    while ( (ch = xt_ff_getc(infile)) != EOF )
	xt_ff_putc(outfile, ch);
    xt_ff_close(infile);
    xt_ff_close(outfile);
    if ( system("diff temp-output popen-output") == 0 )
	puts("Passed.");
    else
	return 1;
    
    // puts/gets
    
    // gets_malloc
    
    // tmpfile
    
    // read/write
    
    // seeko/rewind
    
    // printf/scanf
    
    puts("\nMore tests TBD");
    
    return EX_OK;
}
