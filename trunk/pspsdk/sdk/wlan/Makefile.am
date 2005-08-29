
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

WLAN_OBJS = stub_sceWlanDrv.o 00000000_sceWlanDevIsPowerOn.o 00000001_sceWlanGetSwitchState.o 00000002_sceWlanGetEtherAddr.o 

libpspwlanincludedir = @PSPSDK_INCLUDEDIR@
libpspwlaninclude_HEADERS = pspwlan.h

lib_LIBRARIES = libpspwlan.a
libpspwlan_a_SOURCES = sceWlanDrv.S
libpspwlan_a_LIBADD  = $(WLAN_OBJS)

$(WLAN_OBJS): sceWlanDrv.S
	$(COMPILE) -DF_$* $< -c -o $@
