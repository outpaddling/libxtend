#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sysexits.h>
#include "xtend.h"

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      va_usage() is a simple convenience function that takes a
 *      printf-style variable argument list, prints a message to stderr,
 *      and terminates the proces with an exit status of EX_USAGE.
 *      The message should indicate correct command-line usage of the
 *      calling program as conventional for Unix commands.
 *  
 *  Arguments:
 *      format_string:  printf-style format string
 *      Additional arguments to match placeholders in format_string
 *
 *  Returns:
 *      Does not return, terminates the calling process
 *
 *  See also:
 *      printf(3), vfprintf(3), exit(3), sysexits(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

void    va_usage(const char *format_string, ...)

{
    va_list list;
    char    new_format[XT_FORMAT_MAX_CHARS + 1];
    
    va_start(list,format_string);
    snprintf(new_format, XT_FORMAT_MAX_CHARS, "Usage: %s", format_string);
    vfprintf(stderr,new_format,list);
    exit(EX_USAGE);
}
