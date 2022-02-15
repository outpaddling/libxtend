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

#define BLOCK_SIZE   4096

typedef struct
{
    unsigned char    buff[BLOCK_SIZE + 1];
    size_t  bytes_read;
    size_t  c;
    int     fd;
    int     flags;
}   ffile_t;


ffile_t *ffopen(const char *filename, int flags)

{
    ffile_t *stream;
    
    if ( (stream = malloc(sizeof(*stream))) == NULL )
	return NULL;
    if ( flags & O_WRONLY )
	stream->fd = open(filename, flags, 0644);
    else
	stream->fd = open(filename, flags);
    if ( stream->fd == -1 )
	return NULL;
    stream->bytes_read = 0;
    stream->c = 0;
    stream->flags = flags;
    return stream;
}


int     ffgetc(ffile_t *stream)

{
    if ( stream->c == stream->bytes_read )
    {
	if ( (stream->bytes_read =
	    read(stream->fd, stream->buff, BLOCK_SIZE)) == 0 )
	{
	    //fprintf(stderr, "EOF found.\n");
	    return EOF;
	}
	stream->c = 0;
	//fprintf(stderr, "Read %zd bytes.\n", stream->bytes_read);
    }
    return stream->buff[stream->c++];
}


int     ffputc(int ch, ffile_t *stream)

{
    if ( stream->c == BLOCK_SIZE )
    {
	//stream->buff[stream->c] = '\0';
	//fputs(stream->buff, stderr);
	//fflush(stderr);
	if ( write(stream->fd, stream->buff, BLOCK_SIZE) != BLOCK_SIZE )
	    return EOF;
	stream->c = 0;
    }
    stream->buff[stream->c++] = ch;
    //fprintf(stderr, "%zd %c\n", stream->c, ch);
    return ch;
}


int     ffclose(ffile_t *stream)

{
    if ( stream->flags & O_WRONLY )
	write(stream->fd, stream->buff, stream->c);
    return close(stream->fd);
}


#define FFGETC(st) \
    ((st)->c == (st)->bytes_read ? \
	((st)->bytes_read = read((st)->fd, (st)->buff, BLOCK_SIZE)) == 0 ? \
	    EOF \
	: ((st)->c = 0, (st)->buff[(st)->c++]) \
    : (st)->buff[(st)->c++])

#define FFPUTC(ch, st) \
    ((st)->c == BLOCK_SIZE ? \
	write((st)->fd, (st)->buff, BLOCK_SIZE) != BLOCK_SIZE ? \
	    EOF \
	: ((st)->c = 0, (st)->buff[(st)->c++] = ch) \
    : ((st)->buff[(st)->c++] = ch))

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
	exit(1);
    }
    outfile = ffopen(argv[2], O_WRONLY|O_CREAT|O_TRUNC);
    if ( outfile == NULL )
    {
	fprintf(stderr, "Error opening %s\n", argv[2]);
	exit(1);
    }
    
    while ( (ch = FFGETC(infile)) != EOF )
	FFPUTC(ch, outfile);
    
    ffclose(outfile);
    ffclose(infile);
    return EX_OK;
}


void    usage(char *argv[])

{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EX_USAGE);
}
