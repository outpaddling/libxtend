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
#include "xtend.h"

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

