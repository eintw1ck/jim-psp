	.set noreorder

#include "pspimport.s"

#ifdef F_stub_StdioForUser
	IMPORT_START	"StdioForUser",0x40010000
#endif
#ifdef F_00000000_sceKernelStdioRead
	IMPORT_FUNC	"StdioForUser",0x3054D478,sceKernelStdioRead
#endif
#ifdef F_00000001_sceKernelStdioLseek
	IMPORT_FUNC	"StdioForUser",0x0CBB0571,sceKernelStdioLseek
#endif
#ifdef F_00000002_sceKernelStdioSendChar
	IMPORT_FUNC	"StdioForUser",0xA46785C9,sceKernelStdioSendChar
#endif
#ifdef F_00000003_sceKernelStdioWrite
	IMPORT_FUNC	"StdioForUser",0xA3B931DB,sceKernelStdioWrite
#endif
#ifdef F_00000004_sceKernelStdioClose
	IMPORT_FUNC	"StdioForUser",0x9D061C19,sceKernelStdioClose
#endif
#ifdef F_00000005_sceKernelStdioOpen
	IMPORT_FUNC	"StdioForUser",0x924ABA61,sceKernelStdioOpen
#endif
#ifdef F_00000006_sceKernelStdin
	IMPORT_FUNC	"StdioForUser",0x172D316E,sceKernelStdin
#endif
#ifdef F_00000007_sceKernelStdout
	IMPORT_FUNC	"StdioForUser",0xA6BAB2E9,sceKernelStdout
#endif
#ifdef F_00000008_sceKernelStderr
	IMPORT_FUNC	"StdioForUser",0xF78BA90A,sceKernelStderr
#endif
