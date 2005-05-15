# Mostly written by tyranid inspired by nem's work

		.set noreorder

		.text

		.extern main


##############################################################################


		.ent _start
		.weak _start

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
		lui		$t0, 0x8000				# Attributes
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

		.ent _main
_main:
		# Do mainy stuff ;)
		addiu	$sp, -0x10
		sw		$ra, 0($sp)
		la		$gp, _gp
		jal		main
		nop
		lw		$ra, 0($sp)
		jr		$ra
		addiu	$sp, 0x10
			
		.end _main

_main_thread_name:
		.asciiz	"user_main"
##############################################################################


		.section	.lib.ent,"wa",@progbits
__lib_ent_top:
		.word 0
		.word 0x80000000
		.word 0x00010104
		.word __entrytable


		.section	.lib.ent.btm,"wa",@progbits
__lib_ent_bottom:
		.word	0


		.section	.lib.stub,"wa",@progbits
__lib_stub_top:


		.section	.lib.stub.btm,"wa",@progbits
__lib_stub_bottom:
		.word	0


##############################################################################

		.section	".xodata.sceModuleInfo","wa",@progbits

__moduleinfo:
		.byte	0,0,1,1

		.ascii	"PSPSDK"		#up to 28 char
		.align	5

		.word	_gp
		.word	__lib_ent_top
		.word	__lib_ent_bottom
		.word	__lib_stub_top
		.word	__lib_stub_bottom

##############################################################################

		.section	.rodata.entrytable,"wa",@progbits
__entrytable:
		.word 0xD632ACDB
		.word 0xF01D73A7
		.word _start
		.word __moduleinfo
		.word 0



###############################################################################

		.data


###############################################################################

		.bss
