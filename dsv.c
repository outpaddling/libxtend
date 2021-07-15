#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "xtend.h"

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read next delimiter-separated field from stream. The fields may be
 *      ended by any character in the string delims or by a newline ('\n').
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *      buff:       Character buff into which field is copied
 *      buff_size:  Size of the array passed to buff
 *      delims:     Array of characters that may serve as delimiters
 *      len:        Pointer to a variable which will receive the field length
 *
 *  Returns:
 *      Delimiter ending the field (either a member of delim or newline)
 *
 *  See also:
 *      dsv_skip_field(3), dsv_skip_rest_of_line(3), dsv_read_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-02-24  Jason Bacon Begin
 ***************************************************************************/

int     dsv_read_field(FILE *stream, char buff[], size_t buff_size,
		       const char *delims, size_t *len)

{
    size_t  c;
    char    *p;
    int     ch;
    
    for (c = 0, p = buff; (c < buff_size) && 
			  ( strchr(delims, ch = getc(stream)) == NULL) &&
			  (ch != '\n') && (ch != EOF); ++c, ++p )
	*p = ch;
    *p = '\0';
    
    if ( c == buff_size )
    {
	fprintf(stderr, "dsv_read_field(): Buffer overflow reading field.\n");
	fprintf(stderr, "Buffer size = %zu\n", buff_size);
	fputs(buff, stderr);
	// FIXME: Replace this with another sentinal value?
	// Would require all callers to handle both EOF and overflow
	return EOF;
    }
    
    *len = c;
    return ch;
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read and discard next delimiter-separated field from stream. The
 *      fields may be ended by any character in the string delims or by a
 *      newline ('\n').
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *      delims:     Array of characters that may serve as delimiters
 *
 *  Returns:
 *      Delimiter ending the field (either a member of delim or newline)
 *
 *  See also:
 *      dsv_read_field(3), dsv_skip_rest_of_line(3), dsv_read_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-02-24  Jason Bacon Begin
 ***************************************************************************/

int     dsv_skip_field(FILE *stream, const char *delims)

{
    int     ch;
    
    while ( (strchr(delims, ch = getc(stream)) == NULL) &&
	    (ch != '\n') && (ch != EOF) )
	;
    
    return ch;
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read and discard all remaining fields in a line from stream.
 *      I.e., discard everything up to and including the next newline ('\n').
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *
 *  Returns:
 *      Delimiter ending the field (should always be newline ('\n'))
 *
 *  See also:
 *      dsv_read_field(3), dsv_skip_field(3), dsv_read_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2019-12-06  Jason Bacon Begin
 ***************************************************************************/

int     dsv_skip_rest_of_line(FILE *stream)

{
    int     ch;
    
    while ( ((ch = getc(stream)) != EOF) && (ch != '\n') )
	;
    return ch;
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read a line of an arbitrary DSV file, storing the fields in a
 *      dsv_line_t structure, which contains an array of strings, each
 *      holding one field from the line, and an an array of delimiters,
 *      each holding the character that ended the corresponding field.
 *      Note that each field could potentially end with a different
 *      delimiter, as multiple delimiters can be specified.
 *
 *      This function serves a purpose similar to the split() functions
 *      present in many languages.  However, it does not need to read an
 *      entire line into a character array and then split the array.
 *      Instead, it separates fields as they are read from the input stream.
 *
 *  Arguments:
 *      stream:     FILE stream from which the line is read
 *      dsv_line:   Pointer to a dsv_line_t structure to hold the fields
 *      delims:     Array of acceptable delimiters
 *
 *  Returns:
 *      Actual delimiter of last field (should be newline)
 *
 *  See also:
 *      dsv_read_field(3), dsv_skip_field(3), dsv_skip_rest_of_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-30  Jason Bacon Begin
 ***************************************************************************/

int     dsv_read_line(FILE *stream, dsv_line_t *dsv_line, const char *delims)

{
    int     actual_delim;
    char    field[DSV_FIELD_MAX_CHARS + 1];
    size_t  actual_len;
    
    dsv_line->array_size = 32;  // Start small and double each time we run out
    dsv_line->num_fields = 0;
    
    if ( (dsv_line->fields = xt_malloc(dsv_line->array_size,
				sizeof(*dsv_line->fields))) == NULL )
    {
	fputs("dsv_read_line(): Could not allocate fields.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    
    if ( (dsv_line->delims = xt_malloc(dsv_line->array_size,
				sizeof(*dsv_line->delims))) == NULL )
    {
	fputs("dsv_read_line(): Could not allocate delims.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    
    // FIXME: Check actual_delim and/or actual_len to detect truncation
    while ( ((actual_delim = dsv_read_field(stream,
		field, DSV_FIELD_MAX_CHARS, delims, &actual_len)) != EOF) )
    {
	if ( (dsv_line->fields[dsv_line->num_fields] = strdup(field)) == NULL )
	{
	    fprintf(stderr, "dsv_read_line(): Could not strdup() field %zu.\n",
		    dsv_line->num_fields - 1);
	    exit(EX_UNAVAILABLE);
	}
	dsv_line->delims[dsv_line->num_fields++] = actual_delim;
	if ( dsv_line->num_fields == dsv_line->array_size )
	{
	    dsv_line->array_size *= 2;
	    if ( (dsv_line->fields = xt_realloc(dsv_line->fields,
		    dsv_line->array_size, sizeof(*dsv_line->fields))) == NULL )
	    {
		fputs("dsv_read_line(): Could not reallocate fields.\n", stderr);
		exit(EX_UNAVAILABLE);
	    }
	    
	    if ( (dsv_line->delims = xt_realloc(dsv_line->delims,
		    dsv_line->array_size, sizeof(*dsv_line->delims))) == NULL )
	    {
		fputs("dsv_read_line(): Could not reallocate delims.\n", stderr);
		exit(EX_UNAVAILABLE);
	    }
	}
	if ( actual_delim == '\n' )
	    break;
    }
    return actual_delim;
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Print an arbitrary DSV line for debugging.
 *
 *  Arguments:
 *      stream:     FILE stream to which fields are printed (e.g. stderr)
 *      dsv_line:   Pointer to dsv_line_t structure holding the fields
 *
 *  See also:
 *      dsv_read_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-01  Jason Bacon Begin
 ***************************************************************************/

void    dsv_write_line(FILE *stream, dsv_line_t *dsv_line)

{
    int     c;
    
    for (c = 0; c < dsv_line->num_fields; ++c)
	fprintf(stream, "%s%c", dsv_line->fields[c], dsv_line->delims[c]);
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Duplicate an arbitrary DSV line, allocating space for fields and
 *      delimiters as needed.
 *
 *  Arguments:
 *      src:    Pointer to populated dsv_line_t structure to be duplicated
 *      dest:   Pointer to empty dsv_lint_t structure to receive copy
 *
 *  See also:
 *      dsv_read_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-01  Jason Bacon Begin
 ***************************************************************************/

void    dsv_copy_line(dsv_line_t *dest, dsv_line_t *src)

{
    size_t  c;
    
    // Prune unused pointers in src
    dest->array_size = dest->num_fields = src->num_fields;
    
    // FIXME: Check malloc() success
    dest->fields = xt_malloc(dest->array_size, sizeof(*dest->fields));
    dest->delims = xt_malloc(dest->array_size, sizeof(*dest->delims));
    
    for (c = 0; c < src->num_fields; ++c)
    {
	dest->fields[c] = strdup(src->fields[c]);
	dest->delims[c] = src->delims[c];
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Free allocated memory for a DSV object.
 *
 *  Arguments:
 *      dsv_line:   Pointer to a populated dsv_line_t structure
 *
 *  See also:
 *      dsv_read_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-01  Jason Bacon Begin
 ***************************************************************************/

void    dsv_free_line(dsv_line_t *dsv_line)

{
    int     c;
    
    if ( dsv_line->fields != NULL )
    {
	for (c = 0; c < dsv_line->num_fields; ++c)
	    free(dsv_line->fields[c]);
	free(dsv_line->fields);
    }
    dsv_line->num_fields = 0;
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_read_field(stream, buff, buff_size, '\\\\\t', len)
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *      buff:       Character buff into which field is copied
 *      buff_size:  Size of the array passed to buff
 *      len:        Pointer to a variable which will receive the field length
 *
 *  See also:
 *      dsv_read_field(3)
 ***************************************************************************/

int     tsv_read_field(FILE *stream, char buff[], size_t buff_size,
		       size_t *len)

{
    return dsv_read_field(stream, buff, buff_size, "\t", len);
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_field(stream, '\\\\\t')
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *
 *  See also:
 *      dsv_skip_field(3)
 ***************************************************************************/

int     tsv_skip_field(FILE *stream)

{
    return dsv_skip_field(stream, "\t");
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_rest_of_line(stream)
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *
 *  See also:
 *      dsv_skip_rest_of_line(3)
 ***************************************************************************/

int     tsv_skip_rest_of_line(FILE *stream)

{
    return dsv_skip_rest_of_line(stream);
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_read_field(stream, buff, buff_size, ',', len)
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *      buff:       Character buff into which field is copied
 *      buff_size:  Size of the array passed to buff
 *      len:        Pointer to a variable which will receive the field length
 *
 *  See also:
 *      dsv_read_field(3)
 ***************************************************************************/

int     csv_read_field(FILE *stream, char buff[], size_t buff_size,
		       size_t *len)

{
    return dsv_read_field(stream, buff, buff_size, ",", len);
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_field(stream, ',')
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *
 *  See also:
 *      dsv_skip_field(3)
 ***************************************************************************/

int     csv_skip_field(FILE *stream)

{
    return dsv_skip_field(stream, ",");
}


/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_rest_of_line(stream)
 *
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *
 *  See also:
 *      dsv_skip_rest_of_line(3)
 ***************************************************************************/

int     csv_skip_rest_of_line(FILE *stream)

{
    return dsv_skip_rest_of_line(stream);
}
