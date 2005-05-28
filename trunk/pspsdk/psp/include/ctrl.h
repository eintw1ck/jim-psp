/*
# _____     ___ ____     ___ ____ 
#  ____|   |    ____|   |        | |____|    
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project. 
#-----------------------------------------------------------------------
# Copyright 2001-2005, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details. 
# $Id$
# Header file for the controller library.
*/
#ifndef __CTRL_H__
#define __CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Ctrl Controller Kernel Library */
/*@{*/

/** Enumeration for the controller digital buttons */
enum CtrlButtons
{
	/** Square button */
	CTRL_SQUARE     = 0x8000,
	/** Triangle button */
	CTRL_TRIANGLE   = 0x1000,
	/** Circle button */
	CTRL_CIRCLE     = 0x2000,
	/** Cross button */
	CTRL_CROSS      = 0x4000,
	/** Up D-Pad button */
	CTRL_UP         = 0x0010,
	/** Down D-Pad button */
	CTRL_DOWN      	= 0x0040,
	/** Left D-Pad button */
	CTRL_LEFT      	= 0x0080,
	/** Right D-Pad button */
	CTRL_RIGHT      = 0x0020,
	/** Start button */
	CTRL_START      = 0x0008,
	/** Select button */
	CTRL_SELECT     = 0x0001,
	/** Left trigger */
	CTRL_LTRIGGER   = 0x0100,
	/** Right trigger */
	CTRL_RTRIGGER   = 0x0200,
};

/** Returned controller data */
typedef struct _ctrl_data
{
	/** The current read frame */
	u32 frame;
	/** Bit mask containing zero or more of CtrlButtons */
	u32 buttons;
	/** Analogue stick, X direction */
	u8  analog_x;
	/** Analogue stick, Y direction */
	u8  analog_y; 
	/** Dummy padding value */
	u16 dummy;
	/** Seemingly unused */
	u32 unused;
} __attribute__((packed)) ctrl_data_t; 

/**
 * Set controller sample rate
 *
 * @par Example:
 * @see sceCtrlReadBufferPositive
 *
 * @param arg Should be set to 0
 */
void sceCtrlSetSamplingCycle(int arg);
/**
 * Set analog mode
 *
 * @par Example:
 * @see sceCtrlReadBufferPositive
 *
 * @param on - Pass 1 to enable analogue mode
 */
void CtrlSetAnalogMode(int on);
/**
 * Read buffer positive
 *
 * @par Example:
 * @code
 * ctrl_data_t pad;

 * sceCtrlSetSamplingCycle(0);
 * CtrlSetAnalogMode(1);
 * sceCtrlReadBufferPositive(&pad, 1); 
 * // Do something with the read controller data
 * @endcode
 *
 * @param pad_data - Structure to hold the returned pad data
 * @param option - Unknown function. Always set to 1
 */
void sceCtrlReadBufferPositive(ctrl_data_t *pad_data, int option);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
