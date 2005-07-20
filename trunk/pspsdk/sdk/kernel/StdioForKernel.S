	.set noreorder

#include "pspstub.s"

	STUB_START	"StdioForKernel",0x00010000,0x00020005
	STUB_FUNC	0x98220F3E,sceKernelStdoutReopen
	STUB_FUNC	0xFB5380C5,sceKernelStderrReopen
	STUB_FUNC	0x2CCF071A,fdprintf
	STUB_END
