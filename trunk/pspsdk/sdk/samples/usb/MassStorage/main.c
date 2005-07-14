/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to desmonstrate USB Mass Storage functionality
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * Derived from code written by PspPet
 * Code flow and API usage from VSH module "sysconf_plugin.prx"
 *
 * $Id$
 */
#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <pspthreadman.h>
#include <pspctrl.h>

/* Define the module info section */
PSP_MODULE_INFO("USBSample", 0x1000, 0, 1);
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

//helper function to make things easier
int LoadStartModule(char *path)
{
    u32 loadResult;
    u32 startResult;
    int status;

    loadResult = sceKernelLoadModule(path, 0, NULL);
    if (loadResult & 0x80000000)
	return -1;
    else
	startResult = sceKernelStartModule(loadResult, 0, NULL, &status, NULL);

    if (loadResult != startResult)
	return -2;

    return 0;
}

int main(void)
{
    SceCtrlData pad;
    u32 state = 0;
    u32 oldButtons = 0;
    u32 eventFlag;
    u32 retVal;

    pspDebugScreenInit();
    pspDebugScreenClear();
    //SetupCallbacks();

    //install kernel debug print
    pspDebugInstallKprintfHandler(NULL);

    //setup eventFlag for use with USBStorBoot driver
    //eventFlag = sceKernelCreateEventFlag("USBTestEventFlag", 0, 0, 0);

    //setup Pad
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(0);

    //print header now in case we have any errors
    printf("USB Sample v1.0 by John_K - Based off work by PSPPet\n");

    //start necessary drivers
    LoadStartModule("flash0:/kd/semawm.prx");
    LoadStartModule("flash0:/kd/usbstor.prx");
    LoadStartModule("flash0:/kd/usbstormgr.prx");
    LoadStartModule("flash0:/kd/usbstorms.prx");
    LoadStartModule("flash0:/kd/usbstorboot.prx");

    //setup USB drivers
    retVal = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
    if (retVal != 0) {
	printf("Error starting USB Bus driver (0x%08X)\n", retVal);
	sceKernelSleepThread();
    }
    retVal = sceUsbStart(PSP_USBSTOR_DRIVERNAME, 0, 0);
    if (retVal != 0) {
	printf("Error starting USB Mass Storage driver (0x%08X)\n", retVal);
	sceKernelSleepThread();
    }
    /*retVal = sceUsbstorBootRegisterNotify(eventFlag);
    if (retVal != 0) {
	printf("Error registering eventFlag with USB Mass Storage driver (0x%08X)\n", retVal);
	sceKernelSleepThread();
    }*/
    retVal = sceUsbstorBootSetCapacity(0x800000);
    if (retVal != 0) {
	printf("Error setting capacity with USB Mass Storage driver (0x%08X)\n", retVal);
	sceKernelSleepThread();
    }
    retVal = 0;
    //if everything worked we now enter our main loop
    for (;;) {
    	
	sceCtrlReadBufferPositive(&pad, 1);
	state = sceUsbGetState();
	pspDebugScreenSetXY(0, 0);
	printf("USB Sample v1.0 by John_K - Based off work by PSPPet\n\n");
	printf("%-14s: %s\n", "USB Driver",
	       state & PSP_USB_ACTIVATED ? "activated     " : "deactivated");
	printf("%-14s: %s\n", "USB Cable",
	       state & PSP_USB_CABLE_CONNECTED ? "connected    " : "disconnected");
	printf("%-14s: %s\n", "USB Connection",
	       state & PSP_USB_CONNECTION_ESTABLISHED ? "established" : "not present");
	printf("\nPress X to establish or destroy the USB connection\n");
	printf("Pressing Home will exit immediately (no confirmation)\n");

	if (oldButtons != pad.Buttons) {
	    if (pad.Buttons & PSP_CTRL_CROSS) {
		if (state & PSP_USB_ACTIVATED)
		    retVal = sceUsbDeactivate();
		else
		    retVal = sceUsbActivate(0x1c8);
	    }
	    if (pad.Buttons & PSP_CTRL_HOME) {
		break;
	    }
	}
	oldButtons = pad.Buttons;
	sceDisplayWaitVblankStart();
    }

    //cleanup drivers
    if (state & PSP_USB_ACTIVATED) {
    	retVal = sceUsbDeactivate();
    	if (retVal != 0)
		printf("Error calling sceUsbDeactivate (0x%08X)\n", retVal);
    }
    /*retVal = sceUsbstorBootUnregisterNotify(eventFlag);
    if (retVal != 0)
	printf("Error unregistering eventFlag notification (0x%08X)\n", retVal);
    */
    retVal = sceUsbStop(PSP_USBSTOR_DRIVERNAME, 0, 0);
    if (retVal != 0)
	printf("Error stopping USB Mass Storage driver (0x%08X)\n", retVal);
    /*retVal = sceKernelDeleteEventFlag(eventFlag);
    if (retVal != 0)
	printf("Error deleting eventFlag (0x%08X)\n", retVal);
    */
    retVal = sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
    if (retVal != 0)
	printf("Error stopping USB BUS driver (0x%08X)\n", retVal);
    sceKernelDelayThread(2000000);

    //Exit program
    sceKernelExitGame();
}
