#ifndef __GE_H__
#define __GE_H__

typedef void (*GeCallback)(int id, void *arg);

typedef struct _GeCallbackData
{
	GeCallback signal_func;
	void *signal_arg;
	GeCallback finish_func;
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

#endif /* __GE_H__ */
