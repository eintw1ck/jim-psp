
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

IO_OBJS = stub_IoFileMgrForUser.o 00000000_sceIoPollAsync.o 00000001_sceIoWaitAsync.o 00000002_sceIoWaitAsyncCB.o \
		  00000003_sceIoGetAsyncStat.o 00000004_sceIoChangeAsyncPriority.o 00000005_sceIoSetAsyncCallback.o \
		  00000006_sceIoClose.o 00000007_sceIoCloseAsync.o 00000008_sceIoOpen.o 00000009_sceIoOpenAsync.o \
		  0000000A_sceIoRead.o 0000000B_sceIoReadAsync.o 0000000C_sceIoWrite.o 0000000D_sceIoWriteAsync.o \
		  0000000E_sceIoLseek.o 0000000F_sceIoLseekAsync.o 00000010_sceIoLseek32.o 00000011_sceIoLseek32Async.o \
		  00000012_sceIoIoctl.o 00000013_sceIoIoctlAsync.o 00000014_sceIoDopen.o 00000015_sceIoDread.o \
		  00000016_sceIoDclose.o 00000017_sceIoRemove.o 00000018_sceIoMkdir.o 00000019_sceIoRmdir.o \
		  0000001A_sceIoChdir.o 0000001B_sceIoSync.o 0000001C_sceIoGetstat.o 0000001D_sceIoChstat.o \
		  0000001E_sceIoRename.o 0000001F_sceIoDevctl.o 00000020_sceIoGetDevType.o 00000021_sceIoAssign.o \
		  00000022_sceIoUnassign.o 00000023_sceIoCancel.o 

KERNEL_OBJS = stub_Kernel_Library.o 00000000_sceKernelCpuSuspendIntr.o 00000001_sceKernelCpuResumeIntr.o \
			  00000002_sceKernelCpuResumeIntrWithSync.o 00000003_sceKernelIsCpuIntrSuspended.o \
			  00000004_sceKernelIsCpuIntrEnable.o 

MODMGR_OBJS = stub_ModuleMgrForUser.o 00000000_sceKernelLoadModuleByID.o 00000001_sceKernelLoadModule.o \
			  00000002_sceKernelLoadModuleMs.o 00000003_sceKernelLoadModuleBufferUsbWlan.o \
			  00000004_sceKernelStartModule.o 00000005_sceKernelStopModule.o 00000006_sceKernelUnloadModule.o \
			  00000007_sceKernelSelfStopUnloadModule.o 00000008_sceKernelStopUnloadSelfModule.o \
			  00000009_sceKernelQueryModuleInfo.o 

STDIO_OBJS = stub_StdioForUser.o 00000000_sceKernelStdioRead.o 00000001_sceKernelStdioLseek.o \
			 00000002_sceKernelStdioSendChar.o 00000003_sceKernelStdioWrite.o 00000004_sceKernelStdioClose.o \
			 00000005_sceKernelStdioOpen.o 00000006_sceKernelStdin.o 00000007_sceKernelStdout.o 00000008_sceKernelStderr.o 

SUSPEND_OBJS = stub_sceSuspendForUser.o 00000000_sceKernelPowerLock.o 00000001_sceKernelPowerUnlock.o \
			   00000002_sceKernelPowerTick.o 

SYSMEM_OBJS = stub_SysMemUserForUser.o 00000000_sceKernelMaxFreeMemSize.o 00000001_sceKernelTotalFreeMemSize.o \
			  00000002_sceKernelAllocPartitionMemory.o 00000003_sceKernelFreePartitionMemory.o \
			  00000004_sceKernelGetBlockHeadAddr.o 00000005_sceKernelDevkitVersion.o 

