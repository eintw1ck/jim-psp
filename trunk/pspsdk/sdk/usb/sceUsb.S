	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceUsb
	IMPORT_START	"sceUsb",0x40010000
#endif
#ifdef F_00000000_sceUsbStart
	IMPORT_FUNC	"sceUsb",0xAE5DE6AF,sceUsbStart
#endif
#ifdef F_00000001_sceUsbStop
	IMPORT_FUNC	"sceUsb",0xC2464FA0,sceUsbStop
#endif
#ifdef F_00000002_sceUsbGetState
	IMPORT_FUNC	"sceUsb",0xC21645A4,sceUsbGetState
#endif
#ifdef F_00000003_sceUsbGetDrvList
	IMPORT_FUNC	"sceUsb",0x4E537366,sceUsbGetDrvList
#endif
#ifdef F_00000004_sceUsbGetDrvState
	IMPORT_FUNC	"sceUsb",0x112CC951,sceUsbGetDrvState
#endif
#ifdef F_00000005_sceUsbActivate
	IMPORT_FUNC	"sceUsb",0x586DB82C,sceUsbActivate
#endif
#ifdef F_00000006_sceUsbDeactivate
	IMPORT_FUNC	"sceUsb",0xC572A9C8,sceUsbDeactivate
#endif
#ifdef F_00000007_sceUsbWaitState
	IMPORT_FUNC	"sceUsb",0x5BE0E002,sceUsbWaitState
#endif
#ifdef F_00000008_sceUsbWaitCancel
	IMPORT_FUNC	"sceUsb",0x1C360735,sceUsbWaitCancel
#endif
