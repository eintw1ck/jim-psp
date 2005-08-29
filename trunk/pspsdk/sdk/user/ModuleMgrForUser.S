	.set noreorder

#include "pspimport.s"

#ifdef F_stub_ModuleMgrForUser
	IMPORT_START	"ModuleMgrForUser",0x40010000
#endif
#ifdef F_00000000_sceKernelLoadModuleByID
	IMPORT_FUNC	"ModuleMgrForUser",0xB7F46618,sceKernelLoadModuleByID
#endif
#ifdef F_00000001_sceKernelLoadModule
	IMPORT_FUNC	"ModuleMgrForUser",0x977DE386,sceKernelLoadModule
#endif
#ifdef F_00000002_sceKernelLoadModuleMs
	IMPORT_FUNC	"ModuleMgrForUser",0x710F61B5,sceKernelLoadModuleMs
#endif
#ifdef F_00000003_sceKernelLoadModuleBufferUsbWlan
	IMPORT_FUNC	"ModuleMgrForUser",0xF9275D98,sceKernelLoadModuleBufferUsbWlan
#endif
#ifdef F_00000004_sceKernelStartModule
	IMPORT_FUNC	"ModuleMgrForUser",0x50F0C1EC,sceKernelStartModule
#endif
#ifdef F_00000005_sceKernelStopModule
	IMPORT_FUNC	"ModuleMgrForUser",0xD1FF982A,sceKernelStopModule
#endif
#ifdef F_00000006_sceKernelUnloadModule
	IMPORT_FUNC	"ModuleMgrForUser",0x2E0911AA,sceKernelUnloadModule
#endif
#ifdef F_00000007_sceKernelSelfStopUnloadModule
	IMPORT_FUNC	"ModuleMgrForUser",0xD675EBB8,sceKernelSelfStopUnloadModule
#endif
#ifdef F_00000008_sceKernelStopUnloadSelfModule
	IMPORT_FUNC	"ModuleMgrForUser",0xCC1D3699,sceKernelStopUnloadSelfModule
#endif
#ifdef F_00000009_sceKernelQueryModuleInfo
	IMPORT_FUNC	"ModuleMgrForUser",0x748CBED9,sceKernelQueryModuleInfo
#endif
