	.set noreorder

#include "pspimport.s"

#ifdef F_sceSuspendForUser_0000
	IMPORT_START	"sceSuspendForUser",0x40000000
#endif
#ifdef F_sceSuspendForUser_0001
	IMPORT_FUNC	"sceSuspendForUser",0xEADB1BD7,sceKernelPowerLock
#endif
#ifdef F_sceSuspendForUser_0002
	IMPORT_FUNC	"sceSuspendForUser",0x3AEE7261,sceKernelPowerUnlock
#endif
#ifdef F_sceSuspendForUser_0003
	IMPORT_FUNC	"sceSuspendForUser",0x090CCB3F,sceKernelPowerTick
#endif
