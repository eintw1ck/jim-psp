	.set noreorder

#include "common.s"

	STUB_START	"LoadExecForUser",0x40010000,0x00040005
	STUB_FUNC	0xBD2F1094,sceKernelLoadExec
	STUB_FUNC	0x2AC9954B,sceKernelExitGameWithStatus
	STUB_FUNC	0x05572A5F,sceKernelExitGame
	STUB_FUNC	0x4AC57943,sceKernelRegisterExitCallback
	STUB_END
