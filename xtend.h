#ifndef __xtend_h__
#define __xtend_h__

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef _SYS_STAT_H
#include <sys/stat.h>   // mode_t on Darwin
#endif

#ifdef __linux__
#define strlcpy(dest,src,len)   strcpy(dest,src)
#define strlcat(dest,src,len)   strcat(dest,src)
#endif

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

#if !defined(_STDARG_H_) && !defined(__STDARG_H__)
#include <stdarg.h>
#endif

#define LCM(a,b)    ((a)*(b)/gcd(a,b))

#define XT_CMD_MAX_CHARS    4096
#define XT_FORMAT_MAX_CHARS 4096

#ifndef ISIDENT
#define ISIDENT(c)  ( isalnum(c) | ((c)=='_') )
#endif

/*
 *  Process control
 */

/* spawn*() parent_action */
#define P_NOWAIT  0
#define P_WAIT    1

/* spawn*() echo */
#define P_NOECHO  0
#define P_ECHO    1

#define P_TERM_STATUS(s)    ((s) & 0xff)
#define P_EXIT_CODE(s)      (((s) & 0x0000ff00) >> 8)
#define P_EXEC_FAILED(s)    ( (s) & 0x8000 )

/*
 *  Delimiter-separated data
 */

#define DSV_INIT                { 0, 0, NULL, NULL }
#define DSV_FIELD_MAX_CHARS     32767

#define DSV_FIELD(line,col)     ((line)->fields[col-1]) // 1-based column

typedef struct
{
    size_t      array_size,
		num_fields;
    char        **fields,
		*delims;
}   dsv_line_t;

#include "xtend-protos.h"

#endif  // __xtend_h__
