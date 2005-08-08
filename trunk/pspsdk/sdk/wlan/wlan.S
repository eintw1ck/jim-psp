	.set noreorder

#include "pspstub.s"

	STUB_START	"sceWlanDrv",0x40010000,0x00040005
	STUB_FUNC	0x93440b11,sceWlanDevIsPowerOn
	STUB_FUNC	0x93440b11,sceWlanGPBindRegError
	STUB_FUNC	0xd7763699,sceWlanGetSwitchState
	STUB_FUNC	0x0c622081,sceWlanGetEtherAddr
	STUB_END 