THREADMAN_OBJS = stub_ThreadManForUser.o 00000000__sceKernelReturnFromCallback.o \
				 00000001_sceKernelRegisterThreadEventHandler.o 00000002_sceKernelReleaseThreadEventHandler.o \
				 00000003_sceKernelReferThreadEventHandlerStatus.o 00000004_sceKernelCreateCallback.o \
				 00000005_sceKernelDeleteCallback.o 00000006_sceKernelNotifyCallback.o 00000007_sceKernelCancelCallback.o \
				 00000008_sceKernelGetCallbackCount.o 00000009_sceKernelCheckCallback.o \
				 0000000A_sceKernelReferCallbackStatus.o 0000000B_sceKernelSleepThread.o 0000000C_sceKernelSleepThreadCB.o \
				 0000000D_sceKernelWakeupThread.o 0000000E_sceKernelCancelWakeupThread.o 0000000F_sceKernelSuspendThread.o \
				 00000010_sceKernelResumeThread.o 00000011_sceKernelWaitThreadEnd.o 00000012_sceKernelWaitThreadEndCB.o \
				 00000013_sceKernelDelayThread.o 00000014_sceKernelDelayThreadCB.o 00000015_sceKernelDelaySysClockThread.o \
				 00000016_sceKernelDelaySysClockThreadCB.o 00000017_sceKernelCreateSema.o 00000018_sceKernelDeleteSema.o \
				 00000019_sceKernelSignalSema.o 0000001A_sceKernelWaitSema.o 0000001B_sceKernelWaitSemaCB.o \
				 0000001C_sceKernelPollSema.o 0000001D_sceKernelCancelSema.o 0000001E_sceKernelReferSemaStatus.o \
				 0000001F_sceKernelCreateEventFlag.o 00000020_sceKernelDeleteEventFlag.o 00000021_sceKernelSetEventFlag.o \
				 00000022_sceKernelClearEventFlag.o 00000023_sceKernelWaitEventFlag.o 00000024_sceKernelWaitEventFlagCB.o \
				 00000025_sceKernelPollEventFlag.o 00000026_sceKernelCancelEventFlag.o \
				 00000027_sceKernelReferEventFlagStatus.o 00000028_sceKernelCreateMbx.o 00000029_sceKernelDeleteMbx.o \
				 0000002A_sceKernelSendMbx.o 0000002B_sceKernelReceiveMbx.o 0000002C_sceKernelReceiveMbxCB.o \
				 0000002D_sceKernelPollMbx.o 0000002E_sceKernelCancelReceiveMbx.o 0000002F_sceKernelReferMbxStatus.o \
				 00000030_sceKernelCreateMsgPipe.o 00000031_sceKernelDeleteMsgPipe.o 00000032_sceKernelSendMsgPipe.o \
				 00000033_sceKernelSendMsgPipeCB.o 00000034_sceKernelTrySendMsgPipe.o 00000035_sceKernelReceiveMsgPipe.o \
				 00000036_sceKernelReceiveMsgPipeCB.o 00000037_sceKernelTryReceiveMsgPipe.o \
				 00000038_sceKernelCancelMsgPipe.o 00000039_sceKernelReferMsgPipeStatus.o 0000003A_sceKernelCreateVpl.o \
				 0000003B_sceKernelDeleteVpl.o 0000003C_sceKernelAllocateVpl.o 0000003D_sceKernelAllocateVplCB.o \
				 0000003E_sceKernelTryAllocateVpl.o 0000003F_sceKernelFreeVpl.o 00000040_sceKernelCancelVpl.o \
				 00000041_sceKernelReferVplStatus.o 00000042_sceKernelCreateFpl.o 00000043_sceKernelDeleteFpl.o \
				 00000044_sceKernelAllocateFpl.o 00000045_sceKernelAllocateFplCB.o 00000046_sceKernelTryAllocateFpl.o \
				 00000047_sceKernelFreeFpl.o 00000048_sceKernelCancelFpl.o 00000049_sceKernelReferFplStatus.o \
				 0000004A__sceKernelReturnFromTimerHandler.o 0000004B_sceKernelUSec2SysClock.o \
				 0000004C_sceKernelUSec2SysClockWide.o 0000004D_sceKernelSysClock2USec.o \
				 0000004E_sceKernelSysClock2USecWide.o 0000004F_sceKernelGetSystemTime.o \
				 00000050_sceKernelGetSystemTimeWide.o 00000051_sceKernelGetSystemTimeLow.o \
				 00000052_sceKernelSetAlarm.o 00000053_sceKernelSetSysClockAlarm.o 00000054_sceKernelCancelAlarm.o \
				 00000055_sceKernelReferAlarmStatus.o 00000056_sceKernelCreateVTimer.o 00000057_sceKernelDeleteVTimer.o \
				 00000058_sceKernelGetVTimerBase.o 00000059_sceKernelGetVTimerBaseWide.o \
				 0000005A_sceKernelGetVTimerTime.o 0000005B_sceKernelGetVTimerTimeWide.o \
				 0000005C_sceKernelSetVTimerTime.o 0000005D_sceKernelSetVTimerTimeWide.o \
				 0000005E_sceKernelStartVTimer.o 0000005F_sceKernelStopVTimer.o 00000060_sceKernelSetVTimerHandler.o \
				 00000061_sceKernelSetVTimerHandlerWide.o 00000062_sceKernelCancelVTimerHandler.o \
				 00000063_sceKernelReferVTimerStatus.o 00000064_sceKernelCreateThread.o 00000065_sceKernelDeleteThread.o \
				 00000066_sceKernelStartThread.o 00000067__sceKernelExitThread.o 00000068_sceKernelExitThread.o \
				 00000069_sceKernelExitDeleteThread.o 0000006A_sceKernelTerminateThread.o \
				 0000006B_sceKernelTerminateDeleteThread.o 0000006C_sceKernelSuspendDispatchThread.o \
				 0000006D_sceKernelResumeDispatchThread.o 0000006E_sceKernelChangeCurrentThreadAttr.o \
				 0000006F_sceKernelChangeThreadPriority.o 00000070_sceKernelRotateThreadReadyQueue.o \
				 00000071_sceKernelReleaseWaitThread.o 00000072_sceKernelGetThreadId.o \
				 00000073_sceKernelGetThreadCurrentPriority.o 00000074_sceKernelGetThreadExitStatus.o \
				 00000075_sceKernelCheckThreadStack.o 00000076_sceKernelGetThreadStackFreeSize.o \
				 00000077_sceKernelReferThreadStatus.o 00000078_sceKernelReferThreadRunStatus.o \
				 00000079_sceKernelReferSystemStatus.o 0000007A_sceKernelGetThreadmanIdList.o \
				 0000007B_sceKernelGetThreadmanIdType.o 0000007C_sceKernelReferThreadProfiler.o \
				 0000007D_sceKernelReferGlobalProfiler.o 

