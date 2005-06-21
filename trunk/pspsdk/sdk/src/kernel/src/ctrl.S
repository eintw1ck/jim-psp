	.set noreorder

#include "common.s"

	STUB_START	"sceCtrl",0x40010000,0x00030005
	STUB_FUNC   0x6A2774F3,sceCtrlSetSamplingCycle
	STUB_FUNC	0x1f4011e6,sceCtrlSetSamplingMode
	STUB_FUNC   0x1F803938,sceCtrlReadBufferPositive 
	STUB_END
