#ifndef _XTEND_DSV_H_
#define _XTEND_DSV_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#include "fast-file.h"  // For conversion to ff-dsv.h

#define DSV_DATA_OK             0
#define DSV_DATA_INVALID        -1      // Catch-all for non-specific error
#define DSV_DATA_OUT_OF_RANGE   -2

#define DSV_INIT                { 0, 0, NULL, NULL }
#define DSV_FIELD_MAX_CHARS     32767

// Before including generated headers
typedef struct xt_ff_dsv_line xt_ff_dsv_line_t;

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <biolibc/dsv.h>
 *      -lbiolibc -lxtend
 *
 *  Description:
 *      .B xt_ff_dsv_line_t
 *      is a generic structure for holding a line of data from a delimiter
 *      separated file such as CSV or TSV.
 *  
 *  Examples:
 *
 *  See also:
 *      xt_ff_dsv_line_read(3), xt_ff_dsv_line_write(3), xt_ff_dsv_line_copy(3), xt_ff_dsv_line_free(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-08  Jason Bacon Begin
 ***************************************************************************/

#include "ff-dsv-rvs.h"
#include "ff-dsv-accessors.h"
#include "ff-dsv-mutators.h"

/* dsv.c */
int xt_ff_dsv_read_field(xt_ff_t *stream, char buff[], size_t buff_size, const char *delims, size_t *len);
int xt_ff_dsv_read_field_malloc(xt_ff_t *stream, char **buff, size_t *buff_size, const char *delims, size_t *len);
int xt_ff_dsv_skip_field(xt_ff_t *stream, const char *delims, size_t *len);
int xt_ff_dsv_skip_rest_of_line(xt_ff_t *stream);
xt_ff_dsv_line_t *xt_ff_dsv_line_new(void);
void xt_ff_dsv_line_init(xt_ff_dsv_line_t *xt_ff_dsv_line);
int xt_ff_dsv_line_read(xt_ff_dsv_line_t *xt_ff_dsv_line, xt_ff_t *stream, const char *delims);
int xt_ff_dsv_line_write(xt_ff_dsv_line_t *xt_ff_dsv_line, xt_ff_t *stream);
int xt_ff_dsv_line_copy(xt_ff_dsv_line_t *dest, xt_ff_dsv_line_t *src);
int xt_ff_dsv_line_free(xt_ff_dsv_line_t *xt_ff_dsv_line);
int xt_ff_tsv_read_field(xt_ff_t *stream, char buff[], size_t buff_size, size_t *len);
int xt_ff_tsv_read_field_malloc(xt_ff_t *stream, char **buff, size_t *buff_size, size_t *len);
int xt_ff_tsv_skip_field(xt_ff_t *stream, size_t *len);
int xt_ff_tsv_skip_rest_of_line(xt_ff_t *stream);
int xt_ff_csv_read_field(xt_ff_t *stream, char buff[], size_t buff_size, size_t *len);
int xt_ff_csv_read_field_malloc(xt_ff_t *stream, char **buff, size_t *buff_size, size_t *len);
int xt_ff_csv_skip_field(xt_ff_t *stream, size_t *len);
int xt_ff_csv_skip_rest_of_line(xt_ff_t *stream);

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_DSV_H_
