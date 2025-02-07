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
#include <string.h>
#include "../../fast-file.h"

#define STR_LEN_MAX 128
#define TEST_STRING "Bring home the bacon."

int     main(int argc,char *argv[])

{
    xt_ff_t *infile, *outfile;
    int     ch;
    char    string[STR_LEN_MAX + 1],
	    template[] = "/tmp/temp.XXXXXX";
    
    // puts/gets
    printf("Testing xt_ff_puts() and xt_ff_gets()...  ");
    outfile = xt_ff_open("temp-write-output", O_WRONLY|O_CREAT);
    // xt_ff_gets() does not include the NL in the string
    xt_ff_puts(outfile, TEST_STRING "\n");
    xt_ff_close(outfile);
    infile = xt_ff_open("temp-write-output", O_RDONLY);
    xt_ff_gets(infile, string, STR_LEN_MAX + 1);
    xt_ff_close(infile);
    if ( strcmp(string, TEST_STRING) == 0 )
	puts("Passed.");
    else
	return 1;
    
    // gets_malloc
    
    // popen
    printf("\nTesting xt_ff_popen() read...  ");
    infile = xt_ff_popen("printf '%d + %d = %d\n' 1 2 $((1 + 2))", O_RDONLY);
    outfile = xt_ff_open("temp-read-output", O_WRONLY|O_CREAT);
    while ( (ch = xt_ff_getc(infile)) != EOF )
	xt_ff_putc(outfile, ch);
    xt_ff_close(infile);
    xt_ff_close(outfile);
    if ( system("diff temp-read-output popen-read-output") == 0 )
	puts("Passed.");
    else
	return 1;
    unlink("temp-read-output");
    
    printf("\nTesting xt_ff_popen() write...  ");
    outfile = xt_ff_popen("sed -e 's|bacon|ham|g' > temp-write-output", O_WRONLY);
    xt_ff_puts(outfile, "Bring home the bacon.\n");
    xt_ff_close(outfile);
    if ( system("diff temp-write-output popen-write-output") == 0 )
	puts("Passed.");
    else
	return 1;
    unlink("temp-write-output");
    
    // tmpfile/seeko/rewind
    printf("\nTesting xt_ff_mkstemp(), xt_ff_rewind()...  ");
    outfile = xt_ff_mkstemp(template);
    // printf("Writing %s to %s...\n", TEST_STRING, template);
    xt_ff_puts(outfile, TEST_STRING "\n");
    xt_ff_rewind(outfile);
    xt_ff_gets(outfile, string, STR_LEN_MAX + 1);
    // puts(string);
    xt_ff_close(outfile);
    unlink(template);
    if ( strcmp(string, TEST_STRING) == 0 )
	puts("Passed.");
    else
	return 1;
    
    // read/write
    
    // printf/scanf
    
    puts("\nMore tests TBD");
    
    return EX_OK;
}
