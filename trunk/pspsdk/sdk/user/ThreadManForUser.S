	.set noreorder

#include "pspimport.s"

#ifdef F_stub_ThreadManForUser
	IMPORT_START	"ThreadManForUser",0x40010000
#endif
#ifdef F_00000000__sceKernelReturnFromCallback
	IMPORT_FUNC	"ThreadManForUser",0x6E9EA350,_sceKernelReturnFromCallback
#endif
#ifdef F_00000001_sceKernelRegisterThreadEventHandler
	IMPORT_FUNC	"ThreadManForUser",0x0C106E53,sceKernelRegisterThreadEventHandler
#endif
#ifdef F_00000002_sceKernelReleaseThreadEventHandler
	IMPORT_FUNC	"ThreadManForUser",0x72F3C145,sceKernelReleaseThreadEventHandler
#endif
#ifdef F_00000003_sceKernelReferThreadEventHandlerStatus
	IMPORT_FUNC	"ThreadManForUser",0x369EEB6B,sceKernelReferThreadEventHandlerStatus
#endif
#ifdef F_00000004_sceKernelCreateCallback
	IMPORT_FUNC	"ThreadManForUser",0xE81CAF8F,sceKernelCreateCallback
#endif
#ifdef F_00000005_sceKernelDeleteCallback
	IMPORT_FUNC	"ThreadManForUser",0xEDBA5844,sceKernelDeleteCallback
#endif
#ifdef F_00000006_sceKernelNotifyCallback
	IMPORT_FUNC	"ThreadManForUser",0xC11BA8C4,sceKernelNotifyCallback
#endif
#ifdef F_00000007_sceKernelCancelCallback
	IMPORT_FUNC	"ThreadManForUser",0xBA4051D6,sceKernelCancelCallback
#endif
#ifdef F_00000008_sceKernelGetCallbackCount
	IMPORT_FUNC	"ThreadManForUser",0x2A3D44FF,sceKernelGetCallbackCount
#endif
#ifdef F_00000009_sceKernelCheckCallback
	IMPORT_FUNC	"ThreadManForUser",0x349D6D6C,sceKernelCheckCallback
#endif
#ifdef F_0000000A_sceKernelReferCallbackStatus
	IMPORT_FUNC	"ThreadManForUser",0x730ED8BC,sceKernelReferCallbackStatus
#endif
#ifdef F_0000000B_sceKernelSleepThread
	IMPORT_FUNC	"ThreadManForUser",0x9ACE131E,sceKernelSleepThread
#endif
#ifdef F_0000000C_sceKernelSleepThreadCB
	IMPORT_FUNC	"ThreadManForUser",0x82826F70,sceKernelSleepThreadCB
#endif
#ifdef F_0000000D_sceKernelWakeupThread
	IMPORT_FUNC	"ThreadManForUser",0xD59EAD2F,sceKernelWakeupThread
#endif
#ifdef F_0000000E_sceKernelCancelWakeupThread
	IMPORT_FUNC	"ThreadManForUser",0xFCCFAD26,sceKernelCancelWakeupThread
#endif
#ifdef F_0000000F_sceKernelSuspendThread
	IMPORT_FUNC	"ThreadManForUser",0x9944F31F,sceKernelSuspendThread
#endif
#ifdef F_00000010_sceKernelResumeThread
	IMPORT_FUNC	"ThreadManForUser",0x75156E8F,sceKernelResumeThread
#endif
#ifdef F_00000011_sceKernelWaitThreadEnd
	IMPORT_FUNC	"ThreadManForUser",0x278C0DF5,sceKernelWaitThreadEnd
#endif
#ifdef F_00000012_sceKernelWaitThreadEndCB
	IMPORT_FUNC	"ThreadManForUser",0x840E8133,sceKernelWaitThreadEndCB
#endif
#ifdef F_00000013_sceKernelDelayThread
	IMPORT_FUNC	"ThreadManForUser",0xCEADEB47,sceKernelDelayThread
