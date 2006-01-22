/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspthreadman_kernel.h - Interface to the kernel side of threadman
 *
 * Copyright (c) 2005 James F.
 *
 * $Id$
 */

#ifndef PSPTHREADMANKERNEL_H
#define PSPTHREADMANKERNEL_H

#include <pspkerneltypes.h>
#include <pspthreadman.h>

/** @defgroup ThreadmanKern Thread Manager kernel functions
  * This module contains routines to threads in the kernel
  */

/** @addtogroup ThreadmanKern Thread Manager kernel functions */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Suspend all user mode threads in the system
 *
 * @return 0 on success, < 0 on error
 */
int sceKernelSuspendAllUserThreads(void);


#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* PSPTHREADMANKERNEL_H */
