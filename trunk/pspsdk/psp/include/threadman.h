#ifndef __THREADMAN_H__
#define __THREADMAN_H__

/**
 * Creates a new semaphore
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param name
 * @param attr
 * @param initVal
 * @param maxVal
 * @param option
 * @return A semaphore id
 */
int sceKernelCreateSema(const char* name, int attr, int initVal, int maxVal, int option);
/**
 * Destroy a semaphore
 *
 * @par Example1:
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
 * @par Example1:
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
 * Start thread
 *
 * @par Example1:
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
 * @par Example1:
 * @code
 * @endcode
 *
 * @param name
 * @param func
 */
int sceKernelCreateCallback(const char *name, void *func);

/**
 * Poll callbacks
 *
 * @par Example1:
 * @code
 * @endcode
 */
void sceKernelPollCallbacks(void);

#endif
