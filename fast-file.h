#ifndef _XTEND_FAST_FILE_H_
#define _XTEND_FAST_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _FCNTL_H_
#include <fcntl.h>
#endif

#ifndef _UNISTD_H_
#include <unistd.h>
#endif

#ifndef _XT_COMMON_H_
#include "common.h"
#endif

/*
 *  These macro implementations of xt_ff_getc() and xt_ff_putc() show significantly
 *  lower CPU usage.
 */

#define FFGETC(st) \
    ((st)->c == (st)->bytes_read ? \
	((st)->bytes_read = read((st)->fd, (st)->start, (st)->block_size)) == 0 ? \
	    EOF \
	: ((st)->c = 0, (st)->start[(st)->c++]) \
    : (st)->start[(st)->c++])

#define FFPUTC(ch, st) \
    ((st)->c == (st)->block_size ? \
	write((st)->fd, (st)->start, (st)->block_size) != (st)->block_size ? \
	    EOF \
	: ((st)->c = 0, (st)->start[(st)->c++] = ch) \
    : ((st)->start[(st)->c++] = ch))

#define XT_FAST_FILE_UNGETC_MAX 64L
#define XT_FAST_FILE_MAX_ARGS   128

#define FFILE_INIT  { NULL, NULL, 0, 0, 0, 0, 0, 0, 0 }

typedef struct
{
    unsigned char   *buff;
    unsigned char   *start;
    ssize_t         bytes_read;
    ssize_t         c;
    ssize_t         block_size;
    ssize_t         buff_size;
    int             fd;
    int             flags;
    pid_t           child_pid;
}   xt_ffile_t;

/* fast-file.c */
xt_ffile_t *xt_ff_init_stream(xt_ffile_t *stream);
xt_ffile_t *xt_ff_open_raw(const char *filename, int flags);
xt_ffile_t *xt_ff_dopen(int fd, int flags);
int xt_ff_getc(xt_ffile_t *stream);
int xt_ff_putc(int ch, xt_ffile_t *stream);
int xt_ff_close_raw(xt_ffile_t *stream);
int xt_ff_ungetc(int ch, xt_ffile_t *stream);
xt_ffile_t *xt_ff_stdin(void);
xt_ffile_t *xt_ff_stdout(void);
xt_ffile_t *xt_ff_popen(const char *cmd, int flags);
int xt_ff_pclose(xt_ffile_t *stream);
xt_ffile_t *xt_ff_open(const char *filename, int flags);
int xt_ff_close(xt_ffile_t *stream);
int xt_ff_printf(xt_ffile_t *stream, const char *format, ...);
int xt_ff_read_line_malloc(xt_ffile_t *stream, char **buff, size_t *buff_size, size_t *len);
int xt_ff_puts(const char *string, xt_ffile_t *stream);
char *xt_ff_gets(char *string, size_t size, xt_ffile_t *stream);

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_FAST_FILE_H_