UTILS_OBJS = stub_UtilsForUser.o 00000000_sceKernelDcacheInvalidateRange.o 00000001_sceKernelUtilsMd5Digest.o \
			 00000002_sceKernelUtilsMd5BlockInit.o 00000003_sceKernelUtilsMd5BlockUpdate.o \
			 00000004_sceKernelUtilsMd5BlockResult.o 00000005_sceKernelUtilsSha1Digest.o \
			 00000006_sceKernelUtilsSha1BlockInit.o 00000007_sceKernelUtilsSha1BlockUpdate.o \
			 00000008_sceKernelUtilsSha1BlockResult.o 00000009_sceKernelUtilsMt19937Init.o \
			 0000000A_sceKernelUtilsMt19937UInt.o 0000000B_sceKernelGetGPI.o 0000000C_sceKernelSetGPO.o \
			 0000000D_sceKernelLibcClock.o 0000000E_sceKernelLibcTime.o 0000000F_sceKernelLibcGettimeofday.o \
			 00000010_sceKernelDcacheWritebackAll.o 00000011_sceKernelDcacheWritebackInvalidateAll.o \
			 00000012_sceKernelDcacheWritebackRange.o 00000013_sceKernelDcacheWritebackInvalidateRange.o \
			 00000014_sceKernelDcacheProbe.o 00000015_sceKernelDcacheReadTag.o 00000016_sceKernelIcacheProbe.o \
			 00000017_sceKernelIcacheReadTag.o 
			 
INTERRUPT_OBJS = stub_InterruptManager.o 00000000_sceKernelRegisterSubIntrHandler.o \
				 00000001_sceKernelReleaseSubIntrHandler.o 00000002_sceKernelEnableSubIntr.o \
				 00000003_sceKernelDisableSubIntr.o 00000004_sceKernelSuspendSubIntr.o \
				 00000005_sceKernelResumeSubIntr.o 00000006_sceKernelIsSubInterruptOccurred.o \
				 00000007_QueryIntrHandlerInfo.o 00000008_sceKernelRegisterUserSpaceIntrStack.o 

LOADEXEC_OBJS = stub_LoadExecForUser.o 00000000_sceKernelLoadExec.o 00000001_sceKernelExitGameWithStatus.o \
				00000002_sceKernelExitGame.o 00000003_sceKernelRegisterExitCallback.o 

libpspuserincludedir = @PSPSDK_INCLUDEDIR@
libpspuserinclude_HEADERS =	\
	pspiofilemgr.h		\
	pspiofilemgr_dirent.h	\
	pspiofilemgr_fcntl.h	\
	pspiofilemgr_stat.h	\
	pspkerneltypes.h	\
	pspkerror.h		\
	psploadexec.h		\
	pspmoduleinfo.h		\
	pspmodulemgr.h		\
	pspsysmem.h		\
	pspthreadman.h		\
	pspstdio.h		\
	pspuser.h		\
	psputils.h		\
	pspintmanager.h \
	pspmoduleexport.h

lib_LIBRARIES = libpspuser.a

libpspuser_a_SOURCES =	\
	IoFileMgrForUser.S	\
	InterruptManager.S	\
	Kernel_Library.S	\
	LoadExecForUser.S	\
	ModuleMgrForUser.S	\
	StdioForUser.S		\
	SysMemUserForUser.S	\
	ThreadManForUser.S	\
	UtilsForUser.S		\
	sceSuspendForUser.S	

libpspuser_a_LIBADD = \
$(IO_OBJS) \
$(KERNEL_OBJS) \
$(MODMGR_OBJS) \
$(STDIO_OBJS) \
$(SUSPEND_OBJS) \
$(SYSMEM_OBJS) \
$(THREADMAN_OBJS) \
$(UTILS_OBJS) \
$(INTERRUPT_OBJS) \
$(LOADEXEC_OBJS)

$(IO_OBJS): IoFileMgrForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(KERNEL_OBJS): Kernel_Library.S
	$(COMPILE) -DF_$* $< -c -o $@

$(MODMGR_OBJS): ModuleMgrForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(STDIO_OBJS): StdioForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SUSPEND_OBJS): sceSuspendForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSMEM_OBJS): SysMemUserForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(THREADMAN_OBJS): ThreadManForUser.S
	$(COMPILE) -DF_$* $< -c -o $@
	
$(UTILS_OBJS): UtilsForUser.S
	$(COMPILE) -DF_$* $< -c -o $@

$(INTERRUPT_OBJS): InterruptManager.S
	$(COMPILE) -DF_$* $< -c -o $@

$(LOADEXEC_OBJS): LoadExecForUser.S
	$(COMPILE) -DF_$* $< -c -o $@
