	.set noreorder
#include "common.s"

   STUB_START   "StdioForUser",0x40010000,0x00030005
   STUB_FUNC   0x172D316E,sceKernelStdin
   STUB_FUNC   0xA6BAB2E9,sceKernelStdout
   STUB_FUNC   0xF78BA90A,sceKernelStderr
   STUB_END 

