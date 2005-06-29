# PSP Software Development Kit - http://www.pspdev.org
# -----------------------------------------------------------------------
# Licensed under the BSD license, see LICENSE in PSPSDK root for details.
#
# crt0.S - Startup functions and definitions. Inspired by nem's helloworld.
#
# Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
# Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
# Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
#
# $Id$

		.set noreorder

		.text

		.extern main

#include "as_reg_compat.h"


##############################################################################

		# Support for _init() and _fini().
		.global _init
		.global _fini
		.type	_init, @function
		.type	_fini, @function

		# The .weak keyword ensures there's no error if
		# _init/_fini aren't defined.
		.weak	_init
		.weak	_fini

		# Define the main thread attribute variable as weak
		.weak   _main_thread_attr

		.global _start
		.ent _start

_start:
		addiu 	$sp, -0x10
		sw		$ra, 0($sp)	
		sw		$s0, 4($sp)
		sw		$s1, 8($sp)

		move	$s0, $a0				# Save args
		move	$s1, $a1

		la  	$a0, _main_thread_name	# Main thread setup
		la		$a1, _main
		li		$a2, 0x20				# Priority
		li		$a3, 0x40000			# Stack size

		la		$t0, _main_thread_attr
		bne		$t0, $0, 1f
		nop
		j		2f
		lui		$t0, 0x8000				# Attributes
1:
		lw		$t0, 0($t0)
2:
		jal		sceKernelCreateThread
		move	$t1, $0

		move	$a0, $v0				# Start thread
		move	$a1, $s0
		jal		sceKernelStartThread
		move	$a2, $s1

		lw		$ra, 0($sp)
		lw		$s0, 4($sp)
		lw		$s1, 8($sp)
		move	$v0, $0
		jr 		$ra
		addiu	$sp, 0x10

		.end _start

# Second stage main function
		.ent _main
_main:
		# Do mainy stuff ;)
		addiu	$sp, -0x10
		sw		$ra, 0($sp)

		la		$t0, g_elf_namesize
		sw		$a0, 0($t0)
		la		$t0, g_elf_name
		sw		$a1, 0($t0)
		
		la		$t0, _fbss
		la		$t1, _end

# Clear BSS
	loop:
		sw		$0,0($t0)
		sltu	$v0, $t0, $t1
		bne		$v0, $0, loop
		addiu	$t0, $t0, 4

		la		$gp, _gp

		la		$t0, _init
		beqz	$t0, 1f
		nop
		jalr	$t0
		nop
1:
		jal		main
		nop

		.end _main

		.global _exit
		.ent _exit

_exit:
# Exit
		la		$t0, _fini
		beqz	$t0, 2f
		nop

		jalr	$t0
		nop
2:

		lw		$ra, 0($sp)
		jr		$ra
		addiu	$sp, 0x10
			
		.end _exit

_main_thread_name:
		.asciiz	"user_main"
##############################################################################

		.section	.lib.ent,"a",@progbits
		.align 2
		.word 0
		.word 0x80000000
		.word 0x00010104
		.word __entrytable

##############################################################################

		# Declare module_info as weak so even if PSP_MODULE_INFO()
		# hasn't been defined the program will still link.
		.weak		module_info

		.section	.rodata.sceResident,"a",@progbits
		.align 2
__entrytable:
		.word 0xD632ACDB
		.word 0xF01D73A7
		.word _start
		.word module_info

###############################################################################

		.data
		.global g_elf_name
g_elf_name: .word 0
		.global g_elf_namesize
g_elf_namesize: .word 0

###############################################################################

		.bss
