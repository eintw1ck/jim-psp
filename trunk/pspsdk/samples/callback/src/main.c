// Hello World for PSP
// Created 2005.04.30  by nem 


#include <kernel.h>

int exit_callback(void)
{
	sceKernelExitGame();

	return 0;
}

void CallbackThread(void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback);
	sceKernelRegisterExitCallback(cbid);

	sceKernelPollCallbacks();
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

int main(void)
{
	SetupCallbacks();
	sceKernelSleepThread();

	return 0;
}
