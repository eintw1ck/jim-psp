
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

EXCEPTION_OBJS = stub_ExceptionManagerForKernel.o 00000000_sceKernelRegisterExceptionHandler.o \
				 00000001_sceKernelRegisterPriorityExceptionHandler.o 00000002_sceKernelRegisterDefaultExceptionHandler.o \
				 00000003_sceKernelReleaseExceptionHandler.o 00000004_sceKernelGetActiveDefaultExceptionHandler.o \
				 00000005_sceKernelReleaseDefaultExceptionHandler.o 00000006_sceKernelRegisterNmiHandler.o \
				 00000007_sceKernelReleaseNmiHandler.o 
				 
KDEBUG_OBJS = stub_KDebugForKernel.o 00000000_sceKernelRegisterAssertHandler.o 00000001_sceKernelAssert.o \
			  00000002_sceKernelGetDebugPutchar.o 00000003_sceKernelRegisterDebugPutchar.o \
			  00000004_sceKernelRegisterKprintfHandler.o 00000005_Kprintf.o 00000006_sceKernelDebugWrite.o \
			  00000007_sceKernelRegisterDebugWrite.o 00000008_sceKernelDebugRead.o 00000009_sceKernelRegisterDebugRead.o \
			  0000000A_sceKernelDebugEcho.o 0000000B_sceKernelDebugEchoSet.o 0000000C_KDebugForKernel_24C32559.o \
			  0000000D_sceKernelRemoveByDebugSection.o 0000000E_KDebugForKernel_5282DD5E.o \
			  0000000F_KDebugForKernel_9F8703E4.o 00000010_KDebugForKernel_333DCEC7.o \
			  00000011_KDebugForKernel_E892D9A1.o 00000012_KDebugForKernel_A126F497.o \
			  00000013_KDebugForKernel_B7251823.o 

LOADCORE_OBJS = stub_LoadCoreForKernel.o 00000000_sceKernelCheckPspConfig.o 00000001_sceKernelCheckExecFile.o \
				00000002_sceKernelProbeExecutableObject.o 00000003_sceKernelLoadExecutableObject.o \
				00000004_sceKernelApplyElfRelSection.o 00000005_LoadCoreForKernel_54AB2675.o \
				00000006_sceKernelDcacheWBinvAll.o 00000007_sceKernelIcacheClearAll.o \
				00000008_sceKernelRegisterLibrary.o 00000009_sceKernelRegisterLibraryForUser.o \
				0000000A_sceKernelReleaseLibrary.o 0000000B_sceKernelCanReleaseLibrary.o \
				0000000C_sceKernelLinkLibraryEntries.o 0000000D_sceKernelLinkLibraryEntriesForUser.o \
				0000000E_sceKernelUnLinkLibraryEntries.o 0000000F_sceKernelQueryLoadCoreCB.o \
				00000010_LoadCoreForKernel_616FCCCD.o 00000011_sceKernelModuleFromUID.o \
				00000012_sceKernelCreateModule.o 00000013_sceKernelDeleteModule.o 00000014_sceKernelModuleAssign.o \
				00000015_sceKernelAllocModule.o 00000016_sceKernelFreeModule.o 00000017_sceKernelRegisterModule.o \
				00000018_sceKernelReleaseModule.o 00000019_sceKernelFindModuleByName.o \
				0000001A_sceKernelFindModuleByAddress.o 0000001B_sceKernelFindModuleByUID.o \
				0000001C_sceKernelModuleCount.o 0000001D_sceKernelGetModuleList.o 

IO_OBJS = stub_IoFileMgrForKernel.o 00000000_sceIoPollAsync.o 00000001_sceIoWaitAsync.o 00000002_sceIoWaitAsyncCB.o \
		  00000003_sceIoGetAsyncStat.o 00000004_sceIoChangeAsyncPriority.o 00000005_sceIoSetAsyncCallback.o \
		  00000006_sceIoClose.o 00000007_sceIoCloseAsync.o 00000008_sceIoCloseAll.o 00000009_sceIoOpen.o \
		  0000000A_sceIoOpenAsync.o 0000000B_sceIoReopen.o 0000000C_sceIoRead.o 0000000D_sceIoReadAsync.o \
		  0000000E_sceIoWrite.o 0000000F_sceIoWriteAsync.o 00000010_sceIoLseek.o 00000011_sceIoLseekAsync.o \
		  00000012_sceIoLseek32.o 00000013_sceIoLseek32Async.o 00000014_sceIoIoctl.o 00000015_sceIoIoctlAsync.o \
		  00000016_sceIoDopen.o 00000017_sceIoDread.o 00000018_sceIoDclose.o 00000019_sceIoRemove.o \
		  0000001A_sceIoMkdir.o 0000001B_sceIoRmdir.o 0000001C_sceIoChdir.o 0000001D_sceIoSync.o \
		  0000001E_sceIoGetstat.o 0000001F_sceIoChstat.o 00000020_sceIoRename.o 00000021_sceIoDevctl.o \
		  00000022_sceIoGetDevType.o 00000023_sceIoAssign.o 00000024_sceIoUnassign.o 00000025_sceIoGetThreadCwd.o \
		  00000026_sceIoChangeThreadCwd.o 00000027_sceIoCancel.o 00000028_sceIoAddDrv.o 00000029_sceIoDelDrv.o 

