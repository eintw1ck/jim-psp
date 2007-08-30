	.set noreorder

#include "pspstub.s"

	STUB_START	"sceImpose",0x40010011,0x000F0005
	STUB_FUNC	0x0F341BE4,sceImposeGetHomePopup
	STUB_FUNC	0x24FD7BCF,sceImposeGetLanguageMode
	STUB_FUNC	0x36AA6E91,sceImposeSetLanguageMode
	STUB_FUNC	0x381BD9E7,sceImposeHomeButton
	STUB_FUNC	0x5595A71A,sceImposeSetHomePopup
	STUB_FUNC	0x72189C48,sceImposeSetUMDPopup
	STUB_FUNC	0x8C943191,sceImposeGetBatteryIconStatus
	STUB_FUNC	0x8F6E3518,sceImposeGetBacklightOffTime
	STUB_FUNC	0x967F6D4A,sceImposeSetBacklightOffTime
	STUB_FUNC	0x9BA61B49,sceImpose_9BA61B49
	STUB_FUNC	0xA9884B00,sceImpose_A9884B00
	STUB_FUNC	0xBB3F5DEC,sceImpose_BB3F5DEC
	STUB_FUNC	0xE0887BC8,sceImposeGetUMDPopup
	STUB_FUNC	0xFCD44963,sceImpose_FCD44963
	STUB_FUNC	0xFF1A2F07,sceImpose_FF1A2F07
	STUB_END
