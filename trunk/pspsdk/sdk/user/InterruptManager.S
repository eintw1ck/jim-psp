	.set noreorder

#include "pspimport.s"

#ifdef F_stub_InterruptManager
	IMPORT_START	"InterruptManager",0x40000000
#endif
#ifdef F_00000000_sceKernelRegisterSubIntrHandler
	IMPORT_FUNC	"InterruptManager",0xCA04A2B9,sceKernelRegisterSubIntrHandler
#endif
#ifdef F_00000001_sceKernelReleaseSubIntrHandler
	IMPORT_FUNC	"InterruptManager",0xD61E6961,sceKernelReleaseSubIntrHandler
#endif
#ifdef F_00000002_sceKernelEnableSubIntr
	IMPORT_FUNC	"InterruptManager",0xFB8E22EC,sceKernelEnableSubIntr
#endif
#ifdef F_00000003_sceKernelDisableSubIntr
	IMPORT_FUNC	"InterruptManager",0x8A389411,sceKernelDisableSubIntr
#endif
#ifdef F_00000004_sceKernelSuspendSubIntr
	IMPORT_FUNC	"InterruptManager",0x5CB5A78B,sceKernelSuspendSubIntr
#endif
#ifdef F_00000005_sceKernelResumeSubIntr
	IMPORT_FUNC	"InterruptManager",0x7860E0DC,sceKernelResumeSubIntr
#endif
#ifdef F_00000006_sceKernelIsSubInterruptOccurred
	IMPORT_FUNC	"InterruptManager",0xFC4374B8,sceKernelIsSubInterruptOccurred
#endif
#ifdef F_00000007_QueryIntrHandlerInfo
	IMPORT_FUNC	"InterruptManager",0xD2E8363F,QueryIntrHandlerInfo
#endif
#ifdef F_00000008_sceKernelRegisterUserSpaceIntrStack
	IMPORT_FUNC	"InterruptManager",0xEEE43F47,sceKernelRegisterUserSpaceIntrStack
#endif
