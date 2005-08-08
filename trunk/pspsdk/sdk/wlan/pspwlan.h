/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspwlan.h - Prototypes for the sceWlan library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __PSPWLAN_H__
#define __PSPWLAN_H__

/**
 * Determine if the wlan device is currently powered on
 *
 * @return 0 if off, 1 if on
 */
int sceWlanDevIsPowerOn(void);

/**
 * Determine the state of the Wlan power switch
 *
 * @return 0 if off, 1 if on
 */
int sceWlanGetSwitchState(void);

/**
 * Get the Ethernet Address of the wlan controller
 *
 * @param etherAddr - pointer to a buffer of chars with at least length 7
 * @return 0 on success, < 0 on error
 */
int sceWlanGetEtherAddr(char *etherAddr);

/*
int sceWlanGPBindRegError();
*/
#endif
