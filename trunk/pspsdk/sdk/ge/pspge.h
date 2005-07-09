/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspge.h - Prototypes for the sceGe library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __GE_H__
#define __GE_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Typedef for a GE callback */
typedef void (*GeCallback)(int id, void *arg);

/** Structure to hold the callback data */
typedef struct _GeCallbackData
{
	/** GE callback for the signal interrupt */
	GeCallback signal_func;
	/** GE callback argument for signal interrupt */
	void *signal_arg;
	/** GE callback for the finish interrupt */
	GeCallback finish_func;
	/** GE callback argument for finish interrupt */
	void *finish_arg;
} GeCallbackData;

/**
  * Register callback handlers for the the Ge 
  *
  * @param cb - Configured callback data structure
  * @return The callback ID, < 0 on error
  */
int sceGeSetCallback(GeCallbackData *cb);

/**
  * Unregister the callback handlers
  *
  * @param cbid - The ID of the callbacks from sceGeSetCallback
  * @return < 0 on error
  */
int sceGeUnsetCallback(int cbid);

/** 
  * Enqueue a display list.
  *
  * @param list - The head of the list to queue.
  * @param stall - The stall address.
  * If NULL then no stall address set and the list is transferred immediately.
  * @param cbid - ID of the callback set by calling sceGeSetCallback
  * @param arg - Probably a parameter to the callbacks (to be confirmed)
  *
  * @return The ID of the queue.
  */
int sceGeListEnQueue(void *list, void *stall, int cbid, void *arg);

/**
  * Update the stall address for the specified queue.
  * 
  * @param qid - The ID of the queue.
  * @param stall - The stall address to update
  *
  * @return Unknown. Probably 0 if successful.
  */
int sceGeListUpdateStallAddr(int qid, void *stall);

/** Get the address of VRAM (normally 0x04000000?)
  *
  * @return The base VRAM address
  */
u32 sceGeEdramGetAddr(void);

/** Wait for syncronisation of the list (i.e. the list has ended)
  *
  * @param qid - The queue id of the list
  * @param wait - Set to 0 for wait and 1 to return immediately
  * @return 0?
  */
int sceGeListSync(int qid, int wait);

/**
  * Wait for drawing to complete.
  * 
  * @param wait - Set to 0 for wait or 1 to return immediately.
  * @return 0?
  */
int sceGeDrawSync(int wait);

#ifdef __cplusplus
}
#endif

#endif /* __GE_H__ */
