	.set noreorder

#include "pspstub.s"

	STUB_START	"sceImpose_driver",0x00010011,0x00170005
	STUB_FUNC	0x0F341BE4,sceImposeGetHomePopup
	STUB_FUNC	0x116CFF64,sceImposeCheckVideoOut
	STUB_FUNC	0x116DDED6,sceImposeSetVideoOutMode
	STUB_FUNC	0x1AEED8FE,sceImposeSuspend
	STUB_FUNC	0x1B6E3400,sceImposeGetStatus
	STUB_FUNC	0x24FD7BCF,sceImposeGetLanguageMode
	STUB_FUNC	0x36AA6E91,sceImposeSetLanguageMode
	STUB_FUNC	0x381BD9E7,sceImposeHomeButton
	STUB_FUNC	0x531C9778,sceImposeGetParam
	STUB_FUNC	0x5595A71A,sceImposeSetHomePopup
	STUB_FUNC	0x7084E72C,sceImpose_driver_7084E72C
	STUB_FUNC	0x72189C48,sceImposeSetUMDPopup
	STUB_FUNC	0x810FB7FB,sceImposeSetParam
	STUB_FUNC	0x86924032,sceImposeResume
	STUB_FUNC	0x8C943191,sceImposeGetBatteryIconStatus
	STUB_FUNC	0x8F6E3518,sceImposeGetBacklightOffTime
	STUB_FUNC	0x967F6D4A,sceImposeSetBacklightOffTime
	STUB_FUNC	0x9C8C6C81,sceImposeSetStatus
	STUB_FUNC	0x9DBCE0C4,sceImpose_driver_9DBCE0C4
	STUB_FUNC	0xB415FC59,sceImposeChanges
	STUB_FUNC	0xBDBC42A6,sceImposeInit
	STUB_FUNC	0xC7E36CC7,sceImposeEnd
	STUB_FUNC	0xE0887BC8,sceImposeGetUMDPopup
	STUB_END
