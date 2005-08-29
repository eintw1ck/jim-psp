	.set noreorder

#include "pspimport.s"

#ifdef F_stub_Kernel_Library
	IMPORT_START	"Kernel_Library",0x00010000
#endif
#ifdef F_00000000_sceKernelCpuSuspendIntr
	IMPORT_FUNC	"Kernel_Library",0x092968F4,sceKernelCpuSuspendIntr
#endif
#ifdef F_00000001_sceKernelCpuResumeIntr
	IMPORT_FUNC	"Kernel_Library",0x5F10D406,sceKernelCpuResumeIntr
#endif
#ifdef F_00000002_sceKernelCpuResumeIntrWithSync
	IMPORT_FUNC	"Kernel_Library",0x3B84732D,sceKernelCpuResumeIntrWithSync
#endif
#ifdef F_00000003_sceKernelIsCpuIntrSuspended
	IMPORT_FUNC	"Kernel_Library",0x47A0B729,sceKernelIsCpuIntrSuspended
#endif
#ifdef F_00000004_sceKernelIsCpuIntrEnable
	IMPORT_FUNC	"Kernel_Library",0xB55249D2,sceKernelIsCpuIntrEnable
#endif
