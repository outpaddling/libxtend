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

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "bacon.h"

#define NAME_LEN    128

/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Arguments:   src: String containing meta-characters
 *              dest: expanded string
 *              dest_len: size of destination array
 * Return values: 0 for success
 * Description:
 *      Expand a string containing shell meta-characters, usually a
 *      shell command using C-shell syntax.
 *      Currently supports:
 *          ~/: process owner's home directory
 *          $: environment variable
 ****************************************************************************/

int     meta_chars(dest,src,dest_len)
char    *dest,*src;
size_t  dest_len;

{
    char    home[PATH_MAX+1],*p,*val,var[NAME_LEN+1];
    int     c;
    
    while ( dest_len && (*src != '\0') )
    {
	switch(*src)
	{
	    case    '~':
		++src;
		if ( *src == '/' )  /* Process owner's home dir */
		{
		    get_home_dir(home,PATH_MAX);
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
		for (p=var, c=0; (c<NAME_LEN) && ISIDENT((size_t)(*src)); ++c)
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
    return 0;
}

