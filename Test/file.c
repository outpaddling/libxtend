/***************************************************************************
 *  Description:
 *      FILE test
 *
 *      Edit only as file.c.  file.c is auto-generated.
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
    FILE *fp;
    char    buf[BUFF_SIZE];
    
    if ( argc != 2 )
	usage(argv);
    
    puts("\nFILE");
    fp = fopen(argv[1], "w");
    fputs("Hello, world!\n", fp);
    fprintf(fp, "%d\n", 5000);
    for (c = 0; c < 200000000; ++c)
	fputc(c % 255, fp);
    fclose(fp);
    
    fp = fopen(argv[1], "r");
    fgets(buf, BUFF_SIZE, fp);
    printf("Read back %s", buf);
    //fscanf(fp, "%d", &c);
    while ( getc(fp) != EOF )
	;
    fclose(fp);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
