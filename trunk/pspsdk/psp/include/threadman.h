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

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
