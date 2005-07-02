/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspexception_asm.S - Basic exception handler for applications.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id$
 */

#include "as_reg_compat.h"

	.set noreorder
	.set noat

	.extern _pspDebugExceptRegs
	.extern _pspDebugTrapEntry

	.global _pspDebugExceptionHandler
	.ent    _pspDebugExceptionHandler
_pspDebugExceptionHandler:
	nop
	nop
	la		$v0, _pspDebugExceptRegs
	sw		$0, 0x00($v0)
	sw		$1, 0x04($v0)

	cfc0	$1, $4
	sw		$1, 0x08($v0)
	cfc0 	$1, $5
	sw		$1, 0x0C($v0)
	sw		$4, 0x10($v0)
	sw		$5, 0x14($v0)
	sw		$6, 0x18($v0)
	sw		$7, 0x1C($v0)
	sw		$8, 0x20($v0)
	sw		$9, 0x24($v0)
	sw		$10, 0x28($v0)
	sw		$11, 0x2C($v0)
	sw		$12, 0x30($v0)
	sw		$13, 0x34($v0)
	sw		$14, 0x38($v0)
	sw		$15, 0x3C($v0)
	sw		$16, 0x40($v0)
	sw		$17, 0x44($v0)
	sw		$18, 0x48($v0)
	sw		$19, 0x4C($v0)
	sw		$20, 0x50($v0)
	sw		$21, 0x54($v0)
	sw		$22, 0x58($v0)
	sw		$23, 0x5C($v0)
	sw		$24, 0x60($v0)
	sw		$25, 0x64($v0)
	sw		$26, 0x68($v0)
	sw		$27, 0x6C($v0)
	sw		$28, 0x70($v0)
	sw		$29, 0x74($v0)
	sw		$30, 0x78($v0)
	sw		$31, 0x7C($v0)
	mfc0	$v1,  $12
	sw		$v1,  0x80($v0)
	mfc0	$v1,  $13
	sw		$v1,  0x84($v0)
	mfc0	$v1,  $14
	sw		$v1,  0x88($v0)
	mfc0	$v1,  $8
	sw		$v1,  0x8C($v0)

	la		$2, _pspDebugTrapEntry
	mtc0	$2, $14
	nop
	nop
	eret
	nop
1:				# If all else fails 
	j	1b
	nop

	.end _pspDebugExceptionHandler
