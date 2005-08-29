
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES) 

USBSTOR_OBJS = stub_sceUsbstor.o 00000000_sceUsbstorGetStatus.o 
USBSTORBOOT_OBJS = stub_sceUsbstorBoot.o 00000000_sceUsbstorBootSetCapacity.o 00000001_sceUsbstorBootSetLoadAddr.o 00000002_sceUsbstorBootGetDataSize.o 00000003_sceUsbstorBootSetStatus.o 00000004_sceUsbstorBootRegisterNotify.o 00000005_sceUsbstorBootUnregisterNotify.o 

libpspusbstorincludedir = @PSPSDK_INCLUDEDIR@

libpspusbstorinclude_HEADERS =	\
	pspusbstor.h

lib_LIBRARIES = libpspusbstor.a

libpspusbstor_a_SOURCES = sceUsbstor.S	sceUsbstorBoot.S
libpspusbstor_a_LIBADD = $(USBSTOR_OBJS) $(USBSTORBOOT_OBJS)

$(USBSTOR_OBJS): sceUsbstor.S
	$(COMPILE) -DF_$* $< -c -o $@

$(USBSTORBOOT_OBJS): sceUsbstorBoot.S
	$(COMPILE) -DF_$* $< -c -o $@
