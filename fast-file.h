#ifndef _XTEND_FAST_FILE_H_
#define _XTEND_FAST_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UNISTD_H_
#include <unistd.h>
#endif

#ifndef _XT_COMMON_H_
#include "common.h"
#endif

#define XT_FAST_FILE_UNGETC_MAX 64L
#define XT_FAST_FILE_MAX_ARGS   128

#define FFILE_INIT  { NULL, NULL, 0, 0, 0, 0, 0, 0, 0 }

// Before prototypes and including generated headers
typedef struct xt_fast_file xt_ff_t;

#include "fast-file-rvs.h"
#include "fast-file-accessors.h"
#include "fast-file-mutators.h"

/* fast-file.c */
xt_ff_t *_xt_ff_init_stream(xt_ff_t *stream);
xt_ff_t *_xt_ff_raw_open(const char *filename, int flags);
xt_ff_t *xt_ff_dopen(int fd, int flags);
int _xt_ff_fillbuff(xt_ff_t *stream);
int _xt_ff_raw_close(xt_ff_t *stream);
int xt_ff_ungetc(xt_ff_t *stream, int ch);
xt_ff_t *xt_ff_stdin(void);
xt_ff_t *xt_ff_stdout(void);
xt_ff_t *xt_ff_popen(const char *cmd, int flags);
int _xt_ff_pclose(xt_ff_t *stream);
xt_ff_t *xt_ff_open(const char *filename, int flags);
int xt_ff_close(xt_ff_t *stream);
int xt_ff_printf(xt_ff_t *stream, const char *format, ...);
int xt_ff_read_line_malloc(xt_ff_t *stream, char **buff, size_t *buff_size, size_t *len);
int xt_ff_puts(xt_ff_t *stream, const char *string);
char *xt_ff_gets(xt_ff_t *stream, char *string, size_t size);
xt_ff_t *xt_ff_tmpfile(void);
size_t xt_ff_read(xt_ff_t *stream, void * restrict ptr, size_t size, size_t nmemb);
int xt_ff_seeko(xt_ff_t *stream, off_t offset, int whence);
int xt_ff_rewind(xt_ff_t *stream);


/*
 *  It's normally a bad idea to define functions in a header file, but
 *  this ensures that xt_ff_getc() and xt_ff_putc() can be fully inlined,
 *  even if link-time optimizations are not available.
 */

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
 *          fprintf(stderr, "Cannot open %s for reading.\n", filename);
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

static inline int     xt_ff_getc(xt_ff_t *stream)

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
 *          fprintf(stderr, "Cannot open %s for reading.\n", infilename);
 *          exit(EX_NOINPUT);
 *      }
 *      if ( (outstream = xt_ff_open(outfilename, O_WRONLY|O_CREAT|O_TRUNC)) == NULL )
 *      {
 *          fprintf(stderr, "Cannot open %s for writing.\n", outfilename);
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

static inline int     xt_ff_putc(xt_ff_t *stream, int ch)

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

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_FAST_FILE_H_
