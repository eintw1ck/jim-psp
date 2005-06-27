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
 * $Id$
 */
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include <psptypes.h>
#include <pspiofilemgr.h>
#include <psputils.h>

/* These functions aren't exposed in any public headers, and they probably don't need to be. */
int sceKernelStdin(void);
int sceKernelStdout(void);
int sceKernelStderr(void);

/* Wrappers of the standard open(), close(), read(), write(), and lseek() routines. */
#ifdef F__open
int _open(const char *name, int flags, int mode)
{
	int sce_flags;

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

/* Time routines.  These wrap around the routines provided by the kernel. */
#ifdef F__gettimeofday
int _gettimeofday(struct timeval *tp, struct timezone *tzp)
{
	return sceKernelGettimeofday(tp, tzp);
}
#endif

#ifdef F_clock
clock_t clock(void)
{
	return sceKernelLibcClock();
}
#endif

#ifdef F_time
time_t time(time_t *t)
{
	return sceKernelLibcTime(t);
}
#endif

/* PSP-compatible sbrk(). */
#ifdef F__sbrk
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
