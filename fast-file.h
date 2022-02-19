#ifndef _XTEND_FAST_FILE_H_
#define _XTEND_FAST_FILE_H_

#ifndef _FCNTL_H_
#include <fcntl.h>
#endif

#ifndef _UNISTD_H_
#include <unistd.h>
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

#define XT_FAST_FILE_UNGETC_MAX 16L

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
}   ffile_t;

/* fast-file.c */
ffile_t *ffopen(const char *filename, int flags);
ffile_t *ffdopen(int fd, int flags);
ffile_t *ffstdin(void);
ffile_t *ffstdout(void);
int ffgetc(ffile_t *stream);
int ffputc(int ch, ffile_t *stream);
int ffungetc(int ch, ffile_t *stream);
int ffclose(ffile_t *stream);

#endif  // _XTEND_FAST_FILE_H_
