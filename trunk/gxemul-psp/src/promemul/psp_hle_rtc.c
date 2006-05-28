
#include "psp_hle.h"

SYSCALL(0x20f6,0xc41c2853,0x00000000,"sceRtcGetTickResolution",HLE_unknown,4);
SYSCALL(0x20f7,0x3f7ad767,0x00000000,"sceRtcGetCurrentTick",HLE_unknown,4);
SYSCALL(0x20f8,0x029ca3b3,0x00000000,"sceRtc_029CA3B3",HLE_unknown,4);
SYSCALL(0x20f9,0x4cfa57b0,0x00000000,"sceRtcGetCurrentClock",HLE_unknown,4);
SYSCALL(0x20fa,0xe7c27d1b,0x00000000,"sceRtcGetCurrentClockLocalTime",HLE_unknown,4);
SYSCALL(0x20fb,0x34885e0d,0x00000000,"sceRtcConvertUtcToLocalTime",HLE_unknown,4);
SYSCALL(0x20fc,0x779242a2,0x00000000,"sceRtcConvertLocalTimeToUTC",HLE_unknown,4);
SYSCALL(0x20fd,0x42307a17,0x00000000,"sceRtcIsLeapYear",HLE_unknown,4);
SYSCALL(0x20fe,0x05ef322c,0x00000000,"sceRtcGetDaysInMonth",HLE_unknown,4);
SYSCALL(0x20ff,0x57726bc1,0x00000000,"sceRtcGetDayOfWeek",HLE_unknown,4);
SYSCALL(0x2100,0x4b1b5e82,0x00000000,"sceRtcCheckValid",HLE_unknown,4);
SYSCALL(0x2101,0x3a807cc8,0x00000000,"sceRtcSetTime_t",HLE_unknown,4);
SYSCALL(0x2102,0x27c4594c,0x00000000,"sceRtcGetTime_t",HLE_unknown,4);
SYSCALL(0x2103,0xf006f264,0x00000000,"sceRtcSetDosTime",HLE_unknown,4);
SYSCALL(0x2104,0x36075567,0x00000000,"sceRtcGetDosTime",HLE_unknown,4);
SYSCALL(0x2105,0x7ace4c04,0x00000000,"sceRtcSetWin32FileTime",HLE_unknown,4);
SYSCALL(0x2106,0xcf561893,0x00000000,"sceRtcGetWin32FileTime",HLE_unknown,4);
SYSCALL(0x2107,0x7ed29e40,0x00000000,"sceRtcSetTick",HLE_unknown,4);
SYSCALL(0x2108,0x6ff40acc,0x00000000,"sceRtcGetTick",HLE_unknown,4);
SYSCALL(0x2109,0x9ed0ae87,0x00000000,"sceRtcCompareTick",HLE_unknown,4);
SYSCALL(0x210a,0x44f45e05,0x00000000,"sceRtcTickAddTicks",HLE_unknown,4);
SYSCALL(0x210b,0x26d25a5d,0x00000000,"sceRtcTickAddMicroseconds",HLE_unknown,4);
SYSCALL(0x210c,0xf2a4afe5,0x00000000,"sceRtcTickAddSeconds",HLE_unknown,4);
SYSCALL(0x210d,0xe6605bca,0x00000000,"sceRtcTickAddMinutes",HLE_unknown,4);
SYSCALL(0x210e,0x26d7a24a,0x00000000,"sceRtcTickAddHours",HLE_unknown,4);
SYSCALL(0x210f,0xe51b4b7a,0x00000000,"sceRtcTickAddDays",HLE_unknown,4);
SYSCALL(0x2110,0xcf3a2ca8,0x00000000,"sceRtcTickAddWeeks",HLE_unknown,4);
SYSCALL(0x2111,0xdbf74f1b,0x00000000,"sceRtcTickAddMonths",HLE_unknown,4);
SYSCALL(0x2112,0x42842c77,0x00000000,"sceRtcTickAddYears",HLE_unknown,4);
SYSCALL(0x2113,0xc663b3b9,0x00000000,"sceRtcFormatRFC2822",HLE_unknown,4);
SYSCALL(0x2114,0x7de6711b,0x00000000,"sceRtcFormatRFC2822LocalTime",HLE_unknown,4);
SYSCALL(0x2115,0x0498fb3c,0x00000000,"sceRtcFormatRFC3339",HLE_unknown,4);
SYSCALL(0x2116,0x27f98543,0x00000000,"sceRtcFormatRFC3339LocalTime",HLE_unknown,4);
SYSCALL(0x2117,0xdfbc5f16,0x00000000,"sceRtcParseDateTime",HLE_unknown,4);
SYSCALL(0x2118,0x28e1e988,0x00000000,"sceRtcParseRFC3339",HLE_unknown,4);
 
