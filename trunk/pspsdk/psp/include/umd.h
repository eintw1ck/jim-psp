#ifndef __UMD_H__
#define __UMD_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup UMD UMD Kernel Library */
/*@{*/

/** Enumeration for UMD commands */
enum UmdCommands
{
	/** Command to wait for a UMD disc to be inserted */
	UMD_CMD_WAITFORDISC = 2,
	/** Command to init the UMD so it can be accessed from the mapped drive */
	UMD_CMD_INIT		= 0x20
};

/** UMD Callback function */
typedef int (*UmdCallback)(int unknown, int event);

/** 
  * Check whether there is a disc in the UMD drive
  *
  * @param a - Unknown function, set to 0
  * @return Returns 0 if no disc present, anything else indicates a disc is inserted.
  */
int UmdCheckForDisc(int a);

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
  * i = UmdCheckForDisc(0);
  * if(i == 0)
  * {
  *    UmdSendCommand(UMD_CMD_WAITFORDISC);
  * }
  * sceUmdActivate(1, "disc0:"); // Mount UMD to disc0: file system
  * UmdSendCommand(UMD_CMD_INIT);
  * // Now you can access the UMD using standard sceIo functions
  * @endcode
  *
  */
int sceUmdActivate(int unit, const char *drive);

/** 
  * Send a command to the UMD drive.
  *
  * @param cmd - Command to send to the drive. One of UmdCommands
  * @return < 0 on error
  *
  */
int UmdSendCommand(int cmd);

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
