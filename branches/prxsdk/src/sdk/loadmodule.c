/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * loadmodule.c - Routines to simplify module loading and unloading.
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id$
 */

#include <string.h>
#include <pspuser.h>

SceUID pspSdkLoadStartModule(const char *filename, int mpid)
{
	SceKernelLMOption option;
	SceUID modid = 0;
	int retVal = 0, mresult;

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	retVal = sceKernelLoadModule(filename, 0, &option);
	if(retVal < 0){
		return retVal;
	}

	modid = retVal;

	retVal = sceKernelStartModule(modid, 0, 0, &mresult, NULL);
	if(retVal < 0){
		return retVal;
	}

	return modid;
}


