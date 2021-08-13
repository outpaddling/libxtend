
#ifndef _XTEND_TIME_H_
#define _XTEND_TIME_H_

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

/* difftimeofday.c */
time_t difftimeofday(struct timeval *later, struct timeval *earlier);

#endif  // _XTEND_TIME_H_
