	.set noreorder

#include "pspstub.s"

	STUB_START	"UtilsForKernel",0x40010000,0x00010005
	STUB_FUNC	0x78934841,sceKernelGzipDecompress
	STUB_END
