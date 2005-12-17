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
#include <pspthreadman.h>

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
 * Load a module and start it.
 *
 * @param filename - Path to the module.
 * @param mpid - Memory parition ID to use to load the module int.
 *
 * @returns - The UID of the module on success, otherwise one of ::PspKernelErrorCodes.
 */
SceUID pspSdkLoadStartModule(const char *filename, int mpid);

/**
 * Manually fixup library imports for late binding modules.
 *
 * @param moduleId - Id of the module to fixup
 */
void pspSdkFixupImports(int moduleId);

/**
 * Load Inet related modules.
 * @note You must be in kernel mode to execute this function.
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

/**
 * Search for a thread with the given name and retrieve it's ::SceKernelThreadInfo struct.
 *
 * @param name - The name of the thread to search for.
 * @param pUID - If the thread with the given name is found, it's ::SceUID is stored here.
 * @param pInfo - If the thread with the given name is found, it's ::SceKernelThreadInfo data is stored here.
 *
 * @returns 0 if successful, otherwise one of ::PspKernelErrorCodes.
 */
int pspSdkReferThreadStatusByName(const char *name, SceUID *pUID, SceKernelThreadInfo *pInfo);

/**
 * Search for a semaphore with the given name and retrieve it's ::SceKernelSemaInfo struct.
 *
 * @param name - The name of the sema to search for.
 * @param pUID - If the sema with the given name is found, it's ::SceUID is stored here.
 * @param pInfo - If the sema with the given name is found, it's ::SceKernelSemaInfo data is stored here.
 *
 * @returns 0 if successful, otherwise one of ::PspKernelErrorCodes.
 */
int pspSdkReferSemaStatusByName(const char *name, SceUID *pUID, SceKernelSemaInfo *pInfo);

/**
 * Search for an event flag with the given name and retrieve it's ::SceKernelEventFlagInfo struct.
 *
 * @param name - The name of the event flag to search for.
 * @param pUID - If the event flag with the given name is found, it's ::SceUID is stored here.
 * @param pInfo - If the event flag with the given name is found, it's ::SceKernelEventFlagInfo data is stored here.
 *
 * @returns 0 if successful, otherwise one of ::PspKernelErrorCodes.
 */
int pspSdkReferEventFlagStatusByName(const char *name, SceUID *pUID, SceKernelEventFlagInfo *pInfo);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPSDK_H */
