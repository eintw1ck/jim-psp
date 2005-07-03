/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspkerneltypes.h - PSP kernel types and definitions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

#ifndef PSPKERNELTYPES_H
#define PSPKERNELTYPES_H

#include <psptypes.h>

/** UIDs are used to describe many different kernel objects. */
typedef int SceUID;

/* Misc. kernel types. */
typedef unsigned int SceSize;
typedef int SceSSize;

typedef unsigned char SceUChar;
typedef unsigned int SceUInt;

/* File I/O types. */
typedef int SceMode;
typedef long long int SceOff;
typedef long long int SceIores;

typedef struct _SceKernelSysClock {
	SceUInt32   low;
	SceUInt32   hi;
} SceKernelSysClock;

#endif /* PSPKERNELTYPES_H */