#endif
#ifdef F_00000014_sceKernelDelayThreadCB
	IMPORT_FUNC	"ThreadManForUser",0x68DA9E36,sceKernelDelayThreadCB
#endif
#ifdef F_00000015_sceKernelDelaySysClockThread
	IMPORT_FUNC	"ThreadManForUser",0xBD123D9E,sceKernelDelaySysClockThread
#endif
#ifdef F_00000016_sceKernelDelaySysClockThreadCB
	IMPORT_FUNC	"ThreadManForUser",0x1181E963,sceKernelDelaySysClockThreadCB
#endif
#ifdef F_00000017_sceKernelCreateSema
	IMPORT_FUNC	"ThreadManForUser",0xD6DA4BA1,sceKernelCreateSema
#endif
#ifdef F_00000018_sceKernelDeleteSema
	IMPORT_FUNC	"ThreadManForUser",0x28B6489C,sceKernelDeleteSema
#endif
#ifdef F_00000019_sceKernelSignalSema
	IMPORT_FUNC	"ThreadManForUser",0x3F53E640,sceKernelSignalSema
#endif
#ifdef F_0000001A_sceKernelWaitSema
	IMPORT_FUNC	"ThreadManForUser",0x4E3A1105,sceKernelWaitSema
#endif
#ifdef F_0000001B_sceKernelWaitSemaCB
	IMPORT_FUNC	"ThreadManForUser",0x6D212BAC,sceKernelWaitSemaCB
#endif
#ifdef F_0000001C_sceKernelPollSema
	IMPORT_FUNC	"ThreadManForUser",0x58B1F937,sceKernelPollSema
#endif
#ifdef F_0000001D_sceKernelCancelSema
	IMPORT_FUNC	"ThreadManForUser",0x8FFDF9A2,sceKernelCancelSema
#endif
#ifdef F_0000001E_sceKernelReferSemaStatus
	IMPORT_FUNC	"ThreadManForUser",0xBC6FEBC5,sceKernelReferSemaStatus
#endif
#ifdef F_0000001F_sceKernelCreateEventFlag
	IMPORT_FUNC	"ThreadManForUser",0x55C20A00,sceKernelCreateEventFlag
#endif
#ifdef F_00000020_sceKernelDeleteEventFlag
	IMPORT_FUNC	"ThreadManForUser",0xEF9E4C70,sceKernelDeleteEventFlag
#endif
#ifdef F_00000021_sceKernelSetEventFlag
	IMPORT_FUNC	"ThreadManForUser",0x1FB15A32,sceKernelSetEventFlag
#endif
#ifdef F_00000022_sceKernelClearEventFlag
	IMPORT_FUNC	"ThreadManForUser",0x812346E4,sceKernelClearEventFlag
#endif
#ifdef F_00000023_sceKernelWaitEventFlag
	IMPORT_FUNC	"ThreadManForUser",0x402FCF22,sceKernelWaitEventFlag
#endif
#ifdef F_00000024_sceKernelWaitEventFlagCB
	IMPORT_FUNC	"ThreadManForUser",0x328C546A,sceKernelWaitEventFlagCB
#endif
#ifdef F_00000025_sceKernelPollEventFlag
	IMPORT_FUNC	"ThreadManForUser",0x30FD48F0,sceKernelPollEventFlag
#endif
#ifdef F_00000026_sceKernelCancelEventFlag
	IMPORT_FUNC	"ThreadManForUser",0xCD203292,sceKernelCancelEventFlag
#endif
#ifdef F_00000027_sceKernelReferEventFlagStatus
	IMPORT_FUNC	"ThreadManForUser",0xA66B0120,sceKernelReferEventFlagStatus
#endif
#ifdef F_00000028_sceKernelCreateMbx
	IMPORT_FUNC	"ThreadManForUser",0x8125221D,sceKernelCreateMbx
