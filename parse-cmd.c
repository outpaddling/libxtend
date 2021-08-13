#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "proc.h"
#include "string.h" // strshellcpy()

/***************************************************************************
 *  Library:
 *      #include <xtend/proc.h>
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

void    parse_cmd(char *argv[], char *cmd, size_t cmd_max_chars)

{
    char    cmd2[cmd_max_chars + 1];
    int     c;

    /* Expand shell meta-characters */
    strshellcpy(cmd2, cmd, cmd_max_chars);
    
    /* Break command into tokens for argv[] */
    argv[0] = strtok(cmd2, " \t");
    for (c = 1; (argv[c] = strtok(NULL, " \t")) != NULL; ++c)
	;
}
