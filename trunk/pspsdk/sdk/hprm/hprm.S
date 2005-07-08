	.set noreorder

#include "common.s"

	STUB_START	"sceHprm",0x40010000,0x00080005
	STUB_FUNC	0xC7154136,sceHprmRegisterCallback
	STUB_FUNC	0x444ED0B7,sceHprmUnregisterCallback
	STUB_FUNC	0x208DB1BD,sceHprmIsRemoteExist
	STUB_FUNC	0x7E69EDA4,sceHprmIsHeadphoneExist
	STUB_FUNC	0x219C58F1,sceHprm_219C58F1
	STUB_FUNC	0x1910B327,sceHprmPeekCurrentKey
	STUB_FUNC	0x2BCEC83E,sceHprmPeekLatch
	STUB_FUNC	0x40D2F9F0,sceHprmReadLatch
	STUB_END
