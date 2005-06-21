#ifndef __LOADEXEC_H__
#define __LOADEXEC_H__

/** @defgroup LoadExec LoadExec Library */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup LoadExec */

/*@{*/

/**
 * Register callback
 *
 * @note By installing the exit callback the home button becomes active. However if sceKernelExitGame
 * is not called in the callback it is likely that the psp will just crash.
 *
 * @par Example:
 * @code
 * int exit_callback(void) { sceKernelExitGame(); }
 *
 * cbid = sceKernelCreateCallback("ExitCallback", exit_callback, NULL);
 * sceKernelRegisterExitCallback(cbid);
 * @endcode
 *
 * @param cbid Callback id
 * @return < 0 on error
 */
int sceKernelRegisterExitCallback(int cbid);

/**
 * Exit game and go back to the PSP browser.
 *
 * @note You need to be in a thread in order for this function to work
 *
 */
void sceKernelExitGame(void);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif
