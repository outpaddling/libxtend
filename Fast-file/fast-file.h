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
	((st)->bytes_read = read((st)->fd, (st)->buff, (st)->block_size)) == 0 ? \
	    EOF \
	: ((st)->c = 0, (st)->buff[(st)->c++]) \
    : (st)->buff[(st)->c++])

#define FFPUTC(ch, st) \
    ((st)->c == (st)->block_size ? \
	write((st)->fd, (st)->buff, (st)->block_size) != (st)->block_size ? \
	    EOF \
	: ((st)->c = 0, (st)->buff[(st)->c++] = ch) \
    : ((st)->buff[(st)->c++] = ch))

#define XT_FAST_FILE_UNGETC_MAX 64

typedef struct
{
    unsigned char   *buff;
    unsigned char   *start;
    ssize_t         bytes_read;
    ssize_t         c;
    size_t          block_size;
    size_t          buff_size;
    int             fd;
    int             flags;
}   ffile_t;

/* fast-file.c */
ffile_t *ffopen(const char *filename, int flags);
int ffgetc(ffile_t *stream);
int ffputc(int ch, ffile_t *stream);
int ffclose(ffile_t *stream);

#endif  // _XTEND_FAST_FILE_H_
