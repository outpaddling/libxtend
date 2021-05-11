/* difftimeofday.c */
time_t difftimeofday(struct timeval *later, struct timeval *earlier);
/* fast-cp.c */
int fast_cp(const char *source, const char *dest);
/* fd-purge.c */
void fd_purge(int fd);
/* fgetline.c */
size_t fgetline(FILE *fp, char *buff, size_t maxlen);
/* file-mod-cmp.c */
int file_mod_cmp(const char *file1, const char *file2);
/* gcd.c */
unsigned long gcd(unsigned long a, unsigned long b);
unsigned long lcm(unsigned long a, unsigned long b);
/* get-home-dir.c */
char *get_home_dir(char *dir, size_t maxlen);
/* ltostrn.c */
char *ltostrn(char string[], long val, unsigned base, size_t maxlen);
/* num_size.c */
int num_size(long val, unsigned base);
/* parse-cmd.c */
void parse_cmd(char *argv[], char *cmd);
/* rmkdir.c */
int rmkdir(const char *path, mode_t mode);
/* spawnlp.c */
int spawnlp(int parent_action, int echo, char *infile, char *outfile, char *errfile, char *arg0, ...);
/* spawnvp.c */
int spawnvp(int parent_action, int echo, char *argv[], char *infile, char *outfile, char *errfile);
void redirect(char *infile, char *outfile, char *errfile);
/* strisnum.c */
int strisint(const char *string, int base);
int strisreal(const char *string);
/* strlbasecpy.c */
char *strlbasecpy(char *dest, const char *dest_base, const char *src, size_t len);
/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);
/* strshellcpy.c */
int strshellcpy(char *dest, const char *src, size_t dest_len);
/* valid-extension.c */
_Bool valid_extension(const char *filename, const char *valid_ext);
/* xcfile.c */
FILE *xc_fopen(const char *filename, const char *mode);
int xc_fclose(FILE *stream);
