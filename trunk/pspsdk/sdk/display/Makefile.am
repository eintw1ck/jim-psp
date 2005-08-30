
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

DISPLAY_OBJS = sceDisplay_0000.o sceDisplay_0001.o sceDisplay_0002.o sceDisplay_0003.o sceDisplay_0004.o sceDisplay_0005.o sceDisplay_0006.o sceDisplay_0007.o sceDisplay_0008.o sceDisplay_0009.o sceDisplay_0010.o sceDisplay_0011.o sceDisplay_0012.o sceDisplay_0013.o sceDisplay_0014.o sceDisplay_0015.o sceDisplay_0016.o sceDisplay_0017.o 

libpspdisplayincludedir = @PSPSDK_INCLUDEDIR@
libpspdisplayinclude_HEADERS = pspdisplay.h

lib_LIBRARIES = libpspdisplay.a
libpspdisplay_a_SOURCES = sceDisplay.S
libpspdisplay_a_LIBADD = $(DISPLAY_OBJS)

$(DISPLAY_OBJS): sceDisplay.S
	$(COMPILE) -DF_$* $< -c -o $@
