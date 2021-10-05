#include <string.h>
#include "string.h"     // strlcat() on Linux

/***************************************************************************
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Append an argv style list of arguments to a string.  This is
 *      useful for constructing a command to be passed to a shell via
 *      system() or similar methods.
 *
 *  Arguments:
 *      string              String to which argv elements are appended
 *      argv                Character pointer array to a list of elements
 *      first_arg           Index of first argument to append
 *      string_buff_size    Size of string array including null byte
 *
 *  Returns:
 *      Length of string + all argv elements.  If this is greater than
 *      string_buff_size, then the string has been truncated.
 *
 *  Examples:
 *      char    string[CMD_MAX + 1] = "";
 *
 *      if ( str_argv_cat(string, argv, 0, CMD_MAX + 1) > CMD_MAX + 1 )
 *          fputs("string is truncated.\n", stderr);
 *
 *  See also:
 *      strlcpy(3), strlcat(3), snprintf(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-09-30  Jason Bacon Begin
 ***************************************************************************/

size_t  str_argv_cat(char *string, char *argv[], size_t first_arg,
		     size_t string_buff_size)

{
    size_t  c,
	    len;
    
    len = strlen(string);
    for (c = first_arg; argv[c] != NULL; ++c)
    {
	len += strlen(argv[c]);
	strlcat(string, argv[c], string_buff_size);
	strlcat(string, " ", string_buff_size);
    }
    return len;
}
