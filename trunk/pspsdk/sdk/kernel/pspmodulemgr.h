/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmodulemgr.h - Prototypes to manage manage modules.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
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

typedef struct _mod_param
{
	u32 size;
	u32 unk4;
	u32 unk8;
	u32 unkC;
	u8  unk10;
	u8  unk11;
	u16 unk12;
} __attribute__((packed)) mod_param_t;

/**
  * Load a module.
  * @note This function restricts where it can load from (such as from flash0) 
  * unless you call it in kernel mode. It also must be called from a thread.
  * 
  * @param path - The path to the module to load.
  * @param zero - Unknown, set to 0 
  * @param mod  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @return < 0 on error, otherwise the module id 
  */
int sceKernelLoadModule(const char *path, u32 zero, mod_param_t* mod);

/**
  * Load a module from MS.
  * @note This function restricts what it can load, e.g. it wont load plain executables.
  * 
  * @param path - The path to the module to load.
  * @param zero - Unknown, set to 0 
  * @param mod  - Pointer to a mod_param_t structure. Can be NULL.
  *
  * @return < 0 on error, otherwise the module id 
  */
int sceKernelLoadModuleMs(const char *path, u32 zero, mod_param_t* mod);

/**
  * Start a loaded module.
  *
  * @param modid - The ID of the module returned from LoadModule.
  * @param arglen - Length of the args.
  * @param args - A pointer to the arguments to the module.
  * @param status - Returns the status of the start.
  * @param zero - Unknown, set to 0.
  *
  * @return < 0 on error.
  */
int sceKernelStartModule(int modid, u32 arglen, void* args, u32 *status, u32 zero);

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

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
