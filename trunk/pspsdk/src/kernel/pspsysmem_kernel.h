/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysmem_kernel.h - Interface to the system memory manager (kernel).
 *
 * Copyright (c) 2005 James F.
 *
 * $Id: pspsysmem.h 1095 2005-09-27 21:02:16Z jim $
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef PSPSYSMEMKERNEL_H
#define PSPSYSMEMKERNEL_H

#include <pspkerneltypes.h>
#include <pspsysmem.h>

/** @defgroup SysMemKern System Memory Manager Kernel
  * This module contains routines to manage heaps of memory.
  */

/** @addtogroup SysMemKern System Memory Manager Kernel */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _PspSysmemPartitionInfo
{
	SceSize size;
	unsigned int startaddr;
	unsigned int memsize;
	unsigned int attr;
} PspSysmemPartitionInfo;

/**
 * Query the parition information
 *
 * @param pid  - The partition id
 * @param info - Pointer to the ::PspSysmemPartitionInfo structure
 *
 * @returns 0 on success.
 */
int sceKernelQueryMemoryPartitionInfo(int pid, PspSysmemPartitionInfo *info);

/**
 * Get the total amount of free memory.
 *
 * @param pid - The partition id
 *
 * @returns The total amount of free memory, in bytes.
 */
SceSize sceKernelPartitionTotalFreeMemSize(int pid);

/**
 * Get the size of the largest free memory block.
 *
 * @param pid - The partition id
 *
 * @returns The size of the largest free memory block, in bytes.
 */
SceSize sceKernelPartitionMaxFreeMemSize(int pid);

/**
 * Get the kernel to dump the internal memory table to Kprintf
 */
void sceKernelSysMemDump(void);

/**
 * Dump the list of memory blocks
 */
void sceKernelSysMemDumpBlock(void);

/**
 * Dump the tail blocks
 */
void sceKernelSysMemDumpTail(void);

/**
 * Set the protection of a block of ddr memory
 *
 * @param addr - Address to set protection on
 * @param size - Size of block
 * @param prot - Protection bitmask
 *
 * @return < 0 on error
 */
int sceKernelSetDdrMemoryProtection(void *addr, int size, int prot);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* PSPSYSMEMKERNEL_H */
