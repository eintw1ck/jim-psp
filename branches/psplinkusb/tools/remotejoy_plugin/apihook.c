/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * apihook.c - User mode API hook code for psplink.
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/psplink/apihook.c $
 * $Id: apihook.c 2108 2006-12-18 21:58:13Z tyranid $
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsysmem_kernel.h>
#include <psputilsforkernel.h>
#include <pspmoduleexport.h>
#include <psploadcore.h>
#include <pspthreadman_kernel.h>
#include <pspsdk.h>
#include <stdio.h>
#include <string.h>
#include "libs.h"
#include "apihook.h"

struct SyscallHeader
{
	void *unk;
	unsigned int basenum;
	unsigned int topnum;
	unsigned int size;
};

void *find_syscall_addr(u32 addr)
{
	struct SyscallHeader *head;
	u32 *syscalls;
	void **ptr;
	int size;
	int i;

	asm(
			"cfc0 %0, $12\n"
			: "=r"(ptr)
	   );

	if(!ptr)
	{
		return NULL;
	}

	head = (struct SyscallHeader *) *ptr;
	syscalls = (u32*) (*ptr + 0x10);
	size = (head->size - 0x10) / sizeof(u32);

	for(i = 0; i < size; i++)
	{
		if(syscalls[i] == addr)
		{
			return &syscalls[i];
		}
	}

	return NULL;
}

static void *apiHookAddr(u32 *addr, void *func)
{
	int intc;

	if(!addr)
	{
		return NULL;
	}

	intc = pspSdkDisableInterrupts();
	*addr = (u32) func;
	sceKernelDcacheWritebackInvalidateRange(addr, sizeof(addr));
	sceKernelIcacheInvalidateRange(addr, sizeof(addr));
	pspSdkEnableInterrupts(intc);

	return addr;
}

u32 apiHookByName(SceUID uid, const char *library, const char *name, void *func)
{
	u32 addr;

	addr = libsFindExportByName(uid, library, name);
	if(addr)
	{
		if(!apiHookAddr(find_syscall_addr(addr), func))
		{
			addr = 0;
		}
	}

	return addr;
}

u32 apiHookByNid(SceUID uid, const char *library, u32 nid, void *func)
{
	u32 addr;

	addr = libsFindExportByNid(uid, library, nid);
	if(addr)
	{
		if(!apiHookAddr(find_syscall_addr(addr), func))
		{
			addr = 0;
		}
	}

	return addr;
}
