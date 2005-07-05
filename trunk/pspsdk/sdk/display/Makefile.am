
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpspdisplayincludedir = @PSPSDK_INCLUDEDIR@
libpspdisplayinclude_HEADERS = pspdisplay.h

lib_LIBRARIES = libpspdisplay.a
libpspdisplay_a_SOURCES = display.S

