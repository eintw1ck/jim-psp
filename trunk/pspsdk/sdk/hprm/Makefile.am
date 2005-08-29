
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

HPRM_OBJS = stub_sceHprm.o 00000000_sceHprmRegisterCallback.o 00000001_sceHprmUnregisterCallback.o 00000002_sceHprmIsRemoteExist.o \
			00000003_sceHprmIsHeadphoneExist.o 00000004_sceHprmIsMicrophoneExist.o 00000005_sceHprmPeekCurrentKey.o \
			00000006_sceHprmPeekLatch.o 00000007_sceHprmReadLatch.o 

libpsphprmincludedir = @PSPSDK_INCLUDEDIR@
libpsphprminclude_HEADERS = psphprm.h

lib_LIBRARIES = libpsphprm.a
libpsphprm_a_SOURCES = sceHprm.S
libpsphprm_a_LIBADD  = $(HPRM_OBJS)

$(HPRM_OBJS): sceHprm.S
	$(COMPILE) -DF_$* $< -c -o $@

