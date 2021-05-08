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

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "bacon.h"

/****************************************************************************
 Name:
    Return the name of the process owner's home directory.
 
 Description: 
    get_home_dir() determines the full pathname of the process owner's
    home directory.  The information is retrieved using a call to
    getpwuid(3), and copied to the argument "dir".
    
    The name is stored in dir up to maxlen characters.
    Note that up to maxlen characters are stored, not including the 
    null terminator, hence the buffer should be at least maxlen+1
    bytes long.
 
 Author: 
    Jason W. Bacon
 
 Returns: 
    A pointer to dir, or NULL upon failure.
 ****************************************************************************/

char   *get_home_dir(
	char    dir[],  /* buffer for directory name */
	int     maxlen  /* maximum name length */
	)

{
    int     user;
    struct passwd *pwentry;

    /* Determine who the user is */
    user = getuid();

    /* Get password file entry */
    if ((pwentry = getpwuid(user)) == NULL)
	return (NULL);
 
    strlcpy(dir, pwentry->pw_dir,maxlen);
    return (dir);
}

