#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sysexits.h>
#include "proc.h"
#include "string.h" // strshellcpy()

/***************************************************************************
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      Breaks a shell command into an argv[] style array suitable
 *      for spawnvp() or execv*().  A copy of cmd is created using
 *      strshellcpy(), which expands certain shell features such as
 *      variables and paths starting with '~'.  The copy is then
 *      modified by replacing separators with '\0' and the argv[] array
 *      is populated with pointers to each token in the copy.
 *  
 *  Arguments:
 *      argv:   Pointer array to be filled with command tokens
 *      cmd:    Raw command string with limited meta-character support
 *              from strshellcpy(3)
 *
 *  Returns:
 *      Pointer to strdup() copy of cmd, which should be freed as soon
 *      as possible when argv[] is no longer needed.
 *
 *
 *  Examples:
 *      char *cmd, *argv[], *expanded_cmd;
 *
 *      expanded_cmd = parse_cmd(argv, cmd);
 *      spawnvp(P_WAIT, P_NOECHO, argv, NULL, NULL, NULL);
 *      free(expanded_cmd);
 *
 *  See also:
 *      spawnvp(3), spawnlp(3), exec(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

char    *parse_cmd(char *argv[], const char *cmd)

{
    char    *cmd_copy;
    int     c;

    if ( (cmd_copy = malloc(XT_CMD_MAX_CHARS)) == NULL )
    {
	fprintf(stderr, "parse_cmd(): malloc failed.\n");
	exit(EX_UNAVAILABLE);
    }
    
    /* Expand shell meta-characters */
    // FIXME: Make sure strshellcpy() stops 1 short of max and remove -1
    strshellcpy(cmd_copy, cmd, XT_CMD_MAX_CHARS - 1);
    
    /* Break command into tokens for argv[] */
    argv[0] = strtok(cmd_copy, " \t");
    for (c = 1; (argv[c] = strtok(NULL, " \t")) != NULL; ++c)
	;
    return cmd_copy;
}
