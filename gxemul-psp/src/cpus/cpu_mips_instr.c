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
 *  $Id: cpu_mips_instr.c,v 1.9 2006/02/17 20:27:21 debug Exp $
 *
 *  MIPS instructions.
 *
 *  Individual functions should keep track of cpu->n_translated_instrs.
 *  (If no instruction was executed, then it should be decreased. If, say, 4
 *  instructions were combined into one function and executed, then it should
 *  be increased by 3.)
 */


/*
 *  nop:  Do nothing.
 */
X(nop)
{
}


/*
 *  invalid_32_64:  Attempt to execute a 64-bit instruction on an
 *                  emulated 32-bit processor.
 */
X(invalid_32_64)
{
	fatal("invalid_32_64: TODO\n");
	exit(1);
}


/*
 *  beq:  Branch if equal
 *  bne:  Branch if not equal
 *  b:  Branch (comparing a register to itself, always true)
 *
 *  arg[0] = pointer to rs
 *  arg[1] = pointer to rt
 *  arg[2] = (int32_t) relative offset from the next instruction
 */
X(beq)
{
	MODE_uint_t old_pc = cpu->pc;
	MODE_uint_t rs = reg(ic->arg[0]), rt = reg(ic->arg[1]);
	int x = rs == rt;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		if (x) {
			old_pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
			    MIPS_INSTR_ALIGNMENT_SHIFT);
			cpu->pc = old_pc + (int32_t)ic->arg[2];
			quick_pc_to_pointers(cpu);
		} else
			cpu->cd.mips.next_ic ++;
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(beq_samepage)
{
	MODE_uint_t rs = reg(ic->arg[0]), rt = reg(ic->arg[1]);
	int x = rs == rt;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		if (x)
			cpu->cd.mips.next_ic = (struct mips_instr_call *)
			    ic->arg[2];
		else
			cpu->cd.mips.next_ic ++;
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(bne)
{
	MODE_uint_t old_pc = cpu->pc;
	MODE_uint_t rs = reg(ic->arg[0]), rt = reg(ic->arg[1]);
	int x = rs != rt;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		if (x) {
			old_pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
			    MIPS_INSTR_ALIGNMENT_SHIFT);
			cpu->pc = old_pc + (int32_t)ic->arg[2];
			quick_pc_to_pointers(cpu);
		} else
			cpu->cd.mips.next_ic ++;
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(bne_samepage)
{
	MODE_uint_t rs = reg(ic->arg[0]), rt = reg(ic->arg[1]);
	int x = rs != rt;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		if (x)
			cpu->cd.mips.next_ic = (struct mips_instr_call *)
			    ic->arg[2];
		else
			cpu->cd.mips.next_ic ++;
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(b)
{
	MODE_uint_t old_pc = cpu->pc;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		old_pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
		    MIPS_INSTR_ALIGNMENT_SHIFT);
		cpu->pc = old_pc + (int32_t)ic->arg[2];
		quick_pc_to_pointers(cpu);
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(b_samepage)
{
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT))
		cpu->cd.mips.next_ic = (struct mips_instr_call *) ic->arg[2];
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}


/*
 *  jr, jalr: Jump to a register [and link].
 *
 *  arg[0] = ptr to rs
 *  arg[1] = ptr to rd (for jalr)
 *  arg[2] = (int32_t) relative offset of the next instruction
 */
