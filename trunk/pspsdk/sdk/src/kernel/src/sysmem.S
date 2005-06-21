	.set noreorder
#include "common.s"

   STUB_START   "SysMemUserForUser",0x40000000,0x00030005
   STUB_FUNC   0x237DBD4F,sceKernelAllocPartitionMemory
   STUB_FUNC   0xB6D61D02,sceKernelFreePartitionMemory
   STUB_FUNC   0x9D9A5BA1,sceKernelGetBlockHeadAddr
   STUB_END 

