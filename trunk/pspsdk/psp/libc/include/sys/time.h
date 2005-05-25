#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

#ifndef __time_t_defined
typedef unsigned long time_t;
#define __time_t_defined
#endif

#ifndef __clock_t_defined
typedef unsigned long clock_t;
#define __clock_t_defined
#endif

struct timeval 
{
    long tv_sec;
    long tv_usec;
};

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

#define DST_NONE        0       /* not on dst */
#define DST_USA         1       /* USA style dst */
#define DST_AUST        2       /* Australian style dst */
#define DST_WET         3       /* Western European dst */
#define DST_MET         4       /* Middle European dst */
#define DST_EET         5       /* Eastern European dst */
#define DST_CAN         6       /* Canada */

int gettimeofday(struct timeval *tp, struct timezone *tzp);

#endif
