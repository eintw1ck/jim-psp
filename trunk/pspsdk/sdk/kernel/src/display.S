	.set noreorder

#include "common.s"

	STUB_START	"sceDisplay",0x40010000,0x00040005
	STUB_FUNC	0x0E20F177,sceDisplaySetMode
	STUB_FUNC	0x289D82FE,sceDisplaySetFrameBuf
	STUB_FUNC	0x984C27E7,sceDisplayWaitVblankStart
	STUB_FUNC	0x4CC63FDC,sceDisplaySetVblankCallback
	STUB_END
