/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspreg.h - Prototypes for the sceReg library.
 *
 * Copyright (c) 2005 James F
 *
 * $Id$
 */

#ifndef __REG_H__
#define __REG_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Reg Registry Kernel Library */
/*@{*/

#define SYSTEM_REGISTRY "/system"

typedef unsigned int REGHANDLE;

struct RegParam
{
	unsigned int unk1;     /* 0x0 */
	char name[256];        /* 0x4-0x104 */
	unsigned int namelen;     /* 0x104 */
	unsigned int unk2;     /* 0x108 */
	unsigned int unk3;     /* 0x10C */
};

int sceRegOpenRegistry(struct RegParam *reg, int mode, REGHANDLE *h);
int sceRegFlushRegistry(REGHANDLE h);
int sceRegCloseRegistry(REGHANDLE h);
int sceReg_driver_1D8A762E(REGHANDLE h, const char *name, int mode, REGHANDLE *hd);
int sceReg_driver_0CAE832B(REGHANDLE hd);
int sceReg_driver_0D69BF40(REGHANDLE hd);
int sceReg_1D8A762E(REGHANDLE h, const char *name, int mode, REGHANDLE *hd);
int sceReg_0CAE832B(REGHANDLE hd);
int sceReg_0D69BF40(REGHANDLE hd);
int sceRegGetKeyInfo(REGHANDLE hd, const char *name, REGHANDLE *hk, unsigned int *type, SceSize *size);
int sceRegGetKeyValue(REGHANDLE hd, REGHANDLE hk, void *buf, SceSize size);
int sceRegSetKeyValue(REGHANDLE hd, const char *name, void *buf, SceSize size);

/* Not the real names but give an idea of their function */
#define sceRegDriverOpenDir sceReg_driver_1D8A762E
#define sceRegDriverFlushDir sceReg_driver_0D69BF40
#define sceRegDriverCloseDir sceReg_driver_0CAE832B

#define sceRegOpenDir sceReg_1D8A762E
#define sceRegFlushDir sceReg_0D69BF40
#define sceRegCloseDir sceReg_0CAE832B

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
