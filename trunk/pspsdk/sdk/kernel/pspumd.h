#ifndef __UMD_H__
#define __UMD_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UMD UMD Kernel Library */
/*@{*/

/** Enumeration for UMD stats */
enum UmdDriveStat
{
	/** Wait for disc to be inserted */
	UMD_WAITFORDISC = 2,
	/** Wait for the UMD to be initialised so it can be accessed from the mapped drive */
	UMD_WAITFORINIT		= 0x20
};

/** UMD Callback function */
typedef int (*UmdCallback)(int unknown, int event);

/** 
  * Check whether there is a disc in the UMD drive
  *
  * @param a - Unknown function, set to 0
  * @return Returns 0 if no disc present, anything else indicates a disc is inserted.
  */
int sceUmdCheckMedium(int a);

/** 
  * Activates the UMD drive
  * 
  * @param unit - The unit to initialise (probably). Should be set to 1.
  * @param drive - A prefix string for the fs device to mount the UMD on (e.g. "disc0:")
  * @return < 0 on error
  *
  * @par Example:
  * @code
  * // Wait for disc and mount to filesystem
  * int i;
  * i = sceUmdCheckMedium(0);
  * if(i == 0)
  * {
  *    sceUmdWaitDriveStat(UMD_WAITFORDISC);
  * }
  * sceUmdActivate(1, "disc0:"); // Mount UMD to disc0: file system
  * sceUmdWaitDriveStat(UMD_WAITFORINIT);
  * // Now you can access the UMD using standard sceIo functions
  * @endcode
  *
  */
int sceUmdActivate(int unit, const char *drive);

/** 
  * Wait for a drive to reach a certain state
  *
  * @param stat - The drive stat to wait for.
  * @return < 0 on error
  *
  */
int sceUmdWaitDriveStat(int stat);

/** 
  * Register a callback for the UMD drive.
  * @note Callback is of type UmdCallback
  *
  * @param cbid - A callback ID created from sceKernelCreateCallback
  * @return < 0 on error
  * @par Example:
  * @code
  * cbid = sceKernelCreateCallback("UMD Callback", umd_callback);
  * sceUmdRegisterUMDCallback(cbid);
  * @endcode
  */
int sceUmdRegisterUMDCallBack(int cbid);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
