#ifndef __FILEIO_H__
#define __FILEIO_H__

/** @defgroup FileIO File IO Library 
 *  This module contains the imports for the kernel's IO routines.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup FileIO File IO Library */
/*@{*/

#include <sys/fcntl.h>
#include <sys/dirent.h>

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
 * @param perms - Unix style permission
 * @return A non-negative integer is a valid fd, anything else an error
 */
int sceIoOpen(const char* file, int flags, int perms);

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
int sceIoClose(int fd);

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
int sceIoRead(int fd, void *data, int size);

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
int sceIoWrite(int fd, const void *data, int size);

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
long long sceIoLseek(int fd, long long offset, int whence);

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
u32 sceIoLseek32(int fd, u32 offset, int whence);

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
 * @param mode
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoMkdir(const char *dir, int mode);

/**
 * Remove a directory file
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param path Removes a directory file pointed by the string path
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoRmdir(const char *path);

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
int sceIoDopen(const char *dirname);

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
int sceIoDread(int fd, io_dirent_t* dir);

/**
  * Close an opened directory file descriptor
  *
  * @param fd - Already opened file descriptor (using sceIoDopen)
  * @return < 0 on error
  */
int sceIoDclose(int fd);

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
int sceIoDevctl(const char *dev, u32 cmd, void *indata, int inlen, void *outdata, int outlen);

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
  * 
  */
int sceIoAssign(const char *dev1, const char *dev2, const char *dev3, IoAssignPerms mode, void* unk1, long unk2);

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
int sceIoGetStat(const char *file, io_stat_t *stat);

/** 
  * Change the status of a file.
  *
  * @param file - The path to the file.
  * @param stat - A pointer to an io_stat_t structure.
  * @param bits - Bitmask defining which bits to change.
  *
  * @return < 0 on error.
  */
int sceIoChStat(const char *file, io_stat_t *stat, int bits);

/*@}*/

#ifdef __cplusplus
}
#endif


#endif
