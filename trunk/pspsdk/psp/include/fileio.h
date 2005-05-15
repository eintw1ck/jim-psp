#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <tamtypes.h>
#include <sys/fcntl.h>

int sceIoOpen(const char* file, int mode, int perms);
void sceIoClose(int fd);
int sceIoRead(int fd, void *data, int size);
int sceIoWrite(int fd, void *data, int size);
int sceIoLseek(int fd, int offset, int whence);
int sceIoRemove(const char *file);
int sceIoMkDir(const char *dir, int mode);
int sceIoRmDir(const char *dir);
int sceIoRename(const char *oldname, const char *newname);

#endif
