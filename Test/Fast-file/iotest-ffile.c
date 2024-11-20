#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sysexits.h>
#include "../../fast-file-private.h"

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    xt_ff_t *infile, *outfile;
    int     ch, ch2, ch3;
    
    switch(argc)
    {
	case 3:
	    break;
	
	default:
	    usage(argv);
    }
    if ( strcmp(argv[1],"-") == 0 )
	infile = xt_ff_stdin();
    else
	infile = xt_ff_open(argv[1], O_RDONLY);
    if ( infile == NULL )
    {
	fprintf(stderr, "Error opening %s\n", argv[1]);
	return 1;
    }

    if ( strcmp(argv[2],"-") == 0 )
	outfile = xt_ff_stdout();
    else
	outfile = xt_ff_open(argv[2], O_WRONLY|O_CREAT|O_TRUNC);
    if ( outfile == NULL )
    {
	fprintf(stderr, "Error opening %s\n", argv[2]);
	return 1;
    }

    // Test ungetc extra space behind stream->start
    ch = XT_FF_GETC(infile);
    ch2 = XT_FF_GETC(infile);
    ch3 = XT_FF_GETC(infile);
    xt_ff_ungetc(infile, ch3);
    xt_ff_ungetc(infile, ch2);
    xt_ff_ungetc(infile, ch);
    
    while ( (ch = XT_FF_GETC(infile)) != EOF )
	XT_FF_PUTC(outfile, ch);
    
    xt_ff_close(outfile);
    xt_ff_close(infile);
    
    //outfile = xt_ff_open("xt_ff_printf-test.txt", O_WRONLY|O_CREAT|O_TRUNC);
    //xt_ff_printf(outfile, "%s%d\n", "xt_ff_printf test #", 1);
    //xt_ff_close(outfile);
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
