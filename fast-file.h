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
xt_ff_t *xt_ff_init_stream(xt_ff_t *stream);
xt_ff_t *xt_ff_open_raw(const char *filename, int flags);
xt_ff_t *xt_ff_dopen(int fd, int flags);
int xt_ff_fillbuff(xt_ff_t *stream);
int xt_ff_getc(xt_ff_t *stream);
int xt_ff_putc(xt_ff_t *stream, int ch);
int xt_ff_close_raw(xt_ff_t *stream);
int xt_ff_ungetc(xt_ff_t *stream, int ch);
xt_ff_t *xt_ff_stdin(void);
xt_ff_t *xt_ff_stdout(void);
xt_ff_t *xt_ff_popen(const char *cmd, int flags);
int xt_ff_pclose(xt_ff_t *stream);
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

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_FAST_FILE_H_
