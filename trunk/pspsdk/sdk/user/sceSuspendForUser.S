	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceSuspendForUser
	IMPORT_START	"sceSuspendForUser",0x40000000
#endif
#ifdef F_00000000_sceKernelPowerLock
	IMPORT_FUNC	"sceSuspendForUser",0xEADB1BD7,sceKernelPowerLock
#endif
#ifdef F_00000001_sceKernelPowerUnlock
	IMPORT_FUNC	"sceSuspendForUser",0x3AEE7261,sceKernelPowerUnlock
#endif
#ifdef F_00000002_sceKernelPowerTick
	IMPORT_FUNC	"sceSuspendForUser",0x090CCB3F,sceKernelPowerTick
#endif
