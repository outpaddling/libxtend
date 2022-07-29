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

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    int     c;
    ffile_t *file;
    
    if ( argc != 2 )
	usage(argv);
    
    puts("\nffile_t");
    file = ffopen(argv[1], O_WRONLY|O_CREAT|O_TRUNC);
    for (c = 0; c < 200000000; ++c)
	ffputc(c % 255, file);
    
    ffputs("\nHello, world!\n", file);
    ffprintf(file, "%d\n", 5000);
    ffclose(file);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
