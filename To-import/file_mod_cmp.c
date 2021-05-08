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

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "bacon.h"

/**
 * \addtogroup libbacon
 *  @{
 */

/**
 *  \brief  Compare the modification times of two files.
 *
 *  file_mod_cmp() compares the modification times of file1 and file2.
 *  It compares modification times on two files using the same rules
 *  as "make", and returns an strcmp(3) compatible status value indicating
 *  which is older.  A file that doesn't exist is considered
 *  older than the big bang.
 *  
 *
 *  \returns
 *      A value < 0 if file1 is older or does not exist.
 *      A value > 0 if file2 is older or does not exist.
 *      0 if the files have identical modification times, or neither exists.
 ****************************************************************************/

int     file_mod_cmp(file1, file2)
char   *file1, *file2;

{
    struct stat stats1, stats2;
    int     rc1,rc2;
    extern int errno;

    rc1 = stat(file1, &stats1);
    rc2 = stat(file2, &stats2);
    
    /* Both or neither exist */
    if ( rc1 == rc2 )
    {
	if (rc1 == 0)   /* Both files exist */
	    return(stats1.st_mtime - stats2.st_mtime);
	else
	    return(0);  /* Neither file exists */
    }
    else    /* One of the two files exists */
    {
	if ((rc1 == -1) && (errno == ENOENT))   /* file1 doesn't exist */
	    return (-1);
	else if ((rc2 == -1) && (errno == ENOENT))   /* file2 dne */
	    return (1);
    }
    return(0);
}

/** @} */

