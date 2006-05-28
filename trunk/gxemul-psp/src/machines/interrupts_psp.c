/*
 *  Copyright (C) 2003-2006  Anders Gavare.  All rights reserved.
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
 *  $Id: interrupts.c,v 1.6 2006/02/18 13:42:39 debug Exp $
 *
 *  Machine-dependent interrupt glue.
 */

#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "devices.h"
#include "machine.h"
#include "machine_interrupts.h"
#include "misc.h"

/*
 *  Playstation Portable interrupt routine:
 */
void psp_interrupt(struct machine *m, struct cpu *cpu, int irq_nr, int assrt)
{
	debug("psp_interrupt(): irq_nr=0x%x assrt=%i\n", irq_nr, assrt);

#if 0
	irq_nr -= 8;
	debug("ps2_interrupt(): irq_nr=0x%x assrt=%i\n", irq_nr, assrt);
	if (irq_nr >= 32) {
		int msk = 0;
		switch (irq_nr - 32) {
		case 0:	/*  PCMCIA:  */
			msk = 0x100;
			break;
		case 1:	/*  USB:  */
			msk = 0x400;
			break;
		default:
			fatal("ps2_interrupt(): bad irq_nr %i\n", irq_nr);
		}

		if (assrt)
			m->md_int.ps2_data->sbus_smflg |= msk;
		else
			m->md_int.ps2_data->sbus_smflg &= ~msk;

		if (m->md_int.ps2_data->sbus_smflg != 0)
			cpu_interrupt(cpu, 8 + 1);
		else
			cpu_interrupt_ack(cpu, 8 + 1);
		return;
	}

	if (assrt) {
		/*  OR into the INTR:  */
		if (irq_nr < 16)
			m->md_int.ps2_data->intr |= (1 << irq_nr);
		else
			m->md_int.ps2_data->dmac_reg[0x601] |=
			    (1 << (irq_nr-16));
	} else {
		/*  AND out of the INTR:  */
		if (irq_nr < 16)
			m->md_int.ps2_data->intr &= ~(1 << irq_nr);
		else
			m->md_int.ps2_data->dmac_reg[0x601] &=
			    ~(1 << (irq_nr-16));
	}

	/*  TODO: Hm? How about the mask?  */
	if (m->md_int.ps2_data->intr /*  & m->md_int.ps2_data->imask */ )
		cpu_interrupt(cpu, 2);
	else
		cpu_interrupt_ack(cpu, 2);

	/*  TODO: mask?  */
	if (m->md_int.ps2_data->dmac_reg[0x601] & 0xffff)
		cpu_interrupt(cpu, 3);
	else
		cpu_interrupt_ack(cpu, 3);
#endif
}

