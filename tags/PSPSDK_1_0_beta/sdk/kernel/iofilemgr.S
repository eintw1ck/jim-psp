	.set noreorder

#include "common.s"

	STUB_START	"IoFileMgrForUser",0x40010000,0x00240005
	STUB_FUNC	0xe95a012b, sceIoIoctlAsync
	STUB_FUNC	0x63632449, sceIoIoctl
	STUB_FUNC	0x54f5fb11, sceIoDevctl
	STUB_FUNC	0x89aa9906, sceIoOpenAsync
	STUB_FUNC	0x109f50bc, sceIoOpen
	STUB_FUNC	0xff5940b6, sceIoCloseAsync
	STUB_FUNC	0x810c4bc3, sceIoClose
	STUB_FUNC	0x71b19e77, sceIoLseekAsync
	STUB_FUNC	0x27eb27b8, sceIoLseek
	STUB_FUNC	0x68963324, sceIoLseek32
	STUB_FUNC	0x1B385D8F, sceIoLseek32Async
	STUB_FUNC	0xa0b5a7c2, sceIoReadAsync
	STUB_FUNC	0x6a638d83, sceIoRead
	STUB_FUNC	0x0facab19, sceIoWriteAsync
	STUB_FUNC	0x42ec03ac, sceIoWrite
	STUB_FUNC	0xb29ddf9c, sceIoDopen
	STUB_FUNC	0xe3eb004c, sceIoDread
	STUB_FUNC	0xeb092469, sceIoDclose
	STUB_FUNC	0xf27a9c51, sceIoRemove
	STUB_FUNC	0x06a70004, sceIoMkdir
	STUB_FUNC	0x1117c65f, sceIoRmdir
	STUB_FUNC	0x55f4717d, sceIoChdir
	STUB_FUNC	0xace946e8, sceIoGetstat
	STUB_FUNC	0x779103a0, sceIoRename
	STUB_FUNC	0xb2a628c1, sceIoAssign
	STUB_FUNC	0x6d08a871, sceIoUnassign
	STUB_FUNC	0xe8bc6571, sceIoCancel
	STUB_FUNC	0xb293727f, sceIoChangeAsyncPriority
	STUB_FUNC	0xcb05f8d6, sceIoGetAsyncStat
	STUB_FUNC	0x08bd7374, sceIoGetDevType
	STUB_FUNC	0x3251ea56, sceIoPollAsync
	STUB_FUNC	0xa12a0514, sceIoSetAsyncCallback
	STUB_FUNC	0xab96437f, sceIoSync
	STUB_FUNC	0x35dbd746, sceIoWaitAsyncCB
	STUB_FUNC	0xe23eec33, sceIoWaitAsync
	STUB_FUNC	0xb8a740f4, sceIoChstat
	STUB_END

