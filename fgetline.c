#include <stdio.h>
#include "file.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      fgetline() reads a line of text from a FILE stream.  Input is
 *      terminated when a newline or end of file is encountered,
 *      or when maxlen characters have been read.  Note that up to maxlen
 *      characters may be stored, NOT INCLUDING THE NULL TERMINATOR BYTE,
 *      hence the buffer should be at least maxlen+1 bytes long. Unlike
 *      fgets(3), fgetline() does not store the trailing newline character
 *      in the string.
 *  
 *  Arguments:
 *      fp:     Input stream from which to read
 *      buff:   Character array into which line is read
 *      maxlen: Size of array buff, not counting null byte
 *
 *  Returns:
 *      The number of bytes read, or EOF if EOF is encountered before a newline
 *
 *  See also:
 *      fgets(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/
 
size_t  xt_fgetline(FILE *fp, char *buff, size_t maxlen)

{
    char    *p = buff, 
	    *end = buff+maxlen;
    int     ch;

    /* Read to end of line, end of file, or maxlen characters */
    while ( ((ch = getc(fp)) != EOF) && (ch != '\n') && (p < end) )
	*p++ = ch;
    *p = '\0';      /* Replace \n with \0, or add \0 after last char */
    
    if (ch == EOF)
	return EOF;
    else
	return p - buff;  /* Return string length */
}
