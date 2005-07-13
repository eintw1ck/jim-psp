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
#include <pspkerneltypes.h>

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

/** @defgroup ThreadMan Thread Manager Library
  * Library imports for the kernel threading library.
  */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ThreadMan */

/*@{*/

/** 64-bit system clock type. */
typedef struct SceKernelSysClock {
	SceUInt32   low;
	SceUInt32   hi;
} SceKernelSysClock;


/** Attribute for threads. */
enum PspThreadAttributes
{
	/** Enable VFPU access for the thread. */
	PSP_THREAD_ATTR_VFPU = 0x00004000,
	/** Start the thread in user mode (done automatically 
	  if the thread creating it is in user mode). */
	PSP_THREAD_ATTR_USER = 0x80000000,
	/** Thread is part of the USB/WLAN API. */
	PSP_THREAD_ATTR_USBWLAN = 0xa0000000,
	/** Thread is part of the VSH API. */
	PSP_THREAD_ATTR_VSH = 0xc0000000,
};

/* Maintained for compatibility with older versions of PSPSDK. */
#define THREAD_ATTR_VFPU PSP_THREAD_ATTR_VFPU
#define THREAD_ATTR_USER PSP_THREAD_ATTR_USER

typedef int (*SceKernelThreadEntry)(SceSize args, void *argp);

/** Additional options used when creating threads. */
typedef struct SceKernelThreadOptParam {
	/** Size of the ::SceKernelThreadOptParam structure. */
	SceSize 	size;
	/** UID of the memory block (?) allocated for the thread's stack. */
	SceUID 		stackMpid;
} SceKernelThreadOptParam;

/** Structure to hold the status information for a thread
  * @see sceKernelReferThreadStatus
  */
typedef struct SceKernelThreadInfo {
	/** Size of the structure */
	SceSize     size;
	/** Nul terminated name of the thread */
	char    	name[32];
	/** Thread attributes */
	SceUInt     attr;
	/** Thread status */
	int     	status;
	/** Thread entry point */
	SceKernelThreadEntry    entry;
	/** Thread stack pointer */
	void *  	stack;
	/** Thread stack size */
	int     	stackSize;
	/** Pointer to the gp */
	void *  	gpReg;
	/** Initial priority */
	int     	initPriority;
	/** Current priority */
	int     	currentPriority;
	/** Wait type */
	int     	waitType;
	/** Wait id */
	SceUID  	waitId;
	/** Wakeup count */
	int     	wakeupCount;
	/** Exit status of the thread */
	int     	exitStatus;
	/** Number of clock cycles run */
	SceKernelSysClock   runClocks;
	/** Interrupt preemption count */
	SceUInt     intrPreemptCount;
	/** Thread preemption count */
	SceUInt     threadPreemptCount;
	/** Release count */
	SceUInt     releaseCount;
} SceKernelThreadInfo;

/** Statistics about a running thread.
 * @see sceKernelReferThreadRunStatus.
 */
typedef struct SceKernelThreadRunStatus {
	SceSize 	size;
	int 		status;
	int 		currentPriority;
	int 		waitType;
	int 		waitId;
	int 		wakeupCount;
	SceKernelSysClock runClocks;
	SceUInt 	intrPreemptCount;
	SceUInt 	threadPreemptCount;
	SceUInt 	releaseCount;
} SceKernelThreadRunStatus;

/**
 * Create a thread
 *
 * @par Example:
 * @code
 * int thid;
 * this = sceKernelCreateThread("my_thread", threadFunc, 0x18, 0x10000, 0, NULL);
 * @endcode
 *
 * @param name - An arbitrary thread name.
 * @param entry - The thread function to run when started.
 * @param initPriority - The initial priority of the thread. Less if higher priority.
 * @param stackSize - The size of the initial stack.
 * @param attr - The thread attributes, zero or more of ::PspThreadAttributes.
 * @param option - Additional options specified by ::SceKernelThreadOptParam.

 * @return UID of the created thread, or an error code.
 */
SceUID sceKernelCreateThread(const char *name, SceKernelThreadEntry entry, int initPriority,
                             int stackSize, SceUInt attr, SceKernelThreadOptParam *option);

/**
 * Delate a thread
 *
 * @param thid - UID of the thread to be deleted.
 *
 * @return < 0 on error.
 */
int sceKernelDeleteThread(SceUID thid);

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
int sceKernelStartThread(SceUID thid, SceSize args, void *argp);

/**
 * Exit a thread
 *
 * @param status - Exit status.
 */
int sceKernelExitThread(int status);

/** 
  * Exit a thread and delete itself.
  *
  * @param status - Exit status
  */
int sceKernelExitDeleteThread(int status);

/**
 * Terminate a thread.
 *
 * @param thid - UID of the thread to terminate.
 *
 * @returns Success if >= 0, an error if < 0.
 */
int sceKernelTerminateThread(SceUID thid);

/**
 * Terminate and delete a thread.
 *
 * @param thid - UID of the thread to terminate and delete.
 *
 * @returns Success if >= 0, an error if < 0.
 */
int sceKernelTerminateDeleteThread(SceUID thid);

//
// sceKernelSuspendDispatchThread
// sceKernelResumeDispatchThread
//

/**
 * Sleep thread
 *
 * @return < 0 on error.
 */
int sceKernelSleepThread(void);

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
 * Wake a thread previously put into the sleep state.
 *
 * @param thid - UID of the thread to wake.
 *
 * @returns Success if >= 0, an error if < 0.
 */
int sceKernelWakeupThread(SceUID thid);

