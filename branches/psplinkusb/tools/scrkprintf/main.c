/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * main.c - PSPLINK Screen Kprintf driver
 *
 * Copyright (c) 2007 James F <tyranid@gmail.com>
 *
 * $HeadURL$
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspkdebug.h>
#include <pspsdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PSP_MODULE_INFO("ScrKprintf", PSP_MODULE_KERNEL, 1, 1);

static void PutCharDebug(unsigned short *data, unsigned int type)
{
	if((type & 0xFF00) == 0)
	{
		if((type == '\n') || (type == '\r') || (type >= 32))
		{
			pspDebugScreenPrintData((char*) &type, 1);
		}
	}
}

int main_thread(SceSize args, void *argp)
{
	pspDebugScreenInit();
	sceKernelRegisterDebugPutchar(PutCharDebug);

	sceKernelSleepThread();

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;

	/* Create a high priority thread */
	thid = sceKernelCreateThread("UsbKprintf", main_thread, 7, 0x800, 0, NULL);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, args, argp);
	}
	return 0;
}

/* Module stop entry */
int module_stop(SceSize args, void *argp)
{
	return 0;
}
