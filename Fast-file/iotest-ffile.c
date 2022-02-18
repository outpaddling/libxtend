/***************************************************************************
 *  Description:
 *  
 *  Arguments:
 *
 *  Returns:
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include "fast-file.h"

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    ffile_t *infile, *outfile;
    int     ch;
    
    switch(argc)
    {
	case 3:
	    break;
	
	default:
	    usage(argv);
    }
    infile = ffopen(argv[1], O_RDONLY);
    if ( infile == NULL )
    {
	fprintf(stderr, "Error opening %s\n", argv[1]);
	return 1;
    }
    outfile = ffopen(argv[2], O_WRONLY|O_CREAT|O_TRUNC);
    if ( outfile == NULL )
    {
	fprintf(stderr, "Error opening %s\n", argv[2]);
	return 1;
    }
    
    while ( (ch = FFGETC(infile)) != EOF )
	ffputc(ch, outfile);
    
    ffclose(outfile);
    ffclose(infile);
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
