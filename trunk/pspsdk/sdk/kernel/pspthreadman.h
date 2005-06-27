/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspthreadman.h - Library imports for the kernel threading library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __THREADMAN_H__
#define __THREADMAN_H__

#include <psptypes.h>

/** @defgroup ThreadMan Thread Manager Library
  * Library imports for the kernel threading library.
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ThreadMan */

/*@{*/

/** Structure to hold the status information for a thread
  * @see sceKernelReferThreadStatus
  */
typedef struct _ThreadStatus
{
	/** Size of the structure */
	u32 size;
	/** Nul terminated name of the thread */
	char name[32];
	/** Unknown */
	u32  unk0; // ?
	/** Unknown */
	u32  unk1;
	/** Address of the the thread (likely start address) */
	u32  th_addr;
	/** Base of the stack */
	u32  stack_addr;
	/** Stack size */
	u32  stack_size;
	/** gp */
	u32 gp;
	/** Initial priority */
	u32 init_pri;
	/** Current priority */
	u32 curr_pri;
	/** More unknown */
	u32 unk2[9];
} ThreadStatus;

/** Attribute for threads */
enum ThreadAttributes
{
	/** Enable VFPU access for the thread */
	THREAD_ATTR_VFPU = 0x00004000,
	/** Start the thread in user mode (done automatically 
	  if the thread creating it is in user mode) */
	THREAD_ATTR_USER = 0x80000000,
};

/**
 * Creates a new semaphore
 *
 * @par Example:
 * @code
 * int semaid;
 * semaid = sceKernelCreateSema("MyMutex", 0, 1, 1, 0);
 * @endcode
 *
 * @param name - Specifies the name of the sema
 * @param attr - Sema attribute flags (normally set to 0)
 * @param initVal - Sema initial value 
 * @param maxVal - Sema maximum value
 * @param option - Sema options (normally set to 0)
 * @return A semaphore id
 */
int sceKernelCreateSema(const char* name, int attr, int initVal, int maxVal, int option);

/**
 * Destroy a semaphore
 *
 * @param semaid - The semaid returned from a previous create call.
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceKernelDeleteSema(int semaid);

/**
 * Send a signal to a semaphore
 *
 * @par Example:
 * @code
 * // Signal the sema
 * sceKernelSignalSema(semaid, 1);
 * @endcode
 *
 * @param semaid - The sema id returned from sceKernelCreateSema
 * @param signal - The amount to signal the sema (i.e. if 2 then increment the sema by 2)
 *
 * @return < 0 On error.
 */
int sceKernelSignalSema(int semaid, int signal);

/**
 * Lock a semaphore
 *
 * @par Example:
 * @code
 * sceKernelWaitSema(semaid, 1, 0);
 * @endcode
 *
 * @param semaid - The sema id returned from sceKernelCreateSema
 * @param signal - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param unknown - Unknown.
 *
 * @return < 0 on error.
 */
int sceKernelWaitSema(int semaid, int signal, int unknown);

/**
 * Lock a semaphore a handle callbacks if necessary.
 *
 * @par Example:
 * @code
 * sceKernelWaitSemaCB(semaid, 1, 0);
 * @endcode
 *
 * @param semaid - The sema id returned from sceKernelCreateSema
 * @param signal - The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param unknown - Unknown.
 *
 * @return < 0 on error.
 */
int sceKernelWaitSemaCB(int semaid, int signal, int unknown);


/**
 * Sleep thread
 *
 * @return < 0 on error.
 */
int sceKernelSleepThread(void);

/**
 * Create a thread
 *
 * @par Example:
 * @code
 * int thid;
 * this = sceKernelCreateThread("my_thread", threadFunc, 0x18, 0x10000, 0, 0);
 * @endcode
 *
 * @param name - An arbitrary thread name.
 * @param func - The thread function to run when started.
 * @param initPriority - The initial priority of the thread. Less if higher priority.
 * @param stacksize - The size of the initial stack.
 * @param attributes - The thread attributes, zero or more of ThreadAttributes.
 * @param option - An optional parameter (always 0?)

 * @return < 0 on error, >= 0 Thread ID for use in subsequent functions.
 */
int sceKernelCreateThread(const char* name, void *func, int initPriority, 
						  int stacksize, int attributes, int option);

