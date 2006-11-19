/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * main.c - PSPLINK bootstrap for 271
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL$
 * $Id$
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <string.h>

/* Define the module info section, note the 0x1000 flag to enable start in kernel mode */
PSP_MODULE_INFO("PSPLINKLOADER", 0, 1, 1);

/* Define the thread attribute as 0 so that the main thread does not get converted to user mode */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

#define PATH "psplink.prx"

int main(int argc, char **argv)
{
	pspDebugScreenInit();

	SceUID mod = sceKernelLoadModule(PATH, 0, NULL);
	if (mod < 0)
	{
		printf("Error 0x%08X loading module.\n", mod);
		return 0;
	}

	mod = sceKernelStartModule(mod, strlen(argv[0])+1, argv[0], NULL, NULL);
	if (mod < 0)
	{
		printf("Error 0x%08X starting module.\n", mod);
		return 0;
	}

	return 0;
}
