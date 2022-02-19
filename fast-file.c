#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "mem.h"
#include "fast-file.h"

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <fcntl.h>
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffopen()
 *      initializes a ffile_t stream, much as fopen() does for a FILE
 *      stream.  Unlike fopen(), ffopen() takes the same bit mask
 *      argument as open() to determine the open mode.
 *      See open(3) for details.
 *
 *      An optimally sized buffer for the underlying filesystem is allocated,
 *      along with additional space for limited ffungetc() operations.
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      filename    Absolute or relative path of the file to open
 *      flags       Bit flags passed to open(3)
 *
 *  Returns:
 *      A pointer to a ffile_t object on success, NULL on failure
 *
 *  Examples:
 *      ffile_t *stream;
 *      char    *filename;
 *      
 *      // Read only
 *      stream = ffopen(filename, O_RDONLY);
 *
 *      // Overwrite
 *      stream = ffopen(filename, O_WRONLY|O_CREAT|O_TRUNC);
 *
 *      // Append
 *      stream = ffopen(filename, O_WRONLY|O_APPEND);
 *
 *  See also:
 *      open(3), ffgetc(3), ffputc(3), ffungetc(3), ffclose(3)
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
    //printf("Block size = %zd\n", stream->block_size);
    
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
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffgetc()
 *      and the macro equivalent
 *      .B FFGETC()
 *      read a single character from a ffile_t stream opened by ffopen(3).
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  Pointer to an ffile_t object
 *
 *  Returns:
 *      The character read, or EOF if no more data are available
 *
 *  Examples:
 *      ffile_t *stream;
 *      int     ch;
 *
 *      if ( (stream = ffopen(filename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading.\n", filename);
 *          exit(EX_NOINPUT);
 *      }
 *      while ( (ch = FFGETC(stream)) != EOF )
 *      {
 *      }
 *      ffclose(stream);
 *
 *  See also:
 *      ffopen(3), ffputc(3), ffclose(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     ffgetc(ffile_t *stream)

{
    unsigned char   *start;
    
    if ( stream->c == stream->bytes_read )
    {
	/*
	 *  Move last part of buffer to ungetc() region.  Only the last
	 *  block read should be < block_size chars, and it will never
	 *  be moved here.
	 */
	start = stream->start + stream->block_size - XT_FAST_FILE_UNGETC_MAX;
	memcpy(stream->buff, start, XT_FAST_FILE_UNGETC_MAX);
		
	if ( (stream->bytes_read =
	      read(stream->fd, stream->start, stream->block_size)) == 0 )
	    return EOF;
	stream->c = 0;
    }
    return stream->start[stream->c++];
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffputc()
 *      and the macro equivalent
 *      .B FFPUTC()
 *      write a single character to a ffile_t stream opened by ffopen(3).
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      ch      Character to write to stream
 *      stream  Pointer to an ffile_t object opened by ffopen(3)
 *
 *  Returns:
 *      The character written, or EOF if unable to write
 *
 *  Examples:
 *      char    *infilename, *outfilename;
 *      ffile_t *instream, *outstream;
 *      int     ch;
 *
 *      if ( (instream = ffopen(infilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading.\n", infilename);
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (outstream = ffopen(outfilename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing.\n", outfilename);
 *          exit(EX_NOINPUT);
 *      }
 *      while ( (ch = FFGETC(stream)) != EOF )
 *          FFPUTC(ch, outstream);
 *      ffclose(instream);
 *      ffclose(outstream);
 *
 *  See also:
 *      ffopen(3), ffgetc(3), ffclose(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     ffputc(int ch, ffile_t *stream)

{
    if ( stream->c == stream->block_size )
    {
	if ( write(stream->fd, stream->start, stream->block_size) != stream->block_size )
	    return EOF;
	stream->c = 0;
    }
    stream->start[stream->c++] = ch;
    return ch;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffclose()
 *      closes a ffile_t stream opened by ffopen(3).  It writes out any
 *      remaining data in the output buffer, deallocates memory allocated
 *      by ffopen(3), and closes the underlying file descriptor opened by
 *      open(3).
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  Pointer to an ffile_t object opened by ffopen(3)
 *
 *  Returns:
 *      The return status of the underlying close(3) call
 *
 *  Examples:
 *      char    *infilename, *outfilename;
 *      ffile_t *instream, *outstream;
 *      int     ch;
 *
 *      if ( (instream = ffopen(infilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading.\n", infilename);
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (outstream = ffopen(outfilename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing.\n", outfilename);
 *          exit(EX_NOINPUT);
 *      }
 *      while ( (ch = FFGETC(stream)) != EOF )
 *          FFPUTC(ch, outstream);
 *      ffclose(instream);
 *      ffclose(outstream);
 *
 *  See also:
 *      ffopen(3), ffgetc(3), ffputc(3)
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



/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffungetc()
 *      returns a single character read by ffgetc(3) to the input buffer of
 *      a stream opened by ffopen(3).  All characters from the most recently
 *      read block plus a maximum of XT_FAST_FILE_UNGETC_MAX characters
 *      from the previously read block may be returned.
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      ch      Character to return to the input buffer
 *      stream  Pointer to an ffile_t object opened by ffopen(3)
 *
 *  Returns:
 *      The character written, or EOF if unable to write
 *
 *  Examples:
 *      char    *infilename;
 *      ffile_t *instream;
 *      int     ch;
 *
 *      if ( (instream = ffopen(infilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading.\n", infilename);
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (ch = FFGETC(instream)) != MY_FAVORITE_CHAR )
 *          ungetc(ch, instream);
 *      ffclose(instream);
 *
 *  See also:
 *      ffopen(3), ffgetc(3), ffclose(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-18  Jason Bacon Begin
 ***************************************************************************/

int     ffungetc(int ch, ffile_t *stream)

{
    if ( stream->c > -(XT_FAST_FILE_UNGETC_MAX + 1) )
    {
	stream->start[--stream->c] = ch;
	return ch;
    }
    else
	return EOF;
}
