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

// Added 2022-02-03
#define fgetline(fp, buff, maxlen) \
	    _Pragma("message(\"fgetline() is deprecated.  Use xt_fgetline().\")") \
	    xt_fgetline(fp, buff, maxlen)

#define valid_extension(filename, valid_ext) \
	    _Pragma("message(\"valid_extension() is deprecated.  Use xt_valid_extension().\")") \
	    xt_valid_extension(filename, valid_ext)

#define fast_cp(source, dest) \
	    _Pragma("message(\"fast_cp() is deprecated.  Use xt_fast_cp().\")") \
	    xt_fast_cp(source, dest)

#define file_mod_cmp(file1, file2) \
	    _Pragma("message(\"file_mod_cmp() is deprecated.  Use xt_file_mod_cmp().\")") \
	    xt_file_mod_cmp(file1, file2)

#define fd_purge(fd) \
	    _Pragma("message(\"fd_purge() is deprecated.  Use xt_fd_purge().\")") \
	    xt_fd_purge(fd)

#define get_home_dir(dir, maxlen) \
	    _Pragma("message(\"get_home_dir() is deprecated.  Use xt_get_home_dir().\")") \
	    xt_get_home_dir(dir, maxlen)

#define rmkdir(path, mode) \
	    _Pragma("message(\"rmkdir() is deprecated.  Use xt_rmkdir().\")") \
	    xt_rmkdir(path, mode)

/* valid-extension.c */
bool xt_valid_extension(const char *filename, const char *valid_ext);

/* fast-cp.c */
int xt_fast_cp(const char *source, const char *dest); //__attribute__((deprecated("Use xt_fast_cp()")));

/* file-mod-cmp.c */
int xt_file_mod_cmp(const char *file1, const char *file2);

/* fd-purge.c */
void xt_fd_purge(int fd);

/* fgetline.c */
size_t xt_fgetline(FILE *fp, char *buff, size_t maxlen);

/* get-home-dir.c */
char *xt_get_home_dir(char *dir, size_t maxlen);

/* rmkdir.c */
int xt_rmkdir(const char *path, mode_t mode);

/* xt-file.c */
FILE *xt_fopen(const char *filename, const char *mode);
int xt_fclose(FILE *stream);
ssize_t xt_inhale_strings(FILE *stream, char ***list);
int xt_read_line_malloc(FILE *stream, char **buff, size_t *buff_size, size_t *len);

#endif // _XTEND_FILE_H_