X(jr)
{
	MODE_uint_t rs = reg(ic->arg[0]);
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		cpu->pc = rs;
		quick_pc_to_pointers(cpu);
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(jr_ra)
{
	MODE_uint_t rs = cpu->cd.mips.gpr[MIPS_GPR_RA];
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		cpu->pc = rs;
		quick_pc_to_pointers(cpu);
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(jr_ra_trace)
{
	MODE_uint_t rs = cpu->cd.mips.gpr[MIPS_GPR_RA];
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		cpu->pc = rs;
		cpu_functioncall_trace_return(cpu);
		quick_pc_to_pointers(cpu);
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(jalr)
{
	MODE_uint_t rs = reg(ic->arg[0]), rd;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	rd = cpu->pc & ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
	    MIPS_INSTR_ALIGNMENT_SHIFT);
	rd += (int32_t)ic->arg[2];
	reg(ic->arg[1]) = rd;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		cpu->pc = rs;
		quick_pc_to_pointers(cpu);
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}
X(jalr_trace)
{
	MODE_uint_t rs = reg(ic->arg[0]), rd;
	cpu->cd.mips.delay_slot = TO_BE_DELAYED;
	rd = cpu->pc & ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
	    MIPS_INSTR_ALIGNMENT_SHIFT);
	rd += (int32_t)ic->arg[2];
	reg(ic->arg[1]) = rd;
	ic[1].f(cpu, ic+1);
	cpu->n_translated_instrs ++;
	if (!(cpu->cd.mips.delay_slot & EXCEPTION_IN_DELAY_SLOT)) {
		cpu->pc = rs;
		cpu_functioncall_trace(cpu, cpu->pc);
		quick_pc_to_pointers(cpu);
	}
	cpu->cd.mips.delay_slot = NOT_DELAYED;
}


/*
 *  2-register + immediate:
 *
 *  arg[0] = pointer to rs
 *  arg[1] = pointer to rt
 *  arg[2] = uint32_t immediate value
 */
X(andi) { reg(ic->arg[1]) = reg(ic->arg[0]) & (int32_t)ic->arg[2]; }
X(ori)  { reg(ic->arg[1]) = reg(ic->arg[0]) | (int32_t)ic->arg[2]; }
X(xori) { reg(ic->arg[1]) = reg(ic->arg[0]) ^ (int32_t)ic->arg[2]; }


/*
 *  2-register:
 */
X(mult)
{
	int32_t a = reg(ic->arg[0]), b = reg(ic->arg[1]);
	int64_t res = (int64_t)a * (int64_t)b;
	reg(&cpu->cd.mips.lo) = (int32_t)res;
	reg(&cpu->cd.mips.hi) = (int32_t)(res >> 32);
}
X(multu)
{
	uint32_t a = reg(ic->arg[0]), b = reg(ic->arg[1]);
	uint64_t res = (uint64_t)a * (uint64_t)b;
	reg(&cpu->cd.mips.lo) = (int32_t)res;
	reg(&cpu->cd.mips.hi) = (int32_t)(res >> 32);
}


/*
 *  3-register:
 */
X(addu) { reg(ic->arg[2]) = (int32_t)(reg(ic->arg[0]) + reg(ic->arg[1])); }
X(subu) { reg(ic->arg[2]) = (int32_t)(reg(ic->arg[0]) - reg(ic->arg[1])); }
X(daddu){ reg(ic->arg[2]) = reg(ic->arg[0]) + reg(ic->arg[1]); }
X(dsubu){ reg(ic->arg[2]) = reg(ic->arg[0]) + reg(ic->arg[1]); }
X(slt) {
#ifdef MODE32
	reg(ic->arg[2]) = (int32_t)reg(ic->arg[0]) < (int32_t)reg(ic->arg[1]);
#else
	reg(ic->arg[2]) = (int64_t)reg(ic->arg[0]) < (int64_t)reg(ic->arg[1]);
#endif
}
X(sltu) {
#ifdef MODE32
	reg(ic->arg[2]) = (uint32_t)reg(ic->arg[0]) < (uint32_t)reg(ic->arg[1]);
#else
	reg(ic->arg[2]) = (uint64_t)reg(ic->arg[0]) < (uint64_t)reg(ic->arg[1]);
#endif
}
X(or) { reg(ic->arg[2]) = reg(ic->arg[0]) | reg(ic->arg[1]); }
X(xor) { reg(ic->arg[2]) = reg(ic->arg[0]) ^ reg(ic->arg[1]); }
X(nor) { reg(ic->arg[2]) = ~(reg(ic->arg[0]) | reg(ic->arg[1])); }
X(sll) { reg(ic->arg[2]) = (int32_t)(reg(ic->arg[0]) << ic->arg[1]); }
X(srl) { reg(ic->arg[2]) = (int32_t)((uint32_t)reg(ic->arg[0]) >> ic->arg[1]); }
X(sra) { reg(ic->arg[2]) = (int32_t)((int32_t)reg(ic->arg[0]) >> ic->arg[1]); }
X(mul) { reg(ic->arg[2]) = (int32_t)
	( (int32_t)reg(ic->arg[0]) * (int32_t)reg(ic->arg[1]) ); }


/*
 *  mov:  Move one register into another.
 *
 *  arg[0] = pointer to source
 *  arg[2] = pointer to destination
 */
X(mov)  { reg(ic->arg[2]) = reg(ic->arg[0]); }


/*
 *  clz, clo, dclz, dclo: Count leading zeroes/ones.
 *
 *  arg[0] = pointer to rs
 *  arg[1] = pointer to rd
 */
X(clz)
{
	uint32_t x = reg(ic->arg[0]);
	int count;
	for (count=0; count<32; count++) {
		if (x & 0x80000000UL)
			break;
		x <<= 1;
	}
	reg(ic->arg[1]) = count;
}
X(clo)
{
	uint32_t x = reg(ic->arg[0]);
	int count;
	for (count=0; count<32; count++) {
		if (!(x & 0x80000000UL))
			break;
		x <<= 1;
	}
	reg(ic->arg[1]) = count;
}
X(dclz)
{
	uint64_t x = reg(ic->arg[0]);
	int count;
	for (count=0; count<64; count++) {
		if (x & 0x8000000000000000ULL)
			break;
		x <<= 1;
	}
	reg(ic->arg[1]) = count;
}
X(dclo)
{
	uint64_t x = reg(ic->arg[0]);
	int count;
	for (count=0; count<64; count++) {
		if (!(x & 0x8000000000000000ULL))
			break;
		x <<= 1;
	}
	reg(ic->arg[1]) = count;
}


/*
 *  addiu:  Add immediate (32-bit).
 *
 *  arg[0] = pointer to rs
 *  arg[1] = pointer to rt
 *  arg[2] = (int32_t) immediate value
 */
X(addiu)
{
	reg(ic->arg[1]) = (int32_t)
	    ((int32_t)reg(ic->arg[0]) + (int32_t)ic->arg[2]);
}


/*
 *  daddiu:  Add immediate (64-bit).
 *
 *  arg[0] = pointer to rs
 *  arg[1] = pointer to rt
 *  arg[2] = (int32_t) immediate value
 */
X(daddiu)
{
	reg(ic->arg[1]) = reg(ic->arg[0]) + (int32_t)ic->arg[2];
}


/*
 *  set:  Set a register to an immediate (signed) 32-bit value.
 *
 *  arg[0] = pointer to the register
 *  arg[1] = (int32_t) immediate value
 */
X(set)
{
	reg(ic->arg[0]) = (int32_t)ic->arg[1];
}


/*
 *  mfc0, dmfc0:  Move from Coprocessor 0.
 *  mtc0, dmtc0:  Move to Coprocessor 0.
 *  cfc1: Copy control word from Coprocessor 1.
 *
 *  arg[0] = pointer to GPR (rt)
 *  arg[1] = coprocessor 0 register number | (select << 5)
 *  arg[2] = relative addr of this instruction within the page
 */
X(mfc0)
{
	int rd = ic->arg[1] & 31, select = ic->arg[1] >> 5;
	uint64_t tmp;
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1)<<MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc |= ic->arg[2];
	/*  TODO: cause exception if necessary  */
	coproc_register_read(cpu, cpu->cd.mips.coproc[0], rd, &tmp, select);
	reg(ic->arg[0]) = (int32_t)tmp;
}
X(mtc0)
{
	int rd = ic->arg[1] & 31, select = ic->arg[1] >> 5;
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1)<<MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc |= ic->arg[2];
	/*  TODO: cause exception if necessary  */
	coproc_register_write(cpu, cpu->cd.mips.coproc[0], rd,
	    (uint64_t *)ic->arg[0], 0, select);
}
X(dmfc0)
{
	int rd = ic->arg[1] & 31, select = ic->arg[1] >> 5;
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1)<<MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc |= ic->arg[2];
	/*  TODO: cause exception if necessary  */
	coproc_register_read(cpu, cpu->cd.mips.coproc[0], rd,
	    (uint64_t *)ic->arg[0], select);
}
X(dmtc0)
{
	int rd = ic->arg[1] & 31, select = ic->arg[1] >> 5;
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1)<<MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc |= ic->arg[2];
	/*  TODO: cause exception if necessary  */
	coproc_register_write(cpu, cpu->cd.mips.coproc[0], rd,
	    (uint64_t *)ic->arg[0], 1, select);
}
X(cfc1)
{
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1)<<MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc |= ic->arg[2];
	/*  TODO: cause exception if necessary  */
	reg(ic->arg[0]) = reg(ic->arg[1]);
}


