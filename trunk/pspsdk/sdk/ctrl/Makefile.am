
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

libpspctrlincludedir = @PSPSDK_INCLUDEDIR@
libpspctrlinclude_HEADERS = pspctrl.h

lib_LIBRARIES = libpspctrl.a
libpspctrl_a_SOURCES = ctrl.S

