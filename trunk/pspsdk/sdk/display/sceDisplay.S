	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceDisplay
	IMPORT_START	"sceDisplay",0x40010000
#endif
#ifdef F_00000000_sceDisplaySetMode
	IMPORT_FUNC	"sceDisplay",0x0E20F177,sceDisplaySetMode
#endif
#ifdef F_00000001_sceDisplayGetMode
	IMPORT_FUNC	"sceDisplay",0xDEA197D4,sceDisplayGetMode
#endif
#ifdef F_00000002_sceDisplayGetFramePerSec
	IMPORT_FUNC	"sceDisplay",0xDBA6C4C4,sceDisplayGetFramePerSec
#endif
#ifdef F_00000003_sceDisplaySetHoldMode
	IMPORT_FUNC	"sceDisplay",0x7ED59BC4,sceDisplaySetHoldMode
#endif
#ifdef F_00000004_sceDisplaySetResumeMode
	IMPORT_FUNC	"sceDisplay",0xA544C486,sceDisplaySetResumeMode
#endif
#ifdef F_00000005_sceDisplaySetFrameBuf
	IMPORT_FUNC	"sceDisplay",0x289D82FE,sceDisplaySetFrameBuf
#endif
#ifdef F_00000006_sceDisplayGetFrameBuf
	IMPORT_FUNC	"sceDisplay",0xEEDA2E54,sceDisplayGetFrameBuf
#endif
#ifdef F_00000007_sceDisplayIsForeground
	IMPORT_FUNC	"sceDisplay",0xB4F378FA,sceDisplayIsForeground
#endif
#ifdef F_00000008_sceDisplay_31C4BAA8
	IMPORT_FUNC	"sceDisplay",0x31C4BAA8,sceDisplay_31C4BAA8
#endif
#ifdef F_00000009_sceDisplayGetVcount
	IMPORT_FUNC	"sceDisplay",0x9C6EAAD7,sceDisplayGetVcount
#endif
#ifdef F_0000000A_sceDisplayIsVblank
	IMPORT_FUNC	"sceDisplay",0x4D4E10EC,sceDisplayIsVblank
#endif
#ifdef F_0000000B_sceDisplayWaitVblank
	IMPORT_FUNC	"sceDisplay",0x36CDFADE,sceDisplayWaitVblank
#endif
#ifdef F_0000000C_sceDisplayWaitVblankCB
	IMPORT_FUNC	"sceDisplay",0x8EB9EC49,sceDisplayWaitVblankCB
#endif
#ifdef F_0000000D_sceDisplayWaitVblankStart
	IMPORT_FUNC	"sceDisplay",0x984C27E7,sceDisplayWaitVblankStart
#endif
#ifdef F_0000000E_sceDisplayWaitVblankStartCB
	IMPORT_FUNC	"sceDisplay",0x46F186C3,sceDisplayWaitVblankStartCB
#endif
#ifdef F_0000000F_sceDisplayGetCurrentHcount
	IMPORT_FUNC	"sceDisplay",0x773DD3A3,sceDisplayGetCurrentHcount
#endif
#ifdef F_00000010_sceDisplayGetAccumulatedHcount
	IMPORT_FUNC	"sceDisplay",0x210EAB3A,sceDisplayGetAccumulatedHcount
#endif
