/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_str2file() - Dump a string to a file
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_str2file()
 *      dumps the contents of a string to the named file.  The
 *      file is overwritten if it already exists.
 *  
 *  Arguments:
 *      str         char array containing the text to dump
 *      filename    Pathname of the file to receive the text
 *      mode        Permissions, etc. e.g. 0644
 *
 *  Returns:
 *      XT_OK on success, XT_FAIL on failure.
 *      Check errno for file open failure details.
 *
 *  Examples:
 *      if ( xt_str2file("Hello, world!\n", "hello.txt") != XT_OK )
 *          // Writes text form of errno after message
 *          perror("Failed to write to hello.txt: ");
 *
 *  See also:
 *      xt_file2str(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-10-05  Jason Bacon Begin
 ***************************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "common.h"

int     xt_str2file(const char *str, const char *filename, unsigned mode)

{
    int     fd;
    
    if ( (fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, mode)) == -1 )
        return XT_FAIL;
    
    if ( write(fd, str, strlen(str)) == -1 )
    {
        close(fd);
        return XT_FAIL;
    }
    
    close(fd);
    
    return XT_OK;
}
