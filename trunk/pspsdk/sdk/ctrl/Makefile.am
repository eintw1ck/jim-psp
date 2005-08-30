
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

CTRL_OBJS = sceCtrl_0000.o sceCtrl_0001.o sceCtrl_0002.o sceCtrl_0003.o sceCtrl_0004.o sceCtrl_0005.o sceCtrl_0006.o sceCtrl_0007.o sceCtrl_0008.o sceCtrl_0009.o sceCtrl_0010.o sceCtrl_0011.o sceCtrl_0012.o sceCtrl_0013.o sceCtrl_0014.o

libpspctrlincludedir = @PSPSDK_INCLUDEDIR@
libpspctrlinclude_HEADERS = pspctrl.h

lib_LIBRARIES = libpspctrl.a
libpspctrl_a_SOURCES = sceCtrl.S
libpspctrl_a_LIBADD = $(CTRL_OBJS)

$(CTRL_OBJS): sceCtrl.S
	$(COMPILE) -DF_$* $< -c -o $@

