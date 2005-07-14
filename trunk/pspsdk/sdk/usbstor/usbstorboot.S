	.set noreorder

#include "common.s"

	STUB_START	"sceUsbstorBoot",0x90000,0x00060005
	STUB_FUNC	0xe58818a8,sceUsbstorBootSetCapacity
	STUB_FUNC	0x594bbf95,sceUsbstorBootSetLoadAddr
	STUB_FUNC	0x6d865ecd,sceUsbstorBootGetDataSize
	STUB_FUNC	0xa1119f0d,sceUsbstorBootSetStatus
	STUB_FUNC	0x1f080078,sceUsbstorBootRegisterNotify
	STUB_FUNC	0xa55c9e16,sceUsbstorBootUnregisterNotify
	STUB_END
