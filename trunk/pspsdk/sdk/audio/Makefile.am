
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

libpspaudioincludedir = @PSPSDK_INCLUDEDIR@
libpspaudioinclude_HEADERS = pspaudio.h

libpspaudiolibincludedir = @PSPSDK_INCLUDEDIR@
libpspaudiolibinclude_HEADERS = pspaudiolib.h

lib_LIBRARIES = libpspaudio.a libpspaudiolib.a

libpspaudio_a_SOURCES = audio.S

libpspaudiolib_a_SOURCES = pspaudiolib.c
