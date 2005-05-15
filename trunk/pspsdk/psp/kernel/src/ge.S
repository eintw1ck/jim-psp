	.set noreorder
#include "common.s"

	STUB_START	"sceGe_user",0x40010000,0x000a0005
	STUB_FUNC	0xE47E40E4,sceGeEdramGetAddr
	STUB_FUNC	0xAB49E76A,sceGeListEnQueue
	STUB_FUNC	0x1C0D95A6,sceGeListEnQueueHead
	STUB_FUNC	0xE0D68148,sceGeListUpdateStallAddr
	STUB_FUNC	0x3444EB4,sceGeListSync
	STUB_FUNC	0xB287BD61,sceGeDrawSync
	STUB_FUNC	0xB448EC0D,sceGeBreak
	STUB_FUNC	0x4C06E472,sceGeContinue
	STUB_FUNC	0xA4FC06A4,sceGeSetCallback
	STUB_FUNC	0x5DB22CE,sceGeUnsetCallback
	STUB_END
