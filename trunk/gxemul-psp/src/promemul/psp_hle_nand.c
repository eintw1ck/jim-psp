
#include "psp_hle.h"

/**
	sceNand_driver
*/

SYSCALL(0x220f,0xae4438c7, 0x00000000,"sceNandLock",HLE_sceNandLock,1);
SYSCALL(0x2210,0x41ffa822, 0x00000000,"sceNandUnlock",HLE_sceNandUnlock,0);
SYSCALL(0x2211,0xce9843e6, 0x00000000,"sceNandGetPageSize",HLE_sceNandGetPageSize,0);
SYSCALL(0x2212,0xb07c41d4, 0x00000000,"sceNandGetPagesPerBlock",HLE_sceNandGetPagesPerBlock,0);
SYSCALL(0x2213,0xc32ea051, 0x00000000,"sceNandReadBlockWithRetry",HLE_sceNandReadBlockWithRetry,3);
SYSCALL(0x2214,0x01f09203, 0x00000000,"sceNandIsBadBlock",HLE_sceNandIsBadBlock,1);

// sceNandLock(0)
void HLE_sceNandLock(int32_t arg0)
{
	debug("HLE_sceNandLock(arg0:%08x) ",arg0);
	HLE_RETURN_INT(0);
}
// sceNandUnlock()
void HLE_sceNandUnlock(void)
{
	debug("HLE_sceNandUnlock() ");
	HLE_RETURN_INT(0x00000000);
}

// sceNandGetPageSize()
void HLE_sceNandGetPageSize(void)
{
	debug("HLE_sceNandGetPageSize() ");
	HLE_RETURN_INT(0x00000010);
}
// sceNandGetPagesPerBlock()
void HLE_sceNandGetPagesPerBlock(void)
{
	debug("HLE_sceNandGetPagesPerBlock() ");
	HLE_RETURN_INT(0x00000010);
}
// sceNandReadBlockWithRetry(uiPPN, pBlockBuf, NULL)
void HLE_sceNandReadBlockWithRetry(int32_t arg0,int32_t arg1,int32_t arg2)
{
	debug("HLE_sceNandReadBlockWithRetry(uiPPN:%08x pBlockBuf:%08x arg2:%08x) ",arg0,arg1,arg2);
	HLE_RETURN_INT(0);
}
// sceNandIsBadBlock(uiPPN)
void HLE_sceNandIsBadBlock(int32_t arg0)
{
	debug("HLE_sceNandIsBadBlock(uiPPN:%08x) ",arg0);
	HLE_RETURN_INT(0);
}
 
