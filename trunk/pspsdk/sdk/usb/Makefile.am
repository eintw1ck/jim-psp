
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 

USB_OBJS = stub_sceUsb.o 00000000_sceUsbStart.o 00000001_sceUsbStop.o 00000002_sceUsbGetState.o 00000003_sceUsbGetDrvList.o 00000004_sceUsbGetDrvState.o 00000005_sceUsbActivate.o 00000006_sceUsbDeactivate.o 00000007_sceUsbWaitState.o 00000008_sceUsbWaitCancel.o 

libpspusbincludedir = @PSPSDK_INCLUDEDIR@

libpspusbinclude_HEADERS =	\
	pspusb.h

lib_LIBRARIES = libpspusb.a

libpspusb_a_SOURCES = sceUsb.S
libpspusb_a_LIBADD  = $(USB_OBJS)

$(USB_OBJS): sceUsb.S
	$(COMPILE) -DF_$* $< -c -o $@
