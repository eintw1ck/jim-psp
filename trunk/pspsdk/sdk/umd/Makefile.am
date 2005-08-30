
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

UMD_OBJS = sceUmdUser_0000.o sceUmdUser_0001.o sceUmdUser_0002.o sceUmdUser_0003.o sceUmdUser_0004.o sceUmdUser_0005.o sceUmdUser_0006.o sceUmdUser_0007.o sceUmdUser_0008.o sceUmdUser_0009.o sceUmdUser_0010.o sceUmdUser_0011.o 

libpspumdlincludedir = @PSPSDK_INCLUDEDIR@
libpspumdlinclude_HEADERS = pspumd.h

lib_LIBRARIES = libpspumd.a
libpspumd_a_SOURCES = sceUmdUser.S
libpspumd_a_LIBADD = $(UMD_OBJS)

$(UMD_OBJS): sceUmdUser.S
	$(COMPILE) -DF_$* $< -c -o $@