/*****************************************************************************/


/*
 *  b_samepage_addiu:
 *
 *  Combination of branch within the same page, followed by addiu.
 */
X(b_samepage_addiu)
{
	reg(ic[1].arg[1]) = reg(ic[1].arg[0]) + (int32_t)ic[1].arg[2];
	cpu->n_translated_instrs ++;
	cpu->cd.mips.next_ic = (struct mips_instr_call *) ic->arg[2];
}


/*****************************************************************************/


X(end_of_page)
{
	struct mips_instr_call self;

	/*  Update the PC:  (offset 0, but on the next page)  */
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
	    MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc += (MIPS_IC_ENTRIES_PER_PAGE << MIPS_INSTR_ALIGNMENT_SHIFT);

	/*  Simple jump to the next page (if we are lucky):  */
	if (cpu->cd.mips.delay_slot == NOT_DELAYED) {

		/*  Find the new physpage and update translation pointers:  */
		quick_pc_to_pointers(cpu);

		/*  end_of_page doesn't count as an executed instruction:  */
		cpu->n_translated_instrs --;

		return;
	}

	/*  Tricky situation; the delay slot is on the next virtual page:  */
	/*  fatal("[ end_of_page: delay slot across page boundary! ]\n");  */

	/*  to_be_translated will overwrite the current ic.  */
	self = *ic;

	instr(to_be_translated)(cpu, ic);

	/*  The instruction in the delay slot has now executed.  */

	/*  Find the physpage etc of the instruction in the delay slot
	    (or, if there was an exception, the exception handler):  */
	quick_pc_to_pointers(cpu);

	/*  Restore the end_of_page instr call.  */
	*ic = self;

	/*  fatal("[ end_of_page: back from delay slot ]\n");  */
}