/**
 * Cancel a thread that was to be woken with ::sceKernelWakeupThread.
 *
 * @param thid - UID of the thread to cancel.
 *
 * @returns Success if >= 0, an error if < 0.
 */
int sceKernelCancelWakeupThread(SceUID thid);

/**
 * Suspend a thread.
 *
 * @param thid - UID of the thread to suspend.
 *
 * @returns Success if >= 0, an error if < 0.
 */
int sceKernelSuspendThread(SceUID thid);

/**
 * Resume a thread previously put into a suspended state with ::sceKernelSuspendThread.
 *
 * @param thid - UID of the thread to resume.
 *
 * @returns Success if >= 0, an error if < 0.
 */
int sceKernelResumeThread(SceUID thid);

/** 
  * Wait until a thread has ended.
  *
  * @param thid - Id of the thread to wait for.
  * @param timeout - Timeout in microseconds (assumed).
  *
  * @return < 0 on error.
  */
int sceKernelWaitThreadEnd(SceUID thid, SceUInt *timeout);

/** 
  * Wait until a thread has ended and handle callbacks if necessary.
  *
  * @param thid - Id of the thread to wait for.
  * @param timeout - Timeout in microseconds (assumed).
  *
  * @return < 0 on error.
  */
int sceKernelWaitThreadEndCB(SceUID thid, SceUInt *timeout);

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
void sceKernelDelayThread(SceUInt delay);

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
void sceKernelDelayThreadCB(SceUInt delay);

/**
 * Modify the attributes of the current thread.
 *
 * @param unknown - Set to 0.
 * @param attr - The thread attributes to modify.  One of ::PspThreadAttributes.
 *
 * @returns < 0 on error.
 */
int sceKernelChangeCurrentThreadAttr(int unknown, SceUInt attr);

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
int sceKernelChangeThreadPriority(SceUID thid, int priority);

// sceKernelRotateThreadReadyQueue
//
// sceKernelReleaseWaitThread

/** 
  * Get the current thread Id
  *
  * @return The thread id of the calling thread.
  */
int sceKernelGetThreadId(void);

// sceKernelGetThreadCurrentPriority
//
// sceKernelGetThreadExitStatus
//
// sceKernelCheckThreadStack
// sceKernelGetThreadStackFreeSize

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
int sceKernelReferThreadStatus(SceUID thid, SceKernelThreadInfo *info);

/**
 * Retrive the runtime status of a thread.
 *
 * @param thid - UID of the thread to retrive status.
 * @param status - Pointer to a ::SceKernelThreadRunStatus struct to receive the runtime status.
 *
 * @returns 0 if successful, otherwise the error code.
 */
int sceKernelReferThreadRunStatus(SceUID thid, SceKernelThreadRunStatus *status);


/** Additional options used when creating semaphores. */
typedef struct SceKernelSemaOptParam {
	/** Size of the ::SceKernelSemaOptParam structure. */
	SceSize 	size;
} SceKernelSemaOptParam;

/** Current state of a semaphore.
 * @see sceKernelReferSemaStatus.
 */
typedef struct SceKernelSemaInfo {
	/** Size of the ::SceKernelSemaInfo structure. */
	SceSize 	size;
	/** NUL-terminated name of the semaphore. */
	char 		name[32];
	/** Attributes. */
	SceUInt 	attr;
	/** The initial count the semaphore was created with. */
	int 		initCount;
	/** The current count. */
	int 		currentCount;
	/** The maximum count. */
	int 		maxCount;
	/** The number of threads waiting on the semaphore. */
	int 		numWaitThreads;
} SceKernelSemaInfo;

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
SceUID sceKernelCreateSema(const char *name, SceUInt attr, int initVal, int maxVal, SceKernelSemaOptParam *option);

/**
 * Destroy a semaphore
 *
 * @param semaid - The semaid returned from a previous create call.
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceKernelDeleteSema(SceUID semaid);

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
int sceKernelSignalSema(SceUID semaid, int signal);

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
 * @param timeout - Timeout in microseconds (assumed).
 *
 * @return < 0 on error.
 */
int sceKernelWaitSema(SceUID semaid, int signal, SceUInt *timeout);

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
 * @param timeout - Timeout in microseconds (assumed).
 *
 * @return < 0 on error.
 */
int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt *timeout);

/**
 * Poll a sempahore.
 *
 * @param semaid - UID of the semaphore to poll.
 * @param signal - The value to test for.
 *
 * @return < 0 on error.
 */
int sceKernelPollSema(SceUID semaid, int signal);

/**
 * Retrieve information about a semaphore.
 *
 * @param semaid - UID of the semaphore to retrieve info for.
 * @param info - Pointer to a ::SceKernelSemaInfo struct to receive the info.
 *
 * @returns < 0 on error.
 */
int sceKernelReferSemaStatus(SceUID semaid, SceKernelSemaInfo *info);


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

/** 
  * Poll an event flag for a giveb bit pattern.
  *
  * @param evid - The event id returned by sceKernelCreateEventFlag.
  * @param bits - The bit pattern to poll for.
  * @param wait - 0 to return immediately, 1 to wait until the pattern is matched
  * @param outBits - The bit pattern that was matched.
  * @return < 0 On error
  */
int sceKernelPollEventFlag(int evid, u32 bits, u32 wait, u32 *outBits);

/** 
  * Delete an event flag
  *
  * @param evid - The event id returned by sceKernelCreateEventFlag.
  *
  * @return < 0 On error
  */
int sceKernelDeleteEventFlag(int evid);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
