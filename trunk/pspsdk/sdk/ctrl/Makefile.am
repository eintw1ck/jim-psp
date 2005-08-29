
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

CTRL_OBJS = stub_sceCtrl.o 00000000_sceCtrlSetSamplingCycle.o 00000001_sceCtrlGetSamplingCycle.o \
			00000002_sceCtrlSetSamplingMode.o 00000003_sceCtrlGetSamplingMode.o 00000004_sceCtrlPeekBufferPositive.o \
			00000005_sceCtrlPeekBufferNegative.o 00000006_sceCtrlReadBufferPositive.o 00000007_sceCtrlReadBufferNegative.o \
			00000008_sceCtrlPeekLatch.o 00000009_sceCtrlReadLatch.o 0000000A_sceCtrl_348D99D4.o 0000000B_sceCtrl_AF5960F3.o \
			0000000C_sceCtrl_A68FD260.o 0000000D_sceCtrl_6841BE1A.o 

libpspctrlincludedir = @PSPSDK_INCLUDEDIR@
libpspctrlinclude_HEADERS = pspctrl.h

lib_LIBRARIES = libpspctrl.a
libpspctrl_a_SOURCES = sceCtrl.S
libpspctrl_a_LIBADD = $(CTRL_OBJS)

$(CTRL_OBJS): sceCtrl.S
	$(COMPILE) -DF_$* $< -c -o $@

