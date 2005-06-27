/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psploadexec.h - Process load and exit related functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __LOADEXEC_H__
#define __LOADEXEC_H__

/** @defgroup LoadExec LoadExec Library */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup LoadExec */

/*@{*/

/**
 * Register callback
 *
 * @note By installing the exit callback the home button becomes active. However if sceKernelExitGame
 * is not called in the callback it is likely that the psp will just crash.
 *
 * @par Example:
 * @code
 * int exit_callback(void) { sceKernelExitGame(); }
 *
 * cbid = sceKernelCreateCallback("ExitCallback", exit_callback, NULL);
 * sceKernelRegisterExitCallback(cbid);
 * @endcode
 *
 * @param cbid Callback id
 * @return < 0 on error
 */
int sceKernelRegisterExitCallback(int cbid);

/**
 * Exit game and go back to the PSP browser.
 *
 * @note You need to be in a thread in order for this function to work
 *
 */
void sceKernelExitGame(void);

/** 
  * Execute a new game executable (does not support ms)
  * 
  * @param file - The file to execute.
  * @param unk  - Unknown, set to NULL.
  *
  * @return < 0 on error, probably.
  *
  */
int sceKernelLoadExec(const char *file, void *unk);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif
