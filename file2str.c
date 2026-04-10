/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_file2str() - Inhale a file into a string
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_file2str()
 *      inhales dumps the contents of the named file into a new string,
 *      allocated using malloc().
 *
 *      The programmer is responsible for freeing the memory as soon
 *      as practical.
 *
 *      Note: This function should be used with caution on large files.
 *  
 *  Arguments:
 *      filename    Pathname of the file to read
 *
 *  Returns:
 *      A pointer to the allocated char array on success, NULL on failure.
 *      Check errno for file open failure details.
 *
 *  Examples:
 *      char    *hello;
 *
 *      if ( (string = xt_file2str("hello.txt")) == NULL )
 *      {
 *          // Writes text form of errno after message
 *          perror("Failed to read hello.txt: ");
 *      }
 *      else
 *      {
 *          puts(hello);
 *          free(hello);
 *      }
 *
 *  See also:
 *      xt_str2file(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-10-05  Jason Bacon Begin
 ***************************************************************************/

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"

char    *xt_file2str(const char *filename)

{
    struct stat st;
    int         fd;
    char        *str;
    
    if ( stat(filename, &st) == -1 )
        return NULL;
    
    if ( (fd = open(filename, O_RDONLY)) == -1 )
        return NULL;
    
    if ( (str = malloc(st.st_size)) == NULL )
        return NULL;
    
    if ( read(fd, str, st.st_size) != st.st_size )
    {
        close(fd);
        return NULL;
    }

    str[st.st_size] = '\0';
    close(fd);
    
    return str;
}
