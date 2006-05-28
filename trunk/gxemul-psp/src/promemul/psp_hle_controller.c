#include "psp_hle.h"

SYSCALL(0x213d,0x6a2774f3,0x00000000,"sceCtrlSetSamplingCycle",HLE_sceCtrlSetSamplingCycle,1);
SYSCALL(0x213e,0x02baad91,0x00000000,"sceCtrlGetSamplingCycle",HLE_sceCtrlGetSamplingCycle,1);
SYSCALL(0x213f,0x1f4011e6,0x00000000,"sceCtrlSetSamplingMode",HLE_sceCtrlSetSamplingMode,1);
SYSCALL(0x2140,0xda6b76a1,0x00000000,"sceCtrlGetSamplingMode",HLE_sceCtrlGetSamplingMode,1);
SYSCALL(0x2141,0x3a622550,0x00000000,"sceCtrlPeekBufferPositive",HLE_sceCtrlPeekBufferPositive,2);
SYSCALL(0x2142,0xc152080a,0x00000000,"sceCtrlPeekBufferNegative",HLE_unknown,4);
SYSCALL(0x2143,0x1f803938,0x00000000,"sceCtrlReadBufferPositive",HLE_sceCtrlReadBufferPositive,2);
SYSCALL(0x2144,0x60b81f86,0x00000000,"sceCtrlReadBufferNegative",HLE_unknown,4);
SYSCALL(0x2145,0xb1d0e5cd,0x00000000,"sceCtrlPeekLatch",HLE_unknown,4);
SYSCALL(0x2146,0x0b588501,0x00000000,"sceCtrlReadLatch",HLE_unknown,4);
SYSCALL(0x2147,0x348d99d4,0x00000000,"sceCtrl_348D99D4",HLE_unknown,4);
SYSCALL(0x2148,0xaf5960f3,0x00000000,"sceCtrl_AF5960F3",HLE_unknown,4);
SYSCALL(0x2149,0xa68fd260,0x00000000,"sceCtrl_A68FD260",HLE_unknown,4);
SYSCALL(0x214a,0x6841be1a,0x00000000,"sceCtrl_6841BE1A",HLE_unknown,4);


/**
	(pspctrl.h)
*/

/**
 * Enumeration for the digital controller buttons.
 *
 * @note PSP_CTRL_NOTE can only be read in kernel mode
 */
enum PspCtrlButtons
{
        /** Select button. */
        PSP_CTRL_SELECT     = 0x000001,
        /** Start button. */
        PSP_CTRL_START      = 0x000008,
        /** Up D-Pad button. */
        PSP_CTRL_UP         = 0x000010,
        /** Right D-Pad button. */
        PSP_CTRL_RIGHT      = 0x000020,
        /** Down D-Pad button. */
        PSP_CTRL_DOWN           = 0x000040,
        /** Left D-Pad button. */
        PSP_CTRL_LEFT           = 0x000080,
        /** Left trigger. */
        PSP_CTRL_LTRIGGER   = 0x000100,
        /** Right trigger. */
        PSP_CTRL_RTRIGGER   = 0x000200,
        /** Triangle button. */
        PSP_CTRL_TRIANGLE   = 0x001000,
        /** Circle button. */
        PSP_CTRL_CIRCLE     = 0x002000,
        /** Cross button. */
        PSP_CTRL_CROSS      = 0x004000,
        /** Square button. */
        PSP_CTRL_SQUARE     = 0x008000,
        /** Home button. */
        PSP_CTRL_HOME       = 0x010000,
        /** Hold button. */
        PSP_CTRL_HOLD       = 0x020000,
        /** Music Note button. */
        PSP_CTRL_NOTE       = 0x800000,
};

/** Controller mode. */
enum PspCtrlMode
{
        /* Digitial. */
        PSP_CTRL_MODE_DIGITAL = 0,
        /* Analog. */
        PSP_CTRL_MODE_ANALOG
};

