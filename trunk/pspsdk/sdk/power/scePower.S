	.set noreorder

#include "pspimport.s"

#ifdef F_stub_scePower
	IMPORT_START	"scePower",0x40010000
#endif
#ifdef F_00000000_scePower_2B51FE2F
	IMPORT_FUNC	"scePower",0x2B51FE2F,scePower_2B51FE2F
#endif
#ifdef F_00000001_scePower_442BFBAC
	IMPORT_FUNC	"scePower",0x442BFBAC,scePower_442BFBAC
#endif
#ifdef F_00000002_scePowerTick
	IMPORT_FUNC	"scePower",0xEFD3C963,scePowerTick
#endif
#ifdef F_00000003_scePowerGetIdleTimer
	IMPORT_FUNC	"scePower",0xEDC13FE5,scePowerGetIdleTimer
#endif
#ifdef F_00000004_scePowerIdleTimerEnable
	IMPORT_FUNC	"scePower",0x7F30B3B1,scePowerIdleTimerEnable
#endif
#ifdef F_00000005_scePowerIdleTimerDisable
	IMPORT_FUNC	"scePower",0x972CE941,scePowerIdleTimerDisable
#endif
#ifdef F_00000006_scePowerBatteryUpdateInfo
	IMPORT_FUNC	"scePower",0x27F3292C,scePowerBatteryUpdateInfo
#endif
#ifdef F_00000007_scePower_E8E4E204
	IMPORT_FUNC	"scePower",0xE8E4E204,scePower_E8E4E204
#endif
#ifdef F_00000008_scePowerGetLowBatteryCapacity
	IMPORT_FUNC	"scePower",0xB999184C,scePowerGetLowBatteryCapacity
#endif
#ifdef F_00000009_scePowerIsPowerOnline
	IMPORT_FUNC	"scePower",0x87440F5E,scePowerIsPowerOnline
#endif
#ifdef F_0000000A_scePowerIsBatteryExist
	IMPORT_FUNC	"scePower",0x0AFD0D8B,scePowerIsBatteryExist
#endif
#ifdef F_0000000B_scePowerIsBatteryCharging
	IMPORT_FUNC	"scePower",0x1E490401,scePowerIsBatteryCharging
#endif
#ifdef F_0000000C_scePowerGetBatteryChargingStatus
	IMPORT_FUNC	"scePower",0xB4432BC8,scePowerGetBatteryChargingStatus
#endif
#ifdef F_0000000D_scePowerIsLowBattery
	IMPORT_FUNC	"scePower",0xD3075926,scePowerIsLowBattery
#endif
#ifdef F_0000000E_scePower_78A1A796
	IMPORT_FUNC	"scePower",0x78A1A796,scePower_78A1A796
#endif
#ifdef F_0000000F_scePowerGetBatteryRemainCapacity
	IMPORT_FUNC	"scePower",0x94F5A53F,scePowerGetBatteryRemainCapacity
#endif
#ifdef F_00000010_scePower_FD18A0FF
	IMPORT_FUNC	"scePower",0xFD18A0FF,scePower_FD18A0FF
#endif
#ifdef F_00000011_scePowerGetBatteryLifePercent
	IMPORT_FUNC	"scePower",0x2085D15D,scePowerGetBatteryLifePercent
#endif
#ifdef F_00000012_scePowerGetBatteryLifeTime
	IMPORT_FUNC	"scePower",0x8EFB3FA2,scePowerGetBatteryLifeTime
#endif
#ifdef F_00000013_scePowerGetBatteryTemp
	IMPORT_FUNC	"scePower",0x28E12023,scePowerGetBatteryTemp
#endif
#ifdef F_00000014_scePowerGetBatteryElec
	IMPORT_FUNC	"scePower",0x862AE1A6,scePowerGetBatteryElec
#endif
#ifdef F_00000015_scePowerGetBatteryVolt
	IMPORT_FUNC	"scePower",0x483CE86B,scePowerGetBatteryVolt
