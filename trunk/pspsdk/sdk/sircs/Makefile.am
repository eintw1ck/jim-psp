
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpspsircsincludedir = @PSPSDK_INCLUDEDIR@
libpspsircsinclude_HEADERS = pspsircs.h

lib_LIBRARIES = libpspsircs.a
libpspsircs_a_SOURCES = sircs.S

