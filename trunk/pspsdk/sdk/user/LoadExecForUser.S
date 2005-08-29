	.set noreorder

#include "pspimport.s"

#ifdef F_stub_LoadExecForUser
	IMPORT_START	"LoadExecForUser",0x40010000
#endif
#ifdef F_00000000_sceKernelLoadExec
	IMPORT_FUNC	"LoadExecForUser",0xBD2F1094,sceKernelLoadExec
#endif
#ifdef F_00000001_sceKernelExitGameWithStatus
	IMPORT_FUNC	"LoadExecForUser",0x2AC9954B,sceKernelExitGameWithStatus
#endif
#ifdef F_00000002_sceKernelExitGame
	IMPORT_FUNC	"LoadExecForUser",0x05572A5F,sceKernelExitGame
#endif
#ifdef F_00000003_sceKernelRegisterExitCallback
	IMPORT_FUNC	"LoadExecForUser",0x4AC57943,sceKernelRegisterExitCallback
#endif
