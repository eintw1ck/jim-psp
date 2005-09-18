/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Example of using the GDB stub.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: main.c 705 2005-07-20 18:09:56Z tyranid $
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Define the module info section */
PSP_MODULE_INFO("gdb", 0x1000, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* Initialise SIO and GDB */
__attribute__((constructor))
void loaderInit()
{
	pspDebugScreenInit();
	pspDebugScreenPrintf("Initialising serial port\n");
	pspKernelSetKernelPC();
	pspDebugSioSetBaud(38400);
	pspDebugSioInit();
	pspDebugGdbStubInit();
}

int main(int argc, char *argv[])
{
	pspDebugScreenPrintf("App Started\n");
	
	sceDisplayWaitVblankStart();

	/* Generate a breakpoint to trap into GDB */
	pspDebugBreakpoint();

	SetupCallbacks();

	printf("After Exception\n");

	sceKernelSleepThread();

	return 0;
}
