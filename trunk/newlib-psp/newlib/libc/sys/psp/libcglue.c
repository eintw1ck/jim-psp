/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * libcglue.c - Newlib-compatible system calls.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * 
 */
#include <errno.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/dirent.h>

#include <psptypes.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspsysmem.h>
#include <pspthreadman.h>
#include <psputils.h>
#include <psputility.h>

/* These functions aren't exposed in any public headers, and they probably don't need to be. */
int sceKernelStdin(void);
int sceKernelStdout(void);
int sceKernelStderr(void);

extern char __psp_cwd[MAXPATHLEN + 1];
extern void __psp_init_cwd(char *argv_0);
extern int __psp_path_absolute(const char *in, char *out, int len);

#define __PSP_FILENO_MAX 1024
extern char * __psp_filename_map[__PSP_FILENO_MAX];

#ifdef F_getcwd
char *getcwd(char *buf, size_t size)
{
	if(!buf) {
		errno = EINVAL;
		return NULL;
	}		

	if(strlen(__psp_cwd) >= size) {
		errno = ERANGE;
		return NULL;
	}

	strcpy(buf, __psp_cwd);
	return buf;
}
#endif

#ifdef F_chdir
int chdir(const char *path)
{
	char dest[MAXPATHLEN + 1];
	SceUID uid;

	if(__psp_path_absolute(path, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	/* sceIoChdir doesn't give an indication of whether it worked,
	   so test for existence by attempting to open the dir */
	uid = sceIoDopen(dest);
	if(uid < 0) {
		errno = ENOTDIR;
		return -1;
	}
	sceIoDclose(uid);

	sceIoChdir(dest);
	strcpy(__psp_cwd, dest);
	return 0;
}
#endif

#ifdef F_mkdir
int mkdir(const char *pathname, mode_t mode)
{
	char dest[MAXPATHLEN + 1];

	if(__psp_path_absolute(pathname, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return sceIoMkdir(dest, mode);
}
#endif

#ifdef F_rmdir
int rmdir(const char *pathname)
{
	char dest[MAXPATHLEN + 1];

	if(__psp_path_absolute(pathname, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return sceIoRmdir(dest);
}
#endif

#ifdef F_realpath
char *realpath(const char *path, char *resolved_path)
{
	if(!path || !resolved_path) {
		errno = EINVAL;
		return NULL;
	}
	if(__psp_path_absolute(path, resolved_path, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return NULL;
	}
	if(access(resolved_path, F_OK) < 0) {
		errno = ENOENT;
		return NULL;
	}
	return resolved_path;
}
#endif

/* Wrappers of the standard open(), close(), read(), write(), unlink() and lseek() routines. */
#ifdef F__open
int _open(const char *name, int flags, int mode)
{
       int fd;
	int sce_flags;
	char dest[MAXPATHLEN + 1];

	if(__psp_path_absolute(name, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	/* O_RDONLY starts at 0, where PSP_O_RDONLY starts at 1, so remap the read/write
	   flags by adding 1. */
	sce_flags = (flags & O_ACCMODE) + 1;

	/* Translate standard open flags into the flags understood by the PSP kernel. */
	if (flags & O_APPEND) {
		sce_flags |= PSP_O_APPEND;
	}
	if (flags & O_CREAT) {
		sce_flags |= PSP_O_CREAT;
	}
	if (flags & O_TRUNC) {
		sce_flags |= PSP_O_TRUNC;
	}
	if (flags & O_EXCL) {
		sce_flags |= PSP_O_EXCL;
	}
	if (flags & O_NONBLOCK) {
		sce_flags |= PSP_O_NBLOCK;
	}

       fd = sceIoOpen(dest, sce_flags, mode);
       if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
               __psp_filename_map[fd] = strdup(dest);
       }
       return fd;
}
#endif

#ifdef F__close
int _close(int fd)
{
       if (fd < 0) {
		return -EBADF;
	}

       if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
               if (__psp_filename_map[fd] != NULL) {
                       free(__psp_filename_map[fd]);
                       __psp_filename_map[fd] = NULL;
               }
       }

       return sceIoClose(fd);
}
#endif

#ifdef F__read
int _read(int fd, void *buf, size_t size)
{
       if (fd < 0) {
		return -EBADF;
	}

       return sceIoRead(fd, buf, size);
}
#endif

#ifdef F__write
int _write(int fd, const void *buf, size_t size)
{
       if (fd < 0) {
		return -EBADF;
	}

       return sceIoWrite(fd, buf, size);
}
#endif

#ifdef F__lseek
off_t _lseek(int fd, off_t offset, int whence)
{
       if (fd < 0) {
		return -EBADF;
	}

	/* We don't have to do anything with the whence argument because SEEK_* == PSP_SEEK_*. */
       return (off_t) sceIoLseek(fd, offset, whence);
}
#endif

#ifdef F__unlink
int _unlink(const char *path)
{
	char dest[MAXPATHLEN + 1];

	if(__psp_path_absolute(path, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	return sceIoRemove(dest);
}
#endif

#ifdef F__link
int _link(const char *name1, const char *name2)
{
	return -1; /* not supported */
}
#endif

#ifdef F_opendir
DIR *opendir(const char *filename)
{
	char dest[MAXPATHLEN + 1];
	DIR *dirp;
	SceUID uid;

	/* Normalize pathname so that opendir(".") works */
	if(__psp_path_absolute(filename, dest, MAXPATHLEN) < 0) {
		errno = ENOENT;
		return NULL;
	}

	dirp = (DIR *)malloc(sizeof(DIR));

	uid = sceIoDopen(dest);

	if (uid < 0)
	{
		free(dirp);
		return NULL;
	}

	dirp->uid = uid;

	return dirp;
}
#endif

#ifdef F_readdir
struct dirent *readdir(DIR *dirp)
{
	SceIoDirent *de;

	de = (SceIoDirent *)malloc(sizeof(SceIoDirent));

	if (sceIoDread(dirp->uid, de) <= 0)
	{
		free(de);
		return NULL;
	}

	return (struct dirent *)de;
}
#endif

#ifdef F_closedir
int closedir(DIR *dirp)
{
	if (dirp != NULL)
	{
		int uid;
		uid = dirp->uid;
		free (dirp);
		return sceIoDclose(uid); 
	}
	return -1; 
}
#endif

/* Time routines.  These wrap around the routines provided by the kernel. */
#ifdef F__gettimeofday
int _gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	return sceKernelLibcGettimeofday(tp, tzp);
}

#endif

/* If we're being built for PSPSDK's libc this function isn't defined. */
#ifdef F_glue_gettimeofday
int gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	return sceKernelLibcGettimeofday(tp, tzp);
}
#endif

#if defined(F_clock) || defined(F_glue_clock)
clock_t clock(void)
{
	return sceKernelLibcClock();
}
#endif

#if defined(F_time) || defined(F_glue_time)
time_t time(time_t *t)
{
	return sceKernelLibcTime(t);
}
#endif

#if defined(F_sleep)
unsigned int sleep(unsigned int secs) {
	while(secs--) {	
		sceKernelDelayThreadCB(1000000);
	}
	return 0;
}
#endif

/* PSP-compatible sbrk(). */
#if defined(F__sbrk) || defined(F_glue__sbrk)
/* TODO: Currently our default heap is set to the maximum available block size
   when sbrk() is first called.  Sony seems to always use a default of 64KB,
   with the expectation that user programs will override the default size with
   their own desired size.  The only reason I can think of them doing this is
   to allow each PRX to have their own seperate heap.  I think that their
   method is overkill for most user programs.

   What I'd like to do instead is to use the default of 64KB for PRXes as Sony
   does, but use the maximum available block size for executables.  This avoids
   the requirement of specifying the heap size manually in user programs.
   However, we currently don't have a clean way to distinguish PRXes and normal
   executables, so this code needs to be revisited once we do come up with a
   way. */
#define DEFAULT_PRX_HEAP_SIZE_KB 64

/* If defined it specifies the desired size of the heap, in KB. */
extern unsigned int sce_newlib_heap_kb_size __attribute__((weak));

/* UID of the memory block that represents the heap. */
static SceUID __psp_heap_blockid;

void * _sbrk(ptrdiff_t incr)
{
	static void * heap_bottom = NULL;
	static void * heap_top = NULL;
	static void * heap_ptr = NULL;

	/* Has our heap been initialized? */
	if (heap_bottom == NULL) {
		/* No, initialize the heap. */
		SceSize heap_size;

		if (&sce_newlib_heap_kb_size != NULL) {
			heap_size = sce_newlib_heap_kb_size * 1024;
		} else {
			/* TODO: Here we should distinguish between a PRX and a normal
			   executable.  Right now we assume it's an executable. */
			if (0 /* is a prx */) {
				heap_size = DEFAULT_PRX_HEAP_SIZE_KB * 1024;
			} else {
				heap_size = sceKernelMaxFreeMemSize();
			}
		}

		__psp_heap_blockid = sceKernelAllocPartitionMemory(2, "block", PSP_SMEM_Low, heap_size, NULL);
		if (__psp_heap_blockid > 0) {
			heap_bottom = sceKernelGetBlockHeadAddr(__psp_heap_blockid);
			heap_ptr = heap_bottom;
			heap_top = (unsigned char *) heap_bottom + heap_size;
		}
	}

	void * heap_addr = (void *) -1;
	void * next_heap_ptr = (void *) ((ptrdiff_t) heap_ptr + incr);
	if ((heap_bottom != NULL) && (next_heap_ptr >= heap_bottom) && (next_heap_ptr < heap_top)) {
		heap_addr = heap_ptr;
		heap_ptr = next_heap_ptr;
	}

	return heap_addr;
}

/* Free the heap. */
int __psp_free_heap(void)
{
	if (__psp_heap_blockid > 0) {
		return sceKernelFreePartitionMemory(__psp_heap_blockid);
	}

	return __psp_heap_blockid;
}
#endif

/* Other POSIX routines that must be defined. */
#ifdef F__fstat
int _fstat(int fd, struct stat *sbuf)
{
	int ret;
	SceOff oldpos;
	if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
		if (__psp_filename_map[fd] != NULL) {
			if (strcmp(__psp_filename_map[fd], "  __PSP_STDIO") == 0) {
				memset(sbuf, '\0', sizeof(struct stat));
				sbuf->st_mode = S_IFCHR;
				return 0;
			} else {
			        ret = stat(__psp_filename_map[fd], sbuf);

				/* Find true size of the open file */
				oldpos = sceIoLseek(fd, 0, SEEK_CUR);
				if (oldpos != (off_t) -1) {
					sbuf->st_size = (off_t) sceIoLseek(fd, 0, SEEK_END);
					sceIoLseek(fd, oldpos, SEEK_SET);
				}

				return ret;
			}
		}
	}
	errno = EBADF;
	return -1;
}
#endif

#ifdef F_isatty
int isatty(int fd)
{
       if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
               if (__psp_filename_map[fd] != NULL) {
                       if (strcmp(__psp_filename_map[fd], "  __PSP_STDIO") == 0) {
                               return 1;
                       } else {
                               return 0;
                       }
               }
       }
       return 0;
}
#endif

#ifdef F__stat
static time_t psp_to_epoch_time(ScePspDateTime psp_time)
{
	struct tm conv_time;
	conv_time.tm_year = psp_time.year;
	conv_time.tm_mon = psp_time.month;
	conv_time.tm_mday = psp_time.day;
	conv_time.tm_hour = psp_time.hour;
	conv_time.tm_min = psp_time.minute;
	conv_time.tm_sec = psp_time.second;
	conv_time.tm_isdst = -1;
	return mktime(&conv_time);
}

int _stat(const char *filename, struct stat *buf)
{
	SceIoStat psp_stat;
	char dest[MAXPATHLEN + 1];

	if(__psp_path_absolute(filename, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	memset(buf, '\0', sizeof(struct stat));
	if(sceIoGetstat(dest, &psp_stat) < 0)
		return -1;
	
	buf->st_ctime = psp_to_epoch_time(psp_stat.st_ctime);
	buf->st_atime = psp_to_epoch_time(psp_stat.st_atime);
	buf->st_mtime = psp_to_epoch_time(psp_stat.st_mtime);

	buf->st_mode = (psp_stat.st_mode & 0xfff) |
		       ((FIO_S_ISLNK(psp_stat.st_mode))?(S_IFLNK):(0)) |
		       ((FIO_S_ISREG(psp_stat.st_mode))?(S_IFREG):(0)) |
		       ((FIO_S_ISDIR(psp_stat.st_mode))?(S_IFDIR):(0));
	buf->st_size = psp_stat.st_size;
	return 0;
}
#endif

/* from stat.h in ps2sdk, this function may be correct */
#define FIO_CST_SIZE	0x0004

#ifdef F_truncate
int truncate(const char *filename, off_t length)
{
	SceIoStat psp_stat;
	char dest[MAXPATHLEN + 1];

	if(__psp_path_absolute(filename, dest, MAXPATHLEN) < 0) {
		errno = ENAMETOOLONG;
		return -1;
	}

	psp_stat.st_size = length;
	if(length < 0)
	{
		errno = EINVAL;
		return -1;
	}
	return sceIoChstat(dest, &psp_stat, FIO_CST_SIZE);
}
#endif

/* Unsupported newlib system calls. */
#ifdef F__fork
pid_t fork(void)
{
	return (pid_t) -1;
}
#endif

#ifdef F__getpid
pid_t _getpid(void)
{
	return (pid_t) -1;
}
#endif

#ifdef F__kill
int _kill(int unused, int unused2)
{
	return -1;
}
#endif

#ifdef F__wait
pid_t _wait(int *unused)
{
	return (pid_t) -1;
}
#endif

#ifdef F_access
int access(const char *fn, int flags)
{
	struct stat s;
	if (stat(fn, &s))
		return -1;
	if (s.st_mode & S_IFDIR)
		return 0;
	if (flags & W_OK)
	{
		if (s.st_mode & S_IWRITE)
			return 0;
		return -1;
	}
	return 0;
}
#endif

/* Exit. */
#if defined(F__exit) || defined(F_glue__exit)
extern int sce_newlib_nocreate_thread_in_start __attribute__((weak));

extern int __psp_free_heap(void);

void _exit(int status)
{
	if (&sce_newlib_nocreate_thread_in_start != NULL) {
		/* Free the heap created by _sbrk(). */
		__psp_free_heap();

		sceKernelSelfStopUnloadModule(1, 0, NULL);
	} else {
		if (status == 0) {
			/* Free the heap created by _sbrk(). */
			__psp_free_heap();
		}

		sceKernelExitThread(status);
	}

	while (1) ;
}

/* Note: This function is being linked into _exit.o.  

   Because __psp_libc_init is a weak import in crt0.c, the linker
   chooses to ignore an object file in libc.a that contains just this
   function, since it's not necessary for successful compilation.

   By putting it instead in _exit.o, which is already used by crt0.c,
   the linker sees __psp_libc_init and resolves the symbol properly.
*/
void __psp_libc_init(int argc, char *argv[])
{
       int fd;
       (void) argc;

	/* Initialize cwd from this program's path */
	__psp_init_cwd(argv[0]);

       /* Initialize filenamap */
       memset(__psp_filename_map, '\0', sizeof(char *) * __PSP_FILENO_MAX);
       fd = sceKernelStdin();
       if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
               __psp_filename_map[fd] = strdup("  __PSP_STDIO");
       }
       fd = sceKernelStdout();
       if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
               __psp_filename_map[fd] = strdup("  __PSP_STDIO");
       }
       fd = sceKernelStderr();
       if ((fd >= 0) && (fd < __PSP_FILENO_MAX)) {
               __psp_filename_map[fd] = strdup("  __PSP_STDIO");
       }
	
	/* Initialize timezone from PSP configuration */
	int tzOffset = 0;
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_TIMEZONE, &tzOffset);
	int tzOffsetAbs = tzOffset < 0 ? -tzOffset : tzOffset;
	int hours = tzOffsetAbs / 60;
	int minutes = tzOffsetAbs - hours * 60;
 	static char tz[10];
	sprintf(tz, "GMT%s%02i:%02i", tzOffset < 0 ? "+" : "-", hours, minutes);
	setenv("TZ", tz, 1);
	tzset(); 
}

#endif /* F__exit */

/* newlib's errno.h wants a function that returns a pointer to errno. */
#ifdef F_glue___errno
#undef errno

int errno;

/* TODO: Should this be made reentrant (wrapping interrupt disable/enable
   around it should do it)? */
int * __errno(void)
{
	return &errno;
}
#endif