#endif
#ifdef F_00000029_sceKernelDeleteMbx
	IMPORT_FUNC	"ThreadManForUser",0x86255ADA,sceKernelDeleteMbx
#endif
#ifdef F_0000002A_sceKernelSendMbx
	IMPORT_FUNC	"ThreadManForUser",0xE9B3061E,sceKernelSendMbx
#endif
#ifdef F_0000002B_sceKernelReceiveMbx
	IMPORT_FUNC	"ThreadManForUser",0x18260574,sceKernelReceiveMbx
#endif
#ifdef F_0000002C_sceKernelReceiveMbxCB
	IMPORT_FUNC	"ThreadManForUser",0xF3986382,sceKernelReceiveMbxCB
#endif
#ifdef F_0000002D_sceKernelPollMbx
	IMPORT_FUNC	"ThreadManForUser",0x0D81716A,sceKernelPollMbx
#endif
#ifdef F_0000002E_sceKernelCancelReceiveMbx
	IMPORT_FUNC	"ThreadManForUser",0x87D4DD36,sceKernelCancelReceiveMbx
#endif
#ifdef F_0000002F_sceKernelReferMbxStatus
	IMPORT_FUNC	"ThreadManForUser",0xA8E8C846,sceKernelReferMbxStatus
#endif
#ifdef F_00000030_sceKernelCreateMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0x7C0DC2A0,sceKernelCreateMsgPipe
#endif
#ifdef F_00000031_sceKernelDeleteMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0xF0B7DA1C,sceKernelDeleteMsgPipe
#endif
#ifdef F_00000032_sceKernelSendMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0x876DBFAD,sceKernelSendMsgPipe
#endif
#ifdef F_00000033_sceKernelSendMsgPipeCB
	IMPORT_FUNC	"ThreadManForUser",0x7C41F2C2,sceKernelSendMsgPipeCB
#endif
#ifdef F_00000034_sceKernelTrySendMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0x884C9F90,sceKernelTrySendMsgPipe
#endif
#ifdef F_00000035_sceKernelReceiveMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0x74829B76,sceKernelReceiveMsgPipe
#endif
#ifdef F_00000036_sceKernelReceiveMsgPipeCB
	IMPORT_FUNC	"ThreadManForUser",0xFBFA697D,sceKernelReceiveMsgPipeCB
#endif
#ifdef F_00000037_sceKernelTryReceiveMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0xDF52098F,sceKernelTryReceiveMsgPipe
#endif
#ifdef F_00000038_sceKernelCancelMsgPipe
	IMPORT_FUNC	"ThreadManForUser",0x349B864D,sceKernelCancelMsgPipe
#endif
#ifdef F_00000039_sceKernelReferMsgPipeStatus
	IMPORT_FUNC	"ThreadManForUser",0x33BE4024,sceKernelReferMsgPipeStatus
#endif
#ifdef F_0000003A_sceKernelCreateVpl
	IMPORT_FUNC	"ThreadManForUser",0x56C039B5,sceKernelCreateVpl
#endif
#ifdef F_0000003B_sceKernelDeleteVpl
	IMPORT_FUNC	"ThreadManForUser",0x89B3D48C,sceKernelDeleteVpl
#endif
#ifdef F_0000003C_sceKernelAllocateVpl
	IMPORT_FUNC	"ThreadManForUser",0xBED27435,sceKernelAllocateVpl
#endif
#ifdef F_0000003D_sceKernelAllocateVplCB
	IMPORT_FUNC	"ThreadManForUser",0xEC0A693F,sceKernelAllocateVplCB
#endif
#ifdef F_0000003E_sceKernelTryAllocateVpl
	IMPORT_FUNC	"ThreadManForUser",0xAF36D708,sceKernelTryAllocateVpl
#endif
#ifdef F_0000003F_sceKernelFreeVpl
	IMPORT_FUNC	"ThreadManForUser",0xB736E9FF,sceKernelFreeVpl