STDIO_OBJS = stub_StdioForKernel.o 00000000_fdprintf.o 00000001_printf.o 00000002_fdputc.o 00000003_putchar.o \
			 00000004_fdputs.o 00000005_puts.o 00000006_fdgetc.o 00000007_getchar.o 00000008_fdgets.o 00000009_gets.o \
			 0000000A_sceKernelStdin.o 0000000B_sceKernelStdout.o 0000000C_sceKernelStderr.o \
			 0000000D_sceKernelStdoutReopen.o 0000000E_sceKernelStderrReopen.o 
SYSREG_OBJS = stub_sceSysreg_driver.o 00000000_sceSysregInit.o 00000001_sceSysregEnd.o \
			  00000002_sceSysreg_driver_E88B77ED.o 00000003_sceSysreg_driver_CD0F6715.o \
			  00000004_sceSysreg_driver_844AF6BD.o 00000005_sceSysreg_driver_E2A5D1EE.o \
			  00000006_sceSysreg_driver_4F46EEDE.o 00000007_sceSysreg_driver_8F4F4E96.o \
			  00000008_sceSysregTopResetEnable.o 00000009_sceSysregScResetEnable.o \
			  0000000A_sceSysregMeResetEnable.o 0000000B_sceSysregMeResetDisable.o 0000000C_sceSysregAwResetEnable.o \
			  0000000D_sceSysregAwResetDisable.o 0000000E_sceSysregVmeResetEnable.o 0000000F_sceSysregVmeResetDisable.o \
			  00000010_sceSysregAvcResetEnable.o 00000011_sceSysregAvcResetDisable.o 00000012_sceSysregUsbResetEnable.o \
			  00000013_sceSysregUsbResetDisable.o 00000014_sceSysregAtaResetEnable.o 00000015_sceSysregAtaResetDisable.o \
			  00000016_sceSysregMsifResetEnable.o 00000017_sceSysregMsifResetDisable.o 00000018_sceSysregKirkResetEnable.o \
			  00000019_sceSysregKirkResetDisable.o 0000001A_sceSysreg_driver_B21B6CBF.o \
			  0000001B_sceSysreg_driver_BB3623DF.o 0000001C_sceSysreg_driver_53A6838B.o \
			  0000001D_sceSysreg_driver_B4560C45.o 0000001E_sceSysreg_driver_DCA57573.o \
			  0000001F_sceSysregMeBusClockEnable.o 00000020_sceSysregMeBusClockDisable.o \
			  00000021_sceSysreg_driver_4D4CE2B8.o 00000022_sceSysreg_driver_789BD609.o \
			  00000023_sceSysreg_driver_391CE1C0.o 00000024_sceSysreg_driver_82D35024.o \
			  00000025_sceSysreg_driver_AF904657.o 00000026_sceSysreg_driver_438AECE9.o \
			  00000027_sceSysregDmacplusBusClockEnable.o 00000028_sceSysregDmacplusBusClockDisable.o \
			  00000029_sceSysregDmacBusClockEnable.o 0000002A_sceSysregDmacBusClockDisable.o \
			  0000002B_sceSysregKirkBusClockEnable.o 0000002C_sceSysregKirkBusClockDisable.o \
			  0000002D_sceSysregAtaBusClockEnable.o 0000002E_sceSysregAtaBusClockDisable.o \
			  0000002F_sceSysregUsbBusClockEnable.o 00000030_sceSysregUsbBusClockDisable.o \
			  00000031_sceSysregMsifBusClockEnable.o 00000032_sceSysregMsifBusClockDisable.o \
			  00000033_sceSysreg_driver_7CC6CBFD.o 00000034_sceSysreg_driver_EE6B9411.o \
			  00000035_sceSysregEmcsmBusClockEnable.o 00000036_sceSysregEmcsmBusClockDisable.o \
			  00000037_sceSysreg_driver_63B9EB65.o 00000038_sceSysreg_driver_E1AA9788.o \
			  00000039_sceSysregAudioBusClockEnable.o 0000003A_sceSysregAudioBusClockDisable.o \
			  0000003B_sceSysreg_driver_6B01D71B.o 0000003C_sceSysreg_driver_FC186A83.o \
			  0000003D_sceSysreg_driver_7234EA80.o 0000003E_sceSysreg_driver_38EC3281.o \
			  0000003F_sceSysreg_driver_31154490.o 00000040_sceSysreg_driver_8E2D835D.o \
			  00000041_sceSysreg_driver_8835D1E1.o 00000042_sceSysreg_driver_8B90B8B5.o \
			  00000043_sceSysreg_driver_7725CA08.o 00000044_sceSysreg_driver_A3E4154C.o \
			  00000045_sceSysreg_driver_E8533DCA.o 00000046_sceSysreg_driver_F6D83AD0.o \
			  00000047_sceSysreg_driver_A9CD1C1F.o 00000048_sceSysreg_driver_2F216F38.o \
			  00000049_sceSysreg_driver_A24C242A.o 0000004A_sceSysreg_driver_E89243BE.o \
			  0000004B_sceSysreg_driver_7DCA8302.o 0000004C_sceSysreg_driver_45225F8F.o \
			  0000004D_sceSysreg_driver_D74D3AB6.o 0000004E_sceSysreg_driver_AD7C4ACB.o \
			  0000004F_sceSysreg_driver_DC68A93F.o 00000050_sceSysreg_driver_94B0323C.o \
			  00000051_sceSysreg_driver_6417CDD6.o 00000052_sceSysreg_driver_20388C9E.o \
			  00000053_sceSysreg_driver_E3AECFFA.o 00000054_sceSysreg_driver_3BBD0C0C.o \
			  00000055_sceSysreg_driver_C1DA05D2.o 00000056_sceSysreg_driver_DE170397.o \
			  00000057_sceSysreg_driver_1969E840.o 00000058_sceSysreg_driver_1D382514.o \
			  00000059_sceSysreg_driver_833E6FB1.o 0000005A_sceSysreg_driver_03340297.o \
			  0000005B_sceSysreg_driver_9100B4E5.o 0000005C_sceSysreg_driver_0A83FC7B.o \
			  0000005D_sceSysreg_driver_D6628A48.o 0000005E_sceSysreg_driver_1E18EA43.o \
			  0000005F_sceSysregEmcsmIoEnable.o 00000060_sceSysregEmcsmIoDisable.o \
			  00000061_sceSysregUsbIoEnable.o 00000062_sceSysregUsbIoDisable.o 00000063_sceSysregAtaIoEnable.o \
			  00000064_sceSysregAtaIoDisable.o 00000065_sceSysregMsifIoEnable.o 00000066_sceSysregMsifIoDisable.o \
			  00000067_sceSysregLcdcIoEnable.o 00000068_sceSysregLcdcIoDisable.o 00000069_sceSysregAudioIoEnable.o \
			  0000006A_sceSysregAudioIoDisable.o 0000006B_sceSysregIicIoEnable.o 0000006C_sceSysregIicIoDisable.o \
			  0000006D_sceSysregSircsIoEnable.o 0000006E_sceSysregSircsIoDisable.o 0000006F_sceSysreg_driver_F844DDF3.o \
			  00000070_sceSysreg_driver_29A119A1.o 00000071_sceSysregKeyIoEnable.o 00000072_sceSysregKeyIoDisable.o \
			  00000073_sceSysregPwmIoEnable.o 00000074_sceSysregPwmIoDisable.o 00000075_sceSysregUartIoEnable.o \
			  00000076_sceSysregUartIoDisable.o 00000077_sceSysregSpiIoEnable.o 00000078_sceSysregSpiIoDisable.o \
			  00000079_sceSysregGpioIoEnable.o 0000007A_sceSysregGpioIoDisable.o 0000007B_sceSysreg_driver_55B18B84.o \
			  0000007C_sceSysreg_driver_2112E686.o 0000007D_sceSysreg_driver_7B9E9A53.o 0000007E_sceSysreg_driver_7BDF0556.o \
			  0000007F_sceSysreg_driver_8D0FED1E.o 00000080_sceSysreg_driver_A46E9CA8.o \
			  00000081_sceSysreg_driver_633595F2.o 00000082_sceSysregUsbQueryIntr.o \
			  00000083_sceSysregUsbAcquireIntr.o 00000084_sceSysreg_driver_D43E98F6.o \
			  00000085_sceSysreg_driver_BF91FBDA.o 00000086_sceSysreg_driver_36A75390.o \
			  00000087_sceSysregIntrInit.o 00000088_sceSysregIntrEnd.o 00000089_sceSysregInterruptToOther.o \
			  0000008A_sceSysregSemaTryLock.o 0000008B_sceSysregSemaUnlock.o 0000008C_sceSysregEnableIntr.o \
			  0000008D_sceSysregDisableIntr.o 0000008E_sceSysregRequestIntr.o 0000008F_sceSysreg_driver_5664F8B5.o \
			  00000090_sceSysreg_driver_44704E1D.o 00000091_sceSysreg_driver_584AD989.o \
			  00000092_sceSysreg_driver_377F035F.o 00000093_sceSysreg_driver_AB3185FD.o \
			  00000094_sceSysreg_driver_0EA487FA.o 00000095_sceSysreg_driver_136E8F5A.o \
			  00000096_sceSysreg_driver_F4811E00.o 

