	.set noreorder

#include "pspstub.s"

   STUB_START   "Kernel_Library",0x00010000,0x00020005
   STUB_FUNC   0x092968F4,sceKernelCpuSuspendIntr
   STUB_FUNC   0x5F10D406,sceKernelCpuResumeIntr
   STUB_END 