#endif
#ifdef F_00000040_sceKernelCancelVpl
	IMPORT_FUNC	"ThreadManForUser",0x1D371B8A,sceKernelCancelVpl
#endif
#ifdef F_00000041_sceKernelReferVplStatus
	IMPORT_FUNC	"ThreadManForUser",0x39810265,sceKernelReferVplStatus
#endif
#ifdef F_00000042_sceKernelCreateFpl
	IMPORT_FUNC	"ThreadManForUser",0xC07BB470,sceKernelCreateFpl
#endif
#ifdef F_00000043_sceKernelDeleteFpl
	IMPORT_FUNC	"ThreadManForUser",0xED1410E0,sceKernelDeleteFpl
#endif
#ifdef F_00000044_sceKernelAllocateFpl
	IMPORT_FUNC	"ThreadManForUser",0xD979E9BF,sceKernelAllocateFpl
#endif
#ifdef F_00000045_sceKernelAllocateFplCB
	IMPORT_FUNC	"ThreadManForUser",0xE7282CB6,sceKernelAllocateFplCB
#endif
#ifdef F_00000046_sceKernelTryAllocateFpl
	IMPORT_FUNC	"ThreadManForUser",0x623AE665,sceKernelTryAllocateFpl
#endif
#ifdef F_00000047_sceKernelFreeFpl
	IMPORT_FUNC	"ThreadManForUser",0xF6414A71,sceKernelFreeFpl
#endif
#ifdef F_00000048_sceKernelCancelFpl
	IMPORT_FUNC	"ThreadManForUser",0xA8AA591F,sceKernelCancelFpl
#endif
#ifdef F_00000049_sceKernelReferFplStatus
	IMPORT_FUNC	"ThreadManForUser",0xD8199E4C,sceKernelReferFplStatus
#endif
#ifdef F_0000004A__sceKernelReturnFromTimerHandler
	IMPORT_FUNC	"ThreadManForUser",0x0E927AED,_sceKernelReturnFromTimerHandler
#endif
#ifdef F_0000004B_sceKernelUSec2SysClock
	IMPORT_FUNC	"ThreadManForUser",0x110DEC9A,sceKernelUSec2SysClock
#endif
#ifdef F_0000004C_sceKernelUSec2SysClockWide
	IMPORT_FUNC	"ThreadManForUser",0xC8CD158C,sceKernelUSec2SysClockWide
#endif
#ifdef F_0000004D_sceKernelSysClock2USec
	IMPORT_FUNC	"ThreadManForUser",0xBA6B92E2,sceKernelSysClock2USec
#endif
#ifdef F_0000004E_sceKernelSysClock2USecWide
	IMPORT_FUNC	"ThreadManForUser",0xE1619D7C,sceKernelSysClock2USecWide
#endif
#ifdef F_0000004F_sceKernelGetSystemTime
	IMPORT_FUNC	"ThreadManForUser",0xDB738F35,sceKernelGetSystemTime
#endif
#ifdef F_00000050_sceKernelGetSystemTimeWide
	IMPORT_FUNC	"ThreadManForUser",0x82BC5777,sceKernelGetSystemTimeWide
#endif
#ifdef F_00000051_sceKernelGetSystemTimeLow
	IMPORT_FUNC	"ThreadManForUser",0x369ED59D,sceKernelGetSystemTimeLow
#endif
#ifdef F_00000052_sceKernelSetAlarm
	IMPORT_FUNC	"ThreadManForUser",0x6652B8CA,sceKernelSetAlarm
#endif
#ifdef F_00000053_sceKernelSetSysClockAlarm
	IMPORT_FUNC	"ThreadManForUser",0xB2C25152,sceKernelSetSysClockAlarm
#endif
#ifdef F_00000054_sceKernelCancelAlarm
	IMPORT_FUNC	"ThreadManForUser",0x7E65B999,sceKernelCancelAlarm
