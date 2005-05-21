	.set noreorder
#include "common.s"

	STUB_START	"sceUmdUser",0x40010000,0x00040005
	STUB_FUNC	0x46EBB729,UmdCheckForDisc
	STUB_FUNC	0xC6183D47,sceUmdActivate
	STUB_FUNC	0x8EF08FCE,UmdSendCommand
	STUB_FUNC	0xAEE7404D,sceUmdRegisterUMDCallBack
	STUB_END

