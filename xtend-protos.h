/* difftimeofday.c */
time_t difftimeofday(struct timeval *later, struct timeval *earlier);
/* fast-cp.c */
int fast_cp(const char *source, const char *dest);
/* fd_purge.c */
void fd_purge(int fd);
/* fgetline.c */
size_t fgetline(FILE *fp, char *buff, size_t maxlen);
/* file_mod_cmp.c */
int file_mod_cmp(char *file1, char *file2);
/* gcd.c */
unsigned long gcd(unsigned long a, unsigned long b);
unsigned long lcm(unsigned long a, unsigned long b);
/* get_home_dir.c */
char *get_home_dir(char dir[], int maxlen);
/* ltostrn.c */
char *ltostrn(char string[], long val, unsigned base, unsigned maxlen);
/* memicmp.c */
int memicmp(char *str1, char *str2, int len);
/* meta_chars.c */
int meta_chars(char *dest, char *src, size_t dest_len);
/* num_size.c */
int num_size(long val);
/* parse_cmd.c */
void parse_cmd(char *argv[], char *cmd);
/* rmkdir.c */
int rmkdir(char *path, mode_t mode);
/* spawnlp.c */
int spawnlp(int parent_action, int echo, char *infile, char *outfile, char *errfile, char *arg0, ...);
/* spawnvp.c */
int spawnvp(int parent_action, int echo, char *argv[], char *infile, char *outfile, char *errfile);
void redirect(char *infile, char *outfile, char *errfile);
/* strbasecpy.c */
char *strbasecpy(char *dest, char *src, char *dest_base, int len);
/* strblank.c */
int strblank(char *str);
/* strisnum.c */
int strisint(const char *string, int base);
int strisreal(const char *string);
/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);
/* va-usage.c */
void va_usage(char *format_string, ...);
/* valid-extension.c */
_Bool valid_extension(const char *filename, const char *valid_ext);
/* viscpy.c */
char *viscpy(unsigned char dest[], unsigned char src[], size_t maxlen);
/* xcfile.c */
FILE *xc_fopen(const char *filename, const char *mode);
int xc_fclose(FILE *stream);
