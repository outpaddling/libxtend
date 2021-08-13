#ifndef _XTEND_MEM_H_
#define _XTEND_MEM_H_

/* xt-malloc.c */
void *xt_malloc(size_t nelem, size_t size);
void *xt_realloc(void *array, size_t nelem, size_t size);

#endif // _XTEND_MEM_H_
