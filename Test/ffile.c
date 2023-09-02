/***************************************************************************
 *  Description:
 *      xt_ffile_t test
 *
 *      Edit only as ffile.c.  file.c is auto-generated.
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-07-28  Jason Bacon Begin
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sysexits.h>
#include <stdlib.h>
#include "../fast-file-private.h"

#define BUFF_SIZE   1024

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    size_t  c, len;
    xt_ffile_t *fp;
    char    buff[BUFF_SIZE],
	    string[] = "Hello, world!\n";

    if ( argc != 2 )
	usage(argv);
    
    puts("\nxt_ffile_t xt_ff_getc() / xt_ff_putc()");
    
    /*
     *  Write file
     */
    
    fp = xt_ff_open(argv[1], O_WRONLY|O_CREAT|O_TRUNC);
    if ( fp == NULL )
	return 1;
    xt_ff_puts(string, fp);
    xt_ff_printf(fp, "%d\n", 5000);
    for (c = 0; c < 1000000000; ++c)
	xt_ff_putc(c % 255, fp);
    xt_ff_close(fp);
    
    /*
     *  Read back
     */
    
    fp = xt_ff_open(argv[1], O_RDONLY);
    if ( fp == NULL )
	return 1;
    xt_ff_gets(buff, BUFF_SIZE, fp);
    printf("Read back %s\n", buff);

    // Unget and read again
    len = strlen(string);
    for (c = 0; c < len; ++c)
	xt_ff_ungetc(string[len - c - 1], fp);
    xt_ff_gets(buff, BUFF_SIZE, fp);
    printf("Read back ungotten %s\n", buff);
    
    puts("Should print 5000:");
    // FIXME: Not yet implemented 
    // xt_ff_scanf(fp, "%d", &c);
    for (c = 0; c < 4; ++c) // length of "5000"
	putchar(xt_ff_getc(fp));
    putchar('\n');

    puts("Reading bulk data...");
    while ( xt_ff_getc(fp) != EOF )
	;
    xt_ff_close(fp);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