UTILS_OBJS = stub_UtilsForKernel.o 00000000_sceUtilsKernelDcacheWBinvRange.o 00000001_sceKernelUtilsMd5Digest.o \
			 00000002_sceKernelUtilsMd5BlockInit.o 00000003_sceKernelUtilsMd5BlockUpdate.o \
			 00000004_sceKernelUtilsMd5BlockResult.o 00000005_sceKernelUtilsSha1Digest.o \
			 00000006_sceKernelUtilsSha1BlockInit.o 00000007_sceKernelUtilsSha1BlockUpdate.o \
			 00000008_sceKernelUtilsSha1BlockResult.o 00000009_sceKernelUtilsMt19937Init.o \
			 0000000A_sceKernelUtilsMt19937UInt.o 0000000B_sceKernelSetGPIMask.o 0000000C_sceKernelSetGPOMask.o \
			 0000000D_sceKernelGetGPI.o 0000000E_sceKernelSetGPO.o 0000000F_sceKernelRegisterLibcRtcFunc.o \
			 00000010_sceKernelReleaseLibcRtcFunc.o 00000011_sceKernelLibcClock.o 00000012_sceKernelLibcTime.o \
			 00000013_sceKernelLibcGettimeofday.o 00000014_sceKernelDcacheWritebackAll.o \
			 00000015_sceKernelDcacheWritebackInvalidateAll.o 00000016_sceKernelDcacheInvalidateAll.o \
			 00000017_sceKernelDcacheWritebackRange.o 00000018_sceKernelDcacheWritebackInvalidateRange.o \
			 00000019_sceKernelDcacheInvalidateRange.o 0000001A_sceKernelDcacheProbe.o \
			 0000001B_sceKernelDcacheReadTag.o 0000001C_sceKernelIcacheInvalidateAll.o \
			 0000001D_sceKernelIcacheInvalidateRange.o 0000001E_sceKernelIcacheProbe.o \
			 0000001F_sceKernelIcacheReadTag.o 00000020_sceKernelGzipDecompress.o 00000021_sceKernelGzipIsValid.o \
			 00000022_sceKernelGzipGetInfo.o 00000023_sceKernelGzipGetName.o 00000024_sceKernelGzipGetComment.o \
			 00000025_sceKernelGzipGetCompressedData.o 00000026_sceKernelDeflateDecompress.o 

