#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mem.h"
#include "fast-file.h"

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <>
 *      -l
 *
 *  Description:
 *  
 *  Arguments:
 *
 *  Returns:
 *
 *  Examples:
 *
 *  Files:
 *
 *  Environment
 *
 *  See also:
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

ffile_t *ffopen(const char *filename, int flags)

{
    ffile_t     *stream;
    struct stat st;
    
    if ( (stream = xt_malloc(1, sizeof(*stream))) == NULL )
	return NULL;

    if ( flags & O_WRONLY )
	stream->fd = open(filename, flags, 0666);   // Masked by umask
    else
	stream->fd = open(filename, flags);
    if ( stream->fd == -1 )
    {
	free(stream);
	return NULL;
    }

    // Get optimal block size for the underlying filesystem
    if ( stat(filename, &st) != 0 )
    {
	free(stream);
	fprintf(stderr, "ffopen(): Could not stat %s.\n", filename);
	return NULL;
    }
    stream->block_size = st.st_blksize;
    //printf("Block size = %zu\n", stream->block_size);
    
    // Add space for a null byte
    stream->buff_size = XT_FAST_FILE_UNGETC_MAX + stream->block_size + 1;
    if ( (stream->buff = xt_malloc(1, stream->buff_size)) == NULL )
    {
	fputs("ffopen(): Could not allocate buffer.\n", stderr);
	free(stream);
	return NULL;
    }
    stream->start = stream->buff + XT_FAST_FILE_UNGETC_MAX;
    stream->bytes_read = 0;
    stream->c = 0;
    stream->flags = flags;
    return stream;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <>
 *      -l
 *
 *  Description:
 *  
 *  Arguments:
 *
 *  Returns:
 *
 *  Examples:
 *
 *  Files:
 *
 *  Environment
 *
 *  See also:
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     ffgetc(ffile_t *stream)

{
    if ( stream->c == stream->bytes_read )
    {
	if ( (stream->bytes_read =
	    read(stream->fd, stream->start, stream->block_size)) == 0 )
	{
	    //fprintf(stderr, "EOF found.\n");
	    return EOF;
	}
	stream->c = 0;
	//fprintf(stderr, "Read %zd bytes.\n", stream->bytes_read);
    }
    return stream->start[stream->c++];
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <>
 *      -l
 *
 *  Description:
 *  
 *  Arguments:
 *
 *  Returns:
 *
 *  Examples:
 *
 *  Files:
 *
 *  Environment
 *
 *  See also:
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     ffputc(int ch, ffile_t *stream)

{
    if ( stream->c == stream->block_size )
    {
	//stream->buff[stream->c] = '\0';
	//fputs(stream->buff, stderr);
	//fflush(stderr);
	if ( write(stream->fd, stream->start, stream->block_size) != stream->block_size )
	    return EOF;
	stream->c = 0;
    }
    stream->start[stream->c++] = ch;
    //fprintf(stderr, "%zd %c\n", stream->c, ch);
    return ch;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <>
 *      -l
 *
 *  Description:
 *  
 *  Arguments:
 *
 *  Returns:
 *
 *  Examples:
 *
 *  Files:
 *
 *  Environment
 *
 *  See also:
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     ffclose(ffile_t *stream)

{
    int     status;
    
    if ( stream->flags & O_WRONLY )
	write(stream->fd, stream->buff + XT_FAST_FILE_UNGETC_MAX, stream->c);
    status = close(stream->fd);
    free(stream->buff);
    free(stream);
    return status;
}
