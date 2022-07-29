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

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    int     c;
    FILE *file;
    
    if ( argc != 2 )
	usage(argv);
    
    puts("\nFILE");
    file = fopen(argv[1], "w");
    for (c = 0; c < 200000000; ++c)
	fputc(c % 255, file);
    
    fputs("\nHello, world!\n", file);
    fprintf(file, "%d\n", 5000);
    fclose(file);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
