	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceCtrl
	IMPORT_START	"sceCtrl",0x40010000
#endif
#ifdef F_00000000_sceCtrlSetSamplingCycle
	IMPORT_FUNC	"sceCtrl",0x6A2774F3,sceCtrlSetSamplingCycle
#endif
#ifdef F_00000001_sceCtrlGetSamplingCycle
	IMPORT_FUNC	"sceCtrl",0x02BAAD91,sceCtrlGetSamplingCycle
#endif
#ifdef F_00000002_sceCtrlSetSamplingMode
	IMPORT_FUNC	"sceCtrl",0x1F4011E6,sceCtrlSetSamplingMode
#endif
#ifdef F_00000003_sceCtrlGetSamplingMode
	IMPORT_FUNC	"sceCtrl",0xDA6B76A1,sceCtrlGetSamplingMode
#endif
#ifdef F_00000004_sceCtrlPeekBufferPositive
	IMPORT_FUNC	"sceCtrl",0x3A622550,sceCtrlPeekBufferPositive
#endif
#ifdef F_00000005_sceCtrlPeekBufferNegative
	IMPORT_FUNC	"sceCtrl",0xC152080A,sceCtrlPeekBufferNegative
#endif
#ifdef F_00000006_sceCtrlReadBufferPositive
	IMPORT_FUNC	"sceCtrl",0x1F803938,sceCtrlReadBufferPositive
#endif
#ifdef F_00000007_sceCtrlReadBufferNegative
	IMPORT_FUNC	"sceCtrl",0x60B81F86,sceCtrlReadBufferNegative
#endif
#ifdef F_00000008_sceCtrlPeekLatch
	IMPORT_FUNC	"sceCtrl",0xB1D0E5CD,sceCtrlPeekLatch
#endif
#ifdef F_00000009_sceCtrlReadLatch
	IMPORT_FUNC	"sceCtrl",0x0B588501,sceCtrlReadLatch
#endif
#ifdef F_0000000A_sceCtrl_348D99D4
	IMPORT_FUNC	"sceCtrl",0x348D99D4,sceCtrl_348D99D4
#endif
#ifdef F_0000000B_sceCtrl_AF5960F3
	IMPORT_FUNC	"sceCtrl",0xAF5960F3,sceCtrl_AF5960F3
#endif
#ifdef F_0000000C_sceCtrl_A68FD260
	IMPORT_FUNC	"sceCtrl",0xA68FD260,sceCtrl_A68FD260
#endif
#ifdef F_0000000D_sceCtrl_6841BE1A
	IMPORT_FUNC	"sceCtrl",0x6841BE1A,sceCtrl_6841BE1A
#endif
