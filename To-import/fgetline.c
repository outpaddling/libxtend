/*
    Copyright (c) 1994-2003, Jason W. Bacon, Acadix Software Systems
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer. Redistributions
    in binary form must reproduce the above copyright notice, this list of
    conditions and the following disclaimer in the documentation and/or
    other materials provided with the distribution. 

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#include <stdio.h>

/**
 * \addtogroup libbacon
 *  @{
 */

/**
 *  \brief  Safe replacement for gets(3) and fgets(3).
 *
 *  \param  fp      Input stream from which to read
 *  \param  buff    Character array into which line is read
 *  \param  maxlen  Size of array buff
 *
 *  fgetline() reads a line of text from a FILE stream.  Input is
 *  terminated when a newline ('\n') or end of file is encountered,
 *  or when maxlen characters have been read.  Note that up to maxlen
 *  characters may be stored, NOT INCLUDING THE NULL TERMINATOR BYTE,
 *  hence the buffer should be at least maxlen+1 bytes long. Unlike fgets(3),
 *  fgetline() does not store the trailing newline character in the string.
 * 
 *  \return     The number of bytes read.
 ****************************************************************************/
 
size_t  fgetline(
	    FILE *fp,       /* Input stream */
	    char *buff,     /* Buffer in which line will be stored */
	    size_t maxlen   /* Maximum number of characters to store */
	)

{
    char    *p = buff, 
	    *end = buff+maxlen;
    int     ch;

    /* Read to end of line, end of file, or maxlen characters */
    while ( ((ch = getc(fp)) != EOF) && (ch != '\n') && (p < end) )
    {
	*p++ = ch;
    }
    *p = '\0';      /* Replace \n with \0, or add \0 after last char */
    
    if (ch == EOF)
	return EOF;
    else
	return p-buff;  /* Return string length */
}

/** @} */

