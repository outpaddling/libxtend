/* difftimeofday.c */
time_t difftimeofday(struct timeval *later, struct timeval *earlier);
/* dsv.c */
int dsv_read_field(FILE *stream, char buff[], size_t buff_size, const char *delims, size_t *len);
int dsv_skip_field(FILE *stream, const char *delims);
int dsv_skip_rest_of_line(FILE *stream);
int dsv_read_line(FILE *stream, dsv_line_t *dsv_line, const char *delims);
void dsv_write_line(FILE *stream, dsv_line_t *dsv_line);
void dsv_copy_line(dsv_line_t *dest, dsv_line_t *src);
void dsv_free_line(dsv_line_t *dsv_line);
int tsv_read_field(FILE *stream, char buff[], size_t buff_size, size_t *len);
int tsv_skip_field(FILE *stream);
int tsv_skip_rest_of_line(FILE *stream);
int csv_read_field(FILE *stream, char buff[], size_t buff_size, size_t *len);
int csv_skip_field(FILE *stream);
int csv_skip_rest_of_line(FILE *stream);
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
/* strblank.c */
int strblank(const char *string);
/* strisnum.c */
int strisint(const char *string, int base);
int strisreal(const char *string);
/* strlbasecpy.c */
char *strlbasecpy(char *dest, const char *dest_base, const char *src, size_t dstsize);
/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);
/* strshellcpy.c */
int strshellcpy(char *dest, const char *src, size_t dest_len);
/* strsqueeze.c */
size_t strsqueeze(char *dest, const char *src, size_t dstsize);
/* va-usage.c */
void va_usage(const char *format_string, ...);
/* valid-extension.c */
_Bool valid_extension(const char *filename, const char *valid_ext);
/* viscpy.c */
char *viscpy(unsigned char *dest, const unsigned char *src, size_t maxlen);
/* xt-file.c */
FILE *xt_fopen(const char *filename, const char *mode);
int xt_fclose(FILE *stream);
/* xt-malloc.c */
void *xt_malloc(size_t nelem, size_t size);
void *xt_realloc(void *array, size_t nelem, size_t size);
