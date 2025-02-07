#ifdef __linux__
#define _GNU_SOURCE     // vasprintf(), must come before stdio.h
#endif

#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdarg.h>
#include "mem.h"
#include "proc.h"
#include "fast-file-private.h"
#include "common.h"

/*
 *  Non-API function for completing stream initialization for xt_ff_open(3)
 *  and xt_ff_dopen(3)
 */

xt_ff_t *_xt_ff_init_stream(xt_ff_t *stream)

{
    struct stat st;
    
    // Get optimal block size for the underlying filesystem
    if ( fstat(stream->fd, &st) != 0 )
    {
	fprintf(stderr, "_xt_ff_init_stream(): Could not stat fd %d.\n", stream->fd);
	free(stream);
	return NULL;
    }
    stream->disk_block_size = st.st_blksize;
    // fprintf(stderr, "%s(): Block size = %zd\n", __FUNCTION__, stream->disk_block_size);
    // Add space for a null byte
    stream->buff_size = XT_FAST_FILE_UNGETC_MAX + stream->disk_block_size + 1;
    if ( (stream->buff = xt_malloc(1, stream->buff_size)) == NULL )
    {
	fprintf(stderr, "%s(): Could not allocate buffer.\n", __FUNCTION__);
	free(stream);
	return NULL;
    }
    stream->start_ptr = stream->buff + XT_FAST_FILE_UNGETC_MAX;
    stream->bytes_read = 0;
    stream->buff_index = 0;
    
    return stream;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_getc() - Read next character from a fast file stream
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_getc(3)
 *      reads a single character from a xt_ff_t stream opened by xt_ff_open(3).
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  Pointer to an xt_ff_t object
 *
 *  Returns:
 *      The character read, or EOF if no more data are available
 *
 *  Examples:
 *      xt_ff_t *stream;
 *      int     ch;
 *
 *      if ( (stream = xt_ff_open(filename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading: %s.\n",
 *                  filename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      while ( (ch = xt_ff_getc(stream)) != EOF )
 *      {
 *      }
 *      xt_ff_close(stream);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_putc(3), xt_ff_close(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_getc(xt_ff_t *stream)

{
    // unsigned char   *start_ptr;
    
    if ( stream->buff_index == stream->bytes_read )
    {
	/*
	 *  Move last part of buffer to xt_ff_ungetc(3) region.  Only the last
	 *  block read should be < disk_block_size chars, and it will never
	 *  be moved here.
	 */
	// FIXME: I think this is old and no longer needed
	// No recollection of why it was added
	// start_ptr = stream->start_ptr + stream->disk_block_size - XT_FAST_FILE_UNGETC_MAX;
	// memcpy(stream->buff, start_ptr, XT_FAST_FILE_UNGETC_MAX);
	
	return _xt_ff_fillbuff(stream);
    }
    else
	return stream->start_ptr[stream->buff_index++];
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_putc() - Write a character to a fast file stream
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_putc(3)
 *      writes a single character to a xt_ff_t stream opened by xt_ff_open(3).
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      ch      Character to write to stream
 *      stream  Pointer to an xt_ff_t object opened by xt_ff_open(3)
 *
 *  Returns:
 *      The character written, or EOF if unable to write
 *
 *  Examples:
 *      char    *infilename, *outfilename;
 *      xt_ff_t *instream, *outstream;
 *      int     ch;
 *
 *      if ( (instream = xt_ff_open(infilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading: %s.\n",
 *                  infilename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (outstream = xt_ff_open(outfilename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing: %s.\n",
 *                  outfilename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      while ( (ch = xt_ff_getc(stream)) != EOF )
 *          xt_ff_puts(ch, outstream);
 *      xt_ff_close(instream);
 *      xt_ff_close(outstream);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_getc(3), xt_ff_close(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_putc(xt_ff_t *stream, int ch)

{
    if ( stream->buff_index == stream->disk_block_size )
    {
	if ( write(stream->fd, stream->start_ptr, stream->disk_block_size) != stream->disk_block_size )
	    return EOF;
	stream->buff_index = 0;
    }
    stream->start_ptr[stream->buff_index++] = ch;
    return ch;
}


/***************************************************************************
 *  Name:
 *      xt_ff_open() - Open a fast file stream for a raw or compressed file
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_open(3)
 *      opens a raw data file using _xt_ff_raw_open(3)
 *      or a gzipped, bzipped, or
 *      xzipped file using xt_ff_popen(3), returning a pointer to a xt_ff_t
 *      stream.  Must be used in conjunction with xt_ff_close(3).
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *
 *  Arguments:
 *      filename:   Name of the file to be opened
 *      mode:       Bit mask as used by open(2)
 *
 *  Returns:
 *      A pointer to the FILE structure or NULL if open failed
 *
 *  See also:
 *      fopen(3), popen(3), gzip(1), bzip2(1), xz(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-09  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *xt_ff_open(const char *filename, int flags)

{
    char    *ext = strrchr(filename, '.'),
	    cmd[XT_CMD_MAX_CHARS + 1];
    
    if ( ext == NULL )
	ext = "";

    //fprintf(stderr, "flags = %x\n", flags);
    if ( flags == O_RDONLY )    // O_RDONLY = 0x0, no bits set
    {
	// fprintf(stderr, "Reading from %s...\n", filename);
	if ( strcmp(ext, ".gz") == 0 )
	{
// Big Sur zcat requires a .Z extension and CentOS 7 lacks gzcat
#ifdef __APPLE__
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzcat %s", filename);
#else
	    snprintf(cmd, XT_CMD_MAX_CHARS, "zcat %s", filename);
#endif
	    return xt_ff_popen(cmd, flags);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzcat %s", filename);
	    return xt_ff_popen(cmd, flags);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xzcat %s", filename);
	    return xt_ff_popen(cmd, flags);
	}
	else
	    return _xt_ff_raw_open(filename, flags);
    }
    else    // O_WRONLY
    {
	// fprintf(stderr, "Writing to %s...\n", filename);
	if ( strcmp(ext, ".gz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzip -c > %s", filename);
	    return xt_ff_popen(cmd, flags);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzip2 -c > %s", filename);
	    return xt_ff_popen(cmd, flags);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xz -c > %s", filename);
	    return xt_ff_popen(cmd, flags);
	}
	else
	    return _xt_ff_raw_open(filename, flags);
    }
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      _xt_ff_raw_open() - Open a fast file stream for a raw file
 *
 *  Library:
 *      #include <fcntl.h>
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B _xt_ff_raw_open(3)
 *      initializes a xt_ff_t stream, much as fopen(3) does for a FILE
 *      stream.  Unlike fopen(3), _xt_ff_raw_open(3) takes the same bit mask
 *      argument as open(2) to determine the open mode.
 *      See open(3) for details.
 *
 *      An optimally sized buffer for the underlying filesystem is allocated,
 *      along with additional space for limited xt_ff_ungetc(3) operations.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      filename    Absolute or relative path of the file to open
 *      flags       Bit flags passed to open(3)
 *
 *  Returns:
 *      A pointer to a xt_ff_t object on success, NULL on failure
 *
 *  Examples:
 *      xt_ff_t *stream;
 *      char    *filename;
 *      
 *      // Read only
 *      stream = _xt_ff_raw_open(filename, O_RDONLY);
 *
 *      // Overwrite
 *      stream = _xt_ff_raw_open(filename, O_WRONLY|O_CREAT|O_TRUNC);
 *
 *      // Append
 *      stream = _xt_ff_raw_open(filename, O_WRONLY|O_APPEND);
 *
 *  See also:
 *      open(3), xt_ff_getc(3), xt_ff_putc(3), xt_ff_ungetc(3), xt_ff_close(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *_xt_ff_raw_open(const char *filename, int flags)

{
    xt_ff_t     *stream;
    
    if ( (stream = xt_malloc(1, sizeof(*stream))) == NULL )
	return NULL;

    // FIXME: Add other open modes
    if ( flags & O_CREAT )
	stream->fd = open(filename, flags, 0666);   // Masked by umask
    else
	stream->fd = open(filename, flags);
    if ( stream->fd == -1 )
    {
	free(stream);
	return NULL;
    }
    stream->flags = flags;

    return _xt_ff_init_stream(stream);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_dopen() - Create a fast file stream from a file descriptor
 *
 *  Library:
 *      #include <fcntl.h>
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_dopen(3)
 *      initializes a xt_ff_t stream, much as fdopen(3) does for a FILE
 *      stream.  Unlike fdopen(3), xt_ff_dopen(3) takes the same bit mask
 *      argument as open(2) to determine the open mode.
 *      See open(3) for details.
 *
 *      An optimally sized buffer for the underlying filesystem is allocated,
 *      along with additional space for limited xt_ff_ungetc(3) operations.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      fd          Open file descriptor to which stream is attached
 *      flags       Bit flags passed to open(3)
 *
 *  Returns:
 *      A pointer to a xt_ff_t object on success, NULL on failure
 *
 *  Examples:
 *      xt_ff_t *stream;
 *      char    *filename;
 *      int     fd;
 *      
 *      fd = open(filename, O_RDONLY);
 *      stream = xt_ff_dopen(fd, O_RDONLY);
 *
 *  See also:
 *      xt_ff_open(3), open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *xt_ff_dopen(int fd, int flags)

{
    xt_ff_t     *stream;
    
    if ( (stream = xt_malloc(1, sizeof(*stream))) == NULL )
	return NULL;
    
    // FIXME: Can this happen before init?
    stream->fd = fd;
    stream->flags = flags;

    return _xt_ff_init_stream(stream);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_flush(stream)
 *      writes any buffered output in stream to the underlying file
 *      descriptor.  This normally happens when the buffer is full,
 *      the stream is closed using xt_ff_close(stream), or before
 *      a seek is performed on a stream opened for writing.
 *  
 *  Arguments:
 *      stream  Pointer to an xt_ff_t stream
 *
 *  Returns:
 *      Return code of the underlying write(2) call
 *      -1 if stream is not open for writing
 *
 *  Examples:
 *      xt_ff_t *stream;
 *
 *      stream = xt_ff_open(filename, O_WRONLY|O_CREATE);
 *      ...
 *      xt_ff_flush(stream);
 *
 *  See also:
 *      xt_ff_open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-02-07  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_flush(xt_ff_t *stream)

{
    if ( stream->flags & (O_WRONLY|O_RDWR|O_APPEND) )
	return write(stream->fd, stream->start_ptr, stream->buff_index);
    else
	return -1;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      _xt_ff_raw_close() - Close a stream created by _xt_ff_raw_open()
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B _xt_ff_raw_close(3)
 *      closes a xt_ff_t stream opened by _xt_ff_raw_open(3).
 *      It writes out any
 *      remaining data in the output buffer, deallocates memory allocated
 *      by xt_ff_open(3), and closes the underlying file descriptor opened by
 *      open(3).
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  Pointer to an xt_ff_t object opened by xt_ff_open(3)
 *
 *  Returns:
 *      The return status of the underlying close(3) call
 *
 *  Examples:
 *      char    *infilename, *outfilename;
 *      xt_ff_t *instream, *outstream;
 *      int     ch;
 *
 *      if ( (instream = xt_ff_open(infilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading: %s.\n",
 *                  infilename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (outstream = xt_ff_open(outfilename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing: %s.\n",
 *                  outfilename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      while ( (ch = xt_ff_getc(stream)) != EOF )
 *          xt_ff_putc(ch, outstream);
 *      xt_ff_close(instream);
 *      xt_ff_close(outstream);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_getc(3), xt_ff_putc(3)
 *  
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

int     _xt_ff_raw_close(xt_ff_t *stream)

{
    int     status;
    
    if ( stream->flags & (O_WRONLY|O_RDWR|O_APPEND) )
    {
	//fprintf(stderr, "%s(): flushing output...\n", __FUNCTION__);
	//stream->start_ptr[stream->buff_index] = '\0';
	///fprintf(stderr, "buff = %s\n", (char *)stream->start_ptr);
	if ( xt_ff_flush(stream) < 0 )
	    return -1;  // FIXME: Define error constants
    }
    status = close(stream->fd);
    free(stream->buff);
    free(stream);
    return status;
}


/***************************************************************************
 *  _xt_ff_fillbuff(3)
 *  issues a read(2) call to refill the buffer of an xt_ff_t
 *  structure.  It is meant to be called by xt_ff_getc(3),
 *  and should not be used directly.
 *  
 *  History: 
 *  Date        Name        Modification
 *  2023-09-02  Jason Bacon Begin
 ***************************************************************************/

int  _xt_ff_fillbuff(xt_ff_t *stream)

{
    if ( (stream->bytes_read = read(stream->fd, stream->start_ptr,
				    stream->disk_block_size)) == 0 )
	return EOF;
    else
    {
	stream->buff_index = 0;
	return stream->start_ptr[stream->buff_index++];
    }
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_ungetc() - Put a character back into a fast file stream read buffer
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_ungetc(3)
 *      returns a single character read by xt_ff_getc(3) to the input buffer of
 *      a stream opened by xt_ff_open(3).  All characters from the most recently
 *      read block plus a maximum of XT_FAST_FILE_UNGETC_MAX characters
 *      from the previously read block may be returned.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      ch      Character to return to the input buffer
 *      stream  Pointer to an xt_ff_t object opened by xt_ff_open(3)
 *
 *  Returns:
 *      The character written, or EOF if unable to write
 *
 *  Examples:
 *      char    *infilename;
 *      xt_ff_t *instream;
 *      int     ch;
 *
 *      if ( (instream = xt_ff_open(infilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for reading: %s.\n",
 *                  infilename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (ch = xt_ff_getc(instream)) != MY_FAVORITE_CHAR )
 *          xt_ff_ungetc(ch, instream);
 *      xt_ff_close(instream);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_getc(3), xt_ff_close(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-18  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_ungetc(xt_ff_t *stream, int ch)

{
    if ( stream->buff_index > -(XT_FAST_FILE_UNGETC_MAX + 1) )
    {
	stream->start_ptr[--stream->buff_index] = ch;
	return ch;
    }
    else
	return EOF;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_stdin() - Create a fast file stream attached to descriptor 0
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_stdin(3)
 *      is a simple wrapper function for connecting file descriptor 0
 *      to an xt_ff_t object using xt_ff_dopen(3).  This is useful for
 *      high-performance filter programs, where using the traditional
 *      FILE *stdin would cause a bottleneck.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      None
 *
 *  Returns:
 *      Pointer to an xt_ff_t object if successful, NULL otherwise
 *
 *  Examples:
 *      xt_ff_t *stream;
 *
 *      // "-" as a filename argument traditionally indicates stdin
 *      if ( strcmp(argv[arg], "-") == 0 )
 *          stream = xt_ff_stdin(3);
 *      else
 *          stream = xt_ff_open(argv[arg], O_RDONLY);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_dopen(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *xt_ff_stdin(void)

{
    return xt_ff_dopen(0, O_RDONLY);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_stdout() - Create a fast file stream connected to descriptor 1
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_stdout(3)
 *      is a simple wrapper function for connecting file descriptor 1
 *      to an xt_ff_t object using xt_ff_dopen(3).  This is useful for
 *      high-performance filter programs, where using the traditional
 *      FILE *stdout would cause a bottleneck.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      None
 *
 *  Returns:
 *      Pointer to an xt_ff_t object if successful, NULL otherwise
 *
 *  Examples:
 *      xt_ff_t *stream;
 *
 *      // "-" as a filename argument traditionally indicates stdout
 *      if ( strcmp(argv[arg], "-") == 0 )
 *          stream = xt_ff_stdout();
 *      else
 *          stream = xt_ff_open(argv[arg], O_WRONLY|O_CREAT|O_TRUNC);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_dopen(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *xt_ff_stdout(void)

{
    return xt_ff_dopen(1, O_WRONLY|O_APPEND);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_popen() - Create a fast file stream connected to a process
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_popen(3)
 *      creates a pipe for interprocess communication, runs the specified
 *      command, connecting the command's standard input or standard
 *      output to the pipe, and returning a pointer to a xt_ff_t object
 *      connected to the other end.
 *
 *      It behaves much like popen(3), except that it returns a fast-file
 *      xt_ff_t pointer rather than a standard I/O FILE pointer, and
 *      accepts a full set of open(3) flags rather than the fopen(3)
 *      type strings "r", "w", etc.
 *
 *      This allows the calling program to spawn a child process
 *      and read its standard output or write to its standard input as
 *      easily as reading or writing a file.
 *
 *      Note that the stream may be closed with xt_ff_close(3).  Unlike
 *      popen(3), which must be used with pclose(3), it is not necessary
 *      to call _xt_ff_pclose(3) directly.  The xt_ff_close(3) function
 *      automatically determines whether the stream is attached to a pipe.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      cmd     Full command to execute as the child, passed to sh(1)
 *      flags   Open mode flags passed to open(3)
 *
 *  Returns:
 *      Pointer to a xt_ff_ile_t object on success, NULL otherwise
 *
 *  Examples:
 *      xt_ff_t *instream;
 *
 *      if ( (instream = xt_ff_popen("xzcat file.xz", O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Failed to read xzcat file.xz.\n");
 *          exit(EX_NOINPUT);
 *      }
 *
 *      xt_ff_close(instream);
 *
 *  See also:
 *      xt_ff_open(3), xt_ff_close(3), popen(3), open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *xt_ff_popen(const char *cmd, int flags)

{
    pid_t   pid;
    int     fd[2];
    xt_ff_t *stream = NULL;
    char    *argv[XT_FAST_FILE_MAX_ARGS];
    
    if ( pipe(fd) == 0 )
    {
	if ( (pid = fork()) == 0 )  // Child process
	{
	    // Use shell to process redirection, etc.
	    argv[0] = "sh";
	    argv[1] = "-c";
	    argv[2] = (char *)cmd;
	    argv[3] = NULL;

	    if ( flags == O_RDONLY )    // O_RDONLY = 0x0, not bits
	    {
		// Child runs command and writes standard output to pipe
		// Readers won't get EOF until last descriptor is closed
		// so don't leave this lying around
		close(fd[0]);   // Not used by child
		close(1);
		if ( dup(fd[1]) != 1 )
		{
		    fprintf(stderr, "%s: dup() failed to return 1.\n",
			    __FUNCTION__);
		    return NULL;
		}
		execvp("/bin/sh", argv);
		exit(EX_OSERR);    // Should not be reached
	    }
	    else
	    {
		// Child runs command and reads standard input from pipe
		// Readers won't get EOF until last descriptor is closed
		// so don't leave this lying around
		close(fd[1]);   // Not used by child
		close(0);
		if ( dup(fd[0]) != 0 )
		{
		    fprintf(stderr, "%s: dup() failed to return 0.\n",
			    __FUNCTION__);
		    return NULL;
		}
		execvp("/bin/sh", argv);
		exit(EX_OSERR);    // Should not be reached
	    }
	}
	else
	{
	    if ( flags == O_RDONLY )    // O_RDONLY = 0x0, no bits
	    {
		// Parent reads from child via pipe
		// Readers won't get EOF until last descriptor is closed
		// so don't leave this lying around
		close(fd[1]);   // Not used by parent
		if ( (stream = xt_ff_dopen(fd[0], O_RDONLY)) == NULL )
		    return NULL;
	    }
	    else
	    {
		// Parent writes to child via pipe
		// Readers won't get EOF until last descriptor is closed
		// so don't leave this lying around
		close(fd[0]);   // Not used by parent
		if ( (stream = xt_ff_dopen(fd[1], O_WRONLY)) == NULL )
		    return NULL;
	    }
    
	    // Set pid in xt_ff_t stream for waitpid(2) in _xt_ff_pclose(3)
	    stream->child_pid = pid;
	    return stream;
	}
    }
    return stream;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      _xt_ff_pclose() - Close a stream created by xt_ff_popen(3)
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B _xt_ff_pclose(3)
 *      closes a stream opened by xt_ff_popen(3), and
 *      waits for the child process to complete and returns its
 *      exit status.  Unlike the FILE stream functions popen(3) and
 *      pclose(3), it is not necessary to match xt_ff_popen(3) and
 *      _xt_ff_pclose(3).  The xt_ff_close(3) function automatically
 *      senses whether stream if a pipe (FIFO), and calls
 *      _xt_ff_pclose(3) or _xt_ff_raw_close(3) as needed.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  xt_ff_t stream opened by xt_ff_popen(3)
 *
 *  Returns:
 *      Exit status of the child process spawned by xt_ff_popen(3), or -1 on error
 *
 *  Examples:
 *      xt_ff_t *instream;
 *
 *      if ( (instream = xt_ff_popen("xzcat file.xz", O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Failed to read xzcat file.xz.\n");
 *          exit(EX_NOINPUT);
 *      }
 *
 *      xt_ff_close(instream);
 *
 *  See also:
 *      xt_ff_open(3), _xt_ff_pclose(3), popen(3), open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

int     _xt_ff_pclose(xt_ff_t *stream)

{
    int     status = 0;
    pid_t   pid = stream->child_pid;
    
    if ( pid == 0 )
    {
	fprintf(stderr, "%s(): No child PID available.  Was the stream opened with xt_ff_popen()?\n",
		__FUNCTION__);
	return -1;
    }
    
    _xt_ff_raw_close(stream);
    
    // Compatibility with pclose()
    waitpid(pid, &status, 0);
    //fprintf(stderr, "Back from waitpid().\n");
    
    return status;
}


/***************************************************************************
 *  Name:
 *      xt_ff_close() - Close a stream created by xt_ff_open()
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_close(3)
 *      closes a xt_ff_t stream by calling
 *      _xt_ff_raw_close(3) or _xt_ff_pclose(3) as appropriate.
 *      Automatically determines the proper close function to call using
 *      S_ISFIFO() on the stream stat structure.
 *
 *      The xt_ff_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *
 *  Arguments:
 *      stream: Pointer to the xt_ff_t structure to be closed
 *
 *  Returns:
 *      The value returned by _xt_ff_raw_close(3) or _xt_ff_pclose(3)
 *
 *  See also:
 *      xt_ff_popen(3), xt_ff_open(3), gzip(1), bzip2(1), xz(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-10  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_close(xt_ff_t *stream)

{
    struct stat stat;
    
    fstat(stream->fd, &stat);
    if ( S_ISFIFO(stat.st_mode) )
	return _xt_ff_pclose(stream);
    else
	return _xt_ff_raw_close(stream);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_printf() - Print formatted data to a fast file stream
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_printf(3)
 *      writes formatted data to a xt_ff_t stream the same was as
 *      fprintf(3) writes to a FILE stream.
 *
 *      The xt_ff_ile_t system is simpler than and much faster than
 *      traditional FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  Pointer to an xt_ff_t object opened by xt_ff_open(3)
 *      format  Format string indicating how remaining arguments are printed
 *
 *  Returns:
 *      The number of characters written
 *
 *  Examples:
 *      xt_ff_ile_t *stream;
 *      int     count = 1;
 *
 *      if ( (stream = xt_ff_open(filename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Could not open %s.\n", filename);
 *          exit(EX_CANTCREAT);
 *      }
 *      xt_ff_printf(stream, "%d\n", count);
 *      xt_ff_close(stream);
 *
 *  See also:
 *      fprintf(3), xt_ff_open(3), xt_ff_close(3), xt_ff_putc(3), xt_ff_puts(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_printf(xt_ff_t *stream, const char *format, ...)

{
    va_list ap;
    char    *buff;
    int     chars_printed, c;
    
    va_start(ap, format);
    chars_printed = vasprintf(&buff, format, ap);
    for (c = 0; buff[c] != '\0'; ++c)
	xt_ff_putc(stream, buff[c]);
    free(buff);
    return chars_printed;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_puts() - Print a string to a fast file stream
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      xt_ff_puts(3) writes a null-terminated string to the given xt_ff_t
 *      stream.  It is fnuctionally equivalent to fputs(3) with FILE.
 *  
 *  Arguments:
 *      string      A null-terminated string
 *      stream      Pointer to an xt_ff_t structure opened with xt_ff_open(3)
 *
 *  Returns:
 *      A non-negative integer on success, EOF on failure
 *
 *  Examples:
 *      xt_ff_t *outstream;
 *      char    *buff;
 *
 *      if ( (outstream = xt_ff_open(outfilename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing: %s.\n",
 *                  outfilename, strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      xt_ff_puts("Hello, world!\n", outstream);
 *      xt_ff_close(outstream);
 *
 *  See also:
 *      fputs(3), xt_ff_gets(3), xt_ff_open(3), xt_ff_close(3), xt_ff_putc(3), xt_ff_printf(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-07-29  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_puts(xt_ff_t *stream, const char *string)

{
    size_t  c;
    int     status = 0;
    
    for (c = 0; (status >= 0) && (string[c] != '\0'); ++c)
	status = xt_ff_putc(stream, string[c]);
    return status;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_gets() - Read a line from a fast file stream
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      xt_ff_gets(3) writes a line of text from the given xt_ff_t
 *      stream.  It is functionally equivalent to fgets(3) with FILE.
 *  
 *  Arguments:
 *      string      A character array into which the line is read
 *      size        Size of the character array
 *      stream      Pointer to an xt_ff_t structure opened with xt_ff_open(3)
 *
 *  Returns:
 *      A non-negative integer on success, EOF on failure
 *
 *  Examples:
 *      xt_ff_t *instream;
 *      char    buff[BUFF_SIZE];
 *
 *      if ( (instream = xt_ff_open(outfilename, O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing: %s.\n",
 *                  outfilename,strerror(errno));
 *          exit(EX_NOINPUT);
 *      }
 *      xt_ff_gets(buff, BUFF_SIZE, instream);
 *      xt_ff_close(instream);
 *
 *  See also:
 *      fgets(3), xt_ff_puts(3), xt_ff_open(3), xt_ff_close(3), xt_ff_putc(3), xt_ff_printf(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-07-29  Jason Bacon Begin
 ***************************************************************************/

char    *xt_ff_gets(xt_ff_t *stream, char *string, size_t size)

{
    size_t  c;
    int     ch;
    
    c = 0;
    while ( ((ch = XT_FF_GETC(stream)) != '\n') && (ch != EOF) && (c < size - 1) )
	string[c++] = ch;
    if ( (c == 0) && (ch == EOF) )
	return NULL;
    else
	return string;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_gets_malloc() - Read a line from a fast file stream,
 *                                 allocating memory as needed
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_gets_malloc(3)
 *      reads a single line of text (up to the next newline or EOF)
 *      from stream, allocating and/or extending the provided buffer if
 *      needed.
 *  
 *  Arguments:
 *      stream:     xt_ff_t stream from which field is read
 *      buff:       Character buffer into which field is copied
 *      buff_size:  Size of the array passed to buff
 *      len:        Pointer to a variable which will receive the field length
 *
 *  Returns:
 *      Delimiter ending the read: either newline or EOF
 *
 *  Examples:
 *      xt_ff_t *stream;
 *      char    *buff;
 *      size_t  buff_len, len;
 *
 *      while ( xt_ff_ile_read_line_malloc(stream, buff, &buff_len, &len) != EOF )
 *      {
 *      }
 *
 *  See also:
 *      xt_dsv_read_field_malloc(3), xt_ff_getc(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-20  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_gets_malloc(xt_ff_t *stream, char **buff, size_t *buff_size,
			   size_t *len)

{
    size_t  c;
    int     ch;
    
    if ( *buff_size == 0 )
    {
	*buff_size = 1024;
	*buff = xt_malloc(*buff_size, sizeof(**buff));
	if ( *buff == NULL )
	    return XT_MALLOC_FAILED;
    }
    
    for (c = 0; ( ((ch = XT_FF_GETC(stream)) != '\n') && (ch != EOF) ); ++c)
    {
	if ( c == *buff_size - 1 )
	{
	    *buff_size *= 2;
	    *buff = xt_realloc(*buff, *buff_size, sizeof(**buff));
	    if ( *buff == NULL )
		return XT_MALLOC_FAILED;
	}
	(*buff)[c] = ch;
    }
    (*buff)[c] = '\0';
    *len = c;

    /* Trim array */
    if ( *buff_size != c + 1 )
    {
	*buff_size = c + 1;
	*buff = xt_realloc(*buff, *buff_size, sizeof(**buff));
    }
    return ch;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_tmpfile() - Create a fast file stream connected to a temporary file
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_tmpfile(3)
 *      opens a temporary file using mkstemp(3), returning a
 *      xt_ff_t pointer tied to the file descriptor created by
 *      mkstemp(3).  The file is opened for both reading and writing.
 *      This function is analogous to tmpfile(3).
 *  
 *  Arguments:
 *      None.
 *
 *  Returns:
 *      Pointer to a xt_ff_t structure on success, NULL on failure.
 *
 *  Examples:
 *      xt_ff_t *fp = xt_ff_tmpfile(3);
 *      
 *  See also:
 *      tmpfile(3), mkstemp(3).
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-09-02  Jason Bacon Begin
 ***************************************************************************/

xt_ff_t *xt_ff_mkstemp(char template[])

{
    // FIXME: See tmpfile() man page and replicate behavior
    int     fd,
	    flags = O_RDWR|O_CREAT|O_TRUNC; // See mkstemp(3)

    if ( (fd = mkstemp(template)) == -1 )
	return NULL;
    
    return xt_ff_dopen(fd, flags);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_read() - Read a fixed number of bytes from a fast file stream
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_read(3)
 *      reads a fixed number of bytes (size * nmemb) from stream,
 *      storing them at address ptr, which should point to an object
 *      (if nmemb == 1) or array of "nmemb" objects of size "size".
 *  
 *  Arguments:
 *      stream  Pointer to an xt_ff_t structure
 *      ptr     Memory location where data read from stream will be stored
 *      size    Size of one object being read
 *      nmemb   Number of objects to read
 *
 *  Returns:
 *      The number of objects (not bytes) successfully read
 *
 *  Examples:
 *      my_type_t   list[NUM_OBJECTS];
 *      xt_ff_t     *stream;
 *
 *      stream = xt_ff_open("myfile", O_RDONLY);
 *      xt_ff_read(stream, list, sizeof(my_type_t), NUM_OBJECTS);
 *
 *  See also:
 *      xf_ff_write(3), xt_ff_open(3), read(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-09-02  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_ff_read(xt_ff_t *stream, void * restrict ptr,
		   size_t size, size_t nmemb)

{
    // FIXME: This is a naive design chosen for simplicity
    // to ensure initial correctness.  Think about potentially more
    // efficient designs.
    int     ch;
    char    *ch_ptr;
    size_t  bytes_desired = size * nmemb, c;
    
    for (c = 0, ch_ptr = ptr;
	 (c < bytes_desired) && ((ch = XT_FF_GETC(stream)) != EOF); ++c)
	*ch_ptr++ = ch;
    
    return c / size;    // Return number of objects read
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_write() - Write a fixed number of bytes to a fast file stream
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_write(3)
 *      writes a fixed number of bytes (size * nmemb) to stream
 *      from address ptr, which should point to an object
 *      (if nmemb == 1) or array of "nmemb" objects of size "size".
 *  
 *  Arguments:
 *      stream  Pointer to an xt_ff_t structure
 *      ptr     Memory location from which data are written
 *      size    Size of one object being read
 *      nmemb   Number of objects to read
 *
 *  Returns:
 *      The number of objects (not bytes) successfully written
 *
 *  Examples:
 *      my_type_t   list[NUM_OBJECTS];
 *      xt_ff_t     *stream;
 *
 *      stream = xt_ff_open("myfile", O_RDONLY);
 *      xt_ff_write(stream, list, sizeof(my_type_t), NUM_OBJECTS);
 *
 *  See also:
 *      xt_ff_read(2), xt_ff_open(3), write(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-02-06  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_ff_write(xt_ff_t *stream, void * ptr,
		   size_t size, size_t nmemb)

{
    // FIXME: This is a naive design chosen for simplicity
    // to ensure initial correctness.  Think about potentially more
    // efficient designs.
    char    *ch_ptr;
    size_t  bytes_desired = size * nmemb, c;
    
    for (c = 0, ch_ptr = ptr; c < bytes_desired; ++c)
	XT_FF_PUTC(stream, *ch_ptr++);
    
    return c / size;    // Return number of objects completely written
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_seeko() - Reposition file descriptor under a fast file stream
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_seeko(3)
 *      repositions the file descriptor underlying stream to any
 *      position within the file, using lseek(2).  It is analogous
 *      to fseeko(3).  The stream must refer to a regular file, as
 *      pipes are not generally seekable.
 *  
 *  Arguments:
 *      stream  Pointer to a xt_ff_t structure
 *      offset  New position in bytes forward or backward from whence
 *              (positive or negative)
 *      whence  SEEK_SET (beginning of file), SEEK_CUR (current position),
 *              or SEEK_END (end of file)
 *
 *  Returns:
 *      0 on success, -1 on failure (errno set)
 *
 *  Examples:
 *      // Reposition so that 10th byte in the file is the next one read
 *      xt_ff_seeko(stream, 10, SEEK_SET);
 *
 *  See also:
 *      fseek(3), lseek(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-09-02  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_seeko(xt_ff_t *stream, off_t offset, int whence)

{
    int     ch;
    
    // FIXME: This is a naive design chosen for simplicity
    // to ensure initial correctness.  Think about potentially more
    // efficient designs.  In particular, don't purge the input buffer
    // if the seek is within buffered data.
    
    if ( stream->flags & (O_WRONLY|O_RDWR|O_APPEND) )
	xt_ff_flush(stream);
    
    if ( lseek(xt_ff_get_fd(stream), offset, whence) == offset )
    {
	ch = _xt_ff_fillbuff(stream);
	xt_ff_ungetc(stream, ch);
	return 0;   // Success
    }
    else
	return -1;  // lseek() sets errno
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_ff_rewind() - Reposition file descriptor to beginning of file
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ff_rewind(stream)
 *      repositions the underlying file descriptor to the beginning
 *      of the file.  It is equivalent to xt_ff_seeko(stream, 0, SEEK_SET).
 *  
 *  Arguments:
 *      stream  xt_ff_t pointer referring to the file
 *
 *  Returns:
 *      0 on success, -1 on failure (errno set)
 *
 *  See also:
 *      xt_ff_seeko(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-09-02  Jason Bacon Begin
 ***************************************************************************/

int     xt_ff_rewind(xt_ff_t *stream)

{
    return xt_ff_seeko(stream, 0, SEEK_SET);
}
