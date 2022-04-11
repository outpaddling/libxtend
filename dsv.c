#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "dsv.h"
#include "mem.h"
#include "file.h"
#include "common.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read next delimiter-separated field from stream. The fields may be
 *      ended by any character in the string delims or by a newline ('\\\\n').
 *
 *      If the delimiter ending a field is a space, then subsequence spaces
 *      are discarded, so that multiple space characters serve as a single
 *      delimiter.
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      buff        Character buff into which field is copied
 *      buff_size   Size of the array passed to buff
 *      delims      Array of characters that may serve as delimiters
 *      len         Pointer to a variable which will receive the field length
 *
 *  Returns:
 *      Delimiter ending the field (either a member of delim or newline)
 *
 *  See also:
 *      dsv_read_field_malloc(3), dsv_skip_field(3),
 *      dsv_skip_rest_of_line(3), dsv_line_read(3)
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
    int     ch, ch2;
    
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
	exit(EX_SOFTWARE);
    }
    
    *len = c;
    
    /*
     *  Treat space specially in that multiple spaces are considered a single
     *  separator
     */
    if ( ch == ' ' )
    {
	while ( (ch2 = getc(stream)) == ch )
	    ;
	ungetc(ch2, stream);
    }
    return ch;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read next delimiter-separated field from stream, allocating a
 *      buffer to fit in the fashion of strdup(3). The fields may be
 *      ended by any character in the string delims or by a newline ('\\\\n').
 *
 *      If the delimiter ending a field is a space, then subsequence spaces
 *      are discarded, so that multiple space characters serve as a single
 *      delimiter.
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      buff        Character buffer into which field is copied
 *      buff_size   Size of the array passed to buff
 *      delims      Array of characters that may serve as delimiters
 *      len         Pointer to a variable which will receive the field length
 *
 *  Returns:
 *      Delimiter ending the field (either a member of delim or newline)
 *      or XT_MALLOC_FAILED.
 *
 *  See also:
 *      dsv_read_field(3), dsv_skip_field(3), dsv_skip_rest_of_line(3),
 *      dsv_line_read(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-02-24  Jason Bacon Begin
 ***************************************************************************/

int     dsv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size,
		       const char *delims, size_t *len)

