/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmodulemgr.h - Prototypes to manage modules.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef __MODLOAD_H__
#define __MODLOAD_H__

#include <pspkerneltypes.h>

/** @defgroup ModuleMgr Module Manager Library
  * This module contains the imports for the kernel's module management routines.
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ModuleMgr Module Manager Library */
/*@{*/

typedef struct SceKernelLMOption {
	SceSize 		size;
	SceUID 			mpidtext;
	SceUID 			mpiddata;
	unsigned int 	flags;
	char 			position;
	char 			access;
	char 			creserved[2];
} SceKernelLMOption;

typedef struct SceKernelSMOption {
	SceSize 		size;
	SceUID 			mpidstack;
	SceSize 		stacksize;
	int 			priority;
	unsigned int 	attribute;
} SceKernelSMOption;

//sceKernelLoadModuleByID

/**
  * Load a module.
  * @note This function restricts where it can load from (such as from flash0) 
  * unless you call it in kernel mode. It also must be called from a thread.
  * 
  * @param path - The path to the module to load.
  * @param flags - Unknown, set to 0 
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @return < 0 on error, otherwise the module id 
  */
SceUID sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);

/**
  * Load a module from MS.
  * @note This function restricts what it can load, e.g. it wont load plain executables.
  * 
  * @param path - The path to the module to load.
  * @param flags - Unknown, set to 0 
  * @param option  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @return < 0 on error, otherwise the module id 
  */
SceUID sceKernelLoadModuleMs(const char *path, int flags, SceKernelLMOption *option);

/**
  * Start a loaded module.
  *
  * @param modid - The ID of the module returned from LoadModule.
  * @param argsize - Length of the args.
  * @param argp - A pointer to the arguments to the module.
  * @param status - Returns the status of the start.
  * @param option - Unknown, set to 0.
  *
  * @return < 0 on error.
  */
int sceKernelStartModule(SceUID modid, SceSize argsize, void *argp, int *status, SceKernelSMOption *option);

//sceKernelStopModule
//
//sceKernelUnloadModule

/**
 * Stop and unload the current module.
 *
 * @param unknown - Unknown (I've seen 1 passed).
 * @param argsize - Size (in bytes) of the arguments that will be passed to module_stop().
 * @param argp - Pointer to arguments that will be passed to module_stop().
 *
 * @return < 0 on error.
 */
int sceKernelSelfStopUnloadModule(int unknown, SceSize argsize, void *argp);

//sceKernelStopUnloadSelfModule

typedef struct SceKernelModuleInfo {
	SceSize 		size;
	char 			nsegment;
	char 			reserved[3];
	int 			segmentaddr[4];
	int 			segmentsize[4];
	unsigned int 	entry_addr;
	unsigned int 	gp_value;
	unsigned int 	text_addr;
	unsigned int 	text_size;
	unsigned int 	data_size;
	unsigned int 	bss_size;
	/* The following is only available in the v1.5 firmware and above,
	   but as sceKernelQueryModuleInfo is broken in v1.0 is doesn't matter ;) */
	unsigned short  attribute;
	unsigned char   version[2];
	char            name[28];
} SceKernelModuleInfo;

/**
  * Query the information about a loaded module from its UID.
  * @note This fails on v1.0 firmware (and even it worked has a limited structure)
  * so if you want to be compatible with both 1.5 and 1.0 (and you are running in 
  * kernel mode) then call this function first then ::pspDebugQueryModuleInfoV1 
  * if it fails, or make separate v1 and v1.5+ builds.
  *
  * @param uid - The UID of the loaded module.
  * @param mod - Pointer to a SceKernelModuleInfo structure.
  * 
  * @return < 0 on error.
  */
int sceKernelQueryModuleInfo(SceUID uid, SceKernelModuleInfo *mod);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
