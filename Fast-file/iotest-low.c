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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BLOCK_SIZE  32768

void    usage(char *argv[]);

int     main(int argc,char *argv[])

{
    int     infile, outfile;
    char    buff[BLOCK_SIZE];
    ssize_t bytes;
    
    switch(argc)
    {
	case 3:
	    break;
	
	default:
	    usage(argv);
    }
    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0777);
    
    while ( (bytes = read(infile, buff, BLOCK_SIZE)) != 0 )
	write(outfile, buff, bytes);
    
    close(outfile);
    close(infile);
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
