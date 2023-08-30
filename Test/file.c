/***************************************************************************
 *  Description:
 *      FILE test
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
#include "../fast-file-private.h"

#define BUFF_SIZE   1024

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    int     c;
    FILE *fp;
    char    buff[BUFF_SIZE];
    
    if ( argc != 2 )
	usage(argv);
    
    puts("\nFILE fgetc() / fputc()");
    fp = fopen(argv[1], "w");
    if ( fp == NULL )
	return 1;
    fputs("Hello, world!\n", fp);
    fprintf(fp, "%d\n", 5000);
    for (c = 0; c < 1000000000; ++c)
	fputc(c % 255, fp);
    fclose(fp);
    
    fp = fopen(argv[1], "r");
    if ( fp == NULL )
	return 1;
    fgets(buff, BUFF_SIZE, fp);
    printf("Read back %s\n", buff);
    //ffscanff(fp, "%d", &c);
    while ( fgetc(fp) != EOF )
	;
    fclose(fp);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
