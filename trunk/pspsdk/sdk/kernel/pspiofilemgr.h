/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspiofilemgr.h - Prototypes for the sceIo library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <pspkerneltypes.h>
#include <pspiofilemgr_fcntl.h>
#include <pspiofilemgr_stat.h>
#include <pspiofilemgr_dirent.h>

/** @defgroup FileIO File IO Library 
 *  This module contains the imports for the kernel's IO routines.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup FileIO File IO Library */
/*@{*/

/** Permission value for the sceIoAssign function */
enum IoAssignPerms
{
	/** Assign the device read/write */
	IOASSIGN_RDWR = 0,
	/** Assign the device read only */
	IOASSIGN_RDONLY = 1
};

/**
 * Open or create a file for reading or writing
 *
 * @par Example1: Open a file for reading
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", O_RDONLY, 0777)) {
 *	// error
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesnt exist
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", O_WRONLY|O_CREAT, 0777)) {
 *	// error
 * }
 * @endcode
 *
 * @param file - Pointer to a string holding the name of the file to open
 * @param flags - Libc styled flags that are or'ed together
 * @param mode - File access mode.
 * @return A non-negative integer is a valid fd, anything else an error
 */
SceUID sceIoOpen(const char *file, int flags, SceMode mode);

/**
 * Delete a descriptor
 *
 * @code
 * sceIoClose(fd);
 * @endcode
 *
 * @param fd - File descriptor to close
 * @return < 0 on error
 */
int sceIoClose(SceUID fd);

/**
 * Read input
 *
 * @par Example:
 * @code
 * bytes_read = sceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * 
 * @return The number of bytes read
 */
int sceIoRead(SceUID fd, void *data, SceSize size);

/**
 * Write output
 *
 * @par Example:
 * @code
 * bytes_written = sceIoWrite(fd, data, 100);
 * @endcode
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 *
 * @return The number of bytes written
 */
int sceIoWrite(SceUID fd, const void *data, SceSize size);

/**
 * Reposition read/write file descriptor offset
 *
 * @par Example:
 * @code
 * pos = sceIoLseek(fd, -10, SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - Set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return The position in the file after the seek. 
 */
SceOff sceIoLseek(SceUID fd, SceOff offset, int whence);

/**
 * Reposition read/write file descriptor offset (32bit mode)
 *
 * @par Example:
 * @code
 * pos = sceIoLseek32(fd, -10, SEEK_END);
 * @endcode
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - Set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return The position in the file after the seek. 
 */
int sceIoLseek32(SceUID fd, int offset, int whence);

/**
 * Remove directory entry
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param file - Path to the file to remove
 * @return < 0 on error
 */
int sceIoRemove(const char *file);

/**
 * Make a directory file
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param dir
 * @param mode - Access mode.
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoMkdir(const char *dir, SceMode mode);

/**
 * Remove a directory file
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param path - Removes a directory file pointed by the string path
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoRmdir(const char *path);

/**
  * Change the current directory.
  *
  * @param path - The path to change to.
  * @return < 0 on error.
  */
int sceIoChdir(const char *path);

/**
 * Change the name of a file
 *
 * @par Example:
 * @code
 * @endcode
 *
 * @param oldname*
 * @param newname*
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoRename(const char *oldname, const char *newname);

/**
  * Open a directory
  * 
  * @par Example:
  * @code
  * int dfd;
  * dfd = sceIoDopen("device:/");
  * if(dfd >= 0)
  * { Do something with the file descriptor }
  * @endcode
  * @param dirname - The directory to open for reading.
  * @return If >= 0 then a valid file descriptor, otherwise a Sony error code.
  */
SceUID sceIoDopen(const char *dirname);

/** 
  * Reads an entry from an opened file descriptor.
  *
  * @param fd - Already opened file descriptor (using sceIoDopen)
  * @param dir - Pointer to an io_dirent_t structure to hold the file information
  *
  * @return Read status
  * -   0 - No more directory entries left
  * - > 0 - More directory entired to go
  * - < 0 - Error
  */
int sceIoDread(SceUID fd, SceIoDirent *dir);

/**
  * Close an opened directory file descriptor
  *
  * @param fd - Already opened file descriptor (using sceIoDopen)
  * @return < 0 on error
  */
int sceIoDclose(SceUID fd);

/** 
  * Send a devctl command to a device.
  *
  * @par Example: Sending a simple command to a device (not a real devctl)
  * @code
  * sceIoDevctl("ms0:", 0x200000, indata, 4, NULL, NULL); 
  * @endcode
  *
  * @param dev - String for the device to send the devctl to (e.g. "ms0:")
  * @param cmd - The command to send to the device
  * @param indata - A data block to send to the device, if NULL sends no data
  * @param inlen - Length of indata, if 0 sends no data
  * @param outdata - A data block to receive the result of a command, if NULL receives no data
  * @param outlen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int sceIoDevctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/** 
  * Assigns one IO device to another (I guess)
  * @param dev1 - The device name to assign.
  * @param dev2 - The block device to assign from.
  * @param dev3 - The filesystem device to mape the block device to dev1
  * @param mode - Read/Write mode. One of IoAssignPerms.
  * @param unk1 - Unknown, set to NULL.
  * @param unk2 - Unknown, set to 0.
  * @return < 0 on error.
  *
  * @par Example: Reassign flash0 in read/write mode.
  * @code 
  *	sceIoUnassign("flash0");
  * sceIoAssign("flash0", "lflash0:0,0", "fatflash0:", IOASSIGN_RDWR, NULL, 0);
  * @endcode
  * 
  */
