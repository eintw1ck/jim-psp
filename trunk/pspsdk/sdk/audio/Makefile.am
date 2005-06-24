
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpspaudioincludedir = @PSPSDK_INCLUDEDIR@

libpspaudioinclude_HEADERS = pspaudio.h

lib_LIBRARIES = libpspaudio.a

libpspaudio_a_SOURCES = audio.S
