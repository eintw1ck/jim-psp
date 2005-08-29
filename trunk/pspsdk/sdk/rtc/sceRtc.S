	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceRtc
	IMPORT_START	"sceRtc",0x40010000
#endif
#ifdef F_00000000_sceRtcGetTickResolution
	IMPORT_FUNC	"sceRtc",0xC41C2853,sceRtcGetTickResolution
#endif
#ifdef F_00000001_sceRtcGetCurrentTick
	IMPORT_FUNC	"sceRtc",0x3F7AD767,sceRtcGetCurrentTick
#endif
#ifdef F_00000002_sceRtc_029CA3B3
	IMPORT_FUNC	"sceRtc",0x029CA3B3,sceRtc_029CA3B3
#endif
#ifdef F_00000003_sceRtcGetCurrentClock
	IMPORT_FUNC	"sceRtc",0x4CFA57B0,sceRtcGetCurrentClock
#endif
#ifdef F_00000004_sceRtcGetCurrentClockLocalTime
	IMPORT_FUNC	"sceRtc",0xE7C27D1B,sceRtcGetCurrentClockLocalTime
#endif
#ifdef F_00000005_sceRtcConvertUtcToLocalTime
	IMPORT_FUNC	"sceRtc",0x34885E0D,sceRtcConvertUtcToLocalTime
#endif
#ifdef F_00000006_sceRtcConvertLocalTimeToUTC
	IMPORT_FUNC	"sceRtc",0x779242A2,sceRtcConvertLocalTimeToUTC
#endif
#ifdef F_00000007_sceRtcIsLeapYear
	IMPORT_FUNC	"sceRtc",0x42307A17,sceRtcIsLeapYear
#endif
#ifdef F_00000008_sceRtcGetDaysInMonth
	IMPORT_FUNC	"sceRtc",0x05EF322C,sceRtcGetDaysInMonth
#endif
#ifdef F_00000009_sceRtcGetDayOfWeek
	IMPORT_FUNC	"sceRtc",0x57726BC1,sceRtcGetDayOfWeek
#endif
#ifdef F_0000000A_sceRtcCheckValid
	IMPORT_FUNC	"sceRtc",0x4B1B5E82,sceRtcCheckValid
#endif
#ifdef F_0000000B_sceRtcSetTime_t
	IMPORT_FUNC	"sceRtc",0x3A807CC8,sceRtcSetTime_t
#endif
#ifdef F_0000000C_sceRtcGetTime_t
	IMPORT_FUNC	"sceRtc",0x27C4594C,sceRtcGetTime_t
#endif
#ifdef F_0000000D_sceRtcSetDosTime
	IMPORT_FUNC	"sceRtc",0xF006F264,sceRtcSetDosTime
#endif
#ifdef F_0000000E_sceRtcGetDosTime
	IMPORT_FUNC	"sceRtc",0x36075567,sceRtcGetDosTime
#endif
#ifdef F_0000000F_sceRtcSetWin32FileTime
	IMPORT_FUNC	"sceRtc",0x7ACE4C04,sceRtcSetWin32FileTime
#endif
#ifdef F_00000010_sceRtcGetWin32FileTime
	IMPORT_FUNC	"sceRtc",0xCF561893,sceRtcGetWin32FileTime
#endif
#ifdef F_00000011_sceRtcSetTick
	IMPORT_FUNC	"sceRtc",0x7ED29E40,sceRtcSetTick
#endif
#ifdef F_00000012_sceRtcGetTick
	IMPORT_FUNC	"sceRtc",0x6FF40ACC,sceRtcGetTick
#endif
#ifdef F_00000013_sceRtcCompareTick
	IMPORT_FUNC	"sceRtc",0x9ED0AE87,sceRtcCompareTick
#endif
#ifdef F_00000014_sceRtcTickAddTicks
	IMPORT_FUNC	"sceRtc",0x44F45E05,sceRtcTickAddTicks
#endif
#ifdef F_00000015_sceRtcTickAddMicroseconds
	IMPORT_FUNC	"sceRtc",0x26D25A5D,sceRtcTickAddMicroseconds
#endif
#ifdef F_00000016_sceRtcTickAddSeconds
	IMPORT_FUNC	"sceRtc",0xF2A4AFE5,sceRtcTickAddSeconds
#endif
#ifdef F_00000017_sceRtcTickAddMinutes
	IMPORT_FUNC	"sceRtc",0xE6605BCA,sceRtcTickAddMinutes
#endif
#ifdef F_00000018_sceRtcTickAddHours
	IMPORT_FUNC	"sceRtc",0x26D7A24A,sceRtcTickAddHours
#endif
#ifdef F_00000019_sceRtcTickAddDays
	IMPORT_FUNC	"sceRtc",0xE51B4B7A,sceRtcTickAddDays
#endif
#ifdef F_0000001A_sceRtcTickAddWeeks
	IMPORT_FUNC	"sceRtc",0xCF3A2CA8,sceRtcTickAddWeeks
#endif
#ifdef F_0000001B_sceRtcTickAddMonths
	IMPORT_FUNC	"sceRtc",0xDBF74F1B,sceRtcTickAddMonths
#endif
#ifdef F_0000001C_sceRtcTickAddYears
	IMPORT_FUNC	"sceRtc",0x42842C77,sceRtcTickAddYears
#endif
#ifdef F_0000001D_sceRtcFormatRFC2822
	IMPORT_FUNC	"sceRtc",0xC663B3B9,sceRtcFormatRFC2822
#endif
#ifdef F_0000001E_sceRtcFormatRFC2822LocalTime
	IMPORT_FUNC	"sceRtc",0x7DE6711B,sceRtcFormatRFC2822LocalTime
#endif
#ifdef F_0000001F_sceRtcFormatRFC3339
	IMPORT_FUNC	"sceRtc",0x0498FB3C,sceRtcFormatRFC3339
#endif
#ifdef F_00000020_sceRtcFormatRFC3339LocalTime
	IMPORT_FUNC	"sceRtc",0x27F98543,sceRtcFormatRFC3339LocalTime
#endif
#ifdef F_00000021_sceRtcParseDateTime
	IMPORT_FUNC	"sceRtc",0xDFBC5F16,sceRtcParseDateTime
#endif
#ifdef F_00000022_sceRtcParseRFC3339
	IMPORT_FUNC	"sceRtc",0x28E1E988,sceRtcParseRFC3339
#endif