int sceIoAssign(const char *dev1, const char *dev2, const char *dev3, int mode, void* unk1, long unk2);

/** 
  * Unassign an IO device.
  * @param dev - The device to unassign.
  * @return < 0 on error
  *
  * @par Example: See ::sceIoAssign
  */
int sceIoUnassign(const char *dev);

/** 
  * Get the status of a file.
  * 
  * @param file - The path to the file.
  * @param stat - A pointer to an io_stat_t structure.
  * 
  * @return < 0 on error.
  */
int sceIoGetstat(const char *file, SceIoStat *stat);

/** 
  * Change the status of a file.
  *
  * @param file - The path to the file.
  * @param stat - A pointer to an io_stat_t structure.
  * @param bits - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChstat(const char *file, SceIoStat *stat, int bits);

/**
  * Perform an ioctl on a device.
  *
  * @param dev - String for the device to send the devctl to (e.g. "ms0:")
  * @param cmd - The command to send to the device
  * @param indata - A data block to send to the device, if NULL sends no data
  * @param inlen - Length of indata, if 0 sends no data
  * @param outdata - A data block to receive the result of a command, if NULL receives no data
  * @param outlen - Length of outdata, if 0 receives no data
  * @return 0 on success, < 0 on error
  */
int sceIoIoctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/** Structure passed to the init and exit functions of the io driver system */
struct _PspIoDrvArg
{
	/** Pointer to the original driver which was added */
	struct _PspIoDrv *drv;
	/** Pointer to a user defined argument (if written by the driver will preseve across calls */
	void *arg;
};

typedef struct _PspIoDrvArg PspIoDrvArg;

/** Structure passed to the file functions of the io driver system */
struct _PspIoDrvFileArg
{
	/** Unknown */
	u32 unk1;
	/** The file system number, e.g. if a file is opened as host5:/myfile.txt this field will be 5 */
	u32 fs_num;
	/** Pointer to the driver structure */
	struct _PspIoDrvArg *drv;
	/** Unknown, again */
	u32 unk2;
	/** Pointer to a user defined argument, this is preserved on a per file basis */
	void *arg;
};

typedef struct _PspIoDrvFileArg PspIoDrvFileArg;

/** Structure to maintain the file driver pointers */
struct _PspIoDrvFuncs
{
	int (*IoInit)(PspIoDrvArg* arg);
	int (*IoExit)(PspIoDrvArg* arg); 
	int (*IoOpen)(PspIoDrvFileArg *arg, char *file, int flags, SceMode mode); 
	int (*IoClose)(PspIoDrvFileArg *arg); 
	int (*IoRead)(PspIoDrvFileArg *arg, char *data, int len); 
	int (*IoWrite)(PspIoDrvFileArg *arg, const char *data, int len); 
	int (*IoLseek)(PspIoDrvFileArg *arg, u32 unk, long long ofs, int whence); 
	int (*IoIoctl)(PspIoDrvFileArg *arg, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
	int (*IoRemove)(PspIoDrvFileArg *arg, const char *name); 
	int (*IoMkdir)(PspIoDrvFileArg *arg, const char *name, SceMode mode); 
	int (*IoRmdir)(PspIoDrvFileArg *arg, const char *name);
	int (*IoDopen)(PspIoDrvFileArg *arg, const char *dirname); 
	int (*IoDclose)(PspIoDrvFileArg *arg);
	int (*IoDread)(PspIoDrvFileArg *arg, SceIoDirent *dir);
	int (*IoGetstat)(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat);
	int (*IoChstat)(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat, int bits);
	int (*IoRename)(PspIoDrvFileArg *arg, const char *oldname, const char *newname); 
	int (*IoChdir)(PspIoDrvFileArg *arg, const char *dir); 
	int (*IoMount)(PspIoDrvFileArg *arg); 
	int (*IoUmount)(PspIoDrvFileArg *arg); 
	int (*IoDevctl)(PspIoDrvFileArg *arg, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen); 
	int (*IoUnk21)(PspIoDrvFileArg *arg); 
};

typedef struct _PspIoDrvFuncs PspIoDrvFuncs;

struct _PspIoDrv
{
	/** The name of the device to add */
	const char *name;
	/** Device type, this 0x10 is for a filesystem driver */
	u32 dev_type;
	/** Unknown, set to 0x800 */
	u32 unk2;
	/** This seems to be the same as name but capitalised :/ */
	const char *name2;
	/** Pointer to a filled out functions table */
	PspIoDrvFuncs *funcs;
};

typedef struct _PspIoDrv PspIoDrv;

/** 
  * Adds a new IO driver to the system.
  * @note This is only exported in the kernel version of IoFileMgr
  * 
  * @param drv - Pointer to a filled out driver structure
  * @return < 0 on error.
  *
  * @par Example:
  * @code
  * PspIoDrvFuncs host_funcs = { ... };
  * PspIoDrv host_driver = { "host", 0x10, 0x800, "HOST", &host_funcs };
  * sceIoDelDrv("host");
  * sceIoAddDrv(&host_driver);
  * @endcode
  */
int sceIoAddDrv(PspIoDrv *drv);

/**
  * Deletes a IO driver from the system.
  * @note This is only exported in the kernel version of IoFileMgr
  *
  * @param drv_name - Name of the driver to delete.
  * @return < 0 on error
  */
int sceIoDelDrv(const char *drv_name);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
