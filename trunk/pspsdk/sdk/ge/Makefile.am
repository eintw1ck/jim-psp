
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

GE_OBJS = stub_sceGe_user.o 00000000_sceGeEdramGetSize.o 00000001_sceGeEdramGetAddr.o 00000002_sceGeEdramSetAddrTranslation.o 00000003_sceGeGetCmd.o 00000004_sceGeGetMtx.o 00000005_sceGeSaveContext.o 00000006_sceGeRestoreContext.o 00000007_sceGeListEnQueue.o 00000008_sceGeListEnQueueHead.o 00000009_sceGeListDeQueue.o 0000000A_sceGeListUpdateStallAddr.o 0000000B_sceGeListSync.o 0000000C_sceGeDrawSync.o 0000000D_sceGeBreak.o 0000000E_sceGeContinue.o 0000000F_sceGeSetCallback.o 00000010_sceGeUnsetCallback.o 

libpspgeincludedir = @PSPSDK_INCLUDEDIR@
libpspgeinclude_HEADERS = pspge.h

lib_LIBRARIES = libpspge.a
libpspge_a_SOURCES = sceGe_user.S
libpspge_a_LIBADD = $(GE_OBJS)

$(GE_OBJS): sceGe_user.S
	$(COMPILE) -DF_$* $< -c -o $@
