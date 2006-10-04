/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspdisplay_kernel.h - Prototypes for the sceDisplay_driver library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __DISPLAYKERNEL_H__
#define __DISPLAYKERNEL_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Display set framebuf
 *
 * @param pri - Priority
 * @param topaddr - address of start of framebuffer
 * @param bufferwidth - buffer width (must be power of 2)
 * @param pixelformat - One of ::PspDisplayPixelFormats.
 * @param sync - One of ::PspDisplaySetBufSync
 */
void sceDisplay_driver_63E22A26(int pri, void *topaddr, int bufferwidth, int pixelformat, int sync);

/**
 * Get Display Framebuffer information
 *
 * @param pri - Priority
 * @param topaddr - pointer to void* to receive address of start of framebuffer
 * @param bufferwidth - pointer to int to receive buffer width (must be power of 2)
 * @param pixelformat - pointer to int to receive one of ::PspDisplayPixelFormats.
 * @param unk1 - pointer to int, receives unknown, always 1? (vblank sync?)
 */
int sceDisplay_driver_585AEFAD(int pri, void **topaddr, int *bufferwidth, int *pixelformat, int *unk1);

#ifdef __cplusplus
}
#endif

#endif