/** Returned controller data */
typedef struct SceCtrlData {
        /** The current read frame. */
        unsigned int    TimeStamp;
        /** Bit mask containing zero or more of ::PspCtrlButtons. */
        unsigned int    Buttons;
        /** Analogue stick, X axis. */
        unsigned char   Lx;
        /** Analogue stick, Y axis. */
        unsigned char   Ly;
        /** Reserved. */
        unsigned char   Rsrv[6];
} SceCtrlData;

typedef struct SceCtrlLatch {
        unsigned int    uiMake;
        unsigned int    uiBreak;
        unsigned int    uiPress;
        unsigned int    uiRelease;
} SceCtrlLatch;

/**
 * Set the controller cycle setting.
 *
 * @param cycle - Cycle.  Normally set to 0.
 *
 * @returns The previous cycle setting.
 */
//int sceCtrlSetSamplingCycle(int cycle);
void HLE_sceCtrlSetSamplingCycle(int32_t arg0)
{
	debug("HLE_sceCtrlSetSamplingCycle(cycle:%08x) ",arg0);
	HLE_RETURN_INT(0);
}

/**
 * Get the controller current cycle setting.
 *
 * @param pcycle - Return value.
 *
 * @returns 0.
 */
//int sceCtrlGetSamplingCycle(int *pcycle);
void HLE_sceCtrlGetSamplingCycle(int32_t arg0)
{
	debug("HLE_sceCtrlGetSamplingCycle(pcycle:%08x) ",arg0);
	HLE_RETURN_INT(0);
}

/**
 * Set the controller mode.
 *
 * @param mode - One of ::PspCtrlMode.
 *
 * @returns The previous mode.
 */
//int sceCtrlSetSamplingMode(int mode);
void HLE_sceCtrlSetSamplingMode(int32_t arg0)
{
	debug("HLE_sceCtrlSetSamplingMode(mode:%08x) ",arg0);
	HLE_RETURN_INT(0);
}

/**
 * Get the current controller mode.
 *
 * @param pmode - Return value.
 *
 * @returns 0.
 */
//int sceCtrlGetSamplingMode(int *pmode);
void HLE_sceCtrlGetSamplingMode(int32_t arg0)
{
	debug("HLE_sceCtrlGetSamplingMode(pmode:%08x) ",arg0);
	HLE_RETURN_INT(0);
}




//int sceCtrlPeekBufferPositive(SceCtrlData *pad_data, int count);
void HLE_sceCtrlPeekBufferPositive(int32_t arg0,int32_t arg1)
{
	debug("HLE_sceCtrlPeekBufferPositive(pad_data:%08x count:%08x) ",arg0,arg1);
	store_32bit_word(hle_cpu, arg0, 0x00000000);
	store_32bit_word(hle_cpu, arg0+4, 0x00000000);
	store_32bit_word(hle_cpu, arg0+8, 0x00000000);
	store_32bit_word(hle_cpu, arg0+12, 0x00000000);
	HLE_RETURN_INT(0);
}
//int sceCtrlPeekBufferNegative(SceCtrlData *pad_data, int count);

void HLE_sceCtrlReadBufferPositive(int32_t arg0,int32_t arg1)
{
	debug("HLE_sceCtrlReadBufferPositive(pad_data:%08x count:%08x) ",arg0,arg1);
	store_32bit_word(hle_cpu, arg0, 0x00000000);
	store_32bit_word(hle_cpu, arg0+4, 0x00000000);
	store_32bit_word(hle_cpu, arg0+8, 0x00000000);
	store_32bit_word(hle_cpu, arg0+12, 0x00000000);
	HLE_RETURN_INT(0);
}

//int sceCtrlReadBufferNegative(SceCtrlData *pad_data, int count);
//int sceCtrlPeekLatch(SceCtrlLatch *latch_data);
//int sceCtrlReadLatch(SceCtrlLatch *latch_data);
 
