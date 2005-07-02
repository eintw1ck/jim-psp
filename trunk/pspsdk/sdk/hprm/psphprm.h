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

/**
  * sceHprmInit
  *
  */
void sceHprmInit();

/**
  * sceHprmEnd
  *
  */
void sceHprmEnd();

/**
  * sceHprmSuspend
  *
  */
void sceHprmSuspend();

/**
  * sceHprmResume
  *
  */
void sceHprmResume();

/**
  * sceHprmSetConnectCallback
  *
  */
void sceHprmSetConnectCallback();

/**
  * sceHprmRegisterCallback
  *
  */
void sceHprmRegisterCallback();

/**
  * sceHprmReset
  *
  */
void sceHprmReset();

/**
  * sceHprmGetInternalState
  *
  */
void sceHprmGetInternalState();

/**
  * sceHprmGetModel
  *
  */
void sceHprmGetModel();

/**
  * sceHprmPeekCurrentKey
  *
  */
void sceHprmPeekCurrentKey();

/**
  * sceHprmPeekLatch
  *
  */
void sceHprmPeekLatch();

/**
  * sceHprmReadLatch
  *
  */
void sceHprmReadLatch();


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
