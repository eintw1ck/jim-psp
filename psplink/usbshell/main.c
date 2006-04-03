/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * main.c - PSPLINK USB Shell main code
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
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

#define MODULE_NAME "USBShell"

PSP_MODULE_INFO(MODULE_NAME, PSP_MODULE_KERNEL, 1, 1);

#define MAX_CLI 4096

void ttySetUsbHandler(PspDebugPrintHandler usbHandler);
int psplinkParseCommand(unsigned char *command, int direct_term);
void psplinkPrintPrompt(void);
void psplinkExitShell(void);
int usb_read_async_data(unsigned int chan, unsigned char *data, int len);
int usb_write_async_data(unsigned int chan, const void *data, int size);
void usb_async_flush(unsigned int chan);
int usb_wait_for_connect(void);

int usbPrint(const char *data, int size)
{
	usb_write_async_data(0, data, size);

	return size;
}

int main_thread(SceSize args, void *argp)
{
	unsigned char cli[MAX_CLI];
	int cli_pos = 0;

	usb_async_flush(0);
	ttySetUsbHandler(usbPrint);
	usb_wait_for_connect();
	psplinkPrintPrompt();

	while(1)
	{
		if(usb_read_async_data(0, &cli[cli_pos], 1) < 1)
		{
			Kprintf("Error reading async data\n");
			sceKernelDelayThread(250000);
			continue;
		}

		if(cli[cli_pos] == '\n')
		{
			cli[cli_pos] = 0;
			if(psplinkParseCommand(cli, 0) == 1)
			{
				psplinkExitShell();
			}
			psplinkPrintPrompt();
			cli_pos = 0;
		}
		else
		{
			if(cli_pos < (MAX_CLI-1))
			{
				cli_pos++;
			}
		}
	}

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;

	/* Create a high priority thread */
	thid = sceKernelCreateThread("USBShell", main_thread, 12, 0x2000, 0, NULL);
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