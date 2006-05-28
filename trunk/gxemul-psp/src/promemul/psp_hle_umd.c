#include "psp_hle.h"

SYSCALL(0x218c,0x46ebb729,0x00000000,"sceUmdCheckMedium",HLE_unknown,4);
SYSCALL(0x218d,0xc6183d47,0x00000000,"sceUmdActivate",HLE_sceUmdActivate,2);
SYSCALL(0x218e,0xe83742ba,0x00000000,"sceUmdDeactivate",HLE_unknown,4);
SYSCALL(0x218f,0x8ef08fce,0x00000000,"sceUmdWaitDriveStat",HLE_unknown,4);
SYSCALL(0x2190,0x56202973,0x00000000,"sceUmdWaitDriveStatWithTimer",HLE_unknown,4);
SYSCALL(0x2191,0x4a9e5e29,0x00000000,"sceUmdWaitDriveStatCB",HLE_unknown,4);
SYSCALL(0x2192,0x6b4a146c,0x00000000,"sceUmdGetDriveStat",HLE_unknown,4);
SYSCALL(0x2193,0x20628e6f,0x00000000,"sceUmdGetErrorStat",HLE_unknown,4);
SYSCALL(0x2194,0x340b7686,0x00000000,"sceUmdGetDiscInfo",HLE_unknown,4);
SYSCALL(0x2195,0xaee7404d,0x00000000,"sceUmdRegisterUMDCallBack",HLE_unknown,4);
SYSCALL(0x2196,0xbd2bde07,0x00000000,"sceUmdUnRegisterUMDCallBack",HLE_unknown,4);
 
//int sceUmdActivate(int unit, const char *drive);
void HLE_sceUmdActivate(int32_t arg0,int32_t arg1)
{
char *name;
	name=get_userland_string(hle_cpu, arg1);
	debug("HLE_sceUmdActivate(unit:%08x drive name:%s) ",arg0,name);
	HLE_RETURN_INT(0);
}
