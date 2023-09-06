#ifndef _XTEND_MATH_H_
#define _XTEND_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

// FIXME: Write man pages for these
#define XT_MIN(a,b)     ((a) < (b) ? (a) : (b))
#define XT_MAX(a,b)     ((a) > (b) ? (a) : (b))
#define XT_ABS(a)       ((a) >= 0  ? (a) : -(a))
#define XT_SIGNUM(a)    ((a) / XT_ABS(a))

#ifndef _INTTYPES_H_
#include <inttypes.h>
#endif

/* xt_gcd.c */
unsigned long xt_gcd(unsigned long a, unsigned long b);
unsigned long xt_lcm(unsigned long a, unsigned long b);

/* xt_digits.c */
int xt_digits(long val, unsigned base);

/* numeric_cmp.c */
int xt_double_cmp(const double *d1, const double *d2);
int xt_float_cmp(const float *d1, const float *d2);
int xt_long_long_cmp(const long long *d1, const long long *d2);
int xt_long_cmp(const long *d1, const long *d2);
int xt_int_cmp(const int *d1, const int *d2);
int xt_short_cmp(const short *d1, const short *d2);

/* combinatorics.c */
unsigned long xt_n_choose_k(unsigned long n, unsigned long k);
uint64_t xt_factorial(unsigned n);

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_MATH_H_
