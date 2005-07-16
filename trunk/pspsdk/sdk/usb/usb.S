	.set noreorder

#include "pspstub.s"

	STUB_START	"sceUsb",0x40010000,0x00090005
	STUB_FUNC	0xae5de6af,sceUsbStart
	STUB_FUNC	0xc2464fa0,sceUsbStop
	STUB_FUNC	0xc21645a4,sceUsbGetState
	STUB_FUNC	0x4e537366,sceUsbGetDrvList
	STUB_FUNC	0x112cc951,sceUsbGetDrvState
	STUB_FUNC	0x586db82c,sceUsbActivate
	STUB_FUNC	0xc572a9c8,sceUsbDeactivate
	STUB_FUNC	0x5be0e002,sceUsbWaitState
	STUB_FUNC	0x1c360735,sceUsbWaitCancel
	STUB_END
