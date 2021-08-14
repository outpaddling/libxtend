#ifndef _XTEND_FILE_H_
#define _XTEND_FILE_H_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _SYS_STAT_H_
#include <sys/stat.h>   // mode_t on Darwin
#endif

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

// FIXME: Return this instead of EOF in dsv_read*()
// Don't trust that EOF is -1 on all platforms
#define XT_READ_EOF             -1
#define XT_READ_MALLOC_FAILED   -2
#define XT_READ_BUFF_OVERFLOW   -3

#define XT_CMD_MAX_CHARS    4096

/* valid-extension.c */
bool valid_extension(const char *filename, const char *valid_ext);

/* fast-cp.c */
int fast_cp(const char *source, const char *dest);

/* file-mod-cmp.c */
int file_mod_cmp(const char *file1, const char *file2);

/* fd-purge.c */
void fd_purge(int fd);

/* fgetline.c */
size_t fgetline(FILE *fp, char *buff, size_t maxlen);

/* get-home-dir.c */
char *get_home_dir(char *dir, size_t maxlen);

/* rmkdir.c */
int rmkdir(const char *path, mode_t mode);

/* xt-file.c */
FILE *xt_fopen(const char *filename, const char *mode);
int xt_fclose(FILE *stream);

#endif // _XTEND_FILE_H_
