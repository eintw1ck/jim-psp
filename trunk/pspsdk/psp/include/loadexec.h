#ifndef __LOADEXEC_H__
#define __LOADEXEC_H__

/**
 * Register callback
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param cbid Callback id
 */
void sceKernelRegisterExitCallback(int cbid);

/**
 * Exit game
 *
 * @note You need to be in a thread in order for this function to work
 *
 * @par Example1:
 * @code
 * @endcode
 */
void sceKernelExitGame(void);

#endif
