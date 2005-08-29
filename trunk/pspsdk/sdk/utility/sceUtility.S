	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceUtility
	IMPORT_START	"sceUtility",0x40010000
#endif
#ifdef F_00000000_sceUtilityGameSharingInitStart
	IMPORT_FUNC	"sceUtility",0xC492F751,sceUtilityGameSharingInitStart
#endif
#ifdef F_00000001_sceUtilityGameSharingShutdownStart
	IMPORT_FUNC	"sceUtility",0xEFC6F80F,sceUtilityGameSharingShutdownStart
#endif
#ifdef F_00000002_sceUtilityGameSharingUpdate
	IMPORT_FUNC	"sceUtility",0x7853182D,sceUtilityGameSharingUpdate
#endif
#ifdef F_00000003_sceUtilityGameSharingGetStatus
	IMPORT_FUNC	"sceUtility",0x946963F3,sceUtilityGameSharingGetStatus
#endif
#ifdef F_00000004_sceNetplayDialogInitStart
	IMPORT_FUNC	"sceUtility",0x3AD50AE7,sceNetplayDialogInitStart
#endif
#ifdef F_00000005_sceNetplayDialogShutdownStart
	IMPORT_FUNC	"sceUtility",0xBC6B6296,sceNetplayDialogShutdownStart
#endif
#ifdef F_00000006_sceNetplayDialogUpdate
	IMPORT_FUNC	"sceUtility",0x417BED54,sceNetplayDialogUpdate
#endif
#ifdef F_00000007_sceNetplayDialogGetStatus
	IMPORT_FUNC	"sceUtility",0xB6CEE597,sceNetplayDialogGetStatus
#endif
#ifdef F_00000008_sceUtilityNetconfInitStart
	IMPORT_FUNC	"sceUtility",0x4DB1E739,sceUtilityNetconfInitStart
#endif
#ifdef F_00000009_sceUtilityNetconfShutdownStart
	IMPORT_FUNC	"sceUtility",0xF88155F6,sceUtilityNetconfShutdownStart
#endif
#ifdef F_0000000A_sceUtilityNetconfUpdate
	IMPORT_FUNC	"sceUtility",0x91E70E35,sceUtilityNetconfUpdate
#endif
#ifdef F_0000000B_sceUtilityNetconfGetStatus
	IMPORT_FUNC	"sceUtility",0x6332AA39,sceUtilityNetconfGetStatus
#endif
#ifdef F_0000000C_sceUtilitySavedataInitStart
	IMPORT_FUNC	"sceUtility",0x50C4CD57,sceUtilitySavedataInitStart
#endif
#ifdef F_0000000D_sceUtilitySavedataShutdownStart
	IMPORT_FUNC	"sceUtility",0x9790B33C,sceUtilitySavedataShutdownStart
#endif
#ifdef F_0000000E_sceUtilitySavedataUpdate
	IMPORT_FUNC	"sceUtility",0xD4B95FFB,sceUtilitySavedataUpdate
#endif
#ifdef F_0000000F_sceUtilitySavedataGetStatus
	IMPORT_FUNC	"sceUtility",0x8874DBE0,sceUtilitySavedataGetStatus
#endif
#ifdef F_00000010_sceUtility_2995D020
	IMPORT_FUNC	"sceUtility",0x2995D020,sceUtility_2995D020
#endif
#ifdef F_00000011_sceUtility_B62A4061
	IMPORT_FUNC	"sceUtility",0xB62A4061,sceUtility_B62A4061
#endif
#ifdef F_00000012_sceUtility_ED0FAD38
	IMPORT_FUNC	"sceUtility",0xED0FAD38,sceUtility_ED0FAD38
#endif
#ifdef F_00000013_sceUtility_88BC7406
	IMPORT_FUNC	"sceUtility",0x88BC7406,sceUtility_88BC7406
#endif
#ifdef F_00000014_sceUtilityMsgDialogInitStart
	IMPORT_FUNC	"sceUtility",0x2AD8E239,sceUtilityMsgDialogInitStart
#endif
#ifdef F_00000015_sceUtilityMsgDialogShutdownStart
	IMPORT_FUNC	"sceUtility",0x67AF3428,sceUtilityMsgDialogShutdownStart
#endif
#ifdef F_00000016_sceUtilityMsgDialogUpdate
	IMPORT_FUNC	"sceUtility",0x95FC253B,sceUtilityMsgDialogUpdate
#endif
#ifdef F_00000017_sceUtilityMsgDialogGetStatus
	IMPORT_FUNC	"sceUtility",0x9A1C91D7,sceUtilityMsgDialogGetStatus
#endif
#ifdef F_00000018_sceUtilityOskInitStart
	IMPORT_FUNC	"sceUtility",0xF6269B82,sceUtilityOskInitStart
#endif
#ifdef F_00000019_sceUtilityOskShutdownStart
	IMPORT_FUNC	"sceUtility",0x3DFAEBA9,sceUtilityOskShutdownStart
#endif
#ifdef F_0000001A_sceUtilityOskUpdate
	IMPORT_FUNC	"sceUtility",0x4B85C861,sceUtilityOskUpdate
#endif
#ifdef F_0000001B_sceUtilityOskGetStatus
	IMPORT_FUNC	"sceUtility",0xF3F76017,sceUtilityOskGetStatus
#endif
#ifdef F_0000001C_sceUtilitySetSystemParamInt
	IMPORT_FUNC	"sceUtility",0x45C18506,sceUtilitySetSystemParamInt
#endif
#ifdef F_0000001D_sceUtilitySetSystemParamString
	IMPORT_FUNC	"sceUtility",0x41E30674,sceUtilitySetSystemParamString
#endif
#ifdef F_0000001E_sceUtilityGetSystemParamInt
	IMPORT_FUNC	"sceUtility",0xA5DA2406,sceUtilityGetSystemParamInt
#endif
#ifdef F_0000001F_sceUtilityGetSystemParamString
	IMPORT_FUNC	"sceUtility",0x34B78343,sceUtilityGetSystemParamString
#endif
#ifdef F_00000020_sceUtilityCheckNetParam
	IMPORT_FUNC	"sceUtility",0x5EEE6548,sceUtilityCheckNetParam
#endif
#ifdef F_00000021_sceUtilityGetNetParam
	IMPORT_FUNC	"sceUtility",0x434D4B3A,sceUtilityGetNetParam
#endif
