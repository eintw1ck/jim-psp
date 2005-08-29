	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceHprm
	IMPORT_START	"sceHprm",0x40010000
#endif
#ifdef F_00000000_sceHprmRegisterCallback
	IMPORT_FUNC	"sceHprm",0xC7154136,sceHprmRegisterCallback
#endif
#ifdef F_00000001_sceHprmUnregisterCallback
	IMPORT_FUNC	"sceHprm",0x444ED0B7,sceHprmUnregisterCallback
#endif
#ifdef F_00000002_sceHprmIsRemoteExist
	IMPORT_FUNC	"sceHprm",0x208DB1BD,sceHprmIsRemoteExist
#endif
#ifdef F_00000003_sceHprmIsHeadphoneExist
	IMPORT_FUNC	"sceHprm",0x7E69EDA4,sceHprmIsHeadphoneExist
#endif
#ifdef F_00000004_sceHprmIsMicrophoneExist
	IMPORT_FUNC	"sceHprm",0x219C58F1,sceHprmIsMicrophoneExist
#endif
#ifdef F_00000005_sceHprmPeekCurrentKey
	IMPORT_FUNC	"sceHprm",0x1910B327,sceHprmPeekCurrentKey
#endif
#ifdef F_00000006_sceHprmPeekLatch
	IMPORT_FUNC	"sceHprm",0x2BCEC83E,sceHprmPeekLatch
#endif
#ifdef F_00000007_sceHprmReadLatch
	IMPORT_FUNC	"sceHprm",0x40D2F9F0,sceHprmReadLatch
#endif
