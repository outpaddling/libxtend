
#ifndef _XTEND_STRING_H_
#define _XTEND_STRING_H_

#ifdef __linux__
#define strlcpy(dest,src,len)   strcpy(dest,src)
#define strlcat(dest,src,len)   strcat(dest,src)
#endif

#ifndef _STDIO_H_
#include <stdio.h>  // size_t
#endif

/* ltostrn.c */
char *ltostrn(char string[], long val, unsigned base, size_t maxlen);

/* strblank.c */
int strblank(const char *string);

/* strisnum.c */
int strisint(const char *string, int base);
int strisreal(const char *string);

/* strlbasecpy.c */
char *strlbasecpy(char *dest, const char *dest_base, const char *src, size_t dstsize);

/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);

/* strshellcpy.c */
int strshellcpy(char *dest, const char *src, size_t dest_len);

/* strsqueeze.c */
size_t strsqueeze(char *dest, const char *src, size_t dstsize);

/* strviscpy.c */
char *strviscpy(unsigned char *dest, const unsigned char *src, size_t maxlen);

/* strtr.c */
void strtr(char *string, const char *from, const char *to, int flags);

#endif  // _XTEND_STRING_H_
