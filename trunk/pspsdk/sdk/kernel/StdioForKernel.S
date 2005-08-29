	.set noreorder

#include "pspimport.s"

#ifdef F_stub_StdioForKernel
	IMPORT_START	"StdioForKernel",0x00010000
#endif
#ifdef F_00000000_fdprintf
	IMPORT_FUNC	"StdioForKernel",0x2CCF071A,fdprintf
#endif
#ifdef F_00000001_printf
	IMPORT_FUNC	"StdioForKernel",0xCAB439DF,printf
#endif
#ifdef F_00000002_fdputc
	IMPORT_FUNC	"StdioForKernel",0x4F78930A,fdputc
#endif
#ifdef F_00000003_putchar
	IMPORT_FUNC	"StdioForKernel",0xD768752A,putchar
#endif
#ifdef F_00000004_fdputs
	IMPORT_FUNC	"StdioForKernel",0x36B23B8B,fdputs
#endif
#ifdef F_00000005_puts
	IMPORT_FUNC	"StdioForKernel",0xD97C8CB9,puts
#endif
#ifdef F_00000006_fdgetc
	IMPORT_FUNC	"StdioForKernel",0xD2B2A2A7,fdgetc
#endif
#ifdef F_00000007_getchar
	IMPORT_FUNC	"StdioForKernel",0x7E338487,getchar
#endif
#ifdef F_00000008_fdgets
	IMPORT_FUNC	"StdioForKernel",0x11A5127A,fdgets
#endif
#ifdef F_00000009_gets
	IMPORT_FUNC	"StdioForKernel",0xBFF7E760,gets
#endif
#ifdef F_0000000A_sceKernelStdin
	IMPORT_FUNC	"StdioForKernel",0x172D316E,sceKernelStdin
#endif
#ifdef F_0000000B_sceKernelStdout
	IMPORT_FUNC	"StdioForKernel",0xA6BAB2E9,sceKernelStdout
#endif
#ifdef F_0000000C_sceKernelStderr
	IMPORT_FUNC	"StdioForKernel",0xF78BA90A,sceKernelStderr
#endif
#ifdef F_0000000D_sceKernelStdoutReopen
	IMPORT_FUNC	"StdioForKernel",0x98220F3E,sceKernelStdoutReopen
#endif
#ifdef F_0000000E_sceKernelStderrReopen
	IMPORT_FUNC	"StdioForKernel",0xFB5380C5,sceKernelStderrReopen
#endif
