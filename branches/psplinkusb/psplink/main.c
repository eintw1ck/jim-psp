/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * main.c - PSPLINK kernel module main code.
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 * Copyright (c) 2005 Julian T <lovely@crm114.net>
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
#include <pspumd.h>
#include <psputilsforkernel.h>
#include <pspsysmem_kernel.h>
#include <pspthreadman_kernel.h>
#include <usbhostfs.h>
#include "memoryUID.h"
#include "psplink.h"
#include "psplinkcnf.h"
#include "debug.h"
#include "util.h"
#include "sio.h"
#include "shell.h"
#include "config.h"
#include "exception.h"
#include "apihook.h"
#include "tty.h"
#include "disasm.h"
#include "symbols.h"
#include "libs.h"
#include "modload.h"
#include "decodeaddr.h"

PSP_MODULE_INFO("PSPLINK", 0x1000, 1, 1);

#define BOOTLOADER_NAME "PSPLINKLOADER"

struct GlobalContext g_context;

/* The thread ID of the loader */
static int g_loaderthid = 0;

void save_execargs(int argc, char **argv);

int unload_loader(void)
{
	SceModule *mod;
	SceUID modid;
	int ret = 0;
	int status;

	mod = sceKernelFindModuleByName(BOOTLOADER_NAME);
	if(mod != NULL)
	{
		DEBUG_PRINTF("Loader UID: %08X\n", mod->modid);
		/* Stop module */
		modid = mod->modid;
		ret = sceKernelStopModule(modid, 0, NULL, &status, NULL);
		if(ret >= 0)
		{
			ret = sceKernelUnloadModule(modid);
		}
	}
	else
	{
		Kprintf("Couldn't find bootloader\n");
	}

	return 0;
}

void parse_sceargs(SceSize args, void *argp)
{
	int  loc = 0;
	char *ptr = argp;
	int argc = 0;
	char *argv[MAX_ARGS];

	while(loc < args)
	{
		argv[argc] = &ptr[loc];
		loc += strlen(&ptr[loc]) + 1;
		argc++;
		if(argc == (MAX_ARGS-1))
		{
			break;
		}
	}

	argv[argc] = NULL;
	g_loaderthid = 0;

	if(argc > 0)
	{
		char *lastdir;

		g_context.bootfile = argv[0];
		lastdir = strrchr(argv[0], '/');
		if(lastdir != NULL)
		{
			memcpy(g_context.bootpath, argv[0], lastdir - argv[0] + 1);
		}
	}

	if(argc > 1)
	{
		char *endp;
		g_loaderthid = strtoul(argv[1], &endp, 16);
	}
}

void load_psplink_user(const char *bootpath)
{
	char prx_path[MAXPATHLEN];

	strcpy(prx_path, bootpath);
	strcat(prx_path, "psplink_user.prx");
	load_start_module(prx_path, 0, NULL);
}

SceUID load_gdb(const char *bootpath, int argc, char **argv)
{
	char prx_path[MAXPATHLEN];

	strcpy(prx_path, bootpath);
	strcat(prx_path, "usbgdb.prx");
	g_context.gdb = 1;
	return load_start_module(prx_path, argc, argv);
}

void exit_reset(void)
{
	if(g_context.resetonexit)
	{
		psplinkReset();
	}
	else
	{
		psplinkSetK1(0);
		SHELL_PRINT("\nsceKernelExitGame caught!\n");
		/* Kill the thread, bad idea to drop back to the program */
		sceKernelExitThread(0);
	}
}

void psplinkStop(void)
{
	if(g_context.thevent >= 0)
	{
		sceKernelReleaseThreadEventHandler(g_context.thevent);
	}
}

struct SceKernelLoadExecVSHParam 
{ 
	SceSize size; 
	SceSize args; 
	void * argp; 
	const char * key; 
	u32 vshmain_args_size; 
	void *vshmain_args; 
	u32 unk3; 
	u32 unk4; 
	u32 unk5; 
}; 

int sceKernelLoadExecVSHMs2(const char *, struct SceKernelLoadExecVSHParam *params);

