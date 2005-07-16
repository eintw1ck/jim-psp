	.set noreorder

#include "pspstub.s"

	STUB_START	"sceUmdUser",0x40010000,0x000B0005
	STUB_FUNC	0x46EBB729,sceUmdCheckMedium
	STUB_FUNC	0xC6183D47,sceUmdActivate
	STUB_FUNC	0xE83742BA,sceUmdDeactivate
	STUB_FUNC	0x8EF08FCE,sceUmdWaitDriveStat
	STUB_FUNC	0x56202973,sceUmdWaitDriveStatWithTimer
	STUB_FUNC	0x4A9E5E29,sceUmdWaitDriveStatCB
	STUB_FUNC	0x6B4A146C,sceUmdGetDriveStat
	STUB_FUNC	0x20628E6F,sceUmdGetErrorStat
	STUB_FUNC	0x340B7686,sceUmdGetDiscInfo
	STUB_FUNC	0xAEE7404D,sceUmdRegisterUMDCallBack
	STUB_FUNC	0xBD2BDE07,sceUmdUnRegisterUMDCallBack
	STUB_END
