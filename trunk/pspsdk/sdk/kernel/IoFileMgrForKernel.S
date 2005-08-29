	.set noreorder

#include "pspimport.s"

#ifdef F_stub_IoFileMgrForKernel
	IMPORT_START	"IoFileMgrForKernel",0x00010000
#endif
#ifdef F_00000000_sceIoPollAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0x3251EA56,sceIoPollAsync
#endif
#ifdef F_00000001_sceIoWaitAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0xE23EEC33,sceIoWaitAsync
#endif
#ifdef F_00000002_sceIoWaitAsyncCB
	IMPORT_FUNC	"IoFileMgrForKernel",0x35DBD746,sceIoWaitAsyncCB
#endif
#ifdef F_00000003_sceIoGetAsyncStat
	IMPORT_FUNC	"IoFileMgrForKernel",0xCB05F8D6,sceIoGetAsyncStat
#endif
#ifdef F_00000004_sceIoChangeAsyncPriority
	IMPORT_FUNC	"IoFileMgrForKernel",0xB293727F,sceIoChangeAsyncPriority
#endif
#ifdef F_00000005_sceIoSetAsyncCallback
	IMPORT_FUNC	"IoFileMgrForKernel",0xA12A0514,sceIoSetAsyncCallback
#endif
#ifdef F_00000006_sceIoClose
	IMPORT_FUNC	"IoFileMgrForKernel",0x810C4BC3,sceIoClose
#endif
#ifdef F_00000007_sceIoCloseAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0xFF5940B6,sceIoCloseAsync
#endif
#ifdef F_00000008_sceIoCloseAll
	IMPORT_FUNC	"IoFileMgrForKernel",0xA905B705,sceIoCloseAll
#endif
#ifdef F_00000009_sceIoOpen
	IMPORT_FUNC	"IoFileMgrForKernel",0x109F50BC,sceIoOpen
#endif
#ifdef F_0000000A_sceIoOpenAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0x89AA9906,sceIoOpenAsync
#endif
#ifdef F_0000000B_sceIoReopen
	IMPORT_FUNC	"IoFileMgrForKernel",0x3C54E908,sceIoReopen
#endif
#ifdef F_0000000C_sceIoRead
	IMPORT_FUNC	"IoFileMgrForKernel",0x6A638D83,sceIoRead
#endif
#ifdef F_0000000D_sceIoReadAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0xA0B5A7C2,sceIoReadAsync
#endif
#ifdef F_0000000E_sceIoWrite
	IMPORT_FUNC	"IoFileMgrForKernel",0x42EC03AC,sceIoWrite
#endif
#ifdef F_0000000F_sceIoWriteAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0x0FACAB19,sceIoWriteAsync
#endif
#ifdef F_00000010_sceIoLseek
	IMPORT_FUNC	"IoFileMgrForKernel",0x27EB27B8,sceIoLseek
#endif
#ifdef F_00000011_sceIoLseekAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0x71B19E77,sceIoLseekAsync
#endif
#ifdef F_00000012_sceIoLseek32
	IMPORT_FUNC	"IoFileMgrForKernel",0x68963324,sceIoLseek32
#endif
#ifdef F_00000013_sceIoLseek32Async
	IMPORT_FUNC	"IoFileMgrForKernel",0x1B385D8F,sceIoLseek32Async
#endif
#ifdef F_00000014_sceIoIoctl
	IMPORT_FUNC	"IoFileMgrForKernel",0x63632449,sceIoIoctl
#endif
#ifdef F_00000015_sceIoIoctlAsync
	IMPORT_FUNC	"IoFileMgrForKernel",0xE95A012B,sceIoIoctlAsync
#endif
#ifdef F_00000016_sceIoDopen
	IMPORT_FUNC	"IoFileMgrForKernel",0xB29DDF9C,sceIoDopen
#endif
#ifdef F_00000017_sceIoDread
	IMPORT_FUNC	"IoFileMgrForKernel",0xE3EB004C,sceIoDread
#endif
#ifdef F_00000018_sceIoDclose
	IMPORT_FUNC	"IoFileMgrForKernel",0xEB092469,sceIoDclose
#endif
#ifdef F_00000019_sceIoRemove
	IMPORT_FUNC	"IoFileMgrForKernel",0xF27A9C51,sceIoRemove
#endif
#ifdef F_0000001A_sceIoMkdir
	IMPORT_FUNC	"IoFileMgrForKernel",0x06A70004,sceIoMkdir
#endif
#ifdef F_0000001B_sceIoRmdir
	IMPORT_FUNC	"IoFileMgrForKernel",0x1117C65F,sceIoRmdir
#endif
#ifdef F_0000001C_sceIoChdir
	IMPORT_FUNC	"IoFileMgrForKernel",0x55F4717D,sceIoChdir
#endif
#ifdef F_0000001D_sceIoSync
	IMPORT_FUNC	"IoFileMgrForKernel",0xAB96437F,sceIoSync
#endif
#ifdef F_0000001E_sceIoGetstat
	IMPORT_FUNC	"IoFileMgrForKernel",0xACE946E8,sceIoGetstat
#endif
#ifdef F_0000001F_sceIoChstat
	IMPORT_FUNC	"IoFileMgrForKernel",0xB8A740F4,sceIoChstat
#endif
#ifdef F_00000020_sceIoRename
	IMPORT_FUNC	"IoFileMgrForKernel",0x779103A0,sceIoRename
#endif
#ifdef F_00000021_sceIoDevctl
	IMPORT_FUNC	"IoFileMgrForKernel",0x54F5FB11,sceIoDevctl
#endif
#ifdef F_00000022_sceIoGetDevType
	IMPORT_FUNC	"IoFileMgrForKernel",0x08BD7374,sceIoGetDevType
#endif
#ifdef F_00000023_sceIoAssign
	IMPORT_FUNC	"IoFileMgrForKernel",0xB2A628C1,sceIoAssign
#endif
#ifdef F_00000024_sceIoUnassign
	IMPORT_FUNC	"IoFileMgrForKernel",0x6D08A871,sceIoUnassign
#endif
#ifdef F_00000025_sceIoGetThreadCwd
	IMPORT_FUNC	"IoFileMgrForKernel",0x411106BA,sceIoGetThreadCwd
#endif
#ifdef F_00000026_sceIoChangeThreadCwd
	IMPORT_FUNC	"IoFileMgrForKernel",0xCB0A151F,sceIoChangeThreadCwd
#endif
#ifdef F_00000027_sceIoCancel
	IMPORT_FUNC	"IoFileMgrForKernel",0xE8BC6571,sceIoCancel
#endif
#ifdef F_00000028_sceIoAddDrv
	IMPORT_FUNC	"IoFileMgrForKernel",0x8E982A74,sceIoAddDrv
#endif
#ifdef F_00000029_sceIoDelDrv
	IMPORT_FUNC	"IoFileMgrForKernel",0xC7F35804,sceIoDelDrv
#endif
