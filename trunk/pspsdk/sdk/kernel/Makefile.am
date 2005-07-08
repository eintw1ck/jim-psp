
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base

EXTRA_DIST = common.s

libpspkernelincludedir = @PSPSDK_INCLUDEDIR@

libpspkernelinclude_HEADERS =	\
	pspiofilemgr.h		\
	pspiofilemgr_dirent.h	\
	pspiofilemgr_fcntl.h	\
	pspiofilemgr_stat.h	\
	pspkernel.h		\
	pspkerneltypes.h	\
	pspkerror.h		\
	psploadexec.h		\
	pspmoduleinfo.h		\
	pspmodulemgr.h		\
	pspsysmem.h		\
	pspthreadman.h		\
	psputils.h

lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	ExceptionManagerForKernel.S \
	KDebugForKernel.S	\
	LoadCoreForKernel.S	\
	iofilemgr_kernel.S	
