/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_dialogs.h - Definitions and Functions for Dialogs
 *                         section of the pspUtility library
 *
 * Copyright (c) 2005 Marcus Comstedt <marcus@mc.pp.se>
 *
 * $Id$
 */
#ifndef __PSPUTILITY_DIALOGS_H__
#define __PSPUTILITY_DIALOGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <psptypes.h>

/** Structure to hold the parameters for a message dialog
  */
typedef struct _SceUtilityMsgDialogParams {
    /** Size of the structure */
    SceSize     size;

    /** Language for predefined guide texts */
    int		language;

    /** Set to 1 for X/O button swap (US model) */
    int         buttonSwap;

    /** ? */
    int		unknown[12];

    /** The message to display (may contain embedded linefeeds) */
    char	message[512];

} SceUtilityMsgDialogParams;


/**
 * Create a message dialog
 *
 * @param params - dialog parameters
 * @returns 0 on success
 */
int sceUtilityMsgDialogInitStart(SceUtilityMsgDialogParams *params);

/**
 * Remove a message dialog currently active.  After calling this
 * function you need to keep calling GetStatus and Update until
 * you get a status of 4.
 */
void sceUtilityMsgDialogShutdownStart(void);

/**
 * Get the current status of a message dialog currently active.
 *
 * @return 2 if the GUI is visible (you need to call sceUtilityMsgDialogGetStatus).
 * 3 if the user cancelled the dialog, and you need to call sceUtilityMsgDialogShutdownStart.
 * 4 if the dialog has been successfully shut down.
 */
int sceUtilityMsgDialogGetStatus(void);

/**
 * Refresh the GUI for a message dialog currently active
 *
 * @param n - unknown, pass 2
 */
void sceUtilityMsgDialogUpdate(int n);

#ifdef __cplusplus
}
#endif

#endif
