#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "string.h"
#include "proc.h"
#include "ctype.h"
#include "mem.h"

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_strlupper() - Copy string and convert lower case to uppper
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strlupper(3) copies a string from src to dest, up to a maximum of
 *      dest_size - 1 characters.
 *      It behaves exactly like strlcpy(3), except that any lower
 *      case characters in the string are converted to upper case.
 *  
 *  Arguments:
 *      src         Pointer to null-terminated string to be copied
 *      dest        Pointer to a character array to receive the copy
 *      dest_size   Size of the destination array
 *
 *  Returns:
 *      Size of the src string.  If this differs from dest_size, then
 *      we knoiw the copy is truncated.
 *
 *  Examples:
 *      char    src[] = "Some text",
 *      dest    [DEST_SIZE + 1];
 *
 *      if ( xt_strlupper(dest, src, DEST_SIZE + 1) != DEST_SIZE + 1 )
 *          fputs("Warning: String truncated.\n", stderr);
 *
 *  See also:
 *      xt_strllower(3), strlcpy(3), strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-01-04  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strlupper(char *dest, const char *src, size_t dest_size)

{
    size_t  c;
    
    for (c = 0; (src[c] != '\0') && (c < dest_size - 1); ++c)
	dest[c] = toupper((int)src[c]);
    dest[c] = '\0';
    while ( src[c] != '\0' )
	++c;
    return c;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_strupper() - Covert all lower case characters to upper
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strupper(3) converts lower case characters in a string to upper
 *      case, overwriting the original.  It is functionally equivalent to
 *      xt_strlupper(str, str, strlen(str)).  It is implemented separately for
 *      efficiency, since using xt_strlupper(3) for this purpose requires
 *      knowing or computing the length of the string and passing three
 *      arguments instead of one.
 *  
 *  Arguments:
 *      str         Pointer to null-terminated string to be copied
 *
 *  Returns:
 *      Size of the src string.
 *
 *  Examples:
 *      char    src[] = "Some text",
 *      dest    [DEST_SIZE + 1];
 *
 *      if ( xt_strlupper(dest, src, DEST_SIZE + 1) != DEST_SIZE + 1 )
 *          fputs("Warning: String truncated.\n", stderr);
 *
 *  See also:
 *      xt_strllower(3), strlcpy(3), strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-01-04  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strupper(char *str)

{
    size_t  c;
    
    for (c = 0; str[c] != '\0'; ++c)
	str[c] = toupper((int)str[c]);
    return c;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_strllower() - Copy string and convert upper case to lower
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strllower(3) copies a string from src to dest, up to a maximum of
 *      dest_size - 1 characters.
 *      It behaves exactly like strlcpy(3), except that any upper
 *      case characters in the string are converted to lower case.
 *  
 *  Arguments:
 *      src         Pointer to null-terminated string to be copied
 *      dest        Pointer to a character array to receive the copy
 *      dest_size   Size of the destination array
 *
 *  Returns:
 *      Size of the src string.  If this differs from dest_size, then
 *      we knoiw the copy is truncated.
 *
 *  Examples:
 *      char    src[] = "Some text",
 *      dest    [DEST_SIZE + 1];
 *
 *      if ( xt_strllower(dest, src, DEST_SIZE + 1) != DEST_SIZE + 1 )
 *          fputs("Warning: String truncated.\n", stderr);
 *
 *  See also:
 *      xt_strllower(3), strlcpy(3), strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-01-04  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strllower(char *dest, const char *src, size_t dest_size)

{
    size_t  c;
    
    for (c = 0; (src[c] != '\0') && (c < dest_size - 1); ++c)
	dest[c] = tolower((int)src[c]);
    dest[c] = '\0';
    while ( src[c] != '\0' )
	++c;
    return c;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_strlower() - Convert all upper case characters to lower
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strlower(3) converts upper case characters in a string to lower
 *      case, overwriting the original.  It is functionally equivalent to
 *      xt_strllower(str, str, strlen(str)).  It is implemented separately for
 *      efficiency, since using xt_strllower(3) for this purpose requires
 *      knowing or computing the length of the string and passing three
 *      arguments instead of one.
 *  
 *  Arguments:
 *      str         Pointer to null-terminated string to be copied
 *
 *  Returns:
 *      Size of the src string.
 *
 *  Examples:
 *      char    src[] = "Some text",
 *      dest    [DEST_SIZE + 1];
 *
 *      if ( xt_strllower(dest, src, DEST_SIZE + 1) != DEST_SIZE + 1 )
 *          fputs("Warning: String truncated.\n", stderr);
 *
 *  See also:
 *      xt_strllower(3), strlcpy(3), strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-01-04  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strlower(char *str)

{
    size_t  c;
    
    for (c = 0; str[c] != '\0'; ++c)
	str[c] = tolower((int)str[c]);
    return c;
}


/***************************************************************************
 *  Name:
 *      xt_str_argv_cat() - Append argv-style list to a string
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Append an argv style list of arguments to a string.  This is
 *      useful for constructing a command to be passed to a shell via
 *      system() or similar methods.
 *
 *  Arguments:
 *      string              String to which argv elements are appended
 *      argv                Character pointer array to a list of elements
 *      first_arg           Index of first argument to append
 *      string_buff_size    Size of string array including null byte
 *
 *  Returns:
 *      Length of string + all argv elements.  If this is greater than
 *      string_buff_size, then the string has been truncated.
 *
 *  Examples:
 *      char    cmd[CMD_MAX + 1] = "ls",
 *              *argv[] = { "-l", NULL };
 *
 *      if ( xt_str_argv_cat(cmd, argv, 0, CMD_MAX + 1) > CMD_MAX + 1 )
 *          fputs("string is truncated.\n", stderr);
 *      else
 *          system(cmd);
 *
 *  See also:
 *      strlcpy(3), strlcat(3), snprintf(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-09-30  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_str_argv_cat(char *string, char *argv[], size_t first_arg,
		     size_t string_buff_size)

{
    size_t  c,
	    len;
    
    len = strlen(string);
    for (c = first_arg; argv[c] != NULL; ++c)
    {
	len += strlen(argv[c]);
	strlcat(string, argv[c], string_buff_size);
	strlcat(string, " ", string_buff_size);
    }
    return len;
}


/***************************************************************************
 *  Name:
 *      xt_strblank() - Return true is a string is empty or only whitespace
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strblank() returns true if the null-terminated string contains only
 *      whitespace or nothing at all.  It is the null-terminated string
 *      equivalent of isblank(3), which tests a single character.
 *  
 *  Arguments:
 *      string: A null-terminated string
 *
 *  Returns:
 *      true is string contains only whitespace, or nothing
 *      false if any non-whitespace characters are present
 *
 *  See also:
 *      isblank(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     xt_strblank(const char *string)

{
    while ( *string != '\0' )
    {
	if ( !isspace((size_t)(*string)) )   /* Not blank? */
	    return 0;
	++string;
    }
    return 1;
}


/***************************************************************************
 *  Name:
 *      xt_strisint() - Return true if string represents an integer value
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Determine whether a string is a valid integer by attempting to
 *      convert it using strtoll().
 *
 *  Arguments:
 *      string: The string to be tested
 *      base:   The expected base of the integer (usually 8, 10, or 16)
 *
 *  Returns:
 *      Non-zero value if the string represents an integer, zero otherwise
 *
 *  See also:
 *      strtoll(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-24  Jason Bacon Begin
 ***************************************************************************/

int     xt_strisint(const char *string, int base)

{
    char    *end;
    
    // FIXME: Use a more efficient design.  No need to actually convert.
    strtoll(string, &end, base);
    return *end == '\0';
}


/***************************************************************************
 *  Name:
 *      xt_strisreal() - Return true if string represents a valid real value
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Determine whether a string is a valid real number by attempting to
 *      convert it using strtod().
 *
 *  Arguments:
 *      string: The string to be tested
 *
 *  Returns:
 *      Non-zero value if the string represents a real number, zero otherwise
 *
 *  See also:
 *      strtod(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-24  Jason Bacon Begin
 ***************************************************************************/

int     xt_strisreal(const char *string)

{
    char    *end;
    
    // FIXME: Use a more efficient design.  No need to actually convert.
    strtod(string, &end);
    return *end == '\0';
}


/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strlbasecpy() is a convenience for copying a string to a non-zero
 *      starting position in another string.  The caller provides the address
 *      of the destination to which string should be copied, the base address
 *      of the array containing the destination, and the TOTAL length of the
 *      destination array.  xt_strlbasecpy() then computes the distance from
 *      the destination address to the end of the array and like strlcpy(),
 *      prevents overrun from occurring.
 *  
 *  Arguments:
 *      dest:       Address to which src is copied
 *      dest_base:  Base address of the array containing dest address
 *      src:        Address of null-terminated string to be copied
 *      dstsize:    Size of the dest array
 *
 *  Returns:
 *      The original value of dest
 *
 *  See also:
 *      strlcpy(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char   *xt_strlbasecpy(char *dest, const char *dest_base, const char *src,
		    size_t dstsize)

{
    char        *save_dest;
    const char  *end;

    save_dest = dest;
    dstsize -= dest-dest_base;
    end = src + dstsize;
    while ((*src != '\0') && (src < end - 1))
	*dest++ = *src++;
    *dest = '\0';
    return (save_dest);
}


/***************************************************************************
 *  Name:
 *      xt_strptrcmp() - Compare two strings through char ** pointers
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Compare two strings via indirect pointers.  This can be used by
 *      qsort(), heapsort(), etc. to sort an argv-style pointer array,
 *      swapping only the pointers rather than the string contents.
 *
 *  Arguments:
 *      p1, p2: Pointers to pointers to the strings to compare
 *
 *  Returns:
 *      0 if the strings are the same, a value < 0 if the string at p1
 *      is lexically < that at p2, a value > 0 otherwise.
 *
 *  See also:
 *      strcmp(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-04  Jason Bacon Begin
 ***************************************************************************/

int     xt_strptrcmp(const char **p1, const char **p2)

{
    return strcmp(*p1, *p2);
}


/***************************************************************************
 *  Name:
 *      xt_strptrcasecmp() - Compare two strings through char ** pointers, case insensitive
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Compare two strings without regard for case
 *      via indirect pointers.  This can be used by
 *      qsort(), heapsort(), etc. to sort an argv-style pointer array,
 *      swapping only the pointers rather than the string contents.
 *
 *  Arguments:
 *      p1, p2: Pointers to pointers to the strings to compare
 *
 *  Returns:
 *      0 if the strings are the same, a value < 0 if the string at p1
 *      is lexically < that at p2, a value > 0 otherwise.
 *
 *  See also:
 *      strcmp(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-04  Jason Bacon Begin
 ***************************************************************************/

int     xt_strptrcasecmp(const char **p1, const char **p2)

{
    return strcasecmp(*p1, *p2);
}


/***************************************************************************
 *  Name:
 *      xt_strshellcpy() - Expand a string containing shell metacharacters
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strshellcpy() expands a string containing shell meta-characters,
 *      usually a shell command, as a Unix shell would do before execution.
 *      This is useful if you want to avoid spawning an unnecessary shell
 *      process, such as when using fork(2) and exec(3) directly instead
 *      of using system(3).
 *
 *      Currently supports:
 *          ~/: process owner's home directory
 *          $: environment variable
 *  
 *  Arguments:
 *      src:        String containing meta-characters
 *      dest:       Expanded string
 *      dest_len:   Size of destination array
 *
 *  Returns:
 *      0 on success, -1 if expansion did not fit in dest_len
 *
 *  See also:
 *      sh(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     xt_strshellcpy(char *dest, const char *src, size_t dest_len)

{
    char    home[PATH_MAX + 1],*p,*val,var[PATH_MAX + 1];
    int     c;
    
    while ( dest_len && (*src != '\0') )
    {
	switch(*src)
	{
	    case    '~':
		++src;
		if ( *src == '/' )  /* Process owner's home dir */
		{
		    xt_get_home_dir(home,PATH_MAX);
		    for (p=home; dest_len-- && (*p != '\0'); )
			*dest++ = *p++;
		}
		else
		{
		    /* Get somebody else's home dir */
		}
		break;
	    case    '$':
		++src;
		/* Get ENV variable name */
		for (p=var, c=0; (c<PATH_MAX) && ISIDENT((size_t)(*src)); ++c)
		    *p++ = *src++;
		*p = '\0';
		
		/* Get value and copy to dest command */
		if ( (val = getenv(var)) != NULL )
		    while ( dest_len-- && (*val != '\0') )
			*dest++ = *val++;
		break;
	    default:
		*dest++ = *src++;
		--dest_len;
	}
    }
    *dest = '\0';
    if ( (dest_len == 0) && (*src != '\0') )
	return -1;
    else
	return 0;
}


