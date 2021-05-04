/* check-extension.c */
void check_extension(const char *filename, const char *valid_ext);
/* strisnum.c */
int strisnum(const char *string);
/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);
/* xcfile.c */
FILE *xc_fopen(const char *filename, const char *mode);
int xc_fclose(FILE *stream);
