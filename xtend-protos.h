/* check-extension.c */
_Bool valid_extension(const char *filename, const char *valid_ext);
/* strisnum.c */
int strisint(const char *string, int base);
int strisreal(const char *string);
/* strptrcmp.c */
int strptrcmp(const char **p1, const char **p2);
/* xcfile.c */
FILE *xc_fopen(const char *filename, const char *mode);
int xc_fclose(FILE *stream);
