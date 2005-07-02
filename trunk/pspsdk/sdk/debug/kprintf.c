/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * kprintf.c - Basic Kprintf handling for applications. 
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id$
 */

#include <pspkernel.h>
#include <pspdebug.h>

#define REGISTER_FUNC_MOD "sceSystemMemoryManager"
#define REGISTER_FUNC_LIB "KDebugForKernel"
#define REGISTER_FUNC_NID 0x7CEB2C09

/* The current kprintf handler */
static PspDebugKprintfHandler curr_handler;

/* Default kprintf handler */
static void _pspDebugDefaultKprintfHandler(const char *format, u32 *args)
{
	pspDebugScreenPrintf(format, args[0], args[1], args[2], args[3]);
}

/* The registered kprintf handler */
static void _pspDebugKprintfHandler(void *arg, const char *format, u32 *args)
{
	if(curr_handler != NULL)
	{
		curr_handler(format, args);
	}
	else
	{
		_pspDebugDefaultKprintfHandler(format, args);
	}
}

/* Install a kprintf handler */
int pspDebugInstallKprintfHandler(PspDebugKprintfHandler handler)
{
	SceModuleInfo *mod;
	int (*sceKernelRegisterKprintfHandler)(void *func, void *args);

	mod = pspDebugFindModule(REGISTER_FUNC_MOD);
	if(mod != NULL)
	{
		sceKernelRegisterKprintfHandler = pspDebugFindExportedFunction(mod, REGISTER_FUNC_LIB, REGISTER_FUNC_NID);
	}

	if((mod == NULL) || (sceKernelRegisterKprintfHandler == NULL))
	{
		pspDebugScreenPrintf("Error findind Kprintf register function\n");
		return -1;
	}

	return sceKernelRegisterKprintfHandler(_pspDebugKprintfHandler, NULL);
}
