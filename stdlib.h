#ifndef _XTEND_ARRAY_H_
#define _XTEND_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

/* xt-shuffle.c */
void *xt_shuffle(void *base, size_t nelem, size_t size);

/* roman.c */
int romantoi(const char *nptr, char **endptr);

#ifdef __cplusplus
}
#endif

#endif // _XTEND_ARRAY_H_
