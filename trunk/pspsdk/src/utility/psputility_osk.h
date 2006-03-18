/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_osk.h - Definitions and Functions for OSK section of
 *                     the pspUtility library
 *
 * Copyright (c) 2006 McZonk
 *
 * $Id$
 */
#ifndef PSPOSK_H
#define PSPOSK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

/**
 * Return-values for sceUtilityOskGetStatus()
**/
typedef enum
{
	PSP_OSK_NONE = 0, /**< No keyboard is currently active. */
	PSP_OSK_INIT, /**< The keyboard is currently being initialized. */
	PSP_OSK_VISIBLE, /**< The keyboard is visible and ready for use. */
	PSP_OSK_QUIT, /**< The keyboard has been canceled and should be shut down. */
	PSP_OSK_FINISHED /**< The keyboard has successfully shut down. */
} SceOskState;

/**
 *
**/
typedef struct _SceUtilityOskData
{
    int unk_00;
    int unk_04;
    int language;
    int unk_12;
    int unk_16;
    int lines;
    int unk_24;
    unsigned short* desc;
    unsigned short* intext;
    int outtextlength;
    unsigned short* outtext;
    int rc;
    int outtextlimit;
} SceUtilityOskData;

/**
 *
**/
typedef struct _SceUtilityOskParams
{
	unsigned int size;
	int language;
	int buttonswap;
	int unk_12; // set 17
	int unk_16; // set 19
	int unk_20; // set 18
	int unk_24; // set 16
	int rc;
	int unk_32;
	int unk_36;
	int unk_40;
	int unk_44;
	int unk_48; // set 1, if 0 nothing happens, if 2 crash ...
	SceUtilityOskData* data;
	int unk_56;
	int unk_60;
} SceUtilityOskParams;

// it should be possible to choose the char set but i have no idea how
// ... it is not language

/**
 * Create a on-screen keyboard
 *
 * @param params - OSK parameters
 * @returns 0 on success
**/
int sceUtilityOskInitStart(SceUtilityOskParams* params);

/**
 * Remove a currently active keyboard. After calling this function you must
 * poll sceUtilityOskGetStatus() until it returns PSP_OSK_FINISHED.
**/
int sceUtilityOskShutdownStart(void);

/**
 * Refresh the GUI for a keyboard currently active
 *
 * @param n - Unknown, pass 2
**/
int sceUtilityOskUpdate(int n);

/**
 * Get the status of a on-screen keyboard currently active.
 *
 * @returns the current status of the keyboard. See SceOskState for details.
**/
int sceUtilityOskGetStatus(void);

#ifdef __cplusplus
}
#endif

#endif
