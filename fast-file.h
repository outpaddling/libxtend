#ifndef _XTEND_FAST_FILE_H_
#define _XTEND_FAST_FILE_H_

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
 *  These macro implementations of ffgetc() and ffputc() show significantly
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
}   ffile_t;

/* fast-file.c */
ffile_t *ff_init_stream(ffile_t *stream);
ffile_t *ffopen(const char *filename, int flags);
ffile_t *ffdopen(int fd, int flags);
int ffgetc(ffile_t *stream);
int ffputc(int ch, ffile_t *stream);
int ffclose(ffile_t *stream);
int ffungetc(int ch, ffile_t *stream);
ffile_t *ffstdin(void);
ffile_t *ffstdout(void);
ffile_t *ffpopen(const char *cmd, int flags);
int ffpclose(ffile_t *stream);
ffile_t *xt_ffopen(const char *filename, int flags);
int xt_ffclose(ffile_t *stream);
int ffprintf(ffile_t *stream, const char *format, ...);

#endif  // _XTEND_FAST_FILE_H_
