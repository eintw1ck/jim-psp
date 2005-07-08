/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudio.h - Prototypes for the sceHprm library.
 *
 * Copyright (c) 2005 Adresd
 *
 * $Id$
 */
#ifndef __HPRM_H__
#define __HPRM_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Hprm Hprm Remote */

/** @addtogroup Hprm */

/*@{*/

/** Enumeration of the remote keys */
enum PspHprmKeys
{
	PSP_HPRM_PLAYPAUSE  = 0x1,
	PSP_HPRM_FORWARD    = 0x4,
	PSP_HPRM_BACK       = 0x8,
	PSP_HPRM_VOL_UP		= 0x10,
	PSP_HPRM_VOL_DOWN   = 0x20,
	PSP_HPRM_HOLD       = 0x80
};

/** 
  * Peek at the current being pressed on the remote.
  * 
  * @param key - Pointer to the u32 to receive the key bitmap, should be one or
  * more of ::PspHprmKeys
  *
  * @return < 0 on error
  */
int sceHprmPeekCurrentKey(u32 *key);

/**
  * Peek at the current latch data.
  *
  * @param latch - Pointer a to a 4 dword array to contain the latch data.
  *
  * @return < 0 on error.
  */
int sceHprmPeekLatch(u32 *latch);

/**
  * Read the current latch data.
  *
  * @param latch - Pointer a to a 4 dword array to contain the latch data.
  *
  * @return < 0 on error.
  */
int sceHprmReadLatch(u32 *latch);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
