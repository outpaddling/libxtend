#ifndef _XTEND_MEM_H_
#define _XTEND_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

/* xt-malloc.c */
void *xt_malloc(size_t nelem, size_t size);
void *xt_realloc(void *array, size_t nelem, size_t size);
void xt_free_strings(char **list);

#ifdef __cplusplus
}
#endif

#endif // _XTEND_MEM_H_
