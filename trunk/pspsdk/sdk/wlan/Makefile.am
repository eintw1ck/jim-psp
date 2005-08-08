
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpspwlanincludedir = @PSPSDK_INCLUDEDIR@
libpspwlaninclude_HEADERS = pspwlan.h

lib_LIBRARIES = libpspwlan.a
libpspwlan_a_SOURCES = wlan.S

