#ifndef __THREADMAN_H__
#define __THREADMAN_H__

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
 * @par Example:
 * @code
 * @endcode
 *
 * @param semaid
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceKernelDeleteSema(int semaid);
/**
 * Send a signal to a semaphore
 *
 * @par Example:
 * @code
 * @endcode
 *
 * @param semaid
 * @param signal
 */
int sceKernelSignalSema(int semaid, int signal);
/**
 * Lock a semaphore
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param semaid
 * @param signal
 * @param unknown
 */
int sceKernelWaitSema(int semaid, int signal, int unknown);
/**
 * Sleep thread
 *
 * @par Example1:
 * @code
 * @endcode
 */
int sceKernelSleepThread(void);
/**
 * Create a thread
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param name
 * @param func
 * @param initPriority
 * @param stacksize
 * @param attributes
 * @param option
 */
int sceKernelCreateThread(const char* name, void *func, int initPriority, 
						  int stacksize, int attributes, int option);
/**
 * Start a created thread
 *
 * @par Example:
 * @code
 * @endcode
 *
 * @param thid
 * @param arg1
 * @param arg2
 */
int sceKernelStartThread(int thid, void *arg1, void *arg2);

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
 * Poll callbacks
 *
 * @note This function must be called in order for callbacks to work. It should also be
 * noted that it will then block indefinetly so it should be called in a seperate thread
 * @par Example:
 * @code
 * // Once all callbacks have been setup call this function
 * sceKernelPollCallbacks();
 * @endcode
 */
void sceKernelPollCallbacks(void);

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

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
