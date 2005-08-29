	.set noreorder

#include "pspimport.s"

#ifdef F_stub_IoFileMgrForUser
	IMPORT_START	"IoFileMgrForUser",0x40010000
#endif
#ifdef F_00000000_sceIoPollAsync
	IMPORT_FUNC	"IoFileMgrForUser",0x3251EA56,sceIoPollAsync
#endif
#ifdef F_00000001_sceIoWaitAsync
	IMPORT_FUNC	"IoFileMgrForUser",0xE23EEC33,sceIoWaitAsync
#endif
#ifdef F_00000002_sceIoWaitAsyncCB
	IMPORT_FUNC	"IoFileMgrForUser",0x35DBD746,sceIoWaitAsyncCB
#endif
#ifdef F_00000003_sceIoGetAsyncStat
	IMPORT_FUNC	"IoFileMgrForUser",0xCB05F8D6,sceIoGetAsyncStat
#endif
#ifdef F_00000004_sceIoChangeAsyncPriority
	IMPORT_FUNC	"IoFileMgrForUser",0xB293727F,sceIoChangeAsyncPriority
#endif
#ifdef F_00000005_sceIoSetAsyncCallback
	IMPORT_FUNC	"IoFileMgrForUser",0xA12A0514,sceIoSetAsyncCallback
#endif
#ifdef F_00000006_sceIoClose
	IMPORT_FUNC	"IoFileMgrForUser",0x810C4BC3,sceIoClose
#endif
#ifdef F_00000007_sceIoCloseAsync
	IMPORT_FUNC	"IoFileMgrForUser",0xFF5940B6,sceIoCloseAsync
#endif
#ifdef F_00000008_sceIoOpen
	IMPORT_FUNC	"IoFileMgrForUser",0x109F50BC,sceIoOpen
#endif
#ifdef F_00000009_sceIoOpenAsync
	IMPORT_FUNC	"IoFileMgrForUser",0x89AA9906,sceIoOpenAsync
#endif
#ifdef F_0000000A_sceIoRead
	IMPORT_FUNC	"IoFileMgrForUser",0x6A638D83,sceIoRead
#endif
#ifdef F_0000000B_sceIoReadAsync
	IMPORT_FUNC	"IoFileMgrForUser",0xA0B5A7C2,sceIoReadAsync
#endif
#ifdef F_0000000C_sceIoWrite
	IMPORT_FUNC	"IoFileMgrForUser",0x42EC03AC,sceIoWrite
#endif
#ifdef F_0000000D_sceIoWriteAsync
	IMPORT_FUNC	"IoFileMgrForUser",0x0FACAB19,sceIoWriteAsync
#endif
#ifdef F_0000000E_sceIoLseek
	IMPORT_FUNC	"IoFileMgrForUser",0x27EB27B8,sceIoLseek
#endif
#ifdef F_0000000F_sceIoLseekAsync
	IMPORT_FUNC	"IoFileMgrForUser",0x71B19E77,sceIoLseekAsync
#endif
#ifdef F_00000010_sceIoLseek32
	IMPORT_FUNC	"IoFileMgrForUser",0x68963324,sceIoLseek32
#endif
#ifdef F_00000011_sceIoLseek32Async
	IMPORT_FUNC	"IoFileMgrForUser",0x1B385D8F,sceIoLseek32Async
#endif
#ifdef F_00000012_sceIoIoctl
	IMPORT_FUNC	"IoFileMgrForUser",0x63632449,sceIoIoctl
#endif
#ifdef F_00000013_sceIoIoctlAsync
	IMPORT_FUNC	"IoFileMgrForUser",0xE95A012B,sceIoIoctlAsync
#endif
#ifdef F_00000014_sceIoDopen
	IMPORT_FUNC	"IoFileMgrForUser",0xB29DDF9C,sceIoDopen
#endif
#ifdef F_00000015_sceIoDread
	IMPORT_FUNC	"IoFileMgrForUser",0xE3EB004C,sceIoDread
#endif
#ifdef F_00000016_sceIoDclose
	IMPORT_FUNC	"IoFileMgrForUser",0xEB092469,sceIoDclose
#endif
#ifdef F_00000017_sceIoRemove
	IMPORT_FUNC	"IoFileMgrForUser",0xF27A9C51,sceIoRemove
#endif
#ifdef F_00000018_sceIoMkdir
	IMPORT_FUNC	"IoFileMgrForUser",0x06A70004,sceIoMkdir
#endif
#ifdef F_00000019_sceIoRmdir
	IMPORT_FUNC	"IoFileMgrForUser",0x1117C65F,sceIoRmdir
#endif
#ifdef F_0000001A_sceIoChdir
	IMPORT_FUNC	"IoFileMgrForUser",0x55F4717D,sceIoChdir
#endif
#ifdef F_0000001B_sceIoSync
	IMPORT_FUNC	"IoFileMgrForUser",0xAB96437F,sceIoSync
#endif
#ifdef F_0000001C_sceIoGetstat
	IMPORT_FUNC	"IoFileMgrForUser",0xACE946E8,sceIoGetstat
#endif
#ifdef F_0000001D_sceIoChstat
	IMPORT_FUNC	"IoFileMgrForUser",0xB8A740F4,sceIoChstat
#endif
#ifdef F_0000001E_sceIoRename
	IMPORT_FUNC	"IoFileMgrForUser",0x779103A0,sceIoRename
#endif
#ifdef F_0000001F_sceIoDevctl
	IMPORT_FUNC	"IoFileMgrForUser",0x54F5FB11,sceIoDevctl
#endif
#ifdef F_00000020_sceIoGetDevType
	IMPORT_FUNC	"IoFileMgrForUser",0x08BD7374,sceIoGetDevType
#endif
#ifdef F_00000021_sceIoAssign
	IMPORT_FUNC	"IoFileMgrForUser",0xB2A628C1,sceIoAssign
#endif
#ifdef F_00000022_sceIoUnassign
	IMPORT_FUNC	"IoFileMgrForUser",0x6D08A871,sceIoUnassign
#endif
#ifdef F_00000023_sceIoCancel
	IMPORT_FUNC	"IoFileMgrForUser",0xE8BC6571,sceIoCancel
#endif
