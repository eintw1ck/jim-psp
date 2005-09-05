/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspkernel.h - Main include file that includes all major kernel headers.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */

#ifndef PSPKERNEL_H
#define PSPKERNEL_H

#include <pspuser.h>
#include <pspiofilemgr_kernel.h>
#include <psploadcore.h>
#include <pspstdio_kernel.h>
#include <pspsysreg.h>
#include <pspkdebug.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the $pc register to a kernel memory address.
 *
 * When the PSP's kernel library stubs are called, they expect to be accessed
 * from the kernel's address space.  Use this function to set $pc to the kernel
 * address space, before calling a kernel library stub.
 */
static __inline__
void pspKernelSetKernelPC(void)
{
	__asm__ volatile (
	"la     $8, 1f\n\t"     \
	"lui    $9, 0x8000\n\t" \
	"or     $8, $9\n\t"     \
	"jr     $8\n\t"         \
	" nop\n\t"              \
	"1:\n\t"
	: : : "$8", "$9");

	/* We need to invalidate the I-cache, to purge any instructions that still
	   refer to addresses in userspace. */
	sceKernelIcacheClearAll();
}

#ifdef __cplusplus
}
#endif

#endif /* PSPKERNEL_H */
