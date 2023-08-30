#ifndef _XTEND_FAST_FILE_PRIVATE_H_
#define _XTEND_FAST_FILE_PRIVATE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _FCNTL_H_
#include <fcntl.h>  // pid_t
#endif

typedef struct
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
}   xt_ffile_t;


/*
 *  Most programs should not use this header, as it exposes xt_ffile_t,
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

#define XT_FF_GETC(st) \
    ((st)->buff_index == (st)->bytes_read ? \
	((st)->bytes_read = read((st)->fd, (st)->start_ptr, (st)->disk_block_size)) == 0 ? \
	    EOF \
	: ((st)->buff_index = 0, (st)->start_ptr[(st)->buff_index++]) \
    : (st)->start_ptr[(st)->buff_index++])

#define XT_FF_PUTC(ch, st) \
    ((st)->buff_index == (st)->disk_block_size ? \
	write((st)->fd, (st)->start_ptr, (st)->disk_block_size) != (st)->disk_block_size ? \
	    EOF \
	: ((st)->buff_index = 0, (st)->start_ptr[(st)->buff_index++] = ch) \
    : ((st)->start_ptr[(st)->buff_index++] = ch))

#include "fast-file.h"

#ifdef  __cplusplus
}
#endif

#endif
