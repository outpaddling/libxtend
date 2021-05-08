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
 * Arguments:   argv: Pointer array to be filled with command tokens
 *              cmd: Raw command string with limited meta-character
 *                   support from meta_chars()
 * Description:
 *      Breaks a shell command into an argv[] style array suitable
 *      for spawnvp() or execv*()
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "bacon.h"

void    parse_cmd(char *argv[], char *cmd)

{
    static char cmd2[256];
    int     c;

    /* Expand shell meta-characters */
    meta_chars(cmd2,cmd,255);
    
    /* Break command into tokens for argv[] */
    argv[0] = strtok(cmd2, " \t");
    for (c = 1; (argv[c] = strtok(NULL, " \t")) != NULL; ++c)
	;
}

