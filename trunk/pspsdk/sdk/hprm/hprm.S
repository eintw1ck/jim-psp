	.set noreorder

#include "common.s"

	STUB_START	"sceHprm",0x40010000,0x00090005 
	STUB_FUNC	0x1c5bc5a0,sceHprmInit
	STUB_FUNC	0x588845da,sceHprmEnd
	STUB_FUNC	0x526bb7f4,sceHprmSuspend
	STUB_FUNC	0x2c7b8b05,sceHprmResume
	STUB_FUNC	0xd222913db,sceHprmSetConnectCallback
	STUB_FUNC	0xc7154136,sceHprmRegisterCallback
	STUB_FUNC	0x4d1e622c,sceHprmReset
	STUB_FUNC	0x7b038474,sceHprmGetInternalState
	STUB_FUNC	0xbad0828e,sceHprmGetModel
	STUB_FUNC	0x1910b327,sceHprmPeekCurrentKey
	STUB_FUNC	0x2bcec83e,sceHprmPeekLatch
	STUB_FUNC	0x40d2f9f0,sceHprmReadLatch
	STUB_END
