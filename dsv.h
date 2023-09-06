#ifndef _XTEND_DSV_H_
#define _XTEND_DSV_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#define DSV_DATA_OK             0
#define DSV_DATA_INVALID        -1      // Catch-all for non-specific error
#define DSV_DATA_OUT_OF_RANGE   -2

#define DSV_INIT                { 0, 0, NULL, NULL }
#define DSV_FIELD_MAX_CHARS     32767

// Before including generated headers
typedef struct xt_dsv_line xt_dsv_line_t;

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <biolibc/dsv.h>
 *      -lbiolibc -lxtend
 *
 *  Description:
 *      .B xt_dsv_line_t
 *      is a generic structure for holding a line of data from a delimiter
 *      separated file such as CSV or TSV.
 *  
 *  Examples:
 *
 *  See also:
 *      xt_dsv_line_read(3), xt_dsv_line_write(3), xt_dsv_line_copy(3), xt_dsv_line_free(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-08  Jason Bacon Begin
 ***************************************************************************/

#include "dsv-rvs.h"
#include "dsv-accessors.h"
#include "dsv-mutators.h"

/* dsv.c */
int xt_dsv_read_field(FILE *stream, char buff[], size_t buff_size, const char *delims, size_t *len);
int xt_dsv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size, const char *delims, size_t *len);
int xt_dsv_skip_field(FILE *stream, const char *delims, size_t *len);
int xt_dsv_skip_rest_of_line(FILE *stream);
xt_dsv_line_t *xt_dsv_line_new(void);
void xt_dsv_line_init(xt_dsv_line_t *xt_dsv_line);
int xt_dsv_line_read(xt_dsv_line_t *xt_dsv_line, FILE *stream, const char *delims);
int xt_dsv_line_write(xt_dsv_line_t *xt_dsv_line, FILE *stream);
int xt_dsv_line_copy(xt_dsv_line_t *dest, xt_dsv_line_t *src);
int xt_dsv_line_free(xt_dsv_line_t *xt_dsv_line);
int xt_tsv_read_field(FILE *stream, char buff[], size_t buff_size, size_t *len);
int xt_tsv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size, size_t *len);
int xt_tsv_skip_field(FILE *stream, size_t *len);
int xt_tsv_skip_rest_of_line(FILE *stream);
int xt_csv_read_field(FILE *stream, char buff[], size_t buff_size, size_t *len);
int xt_csv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size, size_t *len);
int xt_csv_skip_field(FILE *stream, size_t *len);
int xt_csv_skip_rest_of_line(FILE *stream);

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_DSV_H_
