
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/src/base -I$(top_srcdir)/src/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 

USB_OBJS = sceUsb_0000.o sceUsb_0001.o sceUsb_0002.o sceUsb_0003.o sceUsb_0004.o sceUsb_0005.o sceUsb_0006.o sceUsb_0007.o sceUsb_0008.o sceUsb_0009.o 

USBDRIVER_OBJS= sceUsb_driver_0000.o sceUsb_driver_0001.o sceUsb_driver_0002.o sceUsb_driver_0003.o sceUsb_driver_0004.o sceUsb_driver_0005.o sceUsb_driver_0006.o sceUsb_driver_0007.o sceUsb_driver_0008.o sceUsb_driver_0009.o sceUsb_driver_0010.o

USBBUSDRIVER_OBJS=sceUsbBus_driver_0000.o sceUsbBus_driver_0001.o sceUsbBus_driver_0002.o sceUsbBus_driver_0003.o sceUsbBus_driver_0004.o sceUsbBus_driver_0005.o sceUsbBus_driver_0006.o sceUsbBus_driver_0007.o sceUsbBus_driver_0008.o sceUsbBus_driver_0009.o 

libpspusbincludedir = @PSPSDK_INCLUDEDIR@

libpspusbinclude_HEADERS =	\
	pspusb.h pspusbbus.h

lib_LIBRARIES = libpspusb.a libpspusb_driver.a libpspusbbus_driver.a

libpspusb_a_SOURCES = sceUsb.S
libpspusb_a_LIBADD  = $(USB_OBJS)

libpspusb_driver_a_SOURCES = sceUsb_driver.S
libpspusb_driver_a_LIBADD = $(USBDRIVER_OBJS)

libpspusbbus_driver_a_SOURCES = sceUsbBus_driver.S
libpspusbbus_driver_a_LIBADD = $(USBBUSDRIVER_OBJS)

$(USB_OBJS): sceUsb.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBDRIVER_OBJS): sceUsb_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBBUSDRIVER_OBJS): sceUsbBus_driver.S
	$(COMPILE) -DF_$* $< -c -o $@
