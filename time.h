#ifndef _XTEND_TIME_H_
#define _XTEND_TIME_H_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef _SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#define difftimeofday(later, earlier) \
	    _Pragma("message(\"difftimeofday() is deprecated.  Use xt_difftimeofday().\")") \
	    xt_difftimeofday(later, earlier)

/* difftimeofday.c */
time_t xt_difftimeofday(struct timeval *later, struct timeval *earlier);
int xt_tic(struct timeval *start_time, struct rusage *start_usage);
unsigned long xt_toc(FILE *stream, const char *message, struct timeval *start_time, struct rusage *start_usage);

#endif  // _XTEND_TIME_H_
