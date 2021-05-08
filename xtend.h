#ifndef __xtend_h__
#define __xtend_h__

#define XC_CMD_MAX      4096

#ifdef __linux__
#define strlcpy(dest,src,len)   strcpy(dest,src)
#define strlcat(dest,src,len)   strcat(dest,src)
#endif

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

#include "xtend-protos.h"

#endif  // __xtend_h__
