/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_netconf.h - Definitions and Functions for Network Configuration 
 *                         section of the pspUtility library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __PSPUTILITY_NETCONF_H__
#define __PSPUTILITY_NETCONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

enum pspUtilityNetconfActions {
	PSP_NETCONF_ACTION_CONNECTAP,
	PSP_NETCONF_ACTION_DISPLAYSTATUS
};

enum pspUtilityNetconfStatus {
	PSP_NETCONF_STATUS_INIT = 1,
	PSP_NETCONF_STATUS_RUNNING,
	PSP_NETCONF_STATUS_FINISHED
};

typedef struct _pspUtilityNetconfData {
	u32 size;
	int language;
	int buttonSwap;
	int unknown[4];
	int result;
	int unknown2[4];
	int action; //one of pspUtilityNetconfActions
	u32 unknown3;
} pspUtilityNetconfData;

/**
 * Init the Network Configuration Dialog Utility
 *
 * @param data - pointer to pspUtilityNetconfData to be initialized
 * @return 0 on success, < 0 on error
 */
int sceUtilityNetconfInitStart (pspUtilityNetconfData *data);

/**
 * Shutdown the Network Configuration Dialog Utility
 *
 * @return 0 on success, < 0 on error
 */
int sceUtilityNetconfShutdownStart (void);

/**
 * Update the Network Configuration Dialog GUI
 * 
 * @param unknown - unknown; set to 1
 * @return 0 on success, < 0 on error
 */
int sceUtilityNetconfUpdate (int unknown);

/**
 * Get the status of a running Network Configuration Dialog
 *
 * @return one of pspUtilityNetconfStatus on success, < 0 on error
 */
int sceUtilityNetconfGetStatus (void);

#ifdef __cplusplus
}
#endif

#endif
