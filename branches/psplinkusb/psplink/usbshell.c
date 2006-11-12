/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * main.c - PSPLINK USB Shell main code
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/usbshell/main.c $
 * $Id: main.c 2034 2006-10-18 17:02:37Z tyranid $
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspkdebug.h>
#include <pspsdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usbhostfs.h>
#include <usbasync.h>
#include "tty.h"

#define MAX_CLI 4096

void psplinkPrintPrompt(void);

struct AsyncEndpoint g_endp;
struct AsyncEndpoint g_stdin;

int usbShellPrint(const char *data, int size)
{
	usbAsyncWrite(ASYNC_SHELL, data, size);

	return size;
}

int usbStdoutPrint(const char *data, int size)
{
	usbAsyncWrite(ASYNC_STDOUT, data, size);

	return size;
}

int usbStderrPrint(const char *data, int size)
{
	usbAsyncWrite(ASYNC_STDERR, data, size);

	return size;
}

int usbStdinRead(char *data, int size)
{
	int ret = 0;

	while(1)
	{
		ret = usbAsyncRead(ASYNC_STDOUT, (unsigned char*) data, size);
		if(ret < 0)
		{
			sceKernelDelayThread(250000);
			continue;
		}

		break;
	}

	return ret;
}

int usbShellInit(void)
{
	usbAsyncRegister(ASYNC_SHELL, &g_endp);
	usbAsyncRegister(ASYNC_STDOUT, &g_stdin);
	ttySetUsbHandler(usbShellPrint, usbStdoutPrint, usbStderrPrint, usbStdinRead);
	usbWaitForConnect();
	psplinkPrintPrompt();

	return 0;
}

int usbShellReadInput(unsigned char *cli, char **argv, int max_cli, int max_arg)
{
	int cli_pos = 0;
	int argc = 0;
	unsigned char *argstart = cli;

	while(1)
	{
		if(usbAsyncRead(ASYNC_SHELL, &cli[cli_pos], 1) < 1)
		{
			sceKernelDelayThread(250000);
			continue;
		}

		if(cli[cli_pos] == 1)
		{
			cli[cli_pos] = 0;
			break;
		}
		else
		{
			if(cli_pos < (max_cli-1))
			{
				if(cli[cli_pos] == 0)
				{
					if(argc < max_arg)
					{
						argv[argc++] = (char*) argstart;
						argstart = &cli[cli_pos+1];
					}
				}
				cli_pos++;
			}
		}
	}

	return argc;
}
