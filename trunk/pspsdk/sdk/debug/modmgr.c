/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * modmgr.c - Basic module management for applications. (Used when we cannot link to kmode libs)
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id$
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <string.h>

#define EXPORT_MODINFO_NID	0xF01D73A7
#define EXPORT_FINDMOD_NID  0xCF8A41B1

#define EXPORT_VARIABLE 1
#define EXPORT_FUNCTION 0

typedef struct _KernelModuleEntry
{
	struct _KernelModuleEntry *next;
	u32 flags;
	char name[28];
	u32  unk1;
	u32  unk2;
	u32  unk3;
	u32  unk4;
	u32  unk5;
	u32  unk6;
	u32  unk7;
	u8 *export_table;
	u32  export_size;
	u8 *import_table;
	u32  import_size;
} KernelModuleEntry;

static KernelModuleEntry* (*sceKernelFindModuleByName)(const char *name) = NULL;

/* Structure to hold the module export information */
struct PspModuleExport
{
	const char* name;
	u32 flags;
	u8  unk;
	u8  v_count;
	u16 f_count;
	u32 *exports;
} __attribute__((packed));

static void *_pspDebugFindExport(struct PspModuleExport *export, struct PspModuleExport *exp_end, const char *exp_name, u32 nid, int type);

/* General function to find a module within a certain range of memory addresses */
static SceModuleInfo *_pspDebugFindModuleInRange(const char *mod_name, u32 start_addr, u32 end_addr)
{
	SceModuleInfo *curr_mod;
	int found = 0;
	u32 *pstart;
	u32 *pmem;
	u32 *pend;

	pstart = pmem = (u32 *) start_addr;
	pend = (u32 *) (end_addr - sizeof(SceModuleInfo));
	while(pmem < pend)
	{
		curr_mod = (SceModuleInfo *) pmem;
		if(strncmp(curr_mod->modname, mod_name, 27) == 0)
		{
			/* Check memory addresses */
			u32 *ent_top;
			u32 *ent_end;
			u32 *stub_top;
			u32 *stub_end;

			ent_top = curr_mod->ent_top;
			ent_end = curr_mod->ent_end;
			stub_top = curr_mod->stub_top;
			stub_end = curr_mod->stub_end;

			if((ent_top >= pstart) && (ent_end >= ent_top) && (ent_end < pend) &&
				(stub_top >= pstart) && (stub_end >= stub_top) && (stub_end < pend))
			{
				found = 1;
				break;
			}
		}

		pmem++;
	}

	if(found == 0)
	{
		return NULL;
	}

	return curr_mod;
}

/* Find a module in kernel mode */
SceModuleInfo *pspDebugFindModule(const char *mod_name)
{
	SceModuleInfo *ret_mod = NULL;

	/* If we are in kernel mode then we don't have to worry so much, use
	   sceKernelFindModuleByName if we can */
	if(sceKernelFindModuleByName == NULL)
	{
		SceModuleInfo *mod = _pspDebugFindModuleInRange("sceLoaderCore", 0x88000000, 0x8a000000);
		if(mod != NULL)
		{
			sceKernelFindModuleByName = pspDebugFindExportedFunction(mod, "LoadCoreForKernel", EXPORT_FINDMOD_NID);
		}
	}

	if(sceKernelFindModuleByName != NULL)
	{
		KernelModuleEntry *modent;

		modent = sceKernelFindModuleByName(mod_name);
		if(modent != NULL)
		{
			ret_mod = _pspDebugFindExport((struct PspModuleExport*) modent->export_table, 
										  (struct PspModuleExport*) (modent->export_table + modent->export_size),
										  NULL, EXPORT_MODINFO_NID, EXPORT_VARIABLE);
		}
	}
	else
	{
		/* For what ever reason we couldn't find the function, brute force */
		ret_mod =  _pspDebugFindModuleInRange(mod_name, 0x88000000, 0x8a000000);
	}

	return ret_mod;
}

/* Find a module in user mode */
SceModuleInfo *pspDebugFindUserModule(const char *mod_name)
{
	return _pspDebugFindModuleInRange(mod_name, 0x08400000, 0x0a000000);
}

/* General function to find an export, either variable or function */
static void *_pspDebugFindExport(struct PspModuleExport *export, struct PspModuleExport *exp_end, const char *exp_name, u32 nid, int type)
{
	void   *pRet;

	/* We assume that mod is already valid, if not, well though, this isn't supposed to be a
	   general purpose library */

	pRet = NULL;

	while(export < exp_end)
	{
		int found = 0;

		if(exp_name == NULL)
		{
			if(export->name == 0)
			{
				found = 1;
			}
		}
		else if((export->name != 0) && (strcmp(exp_name, export->name) == 0))
		{
			found = 1;
		}

		if(found)
		{
			u32 *nidlist;
			int i;
			int start;
			int end;
			int t_count;

			t_count = export->f_count + export->v_count;
			nidlist = export->exports;

			if(type == EXPORT_VARIABLE)
			{
				start = export->f_count;
				end = t_count;
			}
			else
			{
				start = 0;
				end = export->f_count;
			}

			for(i = start; i < end; i++)
			{
				if(nidlist[i] == nid)
				{
					pRet = (void *) nidlist[i+t_count];
					break;
				}
			}

			break;
		}

		export++;
	}

	return pRet;
}


void *pspDebugFindExportedFunction(SceModuleInfo *mod, const char *exp_name, u32 nid)
{
	if(mod == NULL)
	{
		return NULL;
	}

	return _pspDebugFindExport(mod->ent_top, mod->ent_end, exp_name, nid, EXPORT_FUNCTION);
}

void *pspDebugFindExportedVariable(SceModuleInfo *mod, const char *exp_name, u32 nid)
{
	if(mod == NULL)
	{
		return NULL;
	}

	return _pspDebugFindExport(mod->ent_top, mod->ent_end, exp_name, nid, EXPORT_VARIABLE);
}
