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

/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Return values:
 *      Like memcmp(), strcmp(), etc.
 *          str1 < str2, < 0
 *          str1 > str2, > 0
 *          str1 == str2, 0
 * Description:
 *      Fast case-insensitive fixed-length string comparison
 *      Works for ASCII or EBCDIC, so don't change the 'a' - 'A'
 *      construct
 *********************************************************************/

#include <ctype.h>
#include "bacon.h"

int     memicmp(str1, str2, len)
char   *str1, *str2;
int     len;

{
    /* Don't make static or register - compiler can register cache autos */
    int     c1, c2, diff = 'a' - 'A';

    do
    {
	/* Convert c1 and c2 to lower case before compare */
	if ( isupper(c1 = *str1++) )
	    c1 += diff;
	if ( isupper(c2 = *str2++) )
	    c2 += diff;
    } while ((c1 == c2) && (--len));    /* Go until diff or len */
    return (c1 - c2);   /* Return >0, 0, or <0 */
}

