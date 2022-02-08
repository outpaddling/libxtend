#ifndef _XTEND_DSV_H_
#define _XTEND_DSV_H_

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#define DSV_DATA_OK             0
#define DSV_DATA_INVALID        -1      // Catch-all for non-specific error
#define DSV_DATA_OUT_OF_RANGE   -2

#define DSV_INIT                { 0, 0, NULL, NULL }
#define DSV_FIELD_MAX_CHARS     32767

#define DSV_FIELD(line,col)     ((line)->fields[col-1]) // 1-based column

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <biolibc/dsv.h>
 *      -lbiolibc -lxtend
 *
 *  Description:
 *      .B dsv_line_t
 *      is a generic structure for holding a line of data from a delimiter
 *      separated file such as CSV or TSV.
 *  
 *  Examples:
 *
 *  See also:
 *      dsv_line_read(3), dsv_line_write(3), dsv_line_copy(3), dsv_line_free(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-08  Jason Bacon Begin
 ***************************************************************************/

typedef struct
{
    size_t      array_size,
		num_fields;
    char        **fields,
		*delims;
}   dsv_line_t;

#define DSV_LINE_ARRAY_SIZE(ptr)        ((ptr)->array_size)
#define DSV_LINE_NUM_FIELDS(ptr)        ((ptr)->num_fields)
#define DSV_LINE_FIELDS(ptr)            ((ptr)->fields)
#define DSV_LINE_FIELDS_AE(ptr,c)       ((ptr)->fields[c])
#define DSV_LINE_DELIMS(ptr)            ((ptr)->delims)
#define DSV_LINE_DELIMS_AE(ptr,c)       ((ptr)->delims[c])

#include "dsv-rvs.h"
#include "dsv-accessors.h"
#include "dsv-mutators.h"

/* dsv.c */
int dsv_read_field(FILE *stream, char buff[], size_t buff_size, const char *delims, size_t *len);
int dsv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size, const char *delims, size_t *len);
int dsv_skip_field(FILE *stream, const char *delims);
int dsv_skip_rest_of_line(FILE *stream);
int dsv_line_read(dsv_line_t *dsv_line, FILE *stream, const char *delims);
int dsv_line_write(dsv_line_t *dsv_line, FILE *stream);
int dsv_line_copy(dsv_line_t *dest, dsv_line_t *src);
int dsv_line_free(dsv_line_t *dsv_line);
int tsv_read_field(FILE *stream, char buff[], size_t buff_size, size_t *len);
int tsv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size, size_t *len);
int tsv_skip_field(FILE *stream);
int tsv_skip_rest_of_line(FILE *stream);
int csv_read_field(FILE *stream, char buff[], size_t buff_size, size_t *len);
int csv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size, size_t *len);
int csv_skip_field(FILE *stream);
int csv_skip_rest_of_line(FILE *stream);

#endif  // _XTEND_DSV_H_
