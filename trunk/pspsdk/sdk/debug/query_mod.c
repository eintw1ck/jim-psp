/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * query_mod.c - Replacement for sceKernelQueryModuleInfo for v1.0 units.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <string.h>

/* Internal kernel structure for the module information, only correct on a v1 */
struct SceModuleInfo_v1_Internal
{
	struct SceModuleInfo_v1_Inernal *next;
	unsigned short attribute;	
	unsigned char  version[2];
	char name[28]; 
	unsigned int unk1[7];
	unsigned char *export_table; 
	unsigned int export_size; 
	unsigned char *import_table; 
	unsigned int import_size; 
	unsigned int unk2[4];
	unsigned int entry_addr; 
	unsigned int gp_value; 
	unsigned int text_addr; 
	unsigned int text_size; 
	unsigned int data_size; 
	unsigned int bss_size; 
	unsigned int nsegment; 
	unsigned int segmentaddr[4]; // x7c
	unsigned int segmentsize[4]; // x80
} __attribute__((packed));

struct SceModuleInfo_v1_Internal *sceKernelFindModuleByUID(int modid);

int pspDebugQueryModuleInfoV1(SceUID uid, SceKernelModuleInfo *modinfo)
{
	struct SceModuleInfo_v1_Internal *mod;

	mod = (struct SceModuleInfo_v1_Internal *) sceKernelFindModuleByUID(uid);
	if(mod != NULL)
	{
		memcpy(modinfo->name, mod->name, 28);
		modinfo->attribute = mod->attribute;
		modinfo->version[0] = mod->version[0];
		modinfo->version[1] = mod->version[1];
		modinfo->nsegment = (unsigned char )mod->nsegment;
		modinfo->entry_addr = mod->entry_addr;
		modinfo->gp_value = mod->gp_value;
		modinfo->text_addr = mod->text_addr;
		modinfo->text_size = mod->text_size;
		modinfo->data_size = mod->data_size;
		modinfo->bss_size = mod->bss_size;
		memcpy(modinfo->segmentaddr, mod->segmentaddr, sizeof(unsigned int) * 4);
		memcpy(modinfo->segmentsize, mod->segmentsize, sizeof(unsigned int) * 4);
	}
	else
	{
		return -1;
	}

	return 0;
}
