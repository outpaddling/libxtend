#ifndef _XTEND_STRING_H_
#define _XTEND_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__
#define strlcpy(dest,src,len)   xt_strlcpy(dest,src,len)
#define strlcat(dest,src,len)   xt_strlcat(dest,src,len)
#endif

#ifndef _STDIO_H_
#include <stdio.h>  // size_t
#endif

#ifndef _INTTYPES_H_
#include <inttypes.h>
#endif

/* string.c */
size_t xt_strlupper(char *dest, const char *src, size_t dest_size);
size_t xt_strupper(char *str);
size_t xt_strllower(char *dest, const char *src, size_t dest_size);
size_t xt_strlower(char *str);
size_t xt_str_argv_cat(char *string, char *argv[], size_t first_arg, size_t string_buff_size);
int xt_strblank(const char *string);
int xt_strisint(const char *string, int base);
int xt_strisreal(const char *string);
char *xt_strlbasecpy(char *dest, const char *dest_base, const char *src, size_t dstsize);
int xt_strptrcmp(const char **p1, const char **p2);
int xt_strptrcasecmp(const char **p1, const char **p2);
int xt_strshellcpy(char *dest, const char *src, size_t dest_len);
size_t xt_strsqueeze(char *dest, const char *src, size_t dstsize);
void xt_strtr(char *string, const char *from, const char *to, int flags);
void xt_strtrim(char *string, const char *fat);
char *xt_strviscpy(unsigned char *dest, const unsigned char *src, size_t maxlen);
char *xt_ltostrn(char string[], long val, unsigned base, size_t maxlen);
uint64_t xt_str2u64(const char *str);
int xt_strsplit(char *string, char ***array, const char *sep);

/* strlcpy.c */
size_t  xt_strlcpy(char * restrict dest, const char * restrict src,
		   size_t dstsize);

/* strlcat.c */
size_t  xt_strlcat(char * restrict dest, const char * restrict src,
		   size_t dstsize);

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_STRING_H_
