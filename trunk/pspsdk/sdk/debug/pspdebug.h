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

/** 
  * Scans through memory trying to find the specified module header.
  *
  * @note This scans all of memory, ensure you are in kernel mode before trying this.
  * @param mod_name - The name of module (e.g. sceExceptionManager) 
  * @return A pointer to the module information, if found. Otherwise NULL.
  */
SceModuleInfo *pspDebugFindModule(const char *mod_name);

/** 
  * Scans through memory trying to find the specified module header. For user modules only.
  *
  * @param mod_name - The name of module (e.g. sceExceptionManager) 
  * @return A pointer to the module information, if found. Otherwise NULL.
  */
SceModuleInfo *pspDebugFindUserModule(const char *mod_name);

/**
  * Find an exported function from its module information.
  *
  * @param mod - Pointer to a module info structure, found with ::pspDebugFindModule.
  * @param exp_name - The name of the export library.
  * @param nid - The nid of the function to find.
  *
  * @return A pointer to the function if found, else NULL.
  */
void *pspDebugFindExportedFunction(SceModuleInfo *mod, const char *exp_name, u32 nid);

/**
  * Find an exported variable from its module information.
  *
  * @param mod - Pointer to a module info structure, found with ::pspDebugFindModule.
  * @param exp_name - The name of the export library.
  * @param nid - The nid of the variable to find.
  *
  * @return A pointer to the variable if found, else NULL.
  */
void *pspDebugFindExportedVariable(SceModuleInfo *mod, const char *exp_name, u32 nid);

/**
  * Find an exported function from its module information, based on its name.
  *
  * @param mod - Pointer to a module info structure, found with ::pspDebugFindModule.
  * @param exp_name - The name of the export library.
  * @param name - The name of the function to find.
  *
  * @return A pointer to the function if found, else NULL.
  */
void *pspDebugFindExportedFunctionByName(SceModuleInfo *mod, const char *exp_name, const char *name);

/**
  * Find an exported variable from its module information, based on its name.
  *
  * @param mod - Pointer to a module info structure, found with ::pspDebugFindModule.
  * @param exp_name - The name of the export library.
  * @param name - The name of the variable to find.
  *
  * @return A pointer to the variable if found, else NULL.
  */
void *pspDebugFuncExportedVariableByName(SceModuleInfo *mod, const char *exp_name, const char *name);

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

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
