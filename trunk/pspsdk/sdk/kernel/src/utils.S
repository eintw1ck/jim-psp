	.set noreorder

#include "common.s"

   STUB_START   "UtilsForUser",0x40010000,0x00040005
   STUB_FUNC   0x91E4F6A7,sceKernelLibcClock
   STUB_FUNC   0x27CC57F0,sceKernelLibcTime
   STUB_FUNC   0x71EC4271,sceKernelLibcGettimeofday
   STUB_FUNC   0x79D1C3FA,sceKernelDcacheWritebackAll
   STUB_END 
