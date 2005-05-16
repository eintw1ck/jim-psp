#ifndef __CTRL_H__
#define __CTRL_H__

/* Index for the two analog directions */
#define CTRL_ANALOG_X   0
#define CTRL_ANALOG_Y   1

/* Button bit masks */
#define CTRL_SQUARE     0x8000
#define CTRL_TRIANGLE   0x1000
#define CTRL_CIRCLE     0x2000
#define CTRL_CROSS      0x4000
#define CTRL_UP         0x0010
#define CTRL_DOWN      	0x0040
#define CTRL_LEFT      	0x0080
#define CTRL_RIGHT      0x0020
#define CTRL_START      0x0008
#define CTRL_SELECT     0x0001
#define CTRL_LTRIGGER   0x0100
#define CTRL_RTRIGGER   0x0200

/* Returned control data */
typedef struct _ctrl_data
{
   u32 frame;
   u32 buttons;
   u8  analog[4];
   u32 unused;
} ctrl_data_t; 


/**
 * Set ctrl sample rate
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param arg
 */
void sceCtrlSetSamplingCycle(int arg);
/**
 * Set analog mode
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param on
 */
void CtrlSetAnalogMode(int on);
/**
 * Read buffer positive
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param pad_data
 * @param option
 */
void sceCtrlReadBufferPositive(ctrl_data_t *pad_data, int option);

#endif
