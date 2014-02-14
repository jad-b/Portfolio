/* simple timer functions for use with single processor programs */


#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>

static struct tms ignored;

static unsigned long time1;


start_timer()
{
    time1 = times(&ignored);  /* times returns clock ticks */
}

stop_timer()
{
    unsigned long time2;
    unsigned long totaltime;

    time2 = times(&ignored);
    totaltime = time2 - time1;
    printf ("Elapsed times:  %0.3f seconds\n",
       totaltime/(double)sysconf(_SC_CLK_TCK));
}

