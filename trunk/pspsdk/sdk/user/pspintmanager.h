/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspintmanager.h - Interface to the system interupt manager.
 *
 * Copyright (c) 2005 James F. (tyranid@gmail.com)
 *
 * $Id$
 */

#ifndef PSPINTMANAGER_H
#define PSPINTMANAGER_H

#include <pspkerneltypes.h>

/** @defgroup IntMan Interrupt Manager
  * This module contains routines to manage interrupts.
  */

/** @addtogroup IntMan Interrupt Manager */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

enum PspInterrupts
{
	PSP_VBLANK_INT = 30
};

/** 
  * Register a sub interrupt handler.
  * 
  * @param intno - The interrupt number to register.
  * @param no - The sub interrupt handler number (user controlled)
  * @param handler - The interrupt handler
  * @param arg - An argument passed to the interrupt handler
  *
  * @return < 0 on error.
  */
int sceKernelRegisterSubIntrHandler(int intno, int no, void *handler, void *arg);

/**
  * Release a sub interrupt handler.
  * 
  * @param intno - The interrupt number to register.
  * @param no - The sub interrupt handler number
  *
  * @return < 0 on error.
  */
int sceKernelReleaseSubIntrHandler(int intno, int no);

/**
  * Enable a sub interrupt.
  * 
  * @param intno - The sub interrupt to enable.
  * @param no - The sub interrupt handler number
  * 
  * @return < 0 on error.
  */
int sceKernelEnableSubIntr(int intno, int no);

/**
  * Disable a sub interrupt handler.
  *
  * @param intno - The sub interrupt to disable.
  * @param no - The sub interrupt handler number
  * 
  * @return < 0 on error.
  */
int sceKernelDisableSubIntr(int intno, int no);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* PSPSYSMEM_H */
