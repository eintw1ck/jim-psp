/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Simple PRX example.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id$
 */
#include <pspkernel.h>
#include <stdio.h>

PSP_MODULE_INFO("TESTPRX", 0x1000, 1, 1);

#define WELCOME_MESSAGE "Hello from the PRX\n"

/* Simple thread */
int thread_func(SceSize args, void *argp)
{
	printf(WELCOME_MESSAGE);
	sceKernelSleepThread();

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;

	thid = sceKernelCreateThread("TestThread", thread_func, 0x19, 0x10000, 0, NULL);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, args, argp);
	}

	return 0;
}

/* Exported function returns the address of module_info */
void* getModuleInfo(void)
{
	return (void *) &module_info;
}

