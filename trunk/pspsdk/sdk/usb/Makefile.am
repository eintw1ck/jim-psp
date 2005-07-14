
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 


libpspusbincludedir = @PSPSDK_INCLUDEDIR@

libpspusbinclude_HEADERS =	\
	pspusb.h

lib_LIBRARIES = libpspusb.a

libpspusb_a_SOURCES =	\
	usb.S