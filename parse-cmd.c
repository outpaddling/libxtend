#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "xtend.h"

/***************************************************************************
 *  Library:
 *      #include <xtend.h
 *      -lxtend
 *
 *  Description:
 *      Breaks a shell command into an argv[] style array suitable
 *      for spawnvp() or execv*()
 *  
 *  Arguments:
 *      argv:   Pointer array to be filled with command tokens
 *      cmd:    Raw command string with limited meta-character support
 *              from strshellcpy(3)
 *
 *  See also:
 *      spawnvp(3), spawnlp(3), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

void    parse_cmd(char *argv[], char *cmd)

{
    static char cmd2[XT_CMD_MAX_CHARS + 1];
    int     c;

    /* Expand shell meta-characters */
    strshellcpy(cmd2, cmd, XT_CMD_MAX_CHARS);
    
    /* Break command into tokens for argv[] */
    argv[0] = strtok(cmd2, " \t");
    for (c = 1; (argv[c] = strtok(NULL, " \t")) != NULL; ++c)
	;
}
