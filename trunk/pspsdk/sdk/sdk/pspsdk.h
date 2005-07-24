/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsdk.h - Interface to the PSPSDK utility library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */

#ifndef PSPSDK_H
#define PSPSDK_H

#include <pspkerneltypes.h>
#include <pspmodulemgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PSPSDK PSPSDK Utility Library */

/** @addtogroup PSPSDK */
/*@{*/

/**
  * Query a modules information from its uid.
  * @note this is a replacement function for the broken kernel sceKernelQueryModuleInfo.
  * DO NOT use on a anything above that version. This also needs kernel mode access where
  * the normal one has a user mode stub.
  * 
  * @param uid - The UID of the module to query.
  * @param modinfo - Pointer a module SceKernelModuleInfo structure.
  *
  * @return < 0 on error.
  */
int pspSdkQueryModuleInfoV1(SceUID uid, SceKernelModuleInfo *modinfo);


/**
 * Patch the sceModuleManager module to nullify LoadDeviceCheck() calls.
 *
 * @returns 0 on success, otherwise one of ::PspKernelErrorCodes.
 *
 * @note This function must be called while running in kernel mode.  The program
 * must also be linked against the pspkernel library.
 */
int pspSdkInstallNoDeviceCheckPatch(void);

/**
 * Patch sceLoadCore module to remove loading plain module checks
 *
 * @note This function must be called while running in kernel mode.
 *
 * @returns 0 on success, otherwise one of ::PspKernelErrorCodes.
 */
int pspSdkInstallNoPlainModuleCheckPatch(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPSDK_H */
