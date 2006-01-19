/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - PSPPacker
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * TODO:
 *    - Remove printfs
 *    - include all needed stubs into stubs.S and don't include libraries
 *    - bribe someone to make a prx compatible psp-strip
 *    - make a util based off bin2s to pack a prx and include unpacked size in the .S
 *    - turn this into a prx so we can sceKernelSelfStopUnloadModule to get rid of ourselves
 *
 * NOTE: PSPPacker currently only works with PRXes
 *
 * $Id$
 */
#include <pspkernel.h>
#include <pspsdk.h>
#include <string.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspmodulemgr.h>
#include <psputilsforkernel.h>

PSP_MODULE_INFO("PSPPacker", 0x1000, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);


#define printf	pspDebugScreenPrintf

void _main(SceSize args, void *argp)
{
	static SceUID modid;
	static int retVal, status;
	static SceKernelLMOption option;
	extern u8 *payload;
	extern u32 size_payload;
	extern u32 size_payload_uncomp;
	u8 *buffer;
	SceUID bufferBlock;
	
	pspDebugScreenInit();
    	pspDebugScreenClear();
	pspDebugInstallKprintfHandler(NULL);
	//pspDebugInstallErrorHandler(NULL);
	pspSdkInstallNoPlainModuleCheckPatch();

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = 1;
	option.mpiddata = 1;
	option.position = 0;
	option.access = 1;
	bufferBlock = sceKernelAllocPartitionMemory(2, "PSPPackerBuffer", PSP_SMEM_High, size_payload_uncomp, NULL);
	if (bufferBlock < 0) {
		printf("allocpartitionmemory failed with 0x%08X\n", bufferBlock);
		goto exit;
	}
	buffer = sceKernelGetBlockHeadAddr(bufferBlock);
	retVal = sceKernelGzipDecompress(buffer, size_payload_uncomp, (u8*)&payload, 0);
	if (retVal < 0) {
		printf("sceKernelGzipDecompress failed with 0x%08X\n", retVal);
		goto exit;
	}
	
	modid = sceKernelLoadModuleBufferUsbWlan(size_payload, buffer, 0, &option);
	retVal = sceKernelFreePartitionMemory(bufferBlock);
	if (retVal < 0)
		printf("Error freeing decompress buffer (0x%08X)\n", retVal);
		
	if(modid > 0)
		retVal = sceKernelStartModule(modid, 0, NULL, &status, NULL);

exit:
	/* Let's bug out */
	//sceKernelSelfStopUnloadModule(0, 0, NULL);
	//return 0;
	sceKernelExitDeleteThread(0);
}

int _start(SceSize args, void *argp)
{
    SceUID thid;
    void (*_main_func)(SceSize args, void *argp) = _main;
    _main_func = (void *) ((u32) _main_func | 0x80000000);
	thid = sceKernelCreateThread("PSPPackerThread", (void *) _main_func, 32, 2048, 0, 0);
	sceKernelStartThread(thid, args, argp);
	return 0;
}
/* The entry table provides pointers to the executable's _start() and
   module_info structure. */
static const unsigned int __entrytable[4] __attribute__((section(".rodata.sceResident"))) = {
	0xD632ACDB, 0xF01D73A7, (unsigned int) &_start, (unsigned int) &module_info
};

/* Create the empty library entry used to describe the program's _start() and
   module_info. */
static const struct _library_entry {
	const char *	name;
	unsigned short	version;
	unsigned short	attribute;
	unsigned char	entLen;
	unsigned char	varCount;
	unsigned short	funcCount;
	void *			entrytable;
} _library_entry __attribute__((section(".lib.ent"), used)) = {
	NULL, 0, 0x8000, 4, 1, 1, &__entrytable
};
