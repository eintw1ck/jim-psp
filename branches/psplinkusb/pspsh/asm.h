/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * asm.h - PSPLINK pc terminal simple MIPS assembler
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
 *
 * $HeadURL$
 * $Id$
 */
#ifndef __DISASM_H__
#define __DISASM_H__

int asmAssemble(const char *str, unsigned int PC, unsigned int *inst);

#endif
