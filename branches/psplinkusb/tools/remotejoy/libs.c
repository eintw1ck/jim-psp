/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * libs.c - Module library code for psplink.
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/psplink/libs.c $
 * $Id: libs.c 2106 2006-12-18 18:55:53Z tyranid $
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsysmem_kernel.h>
#include <psputilsforkernel.h>
#include <pspmoduleexport.h>
#include <psploadcore.h>
#include <pspsdk.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "psplink.h"
#include "libs.h"

struct PspModuleImport
{
	const char *name;
	unsigned short version;
	unsigned short attribute;
	unsigned char entLen;
	unsigned char varCount;
	unsigned short funcCount;
	u32 *fnids;
	u32 *funcs;
	u32 *vnids;
	u32 *vars;
} __attribute__((packed));

static struct SceLibraryEntryTable *_libsFindLibrary(SceUID uid, const char *library)
{
	struct SceLibraryEntryTable *entry;
	SceModule *pMod;
	void *entTab;
	int entLen;

	pMod = sceKernelFindModuleByUID(uid);
	if(pMod != NULL)
	{
		int i = 0;

		entTab = pMod->ent_top;
		entLen = pMod->ent_size;
		while(i < entLen)
		{
			entry = (struct SceLibraryEntryTable *) (entTab + i);

			if((entry->libname) && (strcmp(entry->libname, library) == 0))
			{
				return entry;
			}
			else if(!entry->libname && !library)
			{
				return entry;
			}

			i += (entry->len * 4);
		}
	}

	return NULL;
}

void* libsFindExportAddrByNid(SceUID uid, const char *library, u32 nid)
{
	struct SceLibraryEntryTable *entry;
	u32 *addr = NULL;

	entry = _libsFindLibrary(uid, library);
	if(entry)
	{
		int count;
		int total;
		unsigned int *vars;

		total = entry->stubcount + entry->vstubcount;
		vars = entry->entrytable;

		if(entry->stubcount > 0)
		{
			for(count = 0; count < entry->stubcount; count++)
			{
				if(vars[count] == nid)
				{
					return &vars[count+total];
				}
			}
		}
	}

	return addr;
}

u32 libsNameToNid(const char *name)
{
	u8 digest[20];
	u32 nid;

	if(sceKernelUtilsSha1Digest((u8 *) name, strlen(name), digest) >= 0)
	{
		nid = digest[0] | (digest[1] << 8) | (digest[2] << 16) | (digest[3] << 24);
		return nid;
	}

	return 0;
}

void* libsFindExportAddrByName(SceUID uid, const char *library, const char *name)
{
	u32 nid;

	nid = libsNameToNid(name);

	return libsFindExportAddrByNid(uid, library, nid);
}

u32 libsFindExportByName(SceUID uid, const char *library, const char *name)
{
	u32 *addr;

	addr = libsFindExportAddrByName(uid, library, name);
	if(!addr)
	{
		return 0;
	}

	return *addr;
}

u32 libsFindExportByNid(SceUID uid, const char *library, u32 nid)
{
	u32 *addr;

	addr = libsFindExportAddrByNid(uid, library, nid);
	if(!addr)
	{
		return 0;
	}

	return *addr;
}
