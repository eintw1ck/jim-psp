
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

RTC_OBJS = sceRtc_0000.o sceRtc_0001.o sceRtc_0002.o sceRtc_0003.o sceRtc_0004.o sceRtc_0005.o sceRtc_0006.o sceRtc_0007.o sceRtc_0008.o sceRtc_0009.o sceRtc_0010.o sceRtc_0011.o sceRtc_0012.o sceRtc_0013.o sceRtc_0014.o sceRtc_0015.o sceRtc_0016.o sceRtc_0017.o sceRtc_0018.o sceRtc_0019.o sceRtc_0020.o sceRtc_0021.o sceRtc_0022.o sceRtc_0023.o sceRtc_0024.o sceRtc_0025.o sceRtc_0026.o sceRtc_0027.o sceRtc_0028.o sceRtc_0029.o sceRtc_0030.o sceRtc_0031.o sceRtc_0032.o sceRtc_0033.o sceRtc_0034.o sceRtc_0035.o 

libpsprtcincludedir = @PSPSDK_INCLUDEDIR@
libpsprtcinclude_HEADERS = psprtc.h

lib_LIBRARIES = libpsprtc.a
libpsprtc_a_SOURCES = sceRtc.S
libpsprtc_a_LIBADD = $(RTC_OBJS)

$(RTC_OBJS): sceRtc.S
	$(COMPILE) -DF_$* $< -c -o $@