#endif
#ifdef F_00000016_scePower_23436A4A
	IMPORT_FUNC	"scePower",0x23436A4A,scePower_23436A4A
#endif
#ifdef F_00000017_scePower_0CD21B1F
	IMPORT_FUNC	"scePower",0x0CD21B1F,scePower_0CD21B1F
#endif
#ifdef F_00000018_scePower_165CE085
	IMPORT_FUNC	"scePower",0x165CE085,scePower_165CE085
#endif
#ifdef F_00000019_scePowerLock
	IMPORT_FUNC	"scePower",0xD6D016EF,scePowerLock
#endif
#ifdef F_0000001A_scePowerUnlock
	IMPORT_FUNC	"scePower",0xCA3D34C1,scePowerUnlock
#endif
#ifdef F_0000001B_scePowerCancelRequest
	IMPORT_FUNC	"scePower",0xDB62C9CF,scePowerCancelRequest
#endif
#ifdef F_0000001C_scePowerIsRequest
	IMPORT_FUNC	"scePower",0x7FA406DD,scePowerIsRequest
#endif
#ifdef F_0000001D_scePowerRequestStandby
	IMPORT_FUNC	"scePower",0x2B7C7CF4,scePowerRequestStandby
#endif
#ifdef F_0000001E_scePowerRequestSuspend
	IMPORT_FUNC	"scePower",0xAC32C9CC,scePowerRequestSuspend
#endif
#ifdef F_0000001F_scePower_2875994B
	IMPORT_FUNC	"scePower",0x2875994B,scePower_2875994B
#endif
#ifdef F_00000020_scePowerEncodeUBattery
	IMPORT_FUNC	"scePower",0x3951AF53,scePowerEncodeUBattery
#endif
#ifdef F_00000021_scePowerGetResumeCount
	IMPORT_FUNC	"scePower",0x0074EF9B,scePowerGetResumeCount
#endif
#ifdef F_00000022_scePowerRegisterCallback
	IMPORT_FUNC	"scePower",0x04B7766E,scePowerRegisterCallback
#endif
#ifdef F_00000023_scePowerUnregisterCallback
	IMPORT_FUNC	"scePower",0xDFA8BAF8,scePowerUnregisterCallback
#endif
#ifdef F_00000024_scePowerUnregitserCallback
	IMPORT_FUNC	"scePower",0xDB9D28DD,scePowerUnregitserCallback
#endif
#ifdef F_00000025_scePowerSetCpuClockFrequency
	IMPORT_FUNC	"scePower",0x843FBF43,scePowerSetCpuClockFrequency
#endif
#ifdef F_00000026_scePowerSetBusClockFrequency
	IMPORT_FUNC	"scePower",0xB8D7B3FB,scePowerSetBusClockFrequency
#endif
#ifdef F_00000027_scePowerGetCpuClockFrequency
	IMPORT_FUNC	"scePower",0xFEE03A2F,scePowerGetCpuClockFrequency
#endif
#ifdef F_00000028_scePowerGetBusClockFrequency
	IMPORT_FUNC	"scePower",0x478FE6F5,scePowerGetBusClockFrequency
#endif
#ifdef F_00000029_scePowerGetCpuClockFrequencyInt
	IMPORT_FUNC	"scePower",0xFDB5BFE9,scePowerGetCpuClockFrequencyInt
#endif
#ifdef F_0000002A_scePowerGetBusClockFrequencyInt
	IMPORT_FUNC	"scePower",0xBD681969,scePowerGetBusClockFrequencyInt
#endif
#ifdef F_0000002B_scePowerGetCpuClockFrequencyFloat
	IMPORT_FUNC	"scePower",0xB1A52C83,scePowerGetCpuClockFrequencyFloat
#endif
#ifdef F_0000002C_scePowerGetBusClockFrequencyFloat
	IMPORT_FUNC	"scePower",0x9BADB3EB,scePowerGetBusClockFrequencyFloat
#endif
#ifdef F_0000002D_scePowerSetClockFrequency
	IMPORT_FUNC	"scePower",0x737486F2,scePowerSetClockFrequency
#endif
