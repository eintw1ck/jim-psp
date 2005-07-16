	.set noreorder

#include "pspstub.s"

	STUB_START	"sceUsbstor",0x90000,0x00010005
	STUB_FUNC	0x60066cfe,sceUsbstorGetStatus
	STUB_END