/***************************************************************************
 *  Name:
 *      xt_strsqueeze() - Squeeze a string by replacing middle with ...
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Copy string src to dest, reducing to a maximum length of dstsize if
 *      necessary by replacing the center portion of the string with "...".
 *  
 *  Arguments:
 *      dest:   Pointer to a character array of at least len dstsize, where
 *              the possibly modified string is stored.
 *      src:    Point to a character array containing the string to compact
 *      dstsize: Length of the dest array
 *
 *  Returns:
 *      The length of the original string (like strlcpy(3))
 *
 *  Examples:
 *      #define MAXLEN  127
 *      char    limited_str[MAXLEN + 1],
 *              original_str[SOME_OTHER_LEN + 1];
 *      
 *      xt_strsqueeze(limited_str, original_str, MAXLEN + 1);
 *
 *  See also:
 *      strlcpy(3), strlcat(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-29  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_strsqueeze(char *dest, const char *src, size_t dstsize)

{
    size_t  len = strlen(src),
	    left_len,
	    right_len;
    
    if ( len <= dstsize )
	strlcpy(dest, src, dstsize);
    else
    {
	left_len = (dstsize - 3) / 2;
	right_len = dstsize - left_len - 3;
	memcpy(dest, src, left_len);
	strlcat(dest, "...", dstsize);
	strlcat(dest, src + len - right_len + 1, dstsize);
    }
    return len;
}


/***************************************************************************
 *  Name:
 *      xt_strtr() - Library function equivalent of tr(1)
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Translate characters in a string similar to tr(1), where each
 *      occurrence of from[i] is replaced with to[i] in string.
 *
 *      Currently only replacement is supported and flags is ignored.
 *      In the future, additional features such as deletion and
 *      compaction may be supported.
 *  
 *  Arguments:
 *      string  The string to be transformed
 *      from    Characters to be replaced with those in to
 *      to      Characters to replace those in from
 *      flags   Bit mask to enable optional features simlar to tr(1)
 *
 *  Examples:
 *      char    string[] = "Hello";
 *
 *      // Convert string to "HELLO"
 *      xt_strtr(string, "elo", "ELO", 0);
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-08-10  Jason Bacon Begin
 ***************************************************************************/

