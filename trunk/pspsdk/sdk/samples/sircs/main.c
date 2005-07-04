/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Infrared Remote example
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Matthew H <matthewh@webone.com.au>
 *
 * $$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsircs.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("SIRCS", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

// sircs devices are identified by an address
#define SIRCS_ADDR_DVD	0x1b5a

// sircs commands are easily found in lirc
// - interpret as described at 
//   http://sourceforge.net/mailarchive/message.php?msg_id=8833252

// RESET 0x00000000000A8B5B
// 1010 100 | 0 1011 0101 1011
// 001 0101 | 1 1011 0101 1010
// 0x15 | 0x1b5a
#define SIRCS_CMD_RESET	0x15

// PLAY 0x000000000004CB92
// 0100 110 | 0 1011 0101 1011
// 011 0010 | 1 1011 0101 1010
// 0x32 | 0x1b5a
#define SIRCS_CMD_PLAY	0x32

// PAUSE 0x000000000009CB92
// 1001 110 | 0 1011 0101 1011
// 011 1001 | 1 1011 0101 1010
// 0x39 | 0x1b5a
#define SIRCS_CMD_PAUSE	0x39

void send_code(int type, int dev, int cmd) 
{
	struct sircs_data sd;
	int ret;
	int count = 20; // this seems like a good number

	sd.type = type;
	sd.cmd = cmd & 0x7f;
	sd.dev = dev & 0x1fff;

	ret = sceSircsSend(&sd, count); 
	if (ret < 0) 
	{
		printf ("sceSircsSend returned %d\n", ret);
	}
}

/* Exit callback */
int exit_callback(void)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
void CallbackThread(void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
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
	ctrl_data_t pad;
	u32 buttonsold;
	int sirc_bits = 20; // # of bits in code, choose from 12, 15 or 20

	SetupCallbacks();
	pspDebugScreenInit();
	printf ("Sircs Example\n");
        printf ("-------\n");
	printf ("This example can be used with a PS2\n\n");
        printf ("Press CROSS to send PLAY\n");
        printf ("Press SQUARE to send PAUSE\n");
        printf ("Press CIRCLE to send RESET\n");

	do {
		sceCtrlReadBufferPositive(&pad, 1);

		if (pad.buttons != buttonsold) 
		{

			if (pad.buttons & CTRL_CIRCLE) 
			{
				printf ("Sending SIRCS_CMD_RESET\n");
				send_code(sirc_bits, SIRCS_ADDR_DVD, SIRCS_CMD_RESET);
			}

			if (pad.buttons & CTRL_CROSS) 
			{
				printf ("Sending SIRCS_CMD_PLAY\n");
				send_code(sirc_bits, SIRCS_ADDR_DVD, SIRCS_CMD_PLAY);
			}

			if (pad.buttons & CTRL_SQUARE)
			{
				printf ("Sending SIRCS_CMD_RESET\n");
				send_code(sirc_bits, SIRCS_ADDR_DVD, SIRCS_CMD_PAUSE);
			}

			buttonsold = pad.buttons;
		}

		sceDisplayWaitVblankStart(); 
	} while (1);

	return 0;
}
