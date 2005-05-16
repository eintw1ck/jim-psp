#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <tamtypes.h>
#include <sys/fcntl.h>

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
 * @param file pointer to a string holding the name of the file to open
 * @param flags libc styled flags that are or'ed together
 * @param perms Unix style permission
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
 * @param fd int
 */
void sceIoClose(int fd);
/**
 * Read input
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param fd int
 * @param data void*
 * @param size int
 */
int sceIoRead(int fd, void *data, int size);
/**
 * Write output
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param fd int
 * @param data void*
 * @param size int
 */
int sceIoWrite(int fd, void *data, int size);
/**
 * Reposition read/write file descriptor offset
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param fd int
 * @param offset int
 * @param whence int
 */
int sceIoLseek(int fd, int offset, int whence);
/**
 * Remove directory entry
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param file
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
int sceIoMkDir(const char *dir, int mode);
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
int sceIoRmDir(const char *path);
/**
 * Change the name of a file
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param from*
 * @param to*
 * @return Returns the value 0 if its succesful otherwise -1
 */
int sceIoRename(const char *oldname, const char *newname);

#endif