/**
 * Delate a thread
 *
 * @param thid - UID of the thread to be deleted.
 *
 * @return < 0 on error.
 */
int sceKernelDeleteThread(int thid);

/**
 * Start a created thread
 *
 * @par Example:
 * @code
 * @endcode
 *
 * @param thid - Thread id from sceKernelCreateThread
 * @param arglen - Length of the args pointed to by the args parameter
 * @param args - Pointer to the arguments.
 */
int sceKernelStartThread(int thid, int arglen, void *args);

/**
 * Exit a thread
 *
 * @param status - Exit status.
 */
int sceKernelExitThread(int status);

/**
 * Create callback
 *
 * @par Example:
 * @code
 * int cbid;
 * cbid = sceKernelCreateCallback("Exit Callback", exit_cb, NULL);
 * @endcode
 *
 * @param name - A textual name for the callback
 * @param func - A pointer to a function that will be called as the callback
 * @param arg  - Argument for the callback ?
 *
 * @return >= 0 A callback id which can be used in subsequent functions, < 0 an error.
 */
int sceKernelCreateCallback(const char *name, void *func, void *arg);

/**
 * Sleep thread but service any callbacks as necessary
 *
 * @par Example:
 * @code
 * // Once all callbacks have been setup call this function
 * sceKernelSleepThreadCB();
 * @endcode
 */
void sceKernelSleepThreadCB(void);

/** 
  * Get the current thread Id
  *
  * @return The thread id of the calling thread.
  */
int sceKernelGetThreadId(void);

/**
  * Delay the current thread by a specified number of microseconds
  *
  * @param delay - Delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
void sceKernelDelayThread(int delay);

/**
  * Delay the current thread by a specified number of microseconds and handle any callbacks.
  *
  * @param delay - Delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
  */
void sceKernelDelayThreadCB(int delay);

/**
  * Change the threads current priority.
  * 
  * @param thid - The ID of the thread (from sceKernelCreateThread or sceKernelGetThreadId)
  * @param priority - The new priority (the lower the number the higher the priority)
  *
  * @par Example:
  * @code
  * int thid = sceKernelGetThreadId();
  * // Change priority of current thread to 16
  * sceKernelChangeThreadPriority(thid, 16);
  * @endcode
  *
  * @return 0 if successful, otherwise the error code.
  */
int sceKernelChangeThreadPriority(int thid, int priority);

/** 
  * Get the status information for the specified thread.
  * 
  * @param thid - Id of the thread to get status
  * @param status - Pointer to the status structure to receive the data.
  * Note: The structures size field should be set to sizeof(ThreadStatus) 
  * before calling this function.
  *
  * @par Example:
  * @code
  * ThreadStatus status;
  * status.size = sizeof(ThreadStatus);
  * if(sceKernelReferThreadStatus(thid, &status) == 0)
  * { Do something... }
  * @endcode 
  * @return 0 if successful, otherwise the error code.
  */
int sceKernelReferThreadStatus(int thid, ThreadStatus *status);

/** 
  * Wait until a thread has ended.
  *
  * @param thid - Id of the thread to wait for.
  * @param unk  - Unknown, set to 0.
  *
  * @return < 0 on error.
  */
int sceKernelWaitEndThread(int thid, void *unk);

/** 
  * Wait until a thread has ended and handle callbacks if necessary.
  *
  * @param thid - Id of the thread to wait for.
  * @param unk  - Unknown, set to 0.
  *
  * @return < 0 on error.
  */
int sceKernelWaitEndThreadCB(int thid, void *unk);

/** 
  * Create an event flag.
  *
  * @param name - The name of the event flag.
  * @param unk1 - Unknown, set to 0.
  * @param bits - Initial bit pattern.
  * @param unk3 - Unknown, set to 0.
  * @return < 0 on error. >= 0 event flag id.
  *
  * @par Example:
  * @code
  * int evid;
  * evid = sceKernelCreateEventFlag("wait_event", 0, 0, 0);
  * @endcode
  */
int sceKernelCreateEventFlag(const char *name, int unk1, int bits, int unk3);

/** 
  * Set an event flag bit pattern.
  *
  * @param evid - The event id returned by sceKernelCreateEventFlag.
  * @param bits - The bit pattern to set.
  *
  * @return < 0 On error
  */
int sceKernelSetEventFlag(int evid, u32 bits);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
