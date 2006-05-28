#include "psp_hle.h"

// ModuleMgrForUser
SYSCALL(0x20cc,0xb7f46618,0x00000000,"sceKernelLoadModuleByID",HLE_unknown,4);
SYSCALL(0x20cd,0x977de386,0x00000000,"sceKernelLoadModule",HLE_sceKernelLoadModule,3);
SYSCALL(0x20ce,0x710f61b5,0x00000000,"sceKernelLoadModuleMs",HLE_unknown,4);
SYSCALL(0x20cf,0xf9275d98,0x00000000,"sceKernelLoadModuleBufferUsbWlan",HLE_unknown,4);
SYSCALL(0x20d0,0x50f0c1ec,0x00000000,"sceKernelStartModule",HLE_sceKernelStartModule,5);
SYSCALL(0x20d1,0xd1ff982a,0x00000000,"sceKernelStopModule",HLE_unknown,4);
SYSCALL(0x20d2,0x2e0911aa,0x00000000,"sceKernelUnloadModule",HLE_unknown,4);
SYSCALL(0x20d3,0xd675ebb8,0x00000000,"sceKernelSelfStopUnloadModule",HLE_sceKernelSelfStopUnloadModule,3);
SYSCALL(0x20d4,0xcc1d3699,0x00000000,"sceKernelStopUnloadSelfModule",HLE_unknown,4);
SYSCALL(0x20d5,0x748cbed9,0x00000000,"sceKernelQueryModuleInfo",HLE_unknown,4);

int        nummodules=0;

//SceUID sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);
void HLE_sceKernelLoadModule(int32_t arg0,int32_t arg1,int32_t arg2)
{
char *name;
	name=get_userland_string(hle_cpu, arg0);
	debug("HLE_sceKernelLoadModule(name:%s flags:%08x options:%08x) ",name,arg1,arg2);
	free(name);
	nummodules++;
	HLE_RETURN_INT(nummodules-1);
}
//int sceKernelStartModule(SceUID modid, SceSize argsize, void *argp, int *status, SceKernelSMOption *option);
void HLE_sceKernelStartModule(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3,int32_t arg4)
{
	debug("HLE_sceKernelStartModule(modid:%08x argsize:%08x argp:%08x status:%08x option:%08x) ",arg0,arg1,arg2,arg3,arg4);
	HLE_RETURN_INT(0);
}
//int sceKernelGetModuleIdList(SceUID *readbuf, int readbufsize, int *idcount);
void HLE_sceKernelGetModuleIdList(int32_t arg0,int32_t arg1,int32_t arg2)
{
	debug("HLE_sceKernelGetModuleIdList(readbuf:%08x readbufsize:%08x idcount:%08x) ",arg0,arg1,arg2);
	HLE_RETURN_INT(0x80000000);
}
 
//int sceKernelSelfStopUnloadModule(int unknown, SceSize argsize, void *argp);
void HLE_sceKernelSelfStopUnloadModule(int32_t arg0,int32_t arg1,int32_t arg2)
{
	debug("HLE_sceKernelSelfStopUnloadModule(unknown:%08x argsize:%08x argp:%08x) ",arg0,arg1,arg2);
	HLE_RETURN_INT(0x80000000);
}