libpspkernelincludedir = @PSPSDK_INCLUDEDIR@

libpspkernelinclude_HEADERS =	\
	pspiofilemgr_kernel.h	\
	pspkernel.h		\
	psploadcore.h		\
	pspstdio_kernel.h	\
	pspsysreg.h		\
	psputilsforkernel.h
	
lib_LIBRARIES = libpspkernel.a

libpspkernel_a_SOURCES =	\
	ExceptionManagerForKernel.S \
	KDebugForKernel.S	\
	LoadCoreForKernel.S	\
	IoFileMgrForKernel.S	\
	StdioForKernel.S	\
	sceSysreg_driver.S	\
	UtilsForKernel.S
libpspkernel_a_LIBADD = $(EXCEPTION_OBJS) $(KDEBUG_OBJS) $(LOADCORE_OBJS) $(IO_OBJS) \
						$(STDIO_OBJS) $(SYSREG_OBJS) $(UTILS_OBJS)

$(EXCEPTION_OBJS): ExceptionManagerForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(KDEBUG_OBJS): KDebugForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(LOADCORE_OBJS): LoadCoreForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(IO_OBJS): IoFileMgrForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(STDIO_OBJS): StdioForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@

$(SYSREG_OBJS): sceSysreg_driver.S
	$(COMPILE) -DF_$* $< -c -o $@

$(UTILS_OBJS): UtilsForKernel.S
	$(COMPILE) -DF_$* $< -c -o $@
