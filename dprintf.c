#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#if defined(__sun__)

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      The xt_dprintf() function, which takes a file descriptor rather
 *      than a FILE stream pointer, is provided by many systems including
 *      BSDs and Linux, but not by all.  Use of xt_xt_dprintf() from
 *      libxtend will ensure portability of code.
 *  
 *  Arguments:
 *      fd      File descriptor to which items are written
 *      format  printf-style format string
 *      ...     Additional arguments depending on format
 *
 *  Returns:
 *      The number of items written
 *
 *  Examples:
 *      int     fd;
 *
 *      if ( (fd = open(filename, O_WRONLY|O_CREAT)) != -1 )
 *      {
 *          xt_xt_dprintf(fd, "fd = %d\n", fd);
 *          ...
 *          close(fd);
 *      }
 *
 *  See also:
 *      fprintf(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2022-08-20  Jason Bacon Begin
 ***************************************************************************/

int     xt_dprintf(int fd, const char * restrict format, ...)

{
    char    *buff;
    int     count;
    va_list ap;
    
    va_start(ap, format);
    count = vasprintf(&buff, format, ap);
    write(fd, buff, strlen(buff));
    free(buff);
    va_end(ap);
    
    return count;
}
#endif
