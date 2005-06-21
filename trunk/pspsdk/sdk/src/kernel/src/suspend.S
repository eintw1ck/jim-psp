	.set noreorder

#include "common.s"

	STUB_START	"sceSuspendForUser",0x40000000,0x00030005
	STUB_FUNC	0xEADB1BD7,DisableSuspend
	STUB_FUNC	0x3AEE7261,EnableSuspend
	STUB_FUNC	0x090ccb3f,SuspendUnknown_1
	STUB_END
