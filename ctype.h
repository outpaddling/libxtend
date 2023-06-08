#ifndef _XTEND_CTYPE_H_
#define _XTEND_CTYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ISIDENT(c)  ( isalnum(c) | ((c)=='_') )

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_CTYPE_H_