{
    size_t  c;
    int     ch, ch2;
    
    if ( *buff_size == 0 )
    {
	*buff_size = 1024;
	*buff = xt_malloc(*buff_size, sizeof(**buff));
	if ( *buff == NULL )
	    return XT_MALLOC_FAILED;
    }
    
    for (c = 0; ( ((ch = getc(stream)) != '\n') && (ch != EOF) &&
		  strchr(delims, ch) == NULL); ++c )
    {
	if ( c == *buff_size - 1 )
	{
	    *buff_size *= 2;
	    *buff = xt_realloc(*buff, *buff_size, sizeof(**buff));
	    if ( *buff == NULL )
		return XT_MALLOC_FAILED;
	}
	(*buff)[c] = ch;
    }
    (*buff)[c] = '\0';
    *len = c;

    /* Trim array */
    if ( *buff_size != c + 1 )
    {
	*buff_size = c + 1;
	*buff = xt_realloc(*buff, *buff_size, sizeof(**buff));
    }

    /*
     *  Treat space specially in that multiple spaces are considered a single
     *  separator
     */
    if ( ch == ' ' )
    {
	while ( (ch2 = getc(stream)) == ch )
	    ;
	ungetc(ch2, stream);
    }
    return ch;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read and discard next delimiter-separated field from stream. The
 *      fields may be ended by any character in the string delims or by a
 *      newline ('\\\\n').
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      delims      Array of characters that may serve as delimiters
 *      len         Length of field discarded
 *
 *  Returns:
 *      Delimiter ending the field (either a member of delim or newline)
 *
 *  See also:
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_rest_of_line(3), dsv_line_read(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-02-24  Jason Bacon Begin
 ***************************************************************************/

int     dsv_skip_field(FILE *stream, const char *delims, size_t *len)

{
    int     ch;
    
    for (*len = 0; (strchr(delims, ch = getc(stream)) == NULL) &&
	    (ch != '\n') && (ch != EOF); ++*len )
	;
    
    return ch;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read and discard all remaining fields in a line from stream.
 *      I.e., discard everything up to and including the next newline ('\\\\n').
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *
 *  Returns:
 *      Delimiter ending the field (should always be newline ('\\\\n'))
 *
 *  See also:
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_field(3), dsv_line_read(3)
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
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Read a line of an arbitrary DSV file into a dsv_line_t object.
 *      The dsv_line_t structure contains an array of strings, each
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
 *      dsv_line    Pointer to a dsv_line_t structure to hold the fields
 *      stream      FILE stream from which the line is read
 *      delims      Array of acceptable delimiters
 *
 *  Returns:
 *      Actual delimiter of last field (should be newline)
 *
 *  Examples:
 *      dsv_line_t  line;
 *
 *      dsv_line_init(&line);
 *      while ( dsv_line_read(&line, stdin, "\t") != EOF )
 *      {
 *          dsv_line_write(line, stdout);
 *          dsv_line_free(&line);
 *      }
 *
 *  See also:
 *      dsv_line_init(3), dsv_line_free(3),
 *      dsv_line_read(3), dsv_line_write(3), dsv_line_copy(3),
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_field(3), dsv_skip_rest_of_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-30  Jason Bacon Begin
 ***************************************************************************/

int     dsv_line_read(dsv_line_t *dsv_line, FILE *stream, const char *delims)

{
    int     actual_delim;
    char    field[DSV_FIELD_MAX_CHARS + 1];
    size_t  actual_len;
    
    dsv_line->array_size = 32;  // Start small and double each time we run out
    dsv_line->num_fields = 0;
    
    // FIXME: Reuse previously allocated memory?
    if ( (dsv_line->fields = xt_malloc(dsv_line->array_size,
				sizeof(*dsv_line->fields))) == NULL )
    {
	fputs("dsv_line_read(): Could not allocate fields.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    
    if ( (dsv_line->delims = xt_malloc(dsv_line->array_size,
				sizeof(*dsv_line->delims))) == NULL )
    {
	fputs("dsv_line_read(): Could not allocate delims.\n", stderr);
	exit(EX_UNAVAILABLE);
    }
    
    // FIXME: Check actual_delim and/or actual_len to detect truncation
    while ( ((actual_delim = dsv_read_field(stream,
		field, DSV_FIELD_MAX_CHARS, delims, &actual_len)) != EOF) )
    {
	if ( (dsv_line->fields[dsv_line->num_fields] = strdup(field)) == NULL )
	{
	    fprintf(stderr, "dsv_line_read(): Could not strdup() field %zu.\n",
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
		fputs("dsv_line_read(): Could not reallocate fields.\n", stderr);
		exit(EX_UNAVAILABLE);
	    }
	    
	    if ( (dsv_line->delims = xt_realloc(dsv_line->delims,
		    dsv_line->array_size, sizeof(*dsv_line->delims))) == NULL )
	    {
		fputs("dsv_line_read(): Could not reallocate delims.\n", stderr);
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
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Write an arbitrary DSV line to the specified stream.
 *      The dsv_line_t structure contains an array of strings, each
 *      holding one field from the line, and an an array of delimiters,
 *      each holding the character that ended the corresponding field.
 *      Note that each field could potentially end with a different
 *      delimiter, as multiple delimiters can be specified.
 *
 *  Arguments:
 *      dsv_line    Pointer to dsv_line_t structure holding the fields
 *      stream      FILE stream to which fields are printed (e.g. stderr)
 *
 *  Returns:
 *      The number of fields successfully written
 *
 *  Examples:
 *      dsv_line_t  line;
 *
 *      dsv_line_init(&line);
 *      while ( dsv_line_read(&line, stdin, "\t") != EOF )
 *      {
 *          dsv_line_write(line, stdout);
 *          dsv_line_free(&line);
 *      }
 *
 *  See also:
 *      dsv_line_init(3), dsv_line_free(3),
 *      dsv_line_read(3), dsv_line_write(3), dsv_line_copy(3),
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_field(3), dsv_skip_rest_of_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-01  Jason Bacon Begin
 ***************************************************************************/

int     dsv_line_write(dsv_line_t *dsv_line, FILE *stream)

{
    int     c, count = 0;
    
    for (c = 0; c < dsv_line->num_fields; ++c)
    {
	if ( fprintf(stream, "%s%c", dsv_line->fields[c], dsv_line->delims[c]) == 2 )
	    ++count;
    }
    return count;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Initialize a dsv_line_t structure.
 *      The dsv_line_t structure contains an array of strings, each
 *      holding one field from the line, and an an array of delimiters,
 *      each holding the character that ended the corresponding field.
 *      Note that each field could potentially end with a different
 *      delimiter, as multiple delimiters can be specified.
 *  
 *  Arguments:
 *      dsv_line    Pointer to a dsv_lint_t object.    
 *
 *  Examples:
 *      dsv_line_t  line;
 *
 *      dsv_line_init(&line);
 *      while ( dsv_line_read(&line, stdin, "\t") != EOF )
 *      {
 *          dsv_line_write(line, stdout);
 *          dsv_line_free(&line);
 *      }
 *
 *  See also:
 *      dsv_line_init(3), dsv_line_free(3),
 *      dsv_line_read(3), dsv_line_write(3), dsv_line_copy(3),
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_field(3), dsv_skip_rest_of_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-04-11  Jason Bacon Begin
 ***************************************************************************/

void    dsv_line_init(dsv_line_t *dsv_line)

{
    dsv_line->array_size = 0;
    dsv_line->num_fields = 0;
    dsv_line->fields = NULL;
    dsv_line->delims = NULL;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Duplicate an arbitrary dsv_line_t object, allocating space for
 *      fields and delimiters as needed.
 *      The dsv_line_t structure contains an array of strings, each
 *      holding one field from the line, and an an array of delimiters,
 *      each holding the character that ended the corresponding field.
 *      Note that each field could potentially end with a different
 *      delimiter, as multiple delimiters can be specified.
 *
 *  Arguments:
 *      src     Pointer to populated dsv_line_t structure to be duplicated
 *      dest    Pointer to empty dsv_lint_t structure to receive copy
 *
 *  Returns:
 *      XT_OK or XT_MALLOC_FAILED
 *      
 *  See also:
 *      dsv_line_init(3), dsv_line_free(3),
 *      dsv_line_read(3), dsv_line_write(3), dsv_line_copy(3),
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_field(3), dsv_skip_rest_of_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-01  Jason Bacon Begin
 ***************************************************************************/

int     dsv_line_copy(dsv_line_t *dest, dsv_line_t *src)

{
    size_t  c;
    
    // Prune unused pointers in src
    dest->array_size = dest->num_fields = src->num_fields;
    
    // FIXME: Check malloc() success
    dest->fields = xt_malloc(dest->array_size, sizeof(*dest->fields));
    if ( dest->fields == NULL )
	return XT_MALLOC_FAILED;
    dest->delims = xt_malloc(dest->array_size, sizeof(*dest->delims));
    if ( dest->delims == NULL )
	return XT_MALLOC_FAILED;
    
    for (c = 0; c < src->num_fields; ++c)
    {
	if ( (dest->fields[c] = strdup(src->fields[c])) == NULL )
	    return XT_MALLOC_FAILED;
	dest->delims[c] = src->delims[c];
    }
    return XT_OK;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Free allocated memory for a DSV object.
 *      The dsv_line_t structure contains an array of strings, each
 *      holding one field from the line, and an an array of delimiters,
 *      each holding the character that ended the corresponding field.
 *      Note that each field could potentially end with a different
 *      delimiter, as multiple delimiters can be specified.
 *
 *  Arguments:
 *      dsv_line    Pointer to a populated dsv_line_t structure
 *
 *  Returns:
 *      The number of fields freed.  Fields set to NULL are not freed.
 *
 *  Examples:
 *      dsv_line_t  line;
 *
 *      while ( dsv_line_read(&line, stdin, "\t") != EOF )
 *      {
 *          dsv_line_write(line, stdout);
 *          dsv_line_free(&line);
 *      }
 *
 *  See also:
 *      dsv_line_init(3), dsv_line_free(3),
 *      dsv_line_read(3), dsv_line_write(3), dsv_line_copy(3),
 *      dsv_read_field(3), dsv_read_field_malloc(3),
 *      dsv_skip_field(3), dsv_skip_rest_of_line(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-01  Jason Bacon Begin
 ***************************************************************************/

int     dsv_line_free(dsv_line_t *dsv_line)

{
    int     c, count = 0;
    
    if ( dsv_line->fields != NULL )
    {
	for (c = 0; c < dsv_line->num_fields; ++c)
	    if ( dsv_line->fields[c] != NULL )
	    {
		free(dsv_line->fields[c]);
		++count;
	    }
	if ( dsv_line->fields != NULL )
	    free(dsv_line->fields);
    }
    dsv_line->num_fields = 0;
    return count;
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_read_field(stream, buff, buff_size, '\\\\\t', len)
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      buff        Character buff into which field is copied
 *      buff_size   Size of the array passed to buff
 *      len         Pointer to a variable which will receive the field length
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
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_read_field_malloc(stream, *buff, *buff_size, '\\\\\t', len)
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      buff        Character buff into which field is copied
 *      buff_size   Size of the array passed to buff
 *      len         Pointer to a variable which will receive the field length
 *
 *  See also:
 *      dsv_read_field_malloc(3)
 ***************************************************************************/

int     tsv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size,
		       size_t *len)

{
    return dsv_read_field_malloc(stream, buff, buff_size, "\t", len);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_field(stream, '\\\\\t')
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      len         Length of field discarded
 *
 *  See also:
 *      dsv_skip_field(3)
 ***************************************************************************/

int     tsv_skip_field(FILE *stream, size_t *len)

{
    return dsv_skip_field(stream, "\t", len);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_rest_of_line(stream)
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
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
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_read_field(stream, buff, buff_size, ',', len)
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      buff        Character buff into which field is copied
 *      buff_size   Size of the array passed to buff
 *      len         Pointer to a variable which will receive the field length
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
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_read_field_malloc(stream, *buff, *buff_size, ',', len)
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      buff        Character buff into which field is copied
 *      buff_size   Size of the array passed to buff
 *      len         Pointer to a variable which will receive the field length
 *
 *  See also:
 *      dsv_read_field_malloc(3)
 ***************************************************************************/

int     csv_read_field_malloc(FILE *stream, char **buff, size_t *buff_size,
		       size_t *len)

{
    return dsv_read_field_malloc(stream, buff, buff_size, ",", len);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_field(stream, ',')
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *      len         Length of field discarded
 *
 *  See also:
 *      dsv_skip_field(3)
 ***************************************************************************/

int     csv_skip_field(FILE *stream, size_t *len)

{
    return dsv_skip_field(stream, ",", len);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lbiolibc
 *
 *  Description:
 *      Equivalent to dsv_skip_rest_of_line(stream)
 *
 *  Arguments:
 *      stream      FILE stream from which field is read
 *
 *  See also:
 *      dsv_skip_rest_of_line(3)
 ***************************************************************************/

int     csv_skip_rest_of_line(FILE *stream)

{
    return dsv_skip_rest_of_line(stream);
}
