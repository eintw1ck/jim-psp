
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpsppowerincludedir = @PSPSDK_INCLUDEDIR@
libpsppowerinclude_HEADERS = psppower.h

lib_LIBRARIES = libpsppower.a
libpsppower_a_SOURCES = power.S