#endif
#ifdef F_00000055_sceKernelReferAlarmStatus
	IMPORT_FUNC	"ThreadManForUser",0xDAA3F564,sceKernelReferAlarmStatus
#endif
#ifdef F_00000056_sceKernelCreateVTimer
	IMPORT_FUNC	"ThreadManForUser",0x20FFF560,sceKernelCreateVTimer
#endif
#ifdef F_00000057_sceKernelDeleteVTimer
	IMPORT_FUNC	"ThreadManForUser",0x328F9E52,sceKernelDeleteVTimer
#endif
#ifdef F_00000058_sceKernelGetVTimerBase
	IMPORT_FUNC	"ThreadManForUser",0xB3A59970,sceKernelGetVTimerBase
#endif
#ifdef F_00000059_sceKernelGetVTimerBaseWide
	IMPORT_FUNC	"ThreadManForUser",0xB7C18B77,sceKernelGetVTimerBaseWide
#endif
#ifdef F_0000005A_sceKernelGetVTimerTime
	IMPORT_FUNC	"ThreadManForUser",0x034A921F,sceKernelGetVTimerTime
#endif
#ifdef F_0000005B_sceKernelGetVTimerTimeWide
	IMPORT_FUNC	"ThreadManForUser",0xC0B3FFD2,sceKernelGetVTimerTimeWide
#endif
#ifdef F_0000005C_sceKernelSetVTimerTime
	IMPORT_FUNC	"ThreadManForUser",0x542AD630,sceKernelSetVTimerTime
#endif
#ifdef F_0000005D_sceKernelSetVTimerTimeWide
	IMPORT_FUNC	"ThreadManForUser",0xFB6425C3,sceKernelSetVTimerTimeWide
#endif
#ifdef F_0000005E_sceKernelStartVTimer
	IMPORT_FUNC	"ThreadManForUser",0xC68D9437,sceKernelStartVTimer
#endif
#ifdef F_0000005F_sceKernelStopVTimer
	IMPORT_FUNC	"ThreadManForUser",0xD0AEEE87,sceKernelStopVTimer
#endif
#ifdef F_00000060_sceKernelSetVTimerHandler
	IMPORT_FUNC	"ThreadManForUser",0xD8B299AE,sceKernelSetVTimerHandler
#endif
#ifdef F_00000061_sceKernelSetVTimerHandlerWide
	IMPORT_FUNC	"ThreadManForUser",0x53B00E9A,sceKernelSetVTimerHandlerWide
#endif
#ifdef F_00000062_sceKernelCancelVTimerHandler
	IMPORT_FUNC	"ThreadManForUser",0xD2D615EF,sceKernelCancelVTimerHandler
#endif
#ifdef F_00000063_sceKernelReferVTimerStatus
	IMPORT_FUNC	"ThreadManForUser",0x5F32BEAA,sceKernelReferVTimerStatus
#endif
#ifdef F_00000064_sceKernelCreateThread
	IMPORT_FUNC	"ThreadManForUser",0x446D8DE6,sceKernelCreateThread
#endif
#ifdef F_00000065_sceKernelDeleteThread
	IMPORT_FUNC	"ThreadManForUser",0x9FA03CD3,sceKernelDeleteThread
#endif
#ifdef F_00000066_sceKernelStartThread
	IMPORT_FUNC	"ThreadManForUser",0xF475845D,sceKernelStartThread
#endif
#ifdef F_00000067__sceKernelExitThread
	IMPORT_FUNC	"ThreadManForUser",0x532A522E,_sceKernelExitThread
#endif
#ifdef F_00000068_sceKernelExitThread
	IMPORT_FUNC	"ThreadManForUser",0xAA73C935,sceKernelExitThread
#endif
#ifdef F_00000069_sceKernelExitDeleteThread
	IMPORT_FUNC	"ThreadManForUser",0x809CE29B,sceKernelExitDeleteThread
