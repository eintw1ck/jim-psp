	.set noreorder

#include "common.s"

	STUB_START	"IoFileMgrForKernel",0x00010000,0x00050005
	STUB_FUNC	0xa905b705, sceIoCloseAll
	STUB_FUNC	0x411106BA, sceIoGetThreadCwd
	STUB_FUNC	0xCB0A151F, sceIoChangeThreadCwd
	STUB_FUNC	0x8E982A74, sceIoAddDrv
	STUB_FUNC	0xC7F35804, sceIoDelDrv
	STUB_FUNC	0x3C54E908, sceIoReopen
	STUB_END