void    xt_strtr(char *string, const char *from, const char *to, int flags)

{
    char    *p,
	    *i;
    
    for (p = string; *p != '\0'; ++p)
    {
	i = strchr(from, *p);
	if ( i != NULL )
	{
	    //fprintf(stderr, "Replacing %c with %c\n", *p, to[i - from]);
	    //fflush(stderr);
	    *p = to[i - from];
	}
    }
}


/***************************************************************************
 *  Name:
 *      xt_strtrim() - Trim junk from both ends of a string
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Trim unwanted characters off both ends of a string.  Typically
 *      this is whitespace added to a comma-separated file or similar.
 *
 *  Arguments:
 *      string  The string to be trimmed
 *      fat     A string containing a list of characters to be removed
 *
 *  See also:
 *      strsep(3)
 *
 *  Examples:
 *      char    string[] = "  Alfred E. Neumann."
 *
 *      xt_strtrim(string, " .");
 *      puts(string);
 *
 *      Output is "Aldred E. Neumann"
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-09-24  Jason Bacon Begin
 ***************************************************************************/

void    xt_strtrim(char *string, const char *fat)

{
    char    *start, *end;
    
    for (start = string; (*start != '\0') && strchr(fat, *start); ++start)
	;
    for (end = start; *end != '\0'; ++end)
	;
    while ( (end >= string) && strchr(fat, *end) )
	--end;
    end[1] = '\0';
    if ( (start > string) && (end > start) )
	memmove(string, start, end - start + 2);
}


