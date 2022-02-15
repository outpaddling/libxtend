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
#include <sysexits.h>
#include <stdlib.h>

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    FILE    *infile, *outfile;
    int     ch;
    
    switch(argc)
    {
	case 3:
	    break;
	
	default:
	    usage(argv);
    }
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");
    
    while ( (ch = fgetc(infile)) != EOF )
	fputc(ch, outfile);
    
    fclose(outfile);
    fclose(infile);
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
