
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
	pspdisplay.h		\
	pspge.h			\
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
	pspsircs.h		\
	pspsysmem.h		\
	pspthreadman.h		\
	pspumd.h		\
	psputils.h

lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	display.S		\
	ge.S			\
	iofilemgr.S		\
	kernel.S		\
	loadexec.S		\
	modulemgr.S		\
	power.S			\
	sircs.S			\
	stdio.S			\
	suspend.S		\
	sysmem.S		\
	threadman.S		\
	umd.S			\
	utility.S		\
	utils.S
