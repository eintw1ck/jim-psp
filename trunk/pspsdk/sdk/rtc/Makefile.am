
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpsprtcincludedir = @PSPSDK_INCLUDEDIR@
libpsprtcinclude_HEADERS = psprtc.h

lib_LIBRARIES = libpsprtc.a
libpsprtc_a_SOURCES = rtc.S

