#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "mem.h"
#include "fast-file.h"


/*
 *  Non-API function for completing stream initialization for ffopen()
 *  and ffdopen()
 */

ffile_t *ff_init_stream(ffile_t *stream)

{
    struct stat st;
    
    // Get optimal block size for the underlying filesystem
    if ( fstat(stream->fd, &st) != 0 )
    {
	free(stream);
	fprintf(stderr, "ffopen(): Could not stat fd %d.\n", stream->fd);
	return NULL;
    }
    stream->block_size = st.st_blksize;
    //fprintf(stderr, "Block size = %zd\n", stream->block_size);
    // Add space for a null byte
    stream->buff_size = XT_FAST_FILE_UNGETC_MAX + stream->block_size + 1;
    if ( (stream->buff = xt_malloc(1, stream->buff_size)) == NULL )
    {
	fputs("ff_init_stream(): Could not allocate buffer.\n", stderr);
	free(stream);
	return NULL;
    }
    stream->start = stream->buff + XT_FAST_FILE_UNGETC_MAX;
    stream->bytes_read = 0;
    stream->c = 0;
    return stream;
}


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
    stream->flags = flags;

    return ff_init_stream(stream);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <fcntl.h>
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffdopen()
 *      initializes a ffile_t stream, much as fdopen() does for a FILE
 *      stream.  Unlike fdopen(), ffdopen() takes the same bit mask
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
 *      fd          Open file descriptor to which stream is attached
 *      flags       Bit flags passed to open(3)
 *
 *  Returns:
 *      A pointer to a ffile_t object on success, NULL on failure
 *
 *  Examples:
 *      ffile_t *stream;
 *      char    *filename;
 *      int     fd;
 *      
 *      fd = open(filename, O_RDONLY);
 *      stream = ffdopen(fd, O_RDONLY);
 *
 *  See also:
 *      ffopen(3), open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-14  Jason Bacon Begin
 ***************************************************************************/

ffile_t *ffdopen(int fd, int flags)

{
    ffile_t     *stream;
    
    if ( (stream = xt_malloc(1, sizeof(*stream))) == NULL )
	return NULL;
    stream->fd = fd;
    stream->flags = flags;

    return ff_init_stream(stream);
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


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffstdin()
 *      is a simple wrapper function for connecting file descriptor 0
 *      to an ffile_t object using ffdopen(3).  This is useful for
 *      high-performance filter programs, where using the traditional
 *      FILE *stdin would cause a bottleneck.
 *  
 *  Arguments:
 *      None
 *
 *  Returns:
 *      Pointer to an ffile_t object if successful, NULL otherwise
 *
 *  Examples:
 *      ffile_t *stream;
 *
 *      // "-" as a filename argument traditionally indicates stdin
 *      if ( strcmp(argv[arg], "-") == 0 )
 *          stream = ffstdin();
 *      else
 *          stream = ffopen(argv[arg], O_RDONLY);
 *
 *  See also:
 *      ffopen(3), ffdopen(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

ffile_t *ffstdin()

{
    return ffdopen(0, O_RDONLY);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffstdout()
 *      is a simple wrapper function for connecting file descriptor 1
 *      to an ffile_t object using ffdopen(3).  This is useful for
 *      high-performance filter programs, where using the traditional
 *      FILE *stdout would cause a bottleneck.
 *  
 *  Arguments:
 *      None
 *
 *  Returns:
 *      Pointer to an ffile_t object if successful, NULL otherwise
 *
 *  Examples:
 *      ffile_t *stream;
 *
 *      // "-" as a filename argument traditionally indicates stdout
 *      if ( strcmp(argv[arg], "-") == 0 )
 *          stream = ffstdout();
 *      else
 *          stream = ffopen(argv[arg], O_WRONLY|O_CREAT|O_TRUNC);
 *
 *  See also:
 *      ffopen(3), ffdopen(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

ffile_t *ffstdout()

{
    return ffdopen(1, O_WRONLY|O_APPEND);
}


ffile_t *fpopen(const char *cmd, int flags)

{
    pid_t   pid;
    ffile_t *stream = NULL;

    if ( (pid = fork()) == 0 )
    {
	if ( flags & O_RDONLY )
	{
	    // Child runs command and writes to pipe
	    // close(1)
	    // exec()
	}
	else
	{
	    // Child runs command and reads from pipe
	    // close(0)
	    // exec()
	}
    }
    else
    {
	if ( flags & O_RDONLY )
	{
	    // Parent writes to child via pipe
	    // close(1)
	}
	else
	{
	    // Parent reads from child via pipe
	    // close(0)
	}

	// Set pid in ffile_t stream for waitpid() in fpclose()
    }
    return stream;
}


int     fpclose(ffile_t *stream)

{
    // Wait for child to exit
    // return wait4()   // Compatibility with pclose()
    return 0;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      Open a raw data file using fopen() or a gzipped, bzipped, or
 *      xzipped file using popen().  Must be used in conjunction with
 *      xt_fclose() to ensure that fclose() or fpclose() is called where
 *      appropriate.
 *
 *  Arguments:
 *      filename:   Name of the file to be opened
 *      mode:       "r" or "w", passed to fopen() or popen()
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

ffile_t *xt_ffopen(const char *filename, int flags)

{
    char    *ext = strrchr(filename, '.'),
	    cmd[XT_CMD_MAX_CHARS + 1];
    
    if ( ext == NULL )
    {
	// FIXME: Use __FUNCTION__ in all such messages
	fprintf(stderr, "%s(): No filename extension on %s.\n",
		__FUNCTION__, filename);
	return NULL;
    }

    if ( flags & O_RDONLY )
    {
	if ( strcmp(ext, ".gz") == 0 )
	{
// Big Sur zcat requires a .Z extension and CentOS 7 lacks gzcat
#ifdef __APPLE__
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzcat %s", filename);
#else
	    snprintf(cmd, XT_CMD_MAX_CHARS, "zcat %s", filename);
#endif
	    return fpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzcat %s", filename);
	    return fpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xzcat %s", filename);
	    return fpopen(cmd, flags);
	}
	else
	    return ffopen(filename, flags);
    }
    else    // O_WRONLY
    {
	if ( strcmp(ext, ".gz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzip -c > %s", filename);
	    return fpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzip2 -c > %s", filename);
	    return fpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xz -c > %s", filename);
	    return fpopen(cmd, flags);
	}
	else
	    return ffopen(filename, flags);
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      Close a FILE stream with fclose() or fpclose() as appropriate.
 *      Automatically determines the proper close function to call using
 *      S_ISFIFO on the stream stat structure.
 *
 *  Arguments:
 *      stream: The FILE structure to be closed
 *
 *  Returns:
 *      The value returned by fclose() or fpclose()
 *
 *  See also:
 *      fopen(3), popen(3), gzip(1), bzip2(1), xz(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-10  Jason Bacon Begin
 ***************************************************************************/

int     xt_ffclose(ffile_t *stream)

{
    struct stat stat;
    
    fstat(stream->fd, &stat);
    if ( S_ISFIFO(stat.st_mode) )
	return fpclose(stream);
    else
	return ffclose(stream);
}
