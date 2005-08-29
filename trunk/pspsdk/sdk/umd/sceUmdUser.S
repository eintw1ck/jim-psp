	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceUmdUser
	IMPORT_START	"sceUmdUser",0x40010000
#endif
#ifdef F_00000000_sceUmdCheckMedium
	IMPORT_FUNC	"sceUmdUser",0x46EBB729,sceUmdCheckMedium
#endif
#ifdef F_00000001_sceUmdActivate
	IMPORT_FUNC	"sceUmdUser",0xC6183D47,sceUmdActivate
#endif
#ifdef F_00000002_sceUmdDeactivate
	IMPORT_FUNC	"sceUmdUser",0xE83742BA,sceUmdDeactivate
#endif
#ifdef F_00000003_sceUmdWaitDriveStat
	IMPORT_FUNC	"sceUmdUser",0x8EF08FCE,sceUmdWaitDriveStat
#endif
#ifdef F_00000004_sceUmdWaitDriveStatWithTimer
	IMPORT_FUNC	"sceUmdUser",0x56202973,sceUmdWaitDriveStatWithTimer
#endif
#ifdef F_00000005_sceUmdWaitDriveStatCB
	IMPORT_FUNC	"sceUmdUser",0x4A9E5E29,sceUmdWaitDriveStatCB
#endif
#ifdef F_00000006_sceUmdGetDriveStat
	IMPORT_FUNC	"sceUmdUser",0x6B4A146C,sceUmdGetDriveStat
#endif
#ifdef F_00000007_sceUmdGetErrorStat
	IMPORT_FUNC	"sceUmdUser",0x20628E6F,sceUmdGetErrorStat
#endif
#ifdef F_00000008_sceUmdGetDiscInfo
	IMPORT_FUNC	"sceUmdUser",0x340B7686,sceUmdGetDiscInfo
#endif
#ifdef F_00000009_sceUmdRegisterUMDCallBack
	IMPORT_FUNC	"sceUmdUser",0xAEE7404D,sceUmdRegisterUMDCallBack
#endif
#ifdef F_0000000A_sceUmdUnRegisterUMDCallBack
	IMPORT_FUNC	"sceUmdUser",0xBD2BDE07,sceUmdUnRegisterUMDCallBack
#endif
