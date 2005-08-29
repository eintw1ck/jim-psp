
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

POWER_OBJS = stub_scePower.o 00000000_scePower_2B51FE2F.o 00000001_scePower_442BFBAC.o 00000002_scePowerTick.o \
			 00000003_scePowerGetIdleTimer.o 00000004_scePowerIdleTimerEnable.o 00000005_scePowerIdleTimerDisable.o \
			 00000006_scePowerBatteryUpdateInfo.o 00000007_scePower_E8E4E204.o 00000008_scePowerGetLowBatteryCapacity.o \
			 00000009_scePowerIsPowerOnline.o 0000000A_scePowerIsBatteryExist.o 0000000B_scePowerIsBatteryCharging.o \
			 0000000C_scePowerGetBatteryChargingStatus.o 0000000D_scePowerIsLowBattery.o \
			 0000000E_scePower_78A1A796.o 0000000F_scePowerGetBatteryRemainCapacity.o 00000010_scePower_FD18A0FF.o \
			 00000011_scePowerGetBatteryLifePercent.o 00000012_scePowerGetBatteryLifeTime.o \
			 00000013_scePowerGetBatteryTemp.o 00000014_scePowerGetBatteryElec.o 00000015_scePowerGetBatteryVolt.o \
			 00000016_scePower_23436A4A.o 00000017_scePower_0CD21B1F.o 00000018_scePower_165CE085.o \
			 00000019_scePowerLock.o 0000001A_scePowerUnlock.o 0000001B_scePowerCancelRequest.o \
			 0000001C_scePowerIsRequest.o 0000001D_scePowerRequestStandby.o 0000001E_scePowerRequestSuspend.o \
			 0000001F_scePower_2875994B.o 00000020_scePowerEncodeUBattery.o 00000021_scePowerGetResumeCount.o \
			 00000022_scePowerRegisterCallback.o 00000023_scePowerUnregisterCallback.o \
			 00000024_scePowerUnregitserCallback.o 00000025_scePowerSetCpuClockFrequency.o \
			 00000026_scePowerSetBusClockFrequency.o 00000027_scePowerGetCpuClockFrequency.o \
			 00000028_scePowerGetBusClockFrequency.o 00000029_scePowerGetCpuClockFrequencyInt.o \
			 0000002A_scePowerGetBusClockFrequencyInt.o 0000002B_scePowerGetCpuClockFrequencyFloat.o \
			 0000002C_scePowerGetBusClockFrequencyFloat.o 0000002D_scePowerSetClockFrequency.o 

libpsppowerincludedir = @PSPSDK_INCLUDEDIR@
libpsppowerinclude_HEADERS = psppower.h

lib_LIBRARIES = libpsppower.a
libpsppower_a_SOURCES = scePower.S
libpsppower_a_LIBADD = $(POWER_OBJS)

$(POWER_OBJS): scePower.S
	$(COMPILE) -DF_$* $< -c -o $@
