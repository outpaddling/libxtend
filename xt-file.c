#include <string.h>
#include <sysexits.h>
#include <sys/stat.h>
#include "file.h"
#include "mem.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      Open a raw data file using fopen() or a gzipped, bzipped, or
 *      xzipped file using popen().  Must be used in conjunction with
 *      xt_fclose() to ensure that fclose() or pclose() is called where
 *      appropriate.
 *
 *  Arguments:
 *      filename:   Name of the file to be opened
 *      mode:       "r" or "w", passed to fopen() or popen()
 *
 *  Returns:
 *      A pointer to the FILE structure or NULL if open failed
 *
 *  See also:
 *      fopen(3), popen(3), gzip(1), bzip2(1), xz(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-09  Jason Bacon Begin
 ***************************************************************************/

FILE    *xt_fopen(const char *filename, const char *mode)

{
    char    *ext = strrchr(filename, '.'),
	    cmd[XT_CMD_MAX_CHARS + 1];
    
    if ( (strcmp(mode, "r") != 0 ) && (strcmp(mode, "w") != 0) )
    {
	fprintf(stderr, "xt_fopen(): Only \"r\" and \"w\" modes supported.\n");
	return NULL;
    }
    
    if ( ext == NULL )
    {
	fprintf(stderr, "xt_fopen(): No filename extension on %s.\n", filename);
	return NULL;
    }

    if ( *mode == 'r' )
    {
	if ( strcmp(ext, ".gz") == 0 )
	{
// Big Sur zcat requires a .Z extension and CentOS 7 lacks gzcat
#ifdef __APPLE__
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzcat %s", filename);
#else
	    snprintf(cmd, XT_CMD_MAX_CHARS, "zcat %s", filename);
#endif
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzcat %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xzcat %s", filename);
	    return popen(cmd, mode);
	}
	else
	    return fopen(filename, mode);
    }
    else    // "w"
    {
	if ( strcmp(ext, ".gz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "gzip -c > %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "bzip2 -c > %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XT_CMD_MAX_CHARS, "xz -c > %s", filename);
	    return popen(cmd, mode);
	}
	else
	    return fopen(filename, mode);
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      Close a FILE stream with fclose() or pclose() as appropriate.
 *      Automatically determines the proper close function to call using
 *      S_ISFIFO on the stream stat structure.
 *
 *  Arguments:
 *      stream: The FILE structure to be closed
 *
 *  Returns:
 *      The value returned by fclose() or pclose()
 *
 *  See also:
 *      fopen(3), popen(3), gzip(1), bzip2(1), xz(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-10  Jason Bacon Begin
 ***************************************************************************/

int     xt_fclose(FILE *stream)

{
    struct stat stat;
    
    fstat(fileno(stream), &stat);
    if ( S_ISFIFO(stat.st_mode) )
	return pclose(stream);
    else
	return fclose(stream);
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_inhale_strings()
 *      reads a list of strings from a file, one per line, into a pointer
 *      array.  Memory is allocated for the pointer array and for each
 *      string.
 *
 *      Memory should be freed using xt_free_strings(3) as soon as the
 *      strings are no longer needed.
 *
 *      Inhaling large amounts of data into arrays should generally be
 *      avoided in favor of more memory-efficient use-once-and-discard
 *      strategies, but may be advantageous for small lists of strings
 *      accessed repeatedly, or necessary for a few tasks such as sorting.
 *  
 *  Arguments:
 *      stream  FILE * from which strings are read, one per line
 *      list    Pointer to a char ** (poiner array), populated with strings
 *
 *  Returns:
 *      The number of strings read, XT_READ_IO_ERR on read error
 *
 *  Examples:
 *      FILE    *instream;
 *      char    **strings;
 *      ssize_t string_count;
 *
 *      string_count = xt_inhale_strings(instream, &strings);
 *      ...
 *      xt_free_strings(strings);
 *
 *  See also:
 *      xt_free_strings(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-21  Jason Bacon Begin
 ***************************************************************************/

ssize_t xt_inhale_strings(FILE *stream, char ***list)

{
    size_t  list_size = 1024,
	    c,
	    buff_size,
	    len;
    char    *temp;
    
    if ( (*list = (char **)xt_malloc(list_size, sizeof(*list))) == NULL )
    {
	fprintf(stderr, "load_strings(): Unable to allocate list.\n");
	return EX_UNAVAILABLE;
    }
    
    buff_size = 0;  // Make xt_read_line_malloc() allocate a new string
    for (c = 0; xt_read_line_malloc(stream, &temp, &buff_size, &len) != EOF; ++c)
    {
	if ( c == list_size - 1 )
	{
	    list_size *= 2;
	    if ( (*list = (char **)xt_realloc(*list, list_size, sizeof(*list))) == NULL )
	    {
		fprintf(stderr, "load_strings(): Unable to reallocate list.\n");
		return EX_UNAVAILABLE;
	    }
	}
	(*list)[c] = temp;
	buff_size = 0;  // Make xt_read_line_malloc() allocate a new string
    }
    (*list)[c] = NULL;  // So xt_free_strings() doesn't need count
    return c;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_read_line_malloc()
 *      reads a single line of text (up to the next newline or EOF)
 *      from stream, allocating and/or extending the provided buffer if
 *      needed.
 *
 *      The buff_size argument must be initilized to 0 if buff has
 *      not been previously allocated.  This will cause an initial
 *      allocation to occur.  If buff has been previously allocated,
 *      the buff_size must accurately reflect the allocated memory size.
 *      This will happen naturally when reusing buff in a loop, as shown
 *      in the example below.
 *  
 *  Arguments:
 *      stream:     FILE stream from which field is read
 *      buff:       Character buffer into which field is copied
 *      buff_size:  Size of the array passed to buff
 *      len:        Pointer to a variable which will receive the field length
 *
 *  Returns:
 *      Delimiter ending the read: either newline or EOF
 *
 *  Examples:
 *      FILE    *stream;
 *      char    *buff;
 *      size_t  buff_len, len;
 *
 *      // Reuse buff to minimize malloc() calls.  buff will be extended
 *      // as needed when longer strings are read.  Initialize buff here
 *      // rather than above for the most cohesive code.
 *      buff_len = 0;
 *      while ( ffile_read_line_malloc(stream, buff, &buff_len, &len) != EOF )
 *      {
 *      }
 *
 *  See also:
 *      dsv_read_field_malloc(3), ffgetc(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-20  Jason Bacon Begin
 ***************************************************************************/

int     xt_read_line_malloc(FILE *stream, char **buff, size_t *buff_size,
			    size_t *len)

{
    size_t  c;
    int     ch;
    
    if ( *buff_size == 0 )
    {
	*buff_size = 1024;
	*buff = xt_malloc(*buff_size, sizeof(**buff));
	if ( *buff == NULL )
	    return XT_MALLOC_FAILED;
    }
    
    for (c = 0; ( ((ch = getc(stream)) != '\n') && (ch != EOF) ); ++c)
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
    //fprintf(stderr, "buff = %s\n", *buff);
    *len = c;

    /* Trim array */
    if ( *buff_size != c + 1 )
    {
	*buff_size = c + 1;
	*buff = xt_realloc(*buff, *buff_size, sizeof(**buff));
    }
    //fprintf(stderr, "Returning %d\n", ch);
    return ch;
}
