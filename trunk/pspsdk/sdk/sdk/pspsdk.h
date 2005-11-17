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
#include <pspmoduleinfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PSPSDK PSPSDK Utility Library */

/** @addtogroup PSPSDK */
/*@{*/

/**
  * Query a modules information from its uid.
  * @note this is a replacement function for the broken kernel sceKernelQueryModuleInfo in v1.0 firmware
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
  * Get the list of module IDs.
  * @note This is a replacement function for the missing v1.5 sceKernelGetModuleIdList
  * on v1.0 firmware. DO NOT use on anything above that version.
  *
  * @param readbuf - Buffer to store the module list.
  * @param readbufsize - Number of elements in the readbuffer.
  * @param idcount - Returns the number of module ids
  *
  * @return >= 0 on success
  */
int pspSdkGetModuleIdList(SceUID *readbuf, int readbufsize, int *idcount);

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

/**
 * Manually fixup library imports for late binding modules.
 *
 * @param moduleId - Id of the module to fixup
 */
void pspSdkFixupImports(int moduleId);

/**
 * Load Inet related modules.
 * Note: You must be in kernel mode to execute this function.
 *
 * @returns - 0 on success, otherwise one of ::PspKernelErrorCodes.
 */
int pspSdkLoadInetModules();

/**
 * Initialize Inet related modules.
 *
 * @returns - 0 on success, otherwise one of ::PspKernelErrorCodes.
 */
int pspSdkInetInit();

/**
 * Terminate Inet related modules.
 */
void pspSdkInetTerm();

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPSDK_H */
