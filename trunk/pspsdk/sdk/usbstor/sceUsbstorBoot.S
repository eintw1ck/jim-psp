	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceUsbstorBoot
	IMPORT_START	"sceUsbstorBoot",0x40090000
#endif
#ifdef F_00000000_sceUsbstorBootSetCapacity
	IMPORT_FUNC	"sceUsbstorBoot",0xE58818A8,sceUsbstorBootSetCapacity
#endif
#ifdef F_00000001_sceUsbstorBootSetLoadAddr
	IMPORT_FUNC	"sceUsbstorBoot",0x594BBF95,sceUsbstorBootSetLoadAddr
#endif
#ifdef F_00000002_sceUsbstorBootGetDataSize
	IMPORT_FUNC	"sceUsbstorBoot",0x6D865ECD,sceUsbstorBootGetDataSize
#endif
#ifdef F_00000003_sceUsbstorBootSetStatus
	IMPORT_FUNC	"sceUsbstorBoot",0xA1119F0D,sceUsbstorBootSetStatus
#endif
#ifdef F_00000004_sceUsbstorBootRegisterNotify
	IMPORT_FUNC	"sceUsbstorBoot",0x1F080078,sceUsbstorBootRegisterNotify
#endif
#ifdef F_00000005_sceUsbstorBootUnregisterNotify
	IMPORT_FUNC	"sceUsbstorBoot",0xA55C9E16,sceUsbstorBootUnregisterNotify
#endif
