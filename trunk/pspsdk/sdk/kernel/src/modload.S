	.set noreorder

#include "common.s"

	STUB_START	"ModuleMgrForUser",0x40010000,0x00060005
	STUB_FUNC	0xd675ebb8,sceKernelSelfUnloadModule
	STUB_FUNC	0x977de386,sceKernelLoadModule
	STUB_FUNC	0x50f0c1ec,sceKernelStartModule
	STUB_FUNC	0xD1FF982A,sceKernelStopModule
	STUB_FUNC	0x2E0911AA,sceKernelUnloadModule
	STUB_FUNC	0x710F61B5,sceKernelLoadModuleMs
	STUB_END
