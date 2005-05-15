	.set noreorder

#include "common.s"

	STUB_START	"LoadExecForUser",0x40010000,0x20005
	STUB_FUNC	0x5572A5F,sceKernelExitGame
	STUB_FUNC	0x4AC57943,sceKernelRegisterExitCallback
	STUB_END

