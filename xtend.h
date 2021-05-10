#ifndef __xtend_h__
#define __xtend_h__

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#define XT_CMD_MAX      4096

#ifdef __linux__
#define strlcpy(dest,src,len)   strcpy(dest,src)
#define strlcat(dest,src,len)   strcat(dest,src)
#endif

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

#define LCM(a,b)    ((a)*(b)/gcd(a,b))

#ifndef ISIDENT
#define ISIDENT(c)  ( isalnum(c) | ((c)=='_') )
#endif

#ifndef MALLOC
#define MALLOC(nelem,type)   ((type *)malloc((nelem)*sizeof(type)))
#endif

#ifndef REALLOC
#define REALLOC(ptr,nelem,type) ((type *)realloc((ptr),(nelem)*sizeof(type)))
#endif

#include "xtend-protos.h"

#endif  // __xtend_h__
