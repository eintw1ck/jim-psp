/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate how to use savedata utility
 *
 * Copyright (c) 2005 weltall (weltall@consoleworld.org)
 * Based on work by Shine
 *
 * $Id$
 */
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pspmoduleinfo.h>
#include <pspiofilemgr.h>
#include <pspdebug.h>
#include <psputility.h>

/* Define the module info section */
PSP_MODULE_INFO("Savedata Sample", 0, 1, 0);

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf

/* Game information.  This example would place savedata in
   the directory /PSP/SAVEDATA/DEMO111110000, with the 
   encrypted data being stored in the file SAVE.BIN. */
char *gameName = "DEMO11111";
char *saveName = "0000";
char *fileName = "SAVE.BIN";

/* define for buffer length */

#define DATABUFFLEN   0x100000
#define READICON0LEN  0x100000
#define READICON1LEN  0x100000
#define READPIC1LEN   0x100000

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if (thid >= 0)
		sceKernelStartThread(thid, 0, 0);
	return thid;
}

/* Utility Savedata functions */

/* based on Shine's function, args: SceUtilitySavedataParam* savedata pass the save data structure
                       mode: pass the mode parameter 0 = load 1 = save */

void initSavedata(SceUtilitySavedataParam * savedata, int mode)
{
	memset(savedata, 0, sizeof(SceUtilitySavedataParam));
	savedata->size = sizeof(SceUtilitySavedataParam);

	savedata->unknown[0] = 0x11;
	savedata->unknown[1] = 0x13;
	savedata->unknown[2] = 0x12;
	savedata->unknown[3] = 0x10;
	savedata->unknown13 = 1;
	savedata->mode = mode;		/* mode: 0 = load, 1 = save */

	strcpy(savedata->gameName, gameName);	/* first part of the save name, game identifier name */
	strcpy(savedata->saveName, saveName);	/* second part of the save name, save identifier name */
	strcpy(savedata->fileName, fileName);	/* name of the data file */

	/* Allocate buffers used to store various parts of the save data. */
	savedata->dataBuf = malloc(DATABUFFLEN);
	savedata->dataBufSize = DATABUFFLEN;

	savedata->icon0FileData.buf = malloc(READICON0LEN);
	savedata->icon0FileData.bufSize = READICON0LEN;
	savedata->icon1FileData.buf = malloc(READICON1LEN);
	savedata->icon1FileData.bufSize = READICON1LEN;
	savedata->pic1FileData.buf = malloc(READPIC1LEN);
	savedata->pic1FileData.bufSize = READPIC1LEN;
}

void WorkSaveData(int mode)
{
	SceUtilitySavedataParam savedata;

	initSavedata(&savedata, mode);

	int fd_data = sceIoOpen("ms0:/dataBuf", PSP_O_TRUNC | PSP_O_CREAT | PSP_O_WRONLY, 0777);
	int fd_sfo = sceIoOpen("ms0:/sfodata", PSP_O_TRUNC | PSP_O_CREAT | PSP_O_WRONLY, 0777);

	/* If we are writing savedata, then load files and put their contents into the savedata structure. */
	if (mode == 1)				
	{
		sceIoRead(fd_data, savedata.dataBuf, DATABUFFLEN);
		sceIoRead(fd_sfo, &savedata.sfoParam.title, sizeof(savedata.sfoParam.title));
		sceIoRead(fd_sfo, &savedata.sfoParam.savedataTitle, sizeof(savedata.sfoParam.savedataTitle));
		sceIoRead(fd_sfo, &savedata.sfoParam.detail, sizeof(savedata.sfoParam.detail));
		sceIoClose(fd_data);
		sceIoClose(fd_sfo);
	}

	int result = sceUtilitySavedataInitStart(&savedata);
	if (result)
		printf("sceUtilitySavedataInitStart failed: %i\n", result);

	/* Wait for sceUtilitySavedataInitStart() to complete. */
	while (1)					
	{
		result = sceUtilitySavedataGetStatus();
		if (result == 3)
			break;
		sceUtilitySavedataUpdate(1);
		sceDisplayWaitVblankStart();
	}

	/* Shutdown the Savedata Utility. */
	result = sceUtilitySavedataShutdownStart();	
	if (result)
		printf("sceUtilitySavedataShutdownStart() failed: %i", result);

	/* Wait for sceUtilitySavedataShutdownStart() to complete. */
	while (1)					
	{
		result = sceUtilitySavedataGetStatus();
		if (result == 4)
			break;
		sceUtilitySavedataUpdate(1);
		sceDisplayWaitVblankStart();
	}

	/* If we are reading save data then write it to a file in the MS root directory. */
	if (mode == 0)
	{
		sceIoWrite(fd_data, savedata.dataBuf, DATABUFFLEN);
		sceIoWrite(fd_sfo, &savedata.sfoParam.title, sizeof(savedata.sfoParam.title));
		sceIoWrite(fd_sfo, &savedata.sfoParam.savedataTitle, sizeof(savedata.sfoParam.savedataTitle));
		sceIoWrite(fd_sfo, &savedata.sfoParam.detail, sizeof(savedata.sfoParam.detail));
		sceIoClose(fd_data);
		sceIoClose(fd_sfo);
	}
}

/* main routine */
int main(int argc, char *argv[])
{
	SetupCallbacks();
	pspDebugScreenInit();

	printf("sceUtilitySavedata sample\n\n"
		   "Press Circle to load savedata, and put it into ms0:/\n"
		   "Press Cross to save savedata, from files put into ms0:/\n"
		   "Press Triangle to exit.\n\n");

	while (1)
	{
		SceCtrlData pad;

		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_CIRCLE) {
			WorkSaveData(0);
		}
		if (pad.Buttons & PSP_CTRL_CROSS) {
			WorkSaveData(1);
		}
		if (pad.Buttons & PSP_CTRL_TRIANGLE)
			break;
	}

	sceKernelExitGame();
	return 0;
}
