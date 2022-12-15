#ifndef _XTEND_ARRAY_H_
#define _XTEND_ARRAY_H_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

/* xt-shuffle.c */
void *xt_shuffle(void *base, size_t nelem, size_t size);

/* roman.c */
int romantoi(const char *nptr, char **endptr);

#endif // _XTEND_ARRAY_H_