void psplinkReset(void)
{
	unsigned int rev;

	rev = sceKernelDevkitVersion();
	
	/* We only support 271 */
	if(rev == 0x02070110)
	{
		struct SceKernelLoadExecVSHParam param; 
		u32 addr;

		if(memDecode("@sceLoadExec@+0x1DBC", &addr))
		{
			/* Quick and dirty patch for now ;P */
			_sw(0x10000011, addr);
			sceKernelDcacheWritebackInvalidateAll();
			sceKernelIcacheInvalidateAll();
		}

		memset(&param, 0, sizeof(param)); 
		param.size = sizeof(param); 
		param.args = strlen(g_context.bootfile)+1; 
		param.argp = (char*) g_context.bootfile; 
		param.key = "game"; 
		param.vshmain_args_size = 0; 
		param.vshmain_args = NULL; 

		debugDisableHW();
		psplinkSetK1(0);
		SHELL_PRINT("Resetting psplink\n");
		psplinkStop();

		sceKernelLoadExecVSHMs2(g_context.bootfile, &param);
	}
	else
	{
		struct SceKernelLoadExecParam le;
		struct SavedContext *save = (struct SavedContext *) SAVED_ADDR;
		const char *rebootkey = NULL;

		save->magic = SAVED_MAGIC;
		strcpy(save->currdir, g_context.currdir);
		save->rebootkey = g_context.rebootkey;

		debugDisableHW();
		psplinkSetK1(0);
		SHELL_PRINT("Resetting psplink\n");
		psplinkStop();

		le.size = sizeof(le);
		le.args = strlen(g_context.bootfile) + 1;
		le.argp = (char *) g_context.bootfile;
		switch(g_context.rebootkey)
		{
			case REBOOT_MODE_GAME: rebootkey = "game";
								   break;
			case REBOOT_MODE_VSH : rebootkey = "vsh";
								   break;
			case REBOOT_MODE_UPDATER : rebootkey = "updater";
									   break;
			default: rebootkey = NULL;
					 break;

		};
		le.key = rebootkey;

		sceKernelSuspendAllUserThreads();

		sceKernelLoadExec(g_context.bootfile, &le);
	}
}

void psplinkExitShell(void)
{
	sceKernelExitGame();
}

int psplinkPresent(void)
{
	return 1;
}

int RegisterExceptionDummy(void)
{
	return 0;
}

/* Patch out the exception handler setup call for apps which come after us ;P */
int psplinkPatchException(void)
{
	u32 *addr;
	int intc;

	intc = pspSdkDisableInterrupts();
	addr = libsFindExportAddrByNid(refer_module_by_name("sceExceptionManager", NULL), "ExceptionManagerForKernel", 0x565C0B0E);
	if(addr)
	{
		*addr = (u32) RegisterExceptionDummy;
		sceKernelDcacheWritebackInvalidateRange(addr, 4);
		sceKernelIcacheInvalidateRange(addr, 4);
	}
	pspSdkEnableInterrupts(intc);

	return 0;
}

void initialise(SceSize args, void *argp)
{
	struct ConfigContext ctx;
	const char *init_dir = "host0:/";
	struct SavedContext *save = (struct SavedContext *) SAVED_ADDR;

	memset(&g_context, 0, sizeof(g_context));
	map_firmwarerev();
	exceptionInit();
	g_context.thevent = -1;
	parse_sceargs(args, argp);
	configLoad(g_context.bootpath, &ctx);
	disasmSetSymResolver(symbolFindNameByAddressEx);

	if(ctx.pid)
	{
		g_context.pid = ctx.pid;
	}
	else
	{
		g_context.pid = HOSTFSDRIVER_PID;
	}

	ttyInit();
	init_usbhost(g_context.bootpath);

	if(save->magic == SAVED_MAGIC)
	{
		init_dir = save->currdir;
		save->magic = 0;
		g_context.rebootkey = save->rebootkey;
	}

	if(shellInit(init_dir) < 0)
	{
		sceKernelExitGame();
	}

	if(ctx.baudrate == 0)
	{
		ctx.baudrate = DEFAULT_BAUDRATE;
	}

	sioInit(ctx.baudrate);
	sceUmdActivate(1, "disc0:");

	/* Hook sceKernelExitGame */
	apiHookByNid(refer_module_by_name("sceLoadExec", NULL), "LoadExecForUser", 0x05572A5F, exit_reset);

	sceKernelWaitThreadEnd(g_loaderthid, NULL);
	unload_loader();

	psplinkPatchException();

	if(ctx.enableuser)
	{
		load_psplink_user(g_context.bootpath);
	}

	g_context.resetonexit = ctx.resetonexit;

	modLoad(g_context.bootpath);
}

/* Simple thread */
int main_thread(SceSize args, void *argp)
{
	initialise(args, argp);

	shellParseThread(0, NULL);
	sceKernelSleepThread();

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;

	/* Create a high priority thread */
	thid = sceKernelCreateThread("PspLink", main_thread, 8, 64*1024, 0, NULL);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, args, argp);
	}

	return 0;
}
