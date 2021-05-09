#include <errno.h>
#include <sys/stat.h>

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      file_mod_cmp() compares the modification times of file1 and file2.
 *      It compares modification times on two files using the same rules
 *      as "make", and returns an strcmp(3) compatible status value indicating
 *      which is older.  A file that doesn't exist is considered
 *      older than the big bang.
 *  
 *  Arguments:
 *      file1, file2: Names of two filesystem objects whose time stamps
 *      are to be compared
 *
 *  Returns:
 *      A value < 0 if file1 is older or does not exist.
 *      A value > 0 if file2 is older or does not exist.
 *      0 if the files have identical modification times, or neither exists.
 *
 *  See also:
 *      make(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

int     file_mod_cmp(const char *file1, const char *file2)

{
    struct stat stats1, stats2;
    int     rc1,rc2;
    extern int errno;

    rc1 = stat(file1, &stats1);
    rc2 = stat(file2, &stats2);
    
    /* Both or neither exist */
    if ( rc1 == rc2 )
    {
	if (rc1 == 0)   /* Both files exist */
	    return(stats1.st_mtime - stats2.st_mtime);
	else
	    return(0);  /* Neither file exists */
    }
    else    /* One of the two files exists */
    {
	if ((rc1 == -1) && (errno == ENOENT))   /* file1 doesn't exist */
	    return (-1);
	else if ((rc2 == -1) && (errno == ENOENT))   /* file2 dne */
	    return (1);
    }
    return(0);
}
