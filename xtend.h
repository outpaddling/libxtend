#ifndef __xtend_h__
#define __xtend_h__

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#define XC_CMD_MAX      4096

#ifdef __linux__
#define strlcpy(dest,src,len)   strcpy(dest,src)
#define strlcat(dest,src,len)   strcat(dest,src)
#endif

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

#define LCM(a,b)    ((a)*(b)/gcd(a,b))

#include "xtend-protos.h"

#endif  // __xtend_h__
