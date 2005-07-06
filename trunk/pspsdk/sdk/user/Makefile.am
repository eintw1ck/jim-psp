
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base

EXTRA_DIST = common.s

libpspuserincludedir = @PSPSDK_INCLUDEDIR@

libpspuserinclude_HEADERS =	

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
	utils.S			
