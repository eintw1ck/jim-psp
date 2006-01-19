/*
 * PSPPacker
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPPacker root for details.
 *
 * pspstub.c - PSPPacker stub
 *
 * Copyright (c) 2006 TyRaNiD
 * Copyright (c) 2005 John_K
 *
 * $HeadURL$
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <pspmodulemgr.h>
#include <psputilsforkernel.h>
#include <string.h>
#include <stdio.h>
#include "psppacker.h"

PSP_MODULE_INFO("PSPPacker", PSP_MODULE_KERNEL, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

#ifndef NDEBUG
#define dbgprintf(fmt, ...) Kprintf(fmt, ## __VA_ARGS__)
#else
#define dbgprintf(fmt, ...)
#endif

int main_thread(SceSize args, void *argp)
{
	SceUID blockId = -1;
	SceUID modId = -1;
	void *buf = NULL;
	int ret;
	int fd;
	struct PackHeader ph;
	int total_size;
	void *unpacked;

	dbgprintf("PSPPacker ver %d.%d (c) TyRaNiD/John_K 2k6\n", VER_MAJ, VER_MIN);

	fd = sceIoOpen((const char *) argp, PSP_O_RDONLY, 0777);
	if(fd < 0)
	{
		dbgprintf("Error could not open executable %s\n", (const char *) argp);
		goto exit;
	}

	if(sceIoLseek(fd, -sizeof(ph), SEEK_END) < 0)
	{
		dbgprintf("Error could not seek to end of the file\n");
		goto exit;
	}

	if(sceIoRead(fd, &ph, sizeof(ph)) != sizeof(ph))
	{
		dbgprintf("Error could not read in header\n");
		goto exit;
	}

	if(memcmp(ph.magic, PACKER_MAGIC, 4) != 0)
	{
		dbgprintf("Error invalid magic\n");
		goto exit;
	}

	total_size = ((ph.packed_size + 15) & ~15) + ph.unpacked_size;
	dbgprintf("Sizes: Packed %d - Unpacked %d - Total %d\n", ph.packed_size, ph.unpacked_size, total_size);

	if(sceIoLseek(fd, -ph.packed_size - sizeof(ph), SEEK_END) < 0)
	{
		dbgprintf("Error could not seek to start of compressed data\n");
		goto exit;
	}

	blockId = sceKernelAllocPartitionMemory(2, "", PSP_SMEM_High, total_size, NULL);
	if(blockId < 0)
	{
		dbgprintf("Error allocating memory block %08X\n", blockId);
		goto exit;
	}
	dbgprintf("blockId %08X\n", blockId);

	buf = sceKernelGetBlockHeadAddr(blockId);
	dbgprintf("buf %p\n", buf);

	unpacked = buf + ((ph.packed_size + 15) & ~15);

	if(sceIoRead(fd, buf, ph.packed_size) != ph.packed_size)
	{
		dbgprintf("Error could not read in packed data\n");
		goto exit;
	}

	ret = sceKernelGzipDecompress(unpacked, ph.unpacked_size, buf, 0);
	if (ret < 0) {
		dbgprintf("sceKernelGzipDecompress failed with 0x%08X\n", ret);
		goto exit;
	}

	dbgprintf("Loading module from ram %p\n", unpacked);
	modId = sceKernelLoadModuleBufferUsbWlan(ph.unpacked_size, unpacked, 0, NULL);
	if(modId < 0)
	{
		dbgprintf("Error loading module %08X\n", modId);
		goto exit;
	}

	if(blockId >= 0)
	{
		sceKernelFreePartitionMemory(blockId);
	}
	
	dbgprintf("modId %08X\n", modId);
	modId = sceKernelStartModule(modId, args, argp, NULL, NULL);
	dbgprintf("start %08X\n", modId);

exit:

	/* Let's bug out */
	sceKernelExitDeleteThread(0);

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;
	u32 func;

	func = (u32) main_thread;
	func |= 0x80000000;

	/* Create a high priority thread */
	thid = sceKernelCreateThread("main_thread", (void *) func, 0x20, 0x10000, 0, NULL);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, args, argp);
	}

	return 0;
}
