
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

WLAN_OBJS = sceWlanDrv_0000.o sceWlanDrv_0001.o sceWlanDrv_0002.o sceWlanDrv_0003.o 

libpspwlanincludedir = @PSPSDK_INCLUDEDIR@
libpspwlaninclude_HEADERS = pspwlan.h

lib_LIBRARIES = libpspwlan.a
libpspwlan_a_SOURCES = sceWlanDrv.S
libpspwlan_a_LIBADD  = $(WLAN_OBJS)

$(WLAN_OBJS): sceWlanDrv.S
	$(COMPILE) -DF_$* $< -c -o $@
