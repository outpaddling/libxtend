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
#include <sysexits.h>
#include <stdlib.h>
#include "../fast-file.c"

#define BUFF_SIZE   1024

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    int     c;
    xt_ffile_t *fp;
    char    buff[BUFF_SIZE];
    
    if ( argc != 2 )
	usage(argv);
    
    puts("\nxt_ffile_t");
    fp = xt_ff_open(argv[1], O_WRONLY|O_CREAT|O_TRUNC);
    if ( fp == NULL )
	return 1;
    xt_ff_puts("Hello, world!\n", fp);
    xt_ff_printf(fp, "%d\n", 5000);
    for (c = 0; c < 200000000; ++c)
	xt_ff_putc(c % 255, fp);
    xt_ff_close(fp);
    
    fp = xt_ff_open(argv[1], O_RDONLY);
    if ( fp == NULL )
	return 1;
    xt_ff_gets(buff, BUFF_SIZE, fp);
    printf("Read back %s", buff);
    //ffscanff(fp, "%d", &c);
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
