/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusb.h - Prototypes for the sceUsb library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __PSPUSB_H__
#define __PSPUSB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_USBBUS_DRIVERNAME "USBBusDriver"

//Defines for use with status function return values
#define PSP_USB_ACTIVATED              0x200
#define PSP_USB_CABLE_CONNECTED        0x020 
#define PSP_USB_CONNECTION_ESTABLISHED 0x002

/**
  * Start a USB driver.
  * 
  * @param driverName - name of the USB driver to start
  * @param unknown1 - Unknown, set to 0 
  * @param unknown2 - Unknown, set to 0
  *
  * @return 0 on success
  */
int sceUsbStart(const char* driverName, int unknown1, int unknown2);

/**
  * Stop a USB driver.
  * 
  * @param driverName - name of the USB driver to stop
  * @param unknown1 - Unknown, set to 0 
  * @param unknown2 - Unknown, set to 0
  *
  * @return 0 on success
  */
int sceUsbStop(const char* driverName, int unknown1, int unknown2);

/**
  * Activate a USB driver.
  * 
  * @param driverName - name of the USB driver to stop
  * @param unknown1 - Unknown, set to 0 
  * @param unknown2 - Unknown, set to 0
  *
  * @return 0 on success
  */
int sceUsbActivate(u32 flag);

/**
  * Deactivate USB driver.
  *
  * @return 0 on success
  */
int sceUsbDeactivate();

/**
  * Get USB state
  * 
  * @return OR'd PSP_USB_* constants
  */
int sceUsbGetState(void);

// the following are disabled until more testing is done
#if 0
/**
  * Get state of a specific USB driver
  * 
  * @param driverName - name of USB driver to get status from
  *
  * @return unknown
  */
int sceUsbGetDrvState(const char* driverName);


int sceUsbGetDrvList(u32 r4one, u32* r5ret, u32 r6one);
int sceUsbWaitState(?);
int sceUsbWaitCancel(void);
#endif

#ifdef __cplusplus
}
#endif

#endif
