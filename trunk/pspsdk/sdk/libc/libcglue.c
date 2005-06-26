
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
#endif

#ifdef F__read
#endif

#ifdef F__write
#endif

#ifdef F__lseek
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
