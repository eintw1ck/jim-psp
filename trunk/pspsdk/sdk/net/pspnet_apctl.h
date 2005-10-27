/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_apctl.h - PSP networking libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 *
 * Portions based on PspPet's wifi_03 sample code.
 * 
 * $Id$
 */

#ifndef PSPNET_APCTL_H
#define PSPNET_APCTL_H

#ifdef __cplusplus
extern "C" {
#endif

int sceNetApctlInit(int stackSize, int initPriority);

int sceNetApctlTerm(void);

int sceNetApctlGetInfo(int code, void *pInfo);

/*
// sceNetApctlAddHandler
// sceNetApctlDelHandler
*/

int sceNetApctlConnect(int connIndex);

int sceNetApctlDisconnect(void);

int sceNetApctlGetState(int *pState);

#ifdef __cplusplus
}
#endif

#endif /* PSPNET_APCTL_H */