#endif
#ifdef F_0000006A_sceKernelTerminateThread
	IMPORT_FUNC	"ThreadManForUser",0x616403BA,sceKernelTerminateThread
#endif
#ifdef F_0000006B_sceKernelTerminateDeleteThread
	IMPORT_FUNC	"ThreadManForUser",0x383F7BCC,sceKernelTerminateDeleteThread
#endif
#ifdef F_0000006C_sceKernelSuspendDispatchThread
	IMPORT_FUNC	"ThreadManForUser",0x3AD58B8C,sceKernelSuspendDispatchThread
#endif
#ifdef F_0000006D_sceKernelResumeDispatchThread
	IMPORT_FUNC	"ThreadManForUser",0x27E22EC2,sceKernelResumeDispatchThread
#endif
#ifdef F_0000006E_sceKernelChangeCurrentThreadAttr
	IMPORT_FUNC	"ThreadManForUser",0xEA748E31,sceKernelChangeCurrentThreadAttr
#endif
#ifdef F_0000006F_sceKernelChangeThreadPriority
	IMPORT_FUNC	"ThreadManForUser",0x71BC9871,sceKernelChangeThreadPriority
#endif
#ifdef F_00000070_sceKernelRotateThreadReadyQueue
	IMPORT_FUNC	"ThreadManForUser",0x912354A7,sceKernelRotateThreadReadyQueue
#endif
#ifdef F_00000071_sceKernelReleaseWaitThread
	IMPORT_FUNC	"ThreadManForUser",0x2C34E053,sceKernelReleaseWaitThread
#endif
#ifdef F_00000072_sceKernelGetThreadId
	IMPORT_FUNC	"ThreadManForUser",0x293B45B8,sceKernelGetThreadId
#endif
#ifdef F_00000073_sceKernelGetThreadCurrentPriority
	IMPORT_FUNC	"ThreadManForUser",0x94AA61EE,sceKernelGetThreadCurrentPriority
#endif
#ifdef F_00000074_sceKernelGetThreadExitStatus
	IMPORT_FUNC	"ThreadManForUser",0x3B183E26,sceKernelGetThreadExitStatus
#endif
#ifdef F_00000075_sceKernelCheckThreadStack
	IMPORT_FUNC	"ThreadManForUser",0xD13BDE95,sceKernelCheckThreadStack
#endif
#ifdef F_00000076_sceKernelGetThreadStackFreeSize
	IMPORT_FUNC	"ThreadManForUser",0x52089CA1,sceKernelGetThreadStackFreeSize
#endif
#ifdef F_00000077_sceKernelReferThreadStatus
	IMPORT_FUNC	"ThreadManForUser",0x17C1684E,sceKernelReferThreadStatus
#endif
#ifdef F_00000078_sceKernelReferThreadRunStatus
	IMPORT_FUNC	"ThreadManForUser",0xFFC36A14,sceKernelReferThreadRunStatus
#endif
#ifdef F_00000079_sceKernelReferSystemStatus
	IMPORT_FUNC	"ThreadManForUser",0x627E6F3A,sceKernelReferSystemStatus
#endif
#ifdef F_0000007A_sceKernelGetThreadmanIdList
	IMPORT_FUNC	"ThreadManForUser",0x94416130,sceKernelGetThreadmanIdList
#endif
#ifdef F_0000007B_sceKernelGetThreadmanIdType
	IMPORT_FUNC	"ThreadManForUser",0x57CF62DD,sceKernelGetThreadmanIdType
#endif
#ifdef F_0000007C_sceKernelReferThreadProfiler
	IMPORT_FUNC	"ThreadManForUser",0x64D4540E,sceKernelReferThreadProfiler
#endif
#ifdef F_0000007D_sceKernelReferGlobalProfiler
	IMPORT_FUNC	"ThreadManForUser",0x8218B4DD,sceKernelReferGlobalProfiler
#endif
