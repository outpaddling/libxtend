/**********************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 **********************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sysexits.h>
#include "bacon.h"

void    va_usage(char *format_string,...)

{
    va_list list;
    char    new_format[1024];
    
    va_start(list,format_string);
    snprintf(new_format,1023,"Usage: %s",format_string);
    vfprintf(stderr,new_format,list);
    exit(EX_USAGE);
}
