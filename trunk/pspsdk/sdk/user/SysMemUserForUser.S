	.set noreorder

#include "pspimport.s"

#ifdef F_stub_SysMemUserForUser
	IMPORT_START	"SysMemUserForUser",0x40000000
#endif
#ifdef F_00000000_sceKernelMaxFreeMemSize
	IMPORT_FUNC	"SysMemUserForUser",0xA291F107,sceKernelMaxFreeMemSize
#endif
#ifdef F_00000001_sceKernelTotalFreeMemSize
	IMPORT_FUNC	"SysMemUserForUser",0xF919F628,sceKernelTotalFreeMemSize
#endif
#ifdef F_00000002_sceKernelAllocPartitionMemory
	IMPORT_FUNC	"SysMemUserForUser",0x237DBD4F,sceKernelAllocPartitionMemory
#endif
#ifdef F_00000003_sceKernelFreePartitionMemory
	IMPORT_FUNC	"SysMemUserForUser",0xB6D61D02,sceKernelFreePartitionMemory
#endif
#ifdef F_00000004_sceKernelGetBlockHeadAddr
	IMPORT_FUNC	"SysMemUserForUser",0x9D9A5BA1,sceKernelGetBlockHeadAddr
#endif
#ifdef F_00000005_sceKernelDevkitVersion
	IMPORT_FUNC	"SysMemUserForUser",0x3FC9AE6A,sceKernelDevkitVersion
#endif
