/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspintrman_kernel.h - Interface to the system interrupt manager.
 *
 * Copyright (c) 2005 James F. (tyranid@gmail.com)
 *
 * $Id$
 */

#ifndef PSPINTRMAN_KERNEL_H
#define PSPINTRMAN_KERNEL_H

#include <pspkerneltypes.h>

/** @defgroup IntrManKern Interrupt Manager Kernel
  * This module contains routines to manage interrupts.
  */

/** @addtogroup IntrManKern Interrupt Manager Kernel */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Register an interrupt handler.
  * 
  * @param intno - The interrupt number to register.
  * @param no    - The queue number.
  * @param handler - Pointer to the handler.
  * @param arg1    - Unknown (probably a set of flags)
  * @param arg2    - Unknown (probably a common pointer)
  *
  * @return 0 on success.
  */
int sceKernelRegisterIntrHandler(int intno, int no, void *handler, void *arg1, void *arg2);

/**
  * Enable an interrupt.
  * 
  * @param intno - Interrupt to enable.
  *
  * @return 0 on success.
  */
int sceKernelEnableIntr(int intno);

/**
  * Disable an interrupt.
  * 
  * @param intno - Interrupt to disable.
  *
  * @return 0 on success.
  */
int sceKernelDisableIntr(int intno);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* PSPINTRMAN_KERNEL_H */
