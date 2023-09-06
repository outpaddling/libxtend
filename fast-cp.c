#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sysexits.h>
#include "file.h"
#include "math.h"       // xt_lcm(), XT_MIN()

/***************************************************************************
 *  Name:
 *      xt_fast_cp() - Copy a file using optimal block size
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      xt_fast_cp() copies a file using low-level I/O with an optimal
 *      buffer size (the least common multiple of block sizes) for both
 *      source and destination filesystems.
 *  
 *  Arguments:
 *      source, dest: File names of source and destination
 *
 *  Returns:
 *      The return value of the last read(3) call.
 *
 *  See also:
 *      cp(1), read(3), write(3), fstat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     xt_fast_cp(const char *source, const char *dest)

{
    int         infile,outfile;
    struct stat infile_stats,outfile_stats;
    long        x;
    long        buff_size, nbytes;
    char        *buff;
    
    /* Open source and destination files for low level transfer */
    if ( (infile = open(source,O_RDONLY)) == -1 )
	return EX_NOINPUT;
    
    if ( (outfile = open(dest,O_WRONLY|O_CREAT|O_TRUNC,0700)) == -1 )
	return EX_CANTCREAT;

    /* Create buffer of optimum size for both files, 64k max
       Optimum buffer size is any multiple of the both sector sizes
       given by struct stat member st_blksize.  COHERENT cc lacks
       st_blksize */
    fstat(infile,&infile_stats);
    fstat(outfile,&outfile_stats);
    x = xt_lcm(infile_stats.st_blksize,outfile_stats.st_blksize);
    buff_size = XT_MIN(x,256*1024);

    if ( (buff = (char *)malloc(buff_size)) == NULL )
    {
	fputs("xt_fast_cp(): malloc() failed.\n", stderr);
	close(infile);
	close(outfile);
	return -1;
    }
    
    /* Copy file */
    while ( (nbytes = read(infile,buff,buff_size)) > 0 )
	write(outfile,buff,nbytes);
    close(infile);
    close(outfile);
    free(buff);
    return nbytes;  /* Return 0 for success, or error code from read() */
}
