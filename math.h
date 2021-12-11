
#ifndef _XTEND_MATH_H_
#define _XTEND_MATH_H_

#define XT_MIN(a,b) ((a) < (b) ? (a) : (b))
#define XT_MAX(a,b) ((a) > (b) ? (a) : (b))

#ifndef _INTTYPES_H_
#include <inttypes.h>
#endif

/* gcd.c */
unsigned long gcd(unsigned long a, unsigned long b);
unsigned long lcm(unsigned long a, unsigned long b);

/* digits.c */
int digits(long val, unsigned base);

/* numeric_cmp.c */
int double_cmp(const double *d1, const double *d2);
int float_cmp(const float *d1, const float *d2);
int long_long_cmp(const long long *d1, const long long *d2);
int long_cmp(const long *d1, const long *d2);
int int_cmp(const int *d1, const int *d2);
int short_cmp(const short *d1, const short *d2);

/* combinatorics.c */
unsigned long xt_n_choose_k(unsigned long n, unsigned long k);
uint64_t xt_factorial(unsigned n);

#endif  // _XTEND_MATH_H_
