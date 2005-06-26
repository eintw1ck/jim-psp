
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
	pspctrl.h		\
	pspdisplay.h		\
	pspge.h			\
	pspiofilemgr.h		\
	pspiofilemgr_dirent.h	\
	pspiofilemgr_fcntl.h	\
	pspkernel.h		\
	psploadexec.h		\
	pspmoduleinfo.h		\
	pspmodulemgr.h		\
	pspthreadman.h		\
	pspumd.h		\
	psputils.h

lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	ctrl.S			\
	display.S		\
	ge.S			\
	iofilemgr.S		\
	kernel.S		\
	loadexec.S		\
	modulemgr.S		\
	power.S			\
	stdio.S			\
	suspend.S		\
	sysmem.S		\
	threadman.S		\
	umd.S			\
	utility.S		\
	utils.S
