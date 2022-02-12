#ifndef _XTEND_STRING_H_
#define _XTEND_STRING_H_

#ifdef __linux__
#define strlcpy(dest,src,len)   strcpy(dest,src)
#define strlcat(dest,src,len)   strcat(dest,src)
#endif

#ifndef _STDIO_H_
#include <stdio.h>  // size_t
#endif

#ifndef _INTTYPES_H_
#include <inttypes.h>
#endif

/* string.c */
size_t strlupper(char *dest, const char *src, size_t dest_size);
size_t strupper(char *str);
size_t strllower(char *dest, const char *src, size_t dest_size);
size_t strlower(char *str);
size_t str_argv_cat(char *string, char *argv[], size_t first_arg, size_t string_buff_size);
int strblank(const char *string);
int strisint(const char *string, int base);
int strisreal(const char *string);
char *strlbasecpy(char *dest, const char *dest_base, const char *src, size_t dstsize);
int strptrcmp(const char **p1, const char **p2);
int strshellcpy(char *dest, const char *src, size_t dest_len);
size_t strsqueeze(char *dest, const char *src, size_t dstsize);
void strtr(char *string, const char *from, const char *to, int flags);
void strtrim(char *string, const char *fat);
char *strviscpy(unsigned char *dest, const unsigned char *src, size_t maxlen);
char *ltostrn(char string[], long val, unsigned base, size_t maxlen);
uint64_t str2u64(const char *str);
int strsplit(char *string, char ***array, const char *sep);

#endif  // _XTEND_STRING_H_
