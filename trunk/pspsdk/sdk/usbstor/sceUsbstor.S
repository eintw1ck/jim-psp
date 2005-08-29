	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceUsbstor
	IMPORT_START	"sceUsbstor",0x40090000
#endif
#ifdef F_00000000_sceUsbstorGetStatus
	IMPORT_FUNC	"sceUsbstor",0x60066CFE,sceUsbstorGetStatus
#endif
