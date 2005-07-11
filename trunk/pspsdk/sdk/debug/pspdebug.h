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
 *
 * $Id$
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <psptypes.h>
#include <pspmoduleinfo.h>

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
  * Print non-nul terminated strings.
  * 
  * @param buff - Buffer containing the text.
  * @param size - Size of the data
  *
  * @return The number of characters written
  */
int pspDebugScreenPrintData(const char *buff, int size);

/**
  * Get a MIPS stack trace (might work :P)
  *
  * @param results - List of points to store the results of the trace, (up to max)
  * @param max - Maximum number of back traces
*/
void pspDebugGetStackTrace(unsigned int* results,int max);

/** Structure to hold the register data associated with an exception */
typedef struct _PspDebugRegBlock
{
	/** Array of the 32 GPRs */
	u32 r[32];
	/** The status register */
	u32 status;
	/** The cause register */
	u32 cause;
	/** The EPC register */
	u32 epc;
	/** The BadVAddr register (possible unused) */
	u32 badvaddr;
} PspDebugRegBlock;

/** Defines a debug error handler */
typedef void (*PspDebugErrorHandler)(PspDebugRegBlock *regs);

/** 
  * Install an error handler to catch unhandled exceptions.
  * 
  * @param handler - Pointer to a handler function. If set to NULL it will default
  * to resetting the screen and dumping the error.
  * @return < 0 on error
  */
int pspDebugInstallErrorHandler(PspDebugErrorHandler handler);

/**
  * Dump an exception to screen using the pspDebugScreen functions.
  * @note This function will not setup the screen for debug output, you should call sceDebugScreenInit
  * before using it if it isn't already.
  *
  * @param regs - Pointer to a register block.
  *
  */
void pspDebugDumpException(PspDebugRegBlock *regs);

/** Type for Kprintf handler */
typedef int (*PspDebugKprintfHandler)(const char *format, u32 *args);

/** 
  * Install a Kprintf handler into the system.
  *
  * @param handler - Function pointer to the handler.
  * @return < 0 on error.
  */
int pspDebugInstallKprintfHandler(PspDebugKprintfHandler handler);

/** Structure to hold a single stack trace entry */
typedef struct _PspDebugStackTrace
{
	/** The address which called the function */
	u32 call_addr;
	/** The address of the function called */
	u32 func_addr;
} PspDebugStackTrace;

/**
  * Do a stack trace from the current exception. 
  * @note This function really isn't too general purpose and it is more than likely to generate a few 
  * false positives but I consider that better then missing out calls entirely. You have to use your
  * discretion, your code and a objdump to work out if some calls are completely surprious or not ;)
  *
  * @param regs - Pointer to a register block from an exception.
  * @param trace - Pointer to an array of PspDebugStackTrace structures.
  * @param max - The maximum number of traces to make.
  *
  * @return The number of functions found.
  */
int pspDebugGetStackTrace2(PspDebugRegBlock *regs, PspDebugStackTrace *trace, int max);

/** Structure to hold the psp profiler register values */
typedef struct _PspDebugProfilerRegs
{
	u32 enable;
	u32 systemck;
	u32 cpuck;
	u32 stall;
	u32 internal;
	u32 memory;
	u32 copz;
	u32 vfpu;
	u32 sleep;
	u32 bus_access;
	u32 uncached_load;
	u32 uncached_store;
	u32 cached_load;
	u32 cached_store;
	u32 i_miss;
	u32 d_miss;
	u32 d_writeback;
	u32 cop0_inst;
	u32 fpu_inst;
	u32 vfpu_inst;
	u32 local_bus;
} PspDebugProfilerRegs;

/** Enables the profiler hardware */
void pspDebugProfilerEnable(void);

/** Disables the profiler hardware */
void pspDebugProfilerDisable(void);

/** Clear the profiler registers */
void pspDebugProfilerClear(void);

/** Get the profiler register state
  *
  * @param regs - A pointer to a PspDebugProfilerRegs structure.
  */
void pspDebugProfilerGetRegs(PspDebugProfilerRegs *regs);

/** Print the profiler registers to screen */
void pspDebugProfilerPrint(void);

/** Type for the debug print handlers */
typedef int (*PspDebugPrintHandler)(const char *data, int len);

/** Type for the debug input handler */
typedef int (*PspDebugInputHandler)(char *data, int len);

/**
  * Install a handler for stdin (so you can use normal stdio functions)
  *
  * @param handler - A pointer to input handler, NULL to disable.
  *
  * @return < 0 on error, else 0.
  */
int pspDebugInstallStdinHandler(PspDebugInputHandler handler);

/**
  * Install a print handler for stdout (so you can use normal print functions)
  *
  * @param handler - A pointer to print handler, NULL to disable.
  *
  * @return < 0 on error, else 0.
  */
int pspDebugInstallStdoutHandler(PspDebugPrintHandler handler);

/**
  * Install a print handler for stderr (so you can use normal print functions)
  *
  * @param handler - A pointer to print handler, NULL to disable.
  *
  * @return < 0 on error, else 0.
  */
int pspDebugInstallStderrHandler(PspDebugPrintHandler handler);

/**
  * Qeury a modules information from its uid.
  * @note this is a replacement function for the broken kernel sceKernelQueryModuleInfo.
  * DO NOT use on a anything above that version. This also needs kernel mode access where
  * the normal one has a user mode stub.
  * 
  * @param uid - The UID of the module to query.
  * @param modinfo - Pointer a module SceKernelModuleInfo structure.
  *
  * @return < 0 on error.
  */
int pspDebugQueryModuleInfoV1(SceUID uid, SceKernelModuleInfo *modinfo);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
