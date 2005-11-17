/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * inethelper.h - Helper functions for internet related modules
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#include <pspkernel.h>
#include <string.h>
#include <pspsdk.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>
#include <pspnet_apctl.h>
//#include <pspNetApDialogDummy.h>

int loadModule(const char* filename, int mpid) {
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
		Kprintf("sceKernelLoadModule failed with 0x%08X\n", retVal);
		return -1;
	}

	modid = retVal;

	retVal = sceKernelStartModule(modid, 0, 0, &mresult, NULL);
	if(retVal < 0){
		Kprintf("sceKernelStartModule failed with 0x%08X\n", retVal);
		return -1;
	}

	return modid;
}

int loadInetModules() {
	int modID;

	modID = loadModule("flash0:/kd/ifhandle.prx", PSP_MEMORY_PARTITION_KERNEL);
	if (modID < 0)
		return modID;

	modID = loadModule("flash0:/kd/pspnet.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		fixupImports(modID);

	modID = loadModule("flash0:/kd/pspnet_inet.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		fixupImports(modID);

	modID = loadModule("flash0:/kd/pspnet_apctl.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		fixupImports(modID);
/*
	modID = loadModule("flash0:/kd/pspnet_ap_dialog_dummy.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		fixupImports(modID);
*/
	modID = loadModule("flash0:/kd/pspnet_resolver.prx", PSP_MEMORY_PARTITION_USER); 
	if (modID < 0)
		return modID;
	else
		fixupImports(modID);

	return 0;
}

int initInet() {
	u32 retVal;

	retVal = sceNetInit(0x20000, 0x20, 0x1000, 0x20, 0x1000);
	if (retVal != 0)
		return retVal;

	retVal = sceNetInetInit();
	if (retVal != 0)
		return retVal;

	retVal = sceNetResolverInit();
	if (retVal != 0)
		return retVal;
	
	retVal = sceNetApctlInit(0x1000, 0x42);
	if (retVal != 0)
		return retVal;

/*
	retVal = sceNetApDialogDummyInit();
	if(retVal != 0)
		return retVal;
*/
	return 0;
}

void termInet() {
	//sceNetApDialogDummyTerm();
	sceNetApctlTerm();
	sceNetResolverTerm();
	sceNetInetTerm();
	sceNetTerm();
}