/***************************************************************************
 *  Name:
 *      xt_strviscpy() - Copy a string, converting invisible characters
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_strviscpy() copies a string from src to dest, converting invisible
 *      characters to a visible format much like the vis command or cat -v.
 *  
 *  Arguments:
 *      src:    Source string containing invisible characters
 *      dest:   Destination array to receive modified string
 *      maxlen: Maximum number of characters in dest, not including null byte
 *
 *  Returns:
 *      A pointer to dest
 *
 *  See also:
 *      vis(1), cat(1), strlcpy(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char    *xt_strviscpy(unsigned char *dest, const unsigned char *src,
		size_t maxlen)

{
    char    *d = (char *)dest;

    if ( (src == NULL) || (dest == NULL) )
	return NULL;
    
    while ( (*src != '\0') && (maxlen > 0) )
    {
	if ( (((unsigned char)*src < 128) && isprint(*src)) || (*src == '\n') )
	{
	    *d++ = *src++;
	    --maxlen;
	}
	else
	{
	    if ( maxlen > 4 )
	    {
		snprintf(d,maxlen,"\\%03o",(unsigned char)*src);
		++src;
		d+=4;
		maxlen-=4;
	    }
	}
    }
    *d = '\0';
    return (char *)dest;
}


/***************************************************************************
 *  Name:
 *      xt_ltostrn() - Convert a long to a string in any base from 2 to 36
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      xt_ltostrn() is a small, fast integer to string converter that can
 *      convert using any base from 2 to 36.  It is the converse of strtol(3).
 *      The size of the char buffer passed should be 1 more than maxlen to
 *      allow for a null byte.
 *  
 *  Arguments:
 *      string: char array to receive ascii text
 *      val:    value to convert to ascii
 *      base:   number base for conversion, must be between 2 and 36
 *      maxlen: size of 'string' array - 1 (to account for null byte)
 *
 *  Returns:
 *      A pointer to the converted string, or NULL if the string buffer was
 *      not big enough for all the xt_digits
 *
 *  See also:
 *      strtol(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char    *xt_ltostrn(char string[], long val, unsigned base, size_t maxlen)

{
    char    temp[maxlen+1], *p, *s = string;
    int     digit;
    
    if ( base > 36 )
	return NULL;
    
    /* Tack on - sign if negative */
    if ( val < 0 )
    {
	*s++ = '-';
	val = -val;
    }
    
    /* Convert val to ascii xt_digits (in reverse order) */
    for (p=temp; (val > 0) && (maxlen > 0); val /= base, --maxlen)
    {
	digit = val % base;
	if ( digit < 10 )
	    *p++ = digit+'0';
	else
	    *p++ = digit-10+'a';
    }
    
    /* Reverse xt_digits */
    while ( p > temp )
	*s++ = *(--p);
    *s = '\0';
    if ( val > 0 )
	return NULL;
    else
	return string;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_str2u64_hash() - Hash a string of up to 8 characters to a 64-bit integer
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_str2u64_hash()
 *      is a super-fast hash function that converts a string of 8 or fewer
 *      characters to a 64-bit integer.  Strings of more than 8 characters may
 *      also be hashed, though collisions will occur (same hash value for more
 *      than one string) if the first 8 characters are the same.
 *
 *      This sort of hashing is useful for storing lists
 *      of very short strings, as it eliminates the need to use strdup(),
 *      strlcpy(), and strcmp() for processing.  Strings can be compared
 *      for equality using a straight integer comparison.  Strings of 7
 *      or fewer characters can still be accessed as a string by simply
 *      casting to char * for output, then using lexical comparison with strcmp(),
 *      etc.  A string of 8 characters will not have a null-terminator.
 *
 *      The value returned varies depending on endianness.  Hence, hash
 *      values generated on one architecture will need to be byte swapped
 *      before comparison to values generated under a different endianness.
 *  
 *  Arguments:
 *      str     String to convert
 *
 *  Returns:
 *      uint64_t integer containing the characters in str
 *
 *  Examples:
 *      char        *s1 = "hello!", s2 = "Hello!";
 *      uint64_t    v1, v2;
 *      
 *      v1 = xt_str2u64_hash(s1);
 *      v2 = xt_str2u64_hash(s2);
 *      if ( v1 != v2 )
 *          printf("%s and %s are different.\n", (char *)&v1, (char *)&v2);
 *
 *  See also:
 *      strdup(3), strcmp(3), strlcpy(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-02  Jason Bacon Begin
 ***************************************************************************/

uint64_t    xt_str2u64_hash(const char *str)

{
    size_t      c;
    char        *p;
    uint64_t    v = 0;
    
    for (c = 0, p = (char *)&v; (c < sizeof(v)) && (str[c] != '\0'); ++c, ++p)
	*p = str[c];
    return v;
}


/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_strsplit() - Split a string into tokens
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_strsplit()
 *      splits a string into tokens separated by any character
 *      in the string argument sep.
 *      The function interface is similar to split() in awk, except that
 *      sep is a simple list of characters rather than a regular expression.
 *
 *      The array argument should be the address of a char ** variable.
 *      xt_strsplit() allocates memory for the pointers as needed and
 *      assigns one token to each pointer.
 *
 *      xt_strsplit() should only be used when an array of strings
 *      representing the tokens is actually needed.  In cases where each
 *      token can be immediately processed and forgotten, use a loop with
 *      strsep().  Introducing arrays into a program unnecessarily should
 *      avoided as a habit to maximize speed and minimize memory use.
 *
 *      Caution: xt_strsplit() is destructive: It replaces the separators
 *      in string with null bytes.  To preserve the original string,
 *      duplicate it with strdup() first and pass the copy to xt_strsplit().
 *  
 *  Arguments:
 *      string  String to be parsed for tokens
 *      array   Pointer array to be filled with tokens
 *      sep     Character string listing all recognized separators
 *
 *  Returns:
 *      The number of tokens into which string is separated, or 0 if
 *      a memory allocation or other failure occurred.
 *
 *  Examples:
 *      char    *string = "1,2,3,4,5", *copy, **array;
 *      size_t  c, tokens;
 *
 *      copy = strdup(string);
 *      tokens = xt_strsplit(copy, &array, ",");
 *      for (int c = 0; c < tokens; ++c)
 *          puts(array[c]);
 *
 *  See also:
 *      strsep(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-02-12  Jason Bacon Begin
 ***************************************************************************/

int     xt_strsplit(char *string, char ***array, const char *sep)

{
    size_t  c,
	    array_size = 64;

    if ((*array = xt_malloc(array_size, sizeof(*array))) == NULL )
    {
	fprintf(stderr, "xt_strsplit(): malloc() failed.\n");
	return 0;
    }
    
    for (c = 0; ((*array)[c] = strsep(&string, sep)) != NULL; )
    {
	if ( ++c == array_size )
	{
	    *array = xt_realloc(*array, array_size *= 2, sizeof(*array));
	    if ( *array == NULL )
	    {
		fprintf(stderr, "xt_strsplit(): malloc() failed.\n");
		return 0;
	    }
	}
    }
    
    // Trim
    *array = xt_realloc(*array, c, sizeof(*array));
    return c;
}
