/***************************************************************************
 *  Description:
 *      FILE test
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
    FILE *file;
    
    puts("\nFILE");
    file = fopen("testfile", "w");
    for (c = 0; c < 200000000; ++c)
	fputc(c % 255, file);
    fclose(file);
    
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
