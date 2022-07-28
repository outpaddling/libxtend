/***************************************************************************
 *  Description:
 *      ffile_t test
 *
 *  Arguments:
 *
 *  Returns:
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
    
    puts("\nffile_t");
    file = ffopen("testfile", O_WRONLY|O_CREAT|O_TRUNC);
    for (c = 0; c < 200000000; ++c)
	ffputc(c % 255, file);
    ffclose(file);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
