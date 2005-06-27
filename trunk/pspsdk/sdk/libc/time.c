/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * time.c - Standard libc time functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#include <time.h>
#include <psputils.h>

#ifdef F_clock
/* Simple remapping of the kernel functions */
clock_t clock(void) 
{
    return sceKernelLibcClock();
}
#endif

#ifdef F__time
/* Simple remapping of the kernel functions */
time_t time(time_t *tloc)
{
    return sceKernelLibcTime(tloc);
}
#endif

#ifdef F_gettimeofday
/* Simple remapping of the kernel functions */
int gettimeofday(struct timeval *tp, struct timezone *tzp)
{
    return sceKernelGettimeofday(tp, tzp);
}
#endif
