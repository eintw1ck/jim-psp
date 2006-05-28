#include "psp_hle.h"

SYSCALL(0x20d6,0xa291f107,0x00000000,"sceKernelMaxFreeMemSize",HLE_sceKernelMaxFreeMemSize,0);
SYSCALL(0x20d7,0xf919f628,0x00000000,"sceKernelTotalFreeMemSize",HLE_sceKernelTotalFreeMemSize,0);
SYSCALL(0x20d8,0x237dbd4f,0x00000000,"sceKernelAllocPartitionMemory",HLE_sceKernelAllocPartitionMemory,5);
SYSCALL(0x20d9,0xb6d61d02,0x00000000,"sceKernelFreePartitionMemory",HLE_sceKernelFreePartitionMemory,1);
SYSCALL(0x20da,0x9d9a5ba1,0x00000000,"sceKernelGetBlockHeadAddr",HLE_sceKernelGetBlockHeadAddr,1);

/**
	pspsysmem.h
*/

//SceSize sceKernelMaxFreeMemSize(void);
void HLE_sceKernelMaxFreeMemSize(void)
{
	debug("HLE_sceKernelMaxFreeMemSize() ");
	HLE_RETURN_INT(0x00100000); // hack
}

//SceSize sceKernelMaxFreeMemSize(void);
void HLE_sceKernelTotalFreeMemSize(void)
{
	debug("HLE_sceKernelTotalFreeMemSize() ");
	HLE_RETURN_INT(0x00100000); // hack
}

//SceUID sceKernelAllocPartitionMemory(SceUID partitionid, const char *name, int type, SceSize size, void *addr);
void HLE_sceKernelAllocPartitionMemory(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3,int32_t arg4)
{
char *name;
	name=get_userland_string(hle_cpu, arg1);
	debug("HLE_sceKernelAllocPartitionMemory(partitionid:%08x name:%s type:%08x size:%08x addr:%08x) ",
		arg0,name,arg2,arg3,arg4);
	HLE_RETURN_INT(1); // hack
}

/**
 * Free a memory block allocated with ::sceKernelAllocPartitionMemory.
 *
 * @param blockid - UID of the block to free.
 *
 * @returns ? on success, less than 0 on error.
 */
//int sceKernelFreePartitionMemory(SceUID blockid);
void HLE_sceKernelFreePartitionMemory(int32_t arg0)
{
	debug("HLE_sceKernelFreePartitionMemory(blockid:%08x) ",arg0);
	HLE_RETURN_INT(0); // hack
}

/**
 * Get the address of a memory block.
 *
 * @param blockid - UID of the memory block.
 *
 * @returns The lowest address belonging to the memory block.
 */
//void * sceKernelGetBlockHeadAddr(SceUID blockid);
void HLE_sceKernelGetBlockHeadAddr(int32_t arg0)
{
	debug("HLE_sceKernelGetBlockHeadAddr(blockid:%08x) ",arg0);
	HLE_RETURN_INT(0xffffffff8a000000); // hack
}
