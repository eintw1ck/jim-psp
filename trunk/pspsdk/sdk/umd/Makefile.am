
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpspumdlincludedir = @PSPSDK_INCLUDEDIR@
libpspumdlinclude_HEADERS = pspumd.h

lib_LIBRARIES = libpspumd.a
libpspumd_a_SOURCES = umd.S

