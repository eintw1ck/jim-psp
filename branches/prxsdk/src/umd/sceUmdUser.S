	.set noreorder

#include "pspimport.s"

#ifdef F_sceUmdUser_0000
	IMPORT_START	"sceUmdUser",0x40010000
#endif
#ifdef F_sceUmdUser_0001
	IMPORT_FUNC	"sceUmdUser",0x46EBB729,sceUmdCheckMedium
#endif
#ifdef F_sceUmdUser_0002
	IMPORT_FUNC	"sceUmdUser",0xC6183D47,sceUmdActivate
#endif
#ifdef F_sceUmdUser_0003
	IMPORT_FUNC	"sceUmdUser",0xE83742BA,sceUmdDeactivate
#endif
#ifdef F_sceUmdUser_0004
	IMPORT_FUNC	"sceUmdUser",0x8EF08FCE,sceUmdWaitDriveStat
#endif
#ifdef F_sceUmdUser_0005
	IMPORT_FUNC	"sceUmdUser",0x56202973,sceUmdWaitDriveStatWithTimer
#endif
#ifdef F_sceUmdUser_0006
	IMPORT_FUNC	"sceUmdUser",0x4A9E5E29,sceUmdWaitDriveStatCB
#endif
#ifdef F_sceUmdUser_0007
	IMPORT_FUNC	"sceUmdUser",0x6B4A146C,sceUmdGetDriveStat
#endif
#ifdef F_sceUmdUser_0008
	IMPORT_FUNC	"sceUmdUser",0x20628E6F,sceUmdGetErrorStat
#endif
#ifdef F_sceUmdUser_0009
	IMPORT_FUNC	"sceUmdUser",0x340B7686,sceUmdGetDiscInfo
#endif
#ifdef F_sceUmdUser_0010
	IMPORT_FUNC	"sceUmdUser",0xAEE7404D,sceUmdRegisterUMDCallBack
#endif
#ifdef F_sceUmdUser_0011
	IMPORT_FUNC	"sceUmdUser",0xBD2BDE07,sceUmdUnRegisterUMDCallBack
#endif
