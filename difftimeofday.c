#include <sys/time.h>
#include "time.h"

/***************************************************************************
 *  Library:
 *      #include <xtend/time.h>
 *      -lextend
 *
 *  Description:
 *      difftimeofday() returns the difference, in microseconds, between two 
 *      time values returned by gettimeofday(3).  This function can be used
 *      to get a good estimate of the real time elapsed in a process between
 *      any two points (where calls to gettimeofday(3) are strategically
 *      placed.)
 *  
 *  Arguments:
 *      later, earlier: timeval structures populated by gettimeofday(3)
 *
 *  Returns:
 *      The difference between the two times in microseconds
 *
 *  See also:
 *      gettimeofday(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  Circa 1990  Jason Bacon Begin
 ***************************************************************************/

time_t  difftimeofday(struct timeval *later, struct timeval *earlier)

{
    return 1000000 * (later->tv_sec - earlier->tv_sec) +
	    (later->tv_usec - earlier->tv_usec);
}
