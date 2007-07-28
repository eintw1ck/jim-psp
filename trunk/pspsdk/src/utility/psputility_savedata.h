/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_savedata.h - Definitions and Functions for savedata part of
 *                     pspUtility library
 *
 * Copyright (c) 2005    Shine
 *                       weltall <weltall@consoleworld.org>
 *                       Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id$
 */

#ifndef __PSPUTILITY_SAVEDATA_H__
#define __PSPUTILITY_SAVEDATA_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** title, savedataTitle, detail: parts of the unencrypted SFO
    data, it contains what the VSH and standard load screen shows */
typedef struct PspUtilitySavedataSFOParam
{
	char title[0x80];
	char savedataTitle[0x80];
	char detail[0x400];
	unsigned char parentalLevel;
	unsigned char unknown[3];
} PspUtilitySavedataSFOParam;

typedef struct PspUtilitySavedataFileData {
	void *buf;
	SceSize bufSize;
	SceSize size;	/* ??? - why are there two sizes? */
	int unknown;
} PspUtilitySavedataFileData;

/** Structure to hold the parameters for the ::sceUtilitySavedataInitStart function.
  */
typedef struct SceUtilitySavedataParam
{
	pspUtilityDialogCommon base;

	/** mode: 0 to load, 1 to save */
	int mode;
	int unknown12;

	/** unknown13 use 0x10 */
	int unknown13;

	/** gameName: name used from the game for saves, equal for all saves */
	char gameName[16];
	/** saveName: name of the particular save, normally a number */
	char saveName[24];
	/** fileName: name of the data file of the game for example DATA.BIN */
	char fileName[16];

	/** pointer to a buffer that will contain data file unencrypted data */
	void *dataBuf;
	/** size of allocated space to dataBuf */
	SceSize dataBufSize;
	SceSize dataSize;

	PspUtilitySavedataSFOParam sfoParam;

	PspUtilitySavedataFileData icon0FileData;
	PspUtilitySavedataFileData icon1FileData;
	PspUtilitySavedataFileData pic1FileData;
	PspUtilitySavedataFileData snd0FileData;

	unsigned char unknown17[4];
} SceUtilitySavedataParam;


/**
 * Saves or Load savedata to/from the passed structure
 * After having called this continue calling sceUtilitySavedataGetStatus to
 * check if the operation is completed
 *
 * @param params - savedata parameters
 * @returns 0 on success
 */
int sceUtilitySavedataInitStart(SceUtilitySavedataParam * params);

/**
 * Check the current status of the saving/loading/shutdown process
 * Continue calling this to check current status of the process
 * before calling this call also sceUtilitySavedataUpdate
 * @returns 2 if the process is still being processed.
 * 3 on save/load success, then you can call sceUtilitySavedataShutdownStart.
 * 4 on complete shutdown.
 */
int sceUtilitySavedataGetStatus(void);


/**
 * Shutdown the savedata utility. after calling this continue calling
 * ::sceUtilitySavedataGetStatus to check when it has shutdown
 *
 * @return 0 on success
 *
 */
int sceUtilitySavedataShutdownStart(void);

/**
 * Refresh status of the savedata function
 *
 * @param unknown - unknown, pass 1
 */
void sceUtilitySavedataUpdate(int unknown);

#ifdef __cplusplus
}
#endif

#endif
