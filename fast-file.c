#ifdef __linux__
#define _GNU_SOURCE     // vasprintf(), must come before stdio.h
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdarg.h>
#include "mem.h"
#include "proc.h"
#include "fast-file.h"
#include "common.h"

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
 *
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
 *
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
	 *  Move last part of buffer to ffungetc() region.  Only the last
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
    //putchar(ch);
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
    {
	//fprintf(stderr, "ffclose() flushing output...\n");
	//stream->start[stream->c] = '\0';
	//fputs((char *)stream->start, stderr);
	write(stream->fd, stream->start, stream->c);
    }
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
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
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
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
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


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffpopen(3)
 *      creates a pipe for interprocess communication, runs the specified
 *      command, connecting the command's standard input or standard
 *      output to the pipe, and returning a pointer to a ffile_t object
 *      connected to the other end.
 *
 *      It behaves much like popen(3), except that it returns a fast-file
 *      fffile_t pointer rather than a standard I/O FILE pointer, and
 *      accepts a full set of open(3) flags rather than the fopen(3)
 *      type strings "r", "w", etc.
 *
 *      This allows the calling program to spawn a child process
 *      and read its standard output or write to its standard input as
 *      easily as reading or writing a file.
 *
 *      The stream should be closed with ffpclose(3) rather than ffclose(3)
 *      in order to wait for the child process to complete and return its
 *      exit status.
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      cmd     Full command to execute as the child, passed to sh(1)
 *      flags   Open mode flags passed to open(3)
 *
 *  Returns:
 *      Pointer to a ffile_t object on success, NULL otherwise
 *
 *  Examples:
 *      ffile_t *instream;
 *
 *      if ( (instream = ffpopen("xzcat file.xz", O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Failed to read xzcat file.xz.\n");
 *          exit(EX_NOINPUT);
 *      }
 *
 *      ffpclose(instream);
 *
 *  See also:
 *      ffopen(3), ffpclose(3), popen(3), open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

ffile_t *ffpopen(const char *cmd, int flags)

{
    pid_t   pid;
    int     fd[2];
    ffile_t *stream = NULL;
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
		return NULL;    // Should not be reached
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
		return NULL;    // Should not be reached
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
		if ( (stream = ffdopen(fd[0], O_RDONLY)) == NULL )
		    return NULL;
	    }
	    else
	    {
		// Parent writes to child via pipe
		// Readers won't get EOF until last descriptor is closed
		// so don't leave this lying around
		close(fd[0]);   // Not used by parent
		if ( (stream = ffdopen(fd[1], O_WRONLY)) == NULL )
		    return NULL;
	    }
    
	    // Set pid in ffile_t stream for waitpid() in ffpclose()
	    stream->child_pid = pid;
	    return stream;
	}
    }
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
 *      .B ffpclose(3)
 *      closes a stream opened by ffpopen(3), and
 *      waits for the child process to complete and returns its
 *      exit status.
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  ffile_t stream opened by ffpopen(3)
 *
 *  Returns:
 *      Exit status of the child process spawned by ffpopen(3), or -1 on error
 *
 *  Examples:
 *      ffile_t *instream;
 *
 *      if ( (instream = ffpopen("xzcat file.xz", O_RDONLY)) == NULL )
 *      {
 *          fprintf(stderr, "Failed to read xzcat file.xz.\n");
 *          exit(EX_NOINPUT);
 *      }
 *
 *      ffpclose(instream);
 *
 *  See also:
 *      ffopen(3), ffpclose(3), popen(3), open(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

int     ffpclose(ffile_t *stream)

{
    int     status = 0;
    pid_t   pid = stream->child_pid;
    
    if ( pid == 0 )
    {
	fprintf(stderr, "%s(): No child PID available.  Was the stream opened with ffpopen()?\n",
		__FUNCTION__);
	return -1;
    }
    
    ffclose(stream);
    
    // Compatibility with pclose()
    waitpid(pid, &status, 0);
    //fprintf(stderr, "Back from waitpid().\n");
    
    return status;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_ffopen(3)
 *      opens a raw data file using fopen() or a gzipped, bzipped, or
 *      xzipped file using popen(), returning a pointer to a ffile_t
 *      stream.  Must be used in conjunction with
 *      xt_ffclose() to ensure that ffclose() or ffpclose() is called where
 *      appropriate.
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
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

    //fprintf(stderr, "flags = %x\n", flags);
    if ( flags == O_RDONLY )    // O_RDONLY = 0x0, no bits set
    {
	//fprintf(stderr, "Reading from %s...\n", filename);
	if ( strcmp(ext, ".gz") == 0 )
	{
// Big Sur zcat requires a .Z extension and CentOS 7 lacks gzcat
#ifdef __APPLE__
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzcat %s", filename);
#else
	    snprintf(cmd, XT_CMD_MAX_CHARS, "zcat %s", filename);
#endif
	    return ffpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzcat %s", filename);
	    return ffpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xzcat %s", filename);
	    return ffpopen(cmd, flags);
	}
	else
	    return ffopen(filename, flags);
    }
    else    // O_WRONLY
    {
	//fprintf(stderr, "Writing to %s...\n", filename);
	if ( strcmp(ext, ".gz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzip -c > %s", filename);
	    return ffpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzip2 -c > %s", filename);
	    return ffpopen(cmd, flags);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xz -c > %s", filename);
	    return ffpopen(cmd, flags);
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
 *      .B xt_ffclose(3)
 *      closes a ffile_t stream with ffclose() or ffpclose() as appropriate.
 *      Automatically determines the proper close function to call using
 *      S_ISFIFO on the stream stat structure.
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *
 *  Arguments:
 *      stream: The FILE structure to be closed
 *
 *  Returns:
 *      The value returned by ffclose() or ffpclose()
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
	return ffpclose(stream);
    else
	return ffclose(stream);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffprintf(3)
 *      writes formatted data to a ffile_t stream the same was as
 *      fprintf(3) writes to a FILE stream.
 *
 *      The ffile_t system is simpler than and several times as
 *      fast as FILE on typical systems.  It is intended for processing
 *      large files character-by-character, where low-level block I/O
 *      is not convenient, but FILE I/O causes a bottleneck.
 *  
 *  Arguments:
 *      stream  Pointer to an ffile_t object opened by ffopen(3)
 *      format  Format string indicating how remaining arguments are printed
 *
 *  Returns:
 *      The number of characters written
 *
 *  Examples:
 *      ffile_t *stream;
 *      int     count = 1;
 *
 *      if ( (stream = ffopen(filename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Could not open %s.\n", filename);
 *          exit(EX_CANTCREAT);
 *      }
 *      ffprintf(stream, "%d\n", count);
 *      ffclose(stream);
 *
 *  See also:
 *      fprintf(3), ffopen(3), ffclose(3), ffputc(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-19  Jason Bacon Begin
 ***************************************************************************/

int     ffprintf(ffile_t *stream, const char *format, ...)

{
    va_list ap;
    char    *buff;
    int     chars_printed, c;
    
    va_start(ap, format);
    chars_printed = vasprintf(&buff, format, ap);
    for (c = 0; buff[c] != '\0'; ++c)
	FFPUTC(buff[c], stream);
    free(buff);
    return chars_printed;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/fast-file.h>
 *      -lxtend
 *
 *  Description:
 *      .B ffread_line_malloc()
 *      reads a single line of text (up to the next newline or EOF)
 *      from stream, allocating and/or extending the provided buffer if
 *      needed.
 *  
 *  Arguments:
 *      stream:     ffile_t stream from which field is read
 *      buff:       Character buffer into which field is copied
 *      buff_size:  Size of the array passed to buff
 *      len:        Pointer to a variable which will receive the field length
 *
 *  Returns:
 *      Delimiter ending the read: either newline or EOF
 *
 *  Examples:
 *      ffile_t *stream;
 *      char    *buff;
 *      size_t  buff_len, len;
 *
 *      while ( ffile_read_line_malloc(stream, buff, &buff_len, &len) != EOF )
 *      {
 *      }
 *
 *  See also:
 *      dsv_read_field_malloc(3), ffgetc(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-20  Jason Bacon Begin
 ***************************************************************************/

int     ffread_line_malloc(ffile_t *stream, char **buff, size_t *buff_size,
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
    
    for (c = 0; ( ((ch = FFGETC(stream)) != '\n') && (ch != EOF) ); ++c)
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
