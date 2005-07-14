
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 


libpspusbstorincludedir = @PSPSDK_INCLUDEDIR@

libpspusbstorinclude_HEADERS =	\
	pspusbstor.h

lib_LIBRARIES = libpspusbstor.a

libpspusbstor_a_SOURCES =	\
	usbstor.S		\
	usbstorboot.S