
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

UTILITY_OBJS = stub_sceUtility.o 00000000_sceUtilityGameSharingInitStart.o 00000001_sceUtilityGameSharingShutdownStart.o \
			   00000002_sceUtilityGameSharingUpdate.o 00000003_sceUtilityGameSharingGetStatus.o \
			   00000004_sceNetplayDialogInitStart.o 00000005_sceNetplayDialogShutdownStart.o \
			   00000006_sceNetplayDialogUpdate.o 00000007_sceNetplayDialogGetStatus.o \
			   00000008_sceUtilityNetconfInitStart.o 00000009_sceUtilityNetconfShutdownStart.o \
			   0000000A_sceUtilityNetconfUpdate.o 0000000B_sceUtilityNetconfGetStatus.o \
			   0000000C_sceUtilitySavedataInitStart.o 0000000D_sceUtilitySavedataShutdownStart.o \
			   0000000E_sceUtilitySavedataUpdate.o 0000000F_sceUtilitySavedataGetStatus.o \
			   00000010_sceUtility_2995D020.o 00000011_sceUtility_B62A4061.o 00000012_sceUtility_ED0FAD38.o \
			   00000013_sceUtility_88BC7406.o 00000014_sceUtilityMsgDialogInitStart.o \
			   00000015_sceUtilityMsgDialogShutdownStart.o 00000016_sceUtilityMsgDialogUpdate.o \
			   00000017_sceUtilityMsgDialogGetStatus.o 00000018_sceUtilityOskInitStart.o \
			   00000019_sceUtilityOskShutdownStart.o 0000001A_sceUtilityOskUpdate.o \
			   0000001B_sceUtilityOskGetStatus.o 0000001C_sceUtilitySetSystemParamInt.o \
			   0000001D_sceUtilitySetSystemParamString.o 0000001E_sceUtilityGetSystemParamInt.o \
			   0000001F_sceUtilityGetSystemParamString.o 00000020_sceUtilityCheckNetParam.o \
			   00000021_sceUtilityGetNetParam.o 

libpsputilityincludedir = @PSPSDK_INCLUDEDIR@
libpsputilityinclude_HEADERS = psputility.h \
                               psputility_sysparam.h \
                               psputility_netconf.h \
                               psputility_netparam.h \
                               psputility_msgdialog.h

lib_LIBRARIES = libpsputility.a
libpsputility_a_SOURCES = sceUtility.S
libpsputility_a_LIBADD = $(UTILITY_OBJS)

$(UTILITY_OBJS): sceUtility.S
	$(COMPILE) -DF_$* $< -c -o $@
