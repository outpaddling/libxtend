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
 *      Use of these functions should have minimal impact on run time,
 *      unless called many times to measure time of a function with a very
 *      short run time.
 *  
 *  Arguments:
 *      later, earlier: timeval structures populated by gettimeofday(3)
 *
 *  Returns:
 *      The difference between the two times in microseconds
 *
 *  See also:
 *      gettimeofday(2), xt_tic(3), xt_toc(3)
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


/***************************************************************************
 *  Library:
 *      #include <xtend/time.h>
 *      -lxtend
 *
 *  Description:
 *      xt_tic() records the current time in a struct timeval structure.
 *      It is a simple wrapper around gettimeofday(2) meant for use with
 *      xt_toc(3), which reports elapsed time since the xt_tic() call.
 *
 *      The xt_tic() and xt_toc() functions are used to accurately determine
 *      the elapsed time of a segment of code, such as a loop that is
 *      suspected to be costly.  xt_tic() is inserted into the program just
 *      before the code and xt_toc() immediately after.
 *  
 *  Arguments:
 *      start_time  A struct timeval structure populated by xt_tic()
 *
 *  Returns:
 *      The exit status of gettimeofday(2)
 *
 *  Examples:
 *      struct timeval  start_time;
 *
 *      xt_tic(&start_time);
 *      // Code for which elapsed time is to be measured
 *      for (c = 0; c < bignum; ++c)
 *      {
 *          ...
 *      }
 *      xt_toc(stderr, "Elapsed time for loop: ", &start_time);
 *
 *  See also:
 *      xt_toc(3), difftimeofday(3), gettimeofday(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-08-20  Jason Bacon Begin
 ***************************************************************************/

int     xt_tic(struct timeval *start_time)

{
    return gettimeofday(start_time, NULL);
}


/***************************************************************************
 *  Library:
 *      #include <xtend/time.h>
 *      -lxtend
 *
 *  Description:
 *      xt_toc() reports the elapsed time since start_time, which should
 *      have been populated with xt_tic(3) or directly using
 *      gettimeofday(2).  Time is reported in microseconds, and if greater
 *      than one second, days, hours, and seconds.
 *
 *      The xt_tic() and xt_toc() functions are used to accurately determine
 *      the elapsed time of a segment of code, such as a loop that is
 *      suspected to be costly.  xt_tic() is inserted into the program just
 *      before the code and xt_toc() immediately after.
 *  
 *  Arguments:
 *      stream      FILE stream to which output is sent
 *      message     A message to precede the reported time
 *      start_time  A struct timeval structure populated by xt_tic()
 *
 *  Returns:
 *      The time difference in microseconds
 *
 *  Examples:
 *      struct timeval  start_time;
 *
 *      xt_tic(&start_time);
 *      // Code for which elapsed time is to be measured
 *      for (c = 0; c < bignum; ++c)
 *      {
 *          ...
 *      }
 *      xt_toc(stderr, "Elapsed time for loop: ", &start_time);
 *
 *  See also:
 *      xt_tic(3), difftimeofday(3), gettimeofday(2)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-08-20  Jason Bacon Begin
 ***************************************************************************/

unsigned long xt_toc(FILE *stream, const char *message, struct timeval *start_time)

{
    struct timeval  end_time;
    unsigned long   diff, hours, minutes, seconds;
    
    gettimeofday(&end_time, NULL);
    diff = difftimeofday(&end_time, start_time);
    fprintf(stream, "%s%10lu microseconds", message, diff);
    if ( diff >= 1000000 )
    {
	seconds = diff / 1000000;
	minutes = seconds / 60;
	hours = minutes / 24;
	fprintf(stream, " (%lu hours, %lu minutes, %lu seconds)",
		hours, minutes, seconds);
    }
    putc('\n', stream);
    return diff;
}
