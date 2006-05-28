/*
 *  Copyright (C) 2005-2006  Anders Gavare.  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright  
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE   
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *   
 *
 *  $Id: machine_psp.c,v 1.1 2006/01/10 20:30:05 debug Exp $
 */

#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "device.h"
#include "devices.h"
#include "machine.h"
#include "memory.h"
#include "misc.h"

struct vfb_data *fb;
//struct unimplemented_data *io;

#define MEG16	(1024 * 1024 * 16)
MACHINE_SETUP(psp)
{

	debug("machine_setup: Playstation Portable\n");

	machine->machine_name = "Playstation Portable";
	cpu->byte_order = EMUL_LITTLE_ENDIAN;

	if (!machine->use_x11)
		fprintf(stderr, "-------------------------------------"
		    "------------------------------------------\n"
		    "\n  WARNING! You are emulating a PSP without -X. "
		    "You will miss graphical output!\n\n"
		    "-------------------------------------"
		    "------------------------------------------\n");

	/*  480 x 272 pixels framebuffer (512 bytes per line)  */
//	fb = dev_fb_init(machine, machine->memory, 0x04000000, VFB_PSP, 480,272, 512,1088, -15, "Playstation Portable");
	fb = dev_fb_init(machine, machine->memory, 0x04000000, VFB_PSP, 480,272, 512,1088, 8, "Playstation Portable");
//	io = dev_unimplemented_init(machine, machine->memory, 0xbf000000, VFB_PSP, 480,272, 512,1088, 8, "io at bf000000");

/*
	note:	lots of devices is really painfully slow later in memory_rw
		this should be heavily optimized
*/

#if 0
	dev_unimplemented_init(machine,0x1c000000,0x0100,"io_bc000000");
	dev_unimplemented_init(machine,0x1c100000,0x0100,"io_exception");
	dev_unimplemented_init(machine,0x1c200000,0x0100,"io_bc200000");
	dev_unimplemented_init(machine,0x1c300000,0x0100,"io_bc300000");
	dev_unimplemented_init(machine,0x1c400000,0x0100,"io_bc400000");
	dev_unimplemented_init(machine,0x1c500000,0x0100,"io_bc500000");
	dev_unimplemented_init(machine,0x1c600000,0x0100,"io_bc600000");
	dev_unimplemented_init(machine,0x1c700000,0x0100,"io_bc700000");
	dev_unimplemented_init(machine,0x1c800000,0x0100,"io_bc800000");
	dev_unimplemented_init(machine,0x1c900000,0x0100,"io_bc900000");
	dev_unimplemented_init(machine,0x1ca00000,0x0100,"io_bca00000");
	dev_unimplemented_init(machine,0x1cb00000,0x0100,"io_bcb00000");
	dev_unimplemented_init(machine,0x1cc00000,0x0100,"io_bcc00000");

	dev_unimplemented_init(machine,0x1d000000,0x0100,"io_bd000000");
	dev_unimplemented_init(machine,0x1d100000,0x0100,"io_bd100000");
	dev_unimplemented_init(machine,0x1d200000,0x0100,"io_bd200000");
	dev_unimplemented_init(machine,0x1d300000,0x0100,"io_bd300000");
	dev_unimplemented_init(machine,0x1d400000,0x0100,"io_bd400000");
	dev_unimplemented_init(machine,0x1d500000,0x0100,"io_bd500000");
	dev_unimplemented_init(machine,0x1d600000,0x0100,"io_bd600000");
	dev_unimplemented_init(machine,0x1d700000,0x0100,"io_bd700000");
	dev_unimplemented_init(machine,0x1d800000,0x0100,"io_bd800000");
	dev_unimplemented_init(machine,0x1de00000,0x0100,"io_bde00000");
	dev_unimplemented_init(machine,0x1df00000,0x0100,"io_bdf00000");
	dev_unimplemented_init(machine,0x1e000000,0x0100,"io_be000000");
	dev_unimplemented_init(machine,0x1e100000,0x0100,"io_be100000");

	dev_unimplemented_init(machine,0x1e140000,0x0100,"io_be140000");
	dev_unimplemented_init(machine,0x1e200000,0x0100,"io_be200000");
	dev_unimplemented_init(machine,0x1e240000,0x0100,"io_gpio");
	dev_unimplemented_init(machine,0x1e300000,0x0100,"io_be300000");
	dev_unimplemented_init(machine,0x1e340000,0x0100,"io_be340000");
#if 0
	dev_unimplemented_init(machine,0x1e4c0000,0x0100,"io_uart4");
	dev_unimplemented_init(machine,0x1e500000,0x0100,"io_uart3");
	dev_unimplemented_init(machine,0x1e540000,0x0100,"io_uart2");
	dev_unimplemented_init(machine,0x1e580000,0x0100,"io_uart1");
#endif
	dev_psp_uart_init(machine,0x1e4c0000,0x0100,"io_uart4");
	dev_psp_uart_init(machine,0x1e500000,0x0100,"io_uart3");
	dev_psp_uart_init(machine,0x1e540000,0x0100,"io_uart2");
	dev_psp_uart_init(machine,0x1e580000,0x0100,"io_uart1");

	dev_unimplemented_init(machine,0x1e740000,0x0100,"io_be740000");
	dev_unimplemented_init(machine,0x1f000000,0x0100,"io_bf000000");
	dev_unimplemented_init(machine,0x1fa00000,0x0100,"io_bfa00000");

	dev_unimplemented_init(machine,0x1ff00000,0x0100,"io_bff00000");
	dev_unimplemented_init(machine,0x1fff0000,0x0100,"io_bfff0000");
#endif
/*
	device_add(machine, "unimplemented addr=0x1e4c0000 len=0x0100");
	device_add(machine, "unimplemented addr=0x1c000000 len=0x0100");
*/
	// for memory setup see "memory_mips_v2p.c"

/*  
  		cpu->cd.mips.gpr[MIPS_GPR_SP] = 0xfff0;
+ 
+ 		pspbios_init(machine, cpu);
*/
//  		cpu->cd.mips.gpr[MIPS_GPR_SP] = 0xfff0;

}


MACHINE_DEFAULT_CPU(psp)
{
	machine->cpu_name = strdup("Allegrex");
}


MACHINE_DEFAULT_RAM(psp)
{
	// 32mb system memory at (physical) 0x08000000
	machine->physical_ram_in_mb = 32;
	machine->memory_offset_in_mb = (0x08000000/0x00100000);
}


MACHINE_REGISTER(psp)
{
	debug("machine_register: Playstation Portable\n");
	MR_DEFAULT(psp, "Playstation Portable", ARCH_MIPS, MACHINE_PSP, 1, 0);
	me->aliases[0] = "psp";
	me->set_default_ram = machine_default_ram_psp;
	machine_entry_add(me, ARCH_MIPS);
}

