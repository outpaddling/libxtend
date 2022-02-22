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

#ifndef _XT_COMMON_H_
#include "common.h"
#endif

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
ssize_t xt_inhale_strings(FILE *stream, char ***list);
int xt_read_line_malloc(FILE *stream, char **buff, size_t *buff_size, size_t *len);


#endif // _XTEND_FILE_H_
