	.set noreorder

#include "pspimport.s"

#ifdef F_stub_LoadCoreForKernel
	IMPORT_START	"LoadCoreForKernel",0x00010000
#endif
#ifdef F_00000000_sceKernelCheckPspConfig
	IMPORT_FUNC	"LoadCoreForKernel",0xACE23476,sceKernelCheckPspConfig
#endif
#ifdef F_00000001_sceKernelCheckExecFile
	IMPORT_FUNC	"LoadCoreForKernel",0x7BE1421C,sceKernelCheckExecFile
#endif
#ifdef F_00000002_sceKernelProbeExecutableObject
	IMPORT_FUNC	"LoadCoreForKernel",0xBF983EF2,sceKernelProbeExecutableObject
#endif
#ifdef F_00000003_sceKernelLoadExecutableObject
	IMPORT_FUNC	"LoadCoreForKernel",0x7068E6BA,sceKernelLoadExecutableObject
#endif
#ifdef F_00000004_sceKernelApplyElfRelSection
	IMPORT_FUNC	"LoadCoreForKernel",0xB4D6FECC,sceKernelApplyElfRelSection
#endif
#ifdef F_00000005_LoadCoreForKernel_54AB2675
	IMPORT_FUNC	"LoadCoreForKernel",0x54AB2675,LoadCoreForKernel_54AB2675
#endif
#ifdef F_00000006_sceKernelDcacheWBinvAll
	IMPORT_FUNC	"LoadCoreForKernel",0x2952F5AC,sceKernelDcacheWBinvAll
#endif
#ifdef F_00000007_sceKernelIcacheClearAll
	IMPORT_FUNC	"LoadCoreForKernel",0xD8779AC6,sceKernelIcacheClearAll
#endif
#ifdef F_00000008_sceKernelRegisterLibrary
	IMPORT_FUNC	"LoadCoreForKernel",0x99A695F0,sceKernelRegisterLibrary
#endif
#ifdef F_00000009_sceKernelRegisterLibraryForUser
	IMPORT_FUNC	"LoadCoreForKernel",0x5873A31F,sceKernelRegisterLibraryForUser
#endif
#ifdef F_0000000A_sceKernelReleaseLibrary
	IMPORT_FUNC	"LoadCoreForKernel",0x0B464512,sceKernelReleaseLibrary
#endif
#ifdef F_0000000B_sceKernelCanReleaseLibrary
	IMPORT_FUNC	"LoadCoreForKernel",0x9BAF90F6,sceKernelCanReleaseLibrary
#endif
#ifdef F_0000000C_sceKernelLinkLibraryEntries
	IMPORT_FUNC	"LoadCoreForKernel",0x0E760DBA,sceKernelLinkLibraryEntries
#endif
#ifdef F_0000000D_sceKernelLinkLibraryEntriesForUser
	IMPORT_FUNC	"LoadCoreForKernel",0x0DE1F600,sceKernelLinkLibraryEntriesForUser
#endif
#ifdef F_0000000E_sceKernelUnLinkLibraryEntries
	IMPORT_FUNC	"LoadCoreForKernel",0xDA1B09AA,sceKernelUnLinkLibraryEntries
#endif
#ifdef F_0000000F_sceKernelQueryLoadCoreCB
	IMPORT_FUNC	"LoadCoreForKernel",0xC99DD47A,sceKernelQueryLoadCoreCB
#endif
#ifdef F_00000010_LoadCoreForKernel_616FCCCD
	IMPORT_FUNC	"LoadCoreForKernel",0x616FCCCD,LoadCoreForKernel_616FCCCD
#endif
#ifdef F_00000011_sceKernelModuleFromUID
	IMPORT_FUNC	"LoadCoreForKernel",0xF32A2940,sceKernelModuleFromUID
#endif
#ifdef F_00000012_sceKernelCreateModule
	IMPORT_FUNC	"LoadCoreForKernel",0xCD0F3BAC,sceKernelCreateModule
#endif
#ifdef F_00000013_sceKernelDeleteModule
	IMPORT_FUNC	"LoadCoreForKernel",0x6B2371C2,sceKernelDeleteModule
#endif
#ifdef F_00000014_sceKernelModuleAssign
	IMPORT_FUNC	"LoadCoreForKernel",0x7320D964,sceKernelModuleAssign
#endif
#ifdef F_00000015_sceKernelAllocModule
	IMPORT_FUNC	"LoadCoreForKernel",0x44B292AB,sceKernelAllocModule
#endif
#ifdef F_00000016_sceKernelFreeModule
	IMPORT_FUNC	"LoadCoreForKernel",0xBD61D4D5,sceKernelFreeModule
#endif
#ifdef F_00000017_sceKernelRegisterModule
	IMPORT_FUNC	"LoadCoreForKernel",0xAE7C6E76,sceKernelRegisterModule
#endif
#ifdef F_00000018_sceKernelReleaseModule
	IMPORT_FUNC	"LoadCoreForKernel",0x74CF001A,sceKernelReleaseModule
#endif
#ifdef F_00000019_sceKernelFindModuleByName
	IMPORT_FUNC	"LoadCoreForKernel",0xCF8A41B1,sceKernelFindModuleByName
#endif
#ifdef F_0000001A_sceKernelFindModuleByAddress
	IMPORT_FUNC	"LoadCoreForKernel",0xFB8AE27D,sceKernelFindModuleByAddress
#endif
#ifdef F_0000001B_sceKernelFindModuleByUID
	IMPORT_FUNC	"LoadCoreForKernel",0xCCE4A157,sceKernelFindModuleByUID
#endif
#ifdef F_0000001C_sceKernelModuleCount
	IMPORT_FUNC	"LoadCoreForKernel",0x82CE54ED,sceKernelModuleCount
#endif
#ifdef F_0000001D_sceKernelGetModuleList
	IMPORT_FUNC	"LoadCoreForKernel",0xC0584F0C,sceKernelGetModuleList
#endif
