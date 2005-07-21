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
 *
 * $Id$
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

#include <psptypes.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspsysmem.h>
#include <pspthreadman.h>
#include <psputils.h>

/* These functions aren't exposed in any public headers, and they probably don't need to be. */
int sceKernelStdin(void);
int sceKernelStdout(void);
int sceKernelStderr(void);

extern char * __psp_argv_0;

/* Wrappers of the standard open(), close(), read(), write(), unlink() and lseek() routines. */
#ifdef F__open
static int cwd_initialized = 0;

/* Set the current working directory (CWD) to the path where the module was launched. */
void __psp_init_cwd(void)
{
	if (!cwd_initialized && (__psp_argv_0 != NULL)) {
		char base_path[MAXPATHLEN + 1];
		char *end;

		strncpy(base_path, __psp_argv_0, sizeof(base_path) - 1);
		base_path[sizeof(base_path) - 1] = '\0';
		end = strrchr(base_path, '/');
		if (end != NULL) {
			*(end + 1) = '\0';
			sceIoChdir(base_path);
		}

		cwd_initialized = 1;
	}
}

int _open(const char *name, int flags, int mode)
{
	int sce_flags;

	/* Make sure the CWD has been set. */
	if (!cwd_initialized) {
		__psp_init_cwd();
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

	return sceIoOpen(name, sce_flags, mode);
}
#endif

#ifdef F__close
int _close(int fd)
{
	int sce_fd = fd;

	if (fd == STDIN_FILENO) {
		sce_fd = sceKernelStdin();
	} else if (fd == STDOUT_FILENO) {
		sce_fd = sceKernelStdout();
	} else if (fd == STDERR_FILENO) {
		sce_fd == sceKernelStderr();
	}

	if (sce_fd < 0) {
		return -EBADF;
	}

	return sceIoClose(sce_fd);
}
#endif

#ifdef F__read
int _read(int fd, void *buf, size_t size)
{
	int sce_fd = fd;

	if (fd == STDIN_FILENO) {
		sce_fd = sceKernelStdin();
	} else if (fd == STDOUT_FILENO) {
		sce_fd = sceKernelStdout();
	} else if (fd == STDERR_FILENO) {
		sce_fd = sceKernelStderr();
	}

	if (sce_fd < 0) {
		return -EBADF;
	}

	return sceIoRead(sce_fd, buf, size);
}
#endif

#ifdef F__write
int _write(int fd, const void *buf, size_t size)
{
	int sce_fd = fd;

	if (fd == STDIN_FILENO) {
		sce_fd = sceKernelStdin();
	} else if (fd == STDOUT_FILENO) {
		sce_fd = sceKernelStdout();
	} else if (fd == STDERR_FILENO) {
		sce_fd = sceKernelStderr();
	}

	if (sce_fd < 0) {
		return -EBADF;
	}

	return sceIoWrite(sce_fd, buf, size);
}
#endif

#ifdef F__lseek
off_t _lseek(int fd, off_t offset, int whence)
{
	int sce_fd = fd;

	if (fd == STDIN_FILENO) {
		sce_fd = sceKernelStdin();
	} else if (fd == STDOUT_FILENO) {
		sce_fd = sceKernelStdout();
	} else if (fd == STDERR_FILENO) {
		sce_fd = sceKernelStderr();
	}

	if (sce_fd < 0) {
		return -EBADF;
	}

	/* We don't have to do anything with the whence argument because SEEK_* == PSP_SEEK_*. */
	return (off_t) sceIoLseek(sce_fd, offset, whence);
}
#endif

#ifdef F__unlink
int _unlink(const char *path)
{
	return sceIoRemove(path);
}
#endif

#ifdef F__link
int _link(const char *name1, const char *name2)
{
	return -1;
}
#endif

#ifdef F__opendir
DIR *_opendir(const char *filename)
{
	DIR *dirp;
	SceUID uid;

	dirp = (DIR *)malloc(sizeof(DIR));

	uid = sceIoDopen(filename);

	if (uid < 0)
	{
		free(dirp);
		return NULL;
	}

	dirp->uid = uid;

	return dirp;
}
#endif

#ifdef F__readdir
struct SceIoDirent *_readdir(DIR *dirp)
{
	SceIoDirent *de;

	de = (SceIoDirent *)malloc(sizeof(SceIoDirent));

	if (sceIoDread(dirp->uid, de) <= 0)
	{
		free(de);
		return NULL;
	}

	return de;
}
#endif

#ifdef F__closedir
int _closedir(DIR *dirp)
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
	sbuf->st_mode = S_IFCHR;
	return 0;
}
#endif

#ifdef F_isatty
int isatty(int fd)
{
	return 1;
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
#endif

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
