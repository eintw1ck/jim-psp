
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

DISPLAY_OBJS = stub_sceDisplay.o 00000000_sceDisplaySetMode.o 00000001_sceDisplayGetMode.o \
				  00000002_sceDisplayGetFramePerSec.o \
				  00000003_sceDisplaySetHoldMode.o 00000004_sceDisplaySetResumeMode.o 00000005_sceDisplaySetFrameBuf.o \
				  00000006_sceDisplayGetFrameBuf.o 00000007_sceDisplayIsForeground.o 00000008_sceDisplay_31C4BAA8.o \
				  00000009_sceDisplayGetVcount.o 0000000A_sceDisplayIsVblank.o 0000000B_sceDisplayWaitVblank.o \
				  0000000C_sceDisplayWaitVblankCB.o 0000000D_sceDisplayWaitVblankStart.o \
				  0000000E_sceDisplayWaitVblankStartCB.o \
				  0000000F_sceDisplayGetCurrentHcount.o 00000010_sceDisplayGetAccumulatedHcount.o 

libpspdisplayincludedir = @PSPSDK_INCLUDEDIR@
libpspdisplayinclude_HEADERS = pspdisplay.h

lib_LIBRARIES = libpspdisplay.a
libpspdisplay_a_SOURCES = sceDisplay.S
libpspdisplay_a_LIBADD = $(DISPLAY_OBJS)

$(DISPLAY_OBJS): sceDisplay.S
	$(COMPILE) -DF_$* $< -c -o $@
