	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceWlanDrv
	IMPORT_START	"sceWlanDrv",0x40010000
#endif
#ifdef F_00000000_sceWlanDevIsPowerOn
	IMPORT_FUNC	"sceWlanDrv",0x93440B11,sceWlanDevIsPowerOn
#endif
#ifdef F_00000001_sceWlanGetSwitchState
	IMPORT_FUNC	"sceWlanDrv",0xD7763699,sceWlanGetSwitchState
#endif
#ifdef F_00000002_sceWlanGetEtherAddr
	IMPORT_FUNC	"sceWlanDrv",0x0C622081,sceWlanGetEtherAddr
#endif
