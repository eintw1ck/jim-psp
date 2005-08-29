	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceGe_user
	IMPORT_START	"sceGe_user",0x40010000
#endif
#ifdef F_00000000_sceGeEdramGetSize
	IMPORT_FUNC	"sceGe_user",0x1F6752AD,sceGeEdramGetSize
#endif
#ifdef F_00000001_sceGeEdramGetAddr
	IMPORT_FUNC	"sceGe_user",0xE47E40E4,sceGeEdramGetAddr
#endif
#ifdef F_00000002_sceGeEdramSetAddrTranslation
	IMPORT_FUNC	"sceGe_user",0xB77905EA,sceGeEdramSetAddrTranslation
#endif
#ifdef F_00000003_sceGeGetCmd
	IMPORT_FUNC	"sceGe_user",0xDC93CFEF,sceGeGetCmd
#endif
#ifdef F_00000004_sceGeGetMtx
	IMPORT_FUNC	"sceGe_user",0x57C8945B,sceGeGetMtx
#endif
#ifdef F_00000005_sceGeSaveContext
	IMPORT_FUNC	"sceGe_user",0x438A385A,sceGeSaveContext
#endif
#ifdef F_00000006_sceGeRestoreContext
	IMPORT_FUNC	"sceGe_user",0x0BF608FB,sceGeRestoreContext
#endif
#ifdef F_00000007_sceGeListEnQueue
	IMPORT_FUNC	"sceGe_user",0xAB49E76A,sceGeListEnQueue
#endif
#ifdef F_00000008_sceGeListEnQueueHead
	IMPORT_FUNC	"sceGe_user",0x1C0D95A6,sceGeListEnQueueHead
#endif
#ifdef F_00000009_sceGeListDeQueue
	IMPORT_FUNC	"sceGe_user",0x5FB86AB0,sceGeListDeQueue
#endif
#ifdef F_0000000A_sceGeListUpdateStallAddr
	IMPORT_FUNC	"sceGe_user",0xE0D68148,sceGeListUpdateStallAddr
#endif
#ifdef F_0000000B_sceGeListSync
	IMPORT_FUNC	"sceGe_user",0x03444EB4,sceGeListSync
#endif
#ifdef F_0000000C_sceGeDrawSync
	IMPORT_FUNC	"sceGe_user",0xB287BD61,sceGeDrawSync
#endif
#ifdef F_0000000D_sceGeBreak
	IMPORT_FUNC	"sceGe_user",0xB448EC0D,sceGeBreak
#endif
#ifdef F_0000000E_sceGeContinue
	IMPORT_FUNC	"sceGe_user",0x4C06E472,sceGeContinue
#endif
#ifdef F_0000000F_sceGeSetCallback
	IMPORT_FUNC	"sceGe_user",0xA4FC06A4,sceGeSetCallback
#endif
#ifdef F_00000010_sceGeUnsetCallback
	IMPORT_FUNC	"sceGe_user",0x05DB22CE,sceGeUnsetCallback
#endif
