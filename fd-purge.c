#include <unistd.h>
#include <fcntl.h>
#include "file.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/file.h>
 *      -lxtend
 *
 *  Description:
 *      fd_purge() reads and discards unwanted input data (such as leftover
 *      input from a keyboard or mouse) from the input file descriptor fd.
 *  
 *  Arguments:
 *      fd: File descriptor to purge
 *
 *  See also:
 *      read(3), fcntl(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

void    fd_purge(int fd)

{
    char    buff[128];
    int     old_flags;
    
    old_flags = fcntl(fd,F_GETFL,0);
    
    /* Prevent processing from waiting for new input */
    fcntl(fd,F_SETFL,O_NONBLOCK);
    
    /* Remove pending characters */
    while ( read(fd,buff,128) != -1 )
	;
    
    fcntl(fd,F_SETFL,old_flags);
}
