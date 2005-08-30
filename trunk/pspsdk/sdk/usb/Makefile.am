
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 

USB_OBJS = sceUsb_0000.o sceUsb_0001.o sceUsb_0002.o sceUsb_0003.o sceUsb_0004.o sceUsb_0005.o sceUsb_0006.o sceUsb_0007.o sceUsb_0008.o sceUsb_0009.o 

libpspusbincludedir = @PSPSDK_INCLUDEDIR@

libpspusbinclude_HEADERS =	\
	pspusb.h

lib_LIBRARIES = libpspusb.a

libpspusb_a_SOURCES = sceUsb.S
libpspusb_a_LIBADD  = $(USB_OBJS)

$(USB_OBJS): sceUsb.S
	$(COMPILE) -DF_$* $< -c -o $@
