/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputils.h - Prototypes for the sceUtils library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
