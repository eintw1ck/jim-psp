#ifndef __UTILS_H__
#define __UTILS_H__

/** @defgroup Utils Utils Library */

/** @addtogroup Utils */

/*@{*/

#include <sys/time.h>

/**
  * Get the time in seconds since the epoc (1st Jan 1970)
  *
  */
time_t sceKernelLibcTime(time_t *t);

/** 
  * Get the processor clock used since the start of the process
  */
clock_t sceKernelLibcClock(void);

/** 
  * Get the current time of time and time zone information
  */
int sceKernelGettimeofday(struct timeval *tp, struct timezone *tzp);

/** 
  * Write back the data cache to memory
  */
void sceKernelDcacheWritebackAll(void);

/*@}*/

#endif
