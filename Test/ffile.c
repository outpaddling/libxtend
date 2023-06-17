/***************************************************************************
 *  Description:
 *      ffile_t test
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
    ffile_t *fp;
    char    buff[BUFF_SIZE];
    
    if ( argc != 2 )
	usage(argv);
    
    puts("\nffile_t");
    fp = ffopen(argv[1], O_WRONLY|O_CREAT|O_TRUNC);
    if ( fp == NULL )
	return 1;
    ffputs("Hello, world!\n", fp);
    ffprintf(fp, "%d\n", 5000);
    for (c = 0; c < 200000000; ++c)
	ffputc(c % 255, fp);
    ffclose(fp);
    
    fp = ffopen(argv[1], O_RDONLY);
    if ( fp == NULL )
	return 1;
    ffgets(buff, BUFF_SIZE, fp);
    printf("Read back %s", buff);
    //ffscanff(fp, "%d", &c);
    while ( FFGETC(fp) != EOF )
	;
    ffclose(fp);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
