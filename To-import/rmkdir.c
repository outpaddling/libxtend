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

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "bacon.h"

/**********************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 **********************************************************************/

int     rmkdir(char *path,mode_t mode)

{
    char    *parent_end;
    
    /* First try given path */
    if ( mkdir(path,mode) == 0 )
	return 0;
    else
    {
	/* Recursively attempt to make parent directories */
	parent_end = strrchr(path,'/');
	if ( parent_end == NULL )
	{
	    /* Ran out of ancestors - give it up */
	    return -1;
	}
	else
	{
	    /* Try to make parent with recursive call */
	    *parent_end = '\0';
	    if ( rmkdir(path,mode) == 0 )
	    {
		/* If parent successfully made, try again to make current */
		*parent_end = '/';
		return mkdir(path,mode);
	    }
	    else
	    {
		*parent_end = '/';
		return -1;
	    }
	}
    }
}

