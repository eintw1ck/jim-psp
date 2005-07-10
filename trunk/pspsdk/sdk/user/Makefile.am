
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspuserincludedir = @PSPSDK_INCLUDEDIR@
libpspuserinclude_HEADERS =	\
	pspiofilemgr.h		\
	pspiofilemgr_dirent.h	\
	pspiofilemgr_fcntl.h	\
	pspiofilemgr_stat.h	\
	pspkerneltypes.h	\
	pspkerror.h		\
	psploadexec.h		\
	pspmoduleinfo.h		\
	pspmodulemgr.h		\
	pspsysmem.h		\
	pspthreadman.h		\
	pspstdio.h		\
	pspuser.h		\
	psputils.h

lib_LIBRARIES = libpspuser.a

libpspuser_a_SOURCES =	\
	iofilemgr.S		\
	kernel.S		\
	loadexec.S		\
	modulemgr.S		\
	stdio.S			\
	suspend.S		\
	sysmem.S		\
	threadman.S		\
	utils.S			\
	StdioForUser.S	
