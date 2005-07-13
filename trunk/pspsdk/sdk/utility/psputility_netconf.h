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

/**
 * Datatype for sceUtilityGetNetParam
 * since it can return a u32 or a string
 * we use a union to avoid ugly casting
 */
typedef union {
	u32 asUint;
	char asString[128];
} netData;

#define PSP_NETPARAM_NAME          0 // string
#define PSP_NETPARAM_SSID          1 // string
#define PSP_NETPARAM_SECURE        2 // int
#define PSP_NETPARAM_WEPKEY        3 // string
#define PSP_NETPARAM_IS_STATIC_IP  4 // int
#define PSP_NETPARAM_IP            5 // string
#define PSP_NETPARAM_NETMASK       6 // string
#define PSP_NETPARAM_ROUTE         7 // string
#define PSP_NETPARAM_MANUAL_DNS    8 // int
#define PSP_NETPARAM_PRIMARYDNS    9 // string
#define PSP_NETPARAM_SECONDARYDNS 10 // string
#define PSP_NETPARAM_PROXY_USER   11 // string
#define PSP_NETPARAM_PROXY_PASS   12 // string
#define PSP_NETPARAM_USE_PROXY    13 // int
#define PSP_NETPARAM_PROXY_SERVER 14 // string
#define PSP_NETPARAM_PROXY_PORT   15 // int
#define PSP_NETPARAM_UNKNOWN1     16 // int
#define PSP_NETPARAM_UNKNOWN2     17 // int

#define PSP_NETPARAM_ERROR_BAD_NETCONF	0x80110601
#define PSP_NETPARAM_ERROR_BAD_PARAM	0x80110604

/**
 * Check existance of a Net Configuration
 *
 * @param id - id of net Configuration (1 to n)
 * @returns 0 on success, 
 */
int sceUtilityCheckNetParam(int id);

/**
 * Get Net Configuration Parameter
 *
 * @param conf - Net Configuration number (1 to n)
 * (0 returns valid but seems to be a copy of the last config requested)
 * @param param - which parameter to get
 * @param data - parameter data
 * @returns 0 on success, 
 */
int sceUtilityGetNetParam(int conf, int param, netData *data);

#ifdef __cplusplus
}
#endif

#endif
