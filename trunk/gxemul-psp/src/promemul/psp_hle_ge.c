#include "psp_hle.h"

SYSCALL(0x20e5,0x1f6752ad,0x00000000,"sceGeEdramGetSize",HLE_unknown,4);
SYSCALL(0x20e6,0xe47e40e4,0x00000000,"sceGeEdramGetAddr",HLE_sceGeEdramGetAddr,0);
SYSCALL(0x20e7,0xb77905ea,0x00000000,"sceGeEdramSetAddrTranslation",HLE_unknown,4);
SYSCALL(0x20e8,0xdc93cfef,0x00000000,"sceGeGetCmd",HLE_unknown,4);
SYSCALL(0x20e9,0x57c8945b,0x00000000,"sceGeGetMtx",HLE_unknown,4);
SYSCALL(0x20ea,0x438a385a,0x00000000,"sceGeSaveContext",HLE_unknown,4);
SYSCALL(0x20eb,0x0bf608fb,0x00000000,"sceGeRestoreContext",HLE_unknown,4);
SYSCALL(0x20ec,0xab49e76a,0x00000000,"sceGeListEnQueue",HLE_unknown,4);
SYSCALL(0x20ed,0x1c0d95a6,0x00000000,"sceGeListEnQueueHead",HLE_unknown,4);
SYSCALL(0x20ee,0x5fb86ab0,0x00000000,"sceGeListDeQueue",HLE_unknown,4);
SYSCALL(0x20ef,0xe0d68148,0x00000000,"sceGeListUpdateStallAddr",HLE_unknown,4);
SYSCALL(0x20f0,0x03444eb4,0x00000000,"sceGeListSync",HLE_unknown,4);
SYSCALL(0x20f1,0xb287bd61,0x00000000,"sceGeDrawSync",HLE_unknown,4);
SYSCALL(0x20f2,0xb448ec0d,0x00000000,"sceGeBreak",HLE_unknown,4);
SYSCALL(0x20f3,0x4c06e472,0x00000000,"sceGeContinue",HLE_unknown,4);
SYSCALL(0x20f4,0xa4fc06a4,0x00000000,"sceGeSetCallback",HLE_unknown,4);
SYSCALL(0x20f5,0x05db22ce,0x00000000,"sceGeUnsetCallback",HLE_unknown,4);

void HLE_sceGeEdramGetAddr(void)
{
	debug("HLE_sceGeEdramGetAddr() ");

	HLE_RETURN_INT(0x04000000);
}
 
