
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

UMD_OBJS = stub_sceUmdUser.o 00000000_sceUmdCheckMedium.o 00000001_sceUmdActivate.o 00000002_sceUmdDeactivate.o 00000003_sceUmdWaitDriveStat.o 00000004_sceUmdWaitDriveStatWithTimer.o 00000005_sceUmdWaitDriveStatCB.o 00000006_sceUmdGetDriveStat.o 00000007_sceUmdGetErrorStat.o 00000008_sceUmdGetDiscInfo.o 00000009_sceUmdRegisterUMDCallBack.o 0000000A_sceUmdUnRegisterUMDCallBack.o 

libpspumdlincludedir = @PSPSDK_INCLUDEDIR@
libpspumdlinclude_HEADERS = pspumd.h

lib_LIBRARIES = libpspumd.a
libpspumd_a_SOURCES = sceUmdUser.S
libpspumd_a_LIBADD = $(UMD_OBJS)

$(UMD_OBJS): sceUmdUser.S
	$(COMPILE) -DF_$* $< -c -o $@
