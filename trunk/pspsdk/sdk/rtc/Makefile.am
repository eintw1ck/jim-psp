
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/kernel

RTC_OBJS = stub_sceRtc.o 00000000_sceRtcGetTickResolution.o 00000001_sceRtcGetCurrentTick.o \
		   00000002_sceRtc_029CA3B3.o 00000003_sceRtcGetCurrentClock.o 00000004_sceRtcGetCurrentClockLocalTime.o \
		   00000005_sceRtcConvertUtcToLocalTime.o 00000006_sceRtcConvertLocalTimeToUTC.o \
		   00000007_sceRtcIsLeapYear.o 00000008_sceRtcGetDaysInMonth.o 00000009_sceRtcGetDayOfWeek.o \
		   0000000A_sceRtcCheckValid.o 0000000B_sceRtcSetTime_t.o 0000000C_sceRtcGetTime_t.o \
		   0000000D_sceRtcSetDosTime.o 0000000E_sceRtcGetDosTime.o 0000000F_sceRtcSetWin32FileTime.o \
		   00000010_sceRtcGetWin32FileTime.o 00000011_sceRtcSetTick.o 00000012_sceRtcGetTick.o \
		   00000013_sceRtcCompareTick.o 00000014_sceRtcTickAddTicks.o 00000015_sceRtcTickAddMicroseconds.o \
		   00000016_sceRtcTickAddSeconds.o 00000017_sceRtcTickAddMinutes.o 00000018_sceRtcTickAddHours.o \
		   00000019_sceRtcTickAddDays.o 0000001A_sceRtcTickAddWeeks.o 0000001B_sceRtcTickAddMonths.o \
		   0000001C_sceRtcTickAddYears.o 0000001D_sceRtcFormatRFC2822.o 0000001E_sceRtcFormatRFC2822LocalTime.o \
		   0000001F_sceRtcFormatRFC3339.o 00000020_sceRtcFormatRFC3339LocalTime.o 00000021_sceRtcParseDateTime.o \
		   00000022_sceRtcParseRFC3339.o 

libpsprtcincludedir = @PSPSDK_INCLUDEDIR@
libpsprtcinclude_HEADERS = psprtc.h

lib_LIBRARIES = libpsprtc.a
libpsprtc_a_SOURCES = sceRtc.S
libpsprtc_a_LIBADD = $(RTC_OBJS)

$(RTC_OBJS): sceRtc.S
	$(COMPILE) -DF_$* $< -c -o $@
