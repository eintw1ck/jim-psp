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
	return _pspDebugFindModuleInRange(mod_name, 0x88000000, 0x8a000000);
}

/* Find a module in user mode */
SceModuleInfo *pspDebugFindUserModule(const char *mod_name)
{
	return _pspDebugFindModuleInRange(mod_name, 0x08400000, 0x0a000000);
}

/* Find an exported function from its nid and library name */
void *pspDebugFindExportedFunction(SceModuleInfo *mod, const char *exp_name, u32 nid)
{
	struct PspModuleExport *export;
	struct PspModuleExport *exp_end;
	void   *pRet;
	/* We assume that mod is already valid, if not, well though, this isn't supposed to be a
	   general purpose library */

	/* Basic check */
	if(mod == NULL)
	{
		return NULL;
	}

	export = (struct PspModuleExport *) mod->ent_top;
	exp_end = (struct PspModuleExport *) mod->ent_end;
	pRet = NULL;

	/* Skip the first export */
	export++;
	while(export < exp_end)
	{
		if(strcmp(exp_name, export->name) == 0)
		{
			u32 *nidlist;
			int i;
			int t_count;

			t_count = export->f_count + export->v_count;
			nidlist = export->exports;
			for(i = 0; i < export->f_count; i++)
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
