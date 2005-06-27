/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspdebug.h - Prototypes for the pspDebug library
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * $Id$
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Debug Debug Utility Library */

/** @addtogroup Debug */
/*@{*/

/** 
  * Initialise the debug screen
  */
void pspDebugScreenInit(void);

/**
  * Do a printf to the debug screen.
  *
  * @param fmt - Format string to print
  * @param ... - Arguments
  */
void pspDebugScreenPrintf(const char *fmt, ...) __attribute__((format(printf,1,2)));

/** 
  * Set the background color for the text
  * @note To reset the entire screens bg colour you need to call pspDebugScreenClear
  *
  * @param color - A 32bit RGB colour
  */
void pspDebugScreenSetBackColor(u32 color);

/**
  * Set the text color 
  *
  * @param color - A 32 bit RGB color
  */
void pspDebugScreenSetTextColor(u32 color);

/** 
  * Draw a single character to the screen.
  *
  * @param x - The x co-ordinate to draw to (pixel units)
  * @param y - The y co-ordinate to draw to (pixel units)
  * @param color - The text color to draw
  * @param ch - The character to draw
  */
void pspDebugScreenPutChar(int x, int y, u32 color, u8 ch);

/**
  * Set the current X and Y co-ordinate for the screen (in character units)
  */
void pspDebugScreenSetXY(int x, int y);

/** 
  * Get the current X co-ordinate (in character units)
  *
  * @return The X co-ordinate
  */
int pspDebugScreenGetX(void);

/** 
  * Get the current Y co-ordinate (in character units)
  *
  * @return The Y co-ordinate
  */
int pspDebugScreenGetY(void);

/**
  * Clear the debug screen.
  */
void pspDebugScreenClear(void);

/**
  * Get a MIPS stack trace (might work :P)
  *
  * @param results - List of points to store the results of the trace, (up to max)
  * @param max - Maximum number of back traces
*/
void pspDebugGetStackTrace(unsigned int* results,int max);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
