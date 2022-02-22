#ifndef _XTEND_MEM_H_
#define _XTEND_MEM_H_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

/* xt-malloc.c */
void *xt_malloc(size_t nelem, size_t size);
void *xt_realloc(void *array, size_t nelem, size_t size);
void xt_free_strings(char **list);

#endif // _XTEND_MEM_H_
