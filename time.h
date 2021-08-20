
#ifndef _XTEND_TIME_H_
#define _XTEND_TIME_H_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

/* difftimeofday.c */
time_t difftimeofday(struct timeval *later, struct timeval *earlier);
int xt_tic(struct timeval *start_time);
unsigned long xt_toc(FILE *stream, const char *message, struct timeval *start_time);

#endif  // _XTEND_TIME_H_
