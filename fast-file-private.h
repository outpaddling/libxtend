#ifndef _XTEND_FAST_FILE_PRIVATE_H_
#define _XTEND_FAST_FILE_PRIVATE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef LIBXTEND_LIBRARY_BUILD
#pragma message("Most programs should not include fast-file-private.h.  " \
		"Please use the official API in fast-file.h unless you really \n" \
		"need the added performance of XT_FF_GETC() or XT_FF_PUTC() " \
		"over xt_ff_getc() / xt_ff_putc().")
#endif

#ifndef _FCNTL_H_
#include <fcntl.h>  // pid_t
#endif

struct xt_fast_file
{
    unsigned char   *buff;
    unsigned char   *start_ptr;
    ssize_t         bytes_read;
    ssize_t         buff_index;
    ssize_t         disk_block_size;
    ssize_t         buff_size;
    int             fd;
    int             flags;
    pid_t           child_pid;
};


/*
 *  Most programs should not use this header, as it exposes xt_ff_t,
 *  which is meant to be opaque.
 *  However, these macro equivalents of xt_ff_getc() and xt_ff_putc() show
 *  significantly lower CPU usage.  We bend the rules of opaque structures
 *  by installing this header for the sake of those who want the added
 *  performance, but we only document the use of the official API in
 *  xt_ffile.h, and the functions xt_ff_getc(), and xt_ff_putc().  The
 *  functions are significantly faster than using getc() and putc() with
 *  FILE on most systems, and the macros provide a much smaller additional
 *  gain.
 */

#define XT_FF_GETC(stream) \
    ((stream)->buff_index == (stream)->bytes_read \
	? _xt_ff_fillbuff(stream) \
	: (stream)->start_ptr[(stream)->buff_index++])

#define XT_FF_PUTC(stream, ch) \
    ((stream)->buff_index == (stream)->disk_block_size ? \
	write((stream)->fd, (stream)->start_ptr, (stream)->disk_block_size) != (stream)->disk_block_size ? \
	    EOF \
	: ((stream)->buff_index = 0, (stream)->start_ptr[(stream)->buff_index++] = ch) \
    : ((stream)->start_ptr[(stream)->buff_index++] = ch))

#include "fast-file.h"

#ifdef  __cplusplus
}
#endif

#endif
