/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2005, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id$
# Standard libc time functions
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