X(end_of_page2)
{
fatal("this should be removed: end of page2\n");
exit(1);

	/*  Update the PC:  (offset 4, but on the next page)  */
	cpu->pc &= ~((MIPS_IC_ENTRIES_PER_PAGE-1) <<
	    MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc += ((MIPS_IC_ENTRIES_PER_PAGE+1) << MIPS_INSTR_ALIGNMENT_SHIFT);

	if (cpu->cd.mips.delay_slot == NOT_DELAYED) {
		/*  Find the new physpage and update translation pointers:  */
		quick_pc_to_pointers(cpu);

		/*  end_of_page doesn't count as an executed instruction:  */
		cpu->n_translated_instrs --;

		return;
	}

	fatal("DELAY SLOT in DELAY SLOT across a page boundary? HUH?\n");
	exit(1);
}


/*****************************************************************************/


/*
 *  Combine: [Conditional] branch, followed by addiu.
 */
void COMBINE(b_addiu)(struct cpu *cpu, struct mips_instr_call *ic,
	int low_addr)
{
	int n_back = (low_addr >> MIPS_INSTR_ALIGNMENT_SHIFT)
	    & (MIPS_IC_ENTRIES_PER_PAGE - 1);

	if (n_back < 1)
		return;

	if (ic[-1].f == instr(b_samepage)) {
		ic[-1].f = instr(b_samepage_addiu);
		combined;
	}

	/*  TODO: other branches that are followed by addiu should be here  */
}


/*****************************************************************************/


/*
 *  mips_instr_to_be_translated():
 *
 *  Translate an instruction word into an mips_instr_call. ic is filled in with
 *  valid data for the translated instruction, or a "nothing" instruction if
 *  there was a translation failure. The newly translated instruction is then
 *  executed.
 */
X(to_be_translated)
{
	uint64_t addr, low_pc;
	uint32_t iword, imm;
	unsigned char *page;
	unsigned char ib[4];
#ifdef DYNTRANS_BACKEND
	int simple = 0;
#endif
	int main_opcode, rt, rs, rd, sa, s6, x64 = 0;
	int in_crosspage_delayslot = 0;
	int delay_slot_danger = 1;
	void (*samepage_function)(struct cpu *, struct mips_instr_call *);

	/*  Figure out the (virtual) address of the instruction:  */
	low_pc = ((size_t)ic - (size_t)cpu->cd.mips.cur_ic_page)
	    / sizeof(struct mips_instr_call);

	/*  Special case for branch with delayslot on the next page:  */
	if (low_pc >= MIPS_IC_ENTRIES_PER_PAGE) {
		/*  fatal("[ TEMPORARY delay-slot translation ]\n");  */
		low_pc = 0;
		in_crosspage_delayslot = 1;
	}

	addr = cpu->pc & ~((MIPS_IC_ENTRIES_PER_PAGE-1)
	    << MIPS_INSTR_ALIGNMENT_SHIFT);
	addr += (low_pc << MIPS_INSTR_ALIGNMENT_SHIFT);
	cpu->pc = addr;
	addr &= ~((1 << MIPS_INSTR_ALIGNMENT_SHIFT) - 1);

	/*  Read the instruction word from memory:  */
	page = cpu->cd.mips.host_load[(uint32_t)addr >> 12];

	if (page != NULL) {
		/*  fatal("TRANSLATION HIT!\n");  */
		memcpy(ib, page + (addr & 0xfff), sizeof(ib));
	} else {
		/*  fatal("TRANSLATION MISS!\n");  */
		if (!cpu->memory_rw(cpu, cpu->mem, addr, ib,
		    sizeof(ib), MEM_READ, CACHE_INSTRUCTION)) {
			fatal("to_be_translated(): "
			    "read failed: TODO\n");
			goto bad;
		}
	}

	iword = *((uint32_t *)&ib[0]);

	if (cpu->byte_order == EMUL_LITTLE_ENDIAN)
		iword = LE32_TO_HOST(iword);
	else
		iword = BE32_TO_HOST(iword);

	/*  Is the instruction in the delay slot known to be safe?  */
	if ((addr & 0xffc) < 0xffc) {
		/*  TODO: check the instruction  */
		delay_slot_danger = 0;
	}


#define DYNTRANS_TO_BE_TRANSLATED_HEAD
#include "cpu_dyntrans.c"
#undef  DYNTRANS_TO_BE_TRANSLATED_HEAD


	/*
	 *  Translate the instruction:
 	 *
	 *  NOTE: _NEVER_ allow writes to the zero register; all such
	 *  instructions should be made into NOPs.
	 */

	main_opcode = iword >> 26;
	rs = (iword >> 21) & 31;
	rt = (iword >> 16) & 31;
	rd = (iword >> 11) & 31;
	sa = (iword >>  6) & 31;
	imm = (int16_t)iword;
	s6 = iword & 63;

	switch (main_opcode) {

	case HI6_SPECIAL:
		switch (s6) {

		case SPECIAL_SLL:
		case SPECIAL_SRL:
		case SPECIAL_SRA:
			switch (s6) {
			case SPECIAL_SLL:  ic->f = instr(sll); break;
			case SPECIAL_SRL:  ic->f = instr(srl); break;
			case SPECIAL_SRA:  ic->f = instr(sra); break;
			}
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rt];
			ic->arg[1] = sa;
			ic->arg[2] = (size_t)&cpu->cd.mips.gpr[rd];
			if (rd == MIPS_GPR_ZERO)
				ic->f = instr(nop);
			break;

		case SPECIAL_ADDU:
		case SPECIAL_SUBU:
		case SPECIAL_DADDU:
		case SPECIAL_DSUBU:
		case SPECIAL_SLT:
		case SPECIAL_SLTU:
		case SPECIAL_OR:
		case SPECIAL_XOR:
		case SPECIAL_NOR:
		case SPECIAL_MFHI:
		case SPECIAL_MFLO:
		case SPECIAL_MTHI:
		case SPECIAL_MTLO:
			switch (s6) {
			case SPECIAL_ADDU:  ic->f = instr(addu); break;
			case SPECIAL_SUBU:  ic->f = instr(subu); break;
			case SPECIAL_DADDU: ic->f = instr(daddu); x64=1; break;
			case SPECIAL_DSUBU: ic->f = instr(dsubu); x64=1; break;
			case SPECIAL_SLT:   ic->f = instr(slt); break;
			case SPECIAL_SLTU:  ic->f = instr(sltu); break;
			case SPECIAL_OR:    ic->f = instr(or); break;
			case SPECIAL_XOR:   ic->f = instr(xor); break;
			case SPECIAL_NOR:   ic->f = instr(nor); break;
			case SPECIAL_MFHI:  ic->f = instr(mov); break;
			case SPECIAL_MFLO:  ic->f = instr(mov); break;
			case SPECIAL_MTHI:  ic->f = instr(mov); break;
			case SPECIAL_MTLO:  ic->f = instr(mov); break;
			}
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
			ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rt];
			ic->arg[2] = (size_t)&cpu->cd.mips.gpr[rd];
			switch (s6) {
			case SPECIAL_MFHI:
				ic->arg[0] = (size_t)&cpu->cd.mips.hi;
				break;
			case SPECIAL_MFLO:
				ic->arg[0] = (size_t)&cpu->cd.mips.lo;
				break;
			case SPECIAL_MTHI:
				ic->arg[2] = (size_t)&cpu->cd.mips.hi;
				break;
			case SPECIAL_MTLO:
				ic->arg[2] = (size_t)&cpu->cd.mips.lo;
				break;
			}
			/*  rd==0 => nop:  */
			switch (s6) {
			case SPECIAL_MTHI:
			case SPECIAL_MTLO:
				/*  These instructions don't use rd.  */
				break;
			default:if (rd == MIPS_GPR_ZERO)
					ic->f = instr(nop);
			}
			break;

		case SPECIAL_MULT:
		case SPECIAL_MULTU:
			switch (s6) {
			case SPECIAL_MULT : ic->f = instr(mult); break;
			case SPECIAL_MULTU: ic->f = instr(multu); break;
			}
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
			ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rt];
			/*  rd is ignored for most of these instructions,
			    except for multiplication:  */
			switch (s6) {
			case SPECIAL_MULT:
			case SPECIAL_MULTU:
			case SPECIAL_DMULT:
			case SPECIAL_DMULTU:
				ic->arg[2] = (size_t)&cpu->cd.mips.gpr[rd];
				if (rd != MIPS_GPR_ZERO) {
					fatal("TODO: mult with rd NON-zero\n");
					goto bad;
				}
				break;
			}
			break;

		case SPECIAL_JR:
		case SPECIAL_JALR:
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
			ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rd];
			if (main_opcode == SPECIAL_JALR && rd == MIPS_GPR_ZERO)
				main_opcode = SPECIAL_JR;
			ic->arg[2] = (addr & 0xffc) + 4;
			switch (main_opcode) {
			case SPECIAL_JR:
				if (rs == MIPS_GPR_RA) {
					if (cpu->machine->show_trace_tree)
						ic->f = instr(jr_ra_trace);
					else
						ic->f = instr(jr_ra);
				} else {
					ic->f = instr(jr);
				}
				break;
			case SPECIAL_JALR:
				if (cpu->machine->show_trace_tree)
					ic->f = instr(jalr_trace);
				else
					ic->f = instr(jalr);
				break;
			}
			if (in_crosspage_delayslot) {
				fatal("[ WARNING: branch in delay slot? ]\n");
				ic->f = instr(nop);
			}
			break;

		case SPECIAL_SYNC:
			ic->f = instr(nop);
			break;

		default:goto bad;
		}
		break;

	case HI6_BEQ:
	case HI6_BNE:
		samepage_function = NULL;  /*  get rid of a compiler warning  */
		switch (main_opcode) {
		case HI6_BEQ:
			ic->f = instr(beq);
			samepage_function = instr(beq_samepage);
			/*  Special case: comparing a register with itself:  */
			if (rs == rt) {
				ic->f = instr(b);
				samepage_function = instr(b_samepage);
			}
			break;
		case HI6_BNE:
			ic->f = instr(bne);
			samepage_function = instr(bne_samepage);
		}
		ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
		ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rt];
		ic->arg[2] = (imm << MIPS_INSTR_ALIGNMENT_SHIFT)
		    + (addr & 0xffc) + 4;
		/*  Is the offset from the start of the current page still
		    within the same page? Then use the samepage_function:  */
		if ((uint32_t)ic->arg[2] < ((MIPS_IC_ENTRIES_PER_PAGE - 1)
		    << MIPS_INSTR_ALIGNMENT_SHIFT) && (addr & 0xffc) < 0xffc) {
			ic->arg[2] = (size_t) (cpu->cd.mips.cur_ic_page +
			    ((ic->arg[2] >> MIPS_INSTR_ALIGNMENT_SHIFT)
			    & (MIPS_IC_ENTRIES_PER_PAGE - 1)));
			ic->f = samepage_function;
		}
		if (in_crosspage_delayslot) {
			fatal("[ WARNING: branch in delay slot? ]\n");
			ic->f = instr(nop);
		}
		break;

	case HI6_ADDIU:
	case HI6_DADDIU:
	case HI6_ANDI:
	case HI6_ORI:
	case HI6_XORI:
		ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
		ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rt];
		if (main_opcode == HI6_ADDI ||
		    main_opcode == HI6_ADDIU ||
		    main_opcode == HI6_DADDI ||
		    main_opcode == HI6_DADDIU)
			ic->arg[2] = (int16_t)iword;
		else
			ic->arg[2] = (uint16_t)iword;
		switch (main_opcode) {
		case HI6_ADDIU:   ic->f = instr(addiu); break;
		case HI6_DADDIU:  ic->f = instr(daddiu); x64 = 1; break;
		case HI6_ANDI:    ic->f = instr(andi); break;
		case HI6_ORI:     ic->f = instr(ori); break;
		case HI6_XORI:    ic->f = instr(xori); break;
		}
		if (rt == MIPS_GPR_ZERO)
			ic->f = instr(nop);

		if (ic->f == instr(addiu))
			cpu->cd.mips.combination_check = COMBINE(b_addiu);
		break;

	case HI6_LUI:
		ic->f = instr(set);
		ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rt];
		ic->arg[1] = imm << 16;
		if (rt == MIPS_GPR_ZERO)
			ic->f = instr(nop);
		break;

	case HI6_COP0:
		/*  rs contains the coprocessor opcode!  */
		switch (rs) {
		case COPz_MFCz:
		case COPz_DMFCz:
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rt];
			ic->arg[1] = rd + ((iword & 7) << 5);
			ic->arg[2] = addr & 0xffc;
			ic->f = rs == COPz_MFCz? instr(mfc0) : instr(dmfc0);
			if (rt == MIPS_GPR_ZERO)
				ic->f = instr(nop);
			break;
		case COPz_MTCz:
		case COPz_DMTCz:
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rt];
			ic->arg[1] = rd + ((iword & 7) << 5);
			ic->arg[2] = addr & 0xffc;
			ic->f = rs == COPz_MTCz? instr(mtc0) : instr(dmtc0);
			break;
		default:fatal("UNIMPLEMENTED cop0 (rs = %i)\n", rs);
			goto bad;
		}
		break;

	case HI6_COP1:
		/*  rs contains the coprocessor opcode!  */
		switch (rs) {
		case COPz_CFCz:
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rt];
			ic->arg[1] = (size_t)&cpu->cd.mips.coproc[1]->fcr[rd];
			ic->arg[2] = addr & 0xffc;
			ic->f = instr(cfc1);
			if (rt == MIPS_GPR_ZERO)
				ic->f = instr(nop);
			break;
		default:fatal("UNIMPLEMENTED cop1 (rs = %i)\n", rs);
			goto bad;
		}
		break;

	case HI6_SPECIAL2:
		switch (s6) {

		case SPECIAL2_MUL:
			ic->f = instr(mul);
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
			ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rt];
			ic->arg[2] = (size_t)&cpu->cd.mips.gpr[rd];
			if (rd == MIPS_GPR_ZERO)
				ic->f = instr(nop);
			break;

		case SPECIAL2_CLZ:
		case SPECIAL2_CLO:
		case SPECIAL2_DCLZ:
		case SPECIAL2_DCLO:
			switch (s6) {
			case SPECIAL2_CLZ:  ic->f = instr(clz); break;
			case SPECIAL2_CLO:  ic->f = instr(clo); break;
			case SPECIAL2_DCLZ: ic->f = instr(dclz); break;
			case SPECIAL2_DCLO: ic->f = instr(dclo); break;
			}
			ic->arg[0] = (size_t)&cpu->cd.mips.gpr[rs];
			ic->arg[1] = (size_t)&cpu->cd.mips.gpr[rd];
			if (rd == MIPS_GPR_ZERO)
				ic->f = instr(nop);
			break;

		default:goto bad;
		}
		break;

	default:goto bad;
	}

	if (x64)
		ic->f = instr(invalid_32_64);

	if (in_crosspage_delayslot)
		cpu->cd.mips.combination_check = NULL;

#define	DYNTRANS_TO_BE_TRANSLATED_TAIL
#include "cpu_dyntrans.c" 
#undef	DYNTRANS_TO_BE_TRANSLATED_TAIL
}

