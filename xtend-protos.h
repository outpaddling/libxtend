/* difftimeofday.c */
time_t difftimeofday(struct timeval *later, struct timeval *earlier);
/* fast-cp.c */
int fast_cp(const char *source, const char *dest);
/* fd-purge.c */
void fd_purge(int fd);
/* gcd.c */
unsigned long gcd(unsigned long a, unsigned long b);
unsigned long lcm(unsigned long a, unsigned long b);
/* strisnum.c */
int strisint(const char *string, int base);
int strisreal(const char *string);
/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);
/* valid-extension.c */
_Bool valid_extension(const char *filename, const char *valid_ext);
/* xcfile.c */
FILE *xc_fopen(const char *filename, const char *mode);
int xc_fclose(FILE *stream);
