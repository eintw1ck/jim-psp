
/*  AUTOMATICALLY GENERATED! Do not edit.  */

#define DYNTRANS_MAX_VPH_TLB_ENTRIES MIPS_MAX_VPH_TLB_ENTRIES
#define DYNTRANS_ARCH mips
#define DYNTRANS_MIPS
#ifdef DYNTRANS_32
#define DYNTRANS_1LEVEL
#endif
#ifndef DYNTRANS_PAGESIZE
#define DYNTRANS_PAGESIZE 4096
#endif
#define DYNTRANS_IC mips_instr_call
#define DYNTRANS_IC_ENTRIES_PER_PAGE MIPS_IC_ENTRIES_PER_PAGE
#define DYNTRANS_INSTR_ALIGNMENT_SHIFT MIPS_INSTR_ALIGNMENT_SHIFT
#define DYNTRANS_TC_PHYSPAGE mips_tc_physpage
#define DYNTRANS_INVALIDATE_TLB_ENTRY mips_invalidate_tlb_entry
#define DYNTRANS_ADDR_TO_PAGENR MIPS_ADDR_TO_PAGENR
#define DYNTRANS_PC_TO_IC_ENTRY MIPS_PC_TO_IC_ENTRY
#define DYNTRANS_TC_ALLOCATE mips_tc_allocate_default_page
#define DYNTRANS_TC_PHYSPAGE mips_tc_physpage
#define DYNTRANS_PC_TO_POINTERS mips_pc_to_pointers
#define DYNTRANS_PC_TO_POINTERS_GENERIC mips_pc_to_pointers_generic
#define COMBINE_INSTRUCTIONS mips_combine_instructions
#define DISASSEMBLE mips_cpu_disassemble_instr

extern volatile int single_step, single_step_breakpoint;
extern int debugger_n_steps_left_before_interaction;
extern int old_show_trace_tree;
extern int old_instruction_trace;
extern int old_quiet_mode;
extern int show_opcode_statistics;
extern int dyntrans_backend_enable;
extern int quiet_mode;

/* instr uses the same names as in cpu_mips_instr.c */
#define instr(n) mips_instr_ ## n

#ifdef DYNTRANS_DUALMODE_32
#define instr32(n) mips32_instr_ ## n

#endif

/*  This is for marking a physical page as containing
    combined instructions:  */
#define combined (cpu->cd.mips.cur_physpage->flags |= COMBINATIONS)

#define X(n) void mips_instr_ ## n(struct cpu *cpu, \
 struct mips_instr_call *ic)

/*
 *  nothing:  Do nothing.
 *
 *  The difference between this function and a "nop" instruction is that
 *  this function does not increase the program counter or the number of
 *  translated instructions.  It is used to "get out" of running in translated
 *  mode.
 *
 *  IMPORTANT NOTE: Do a   cpu->running_translated = 0;
 *                  before setting cpu->cd.mips.next_ic = &nothing_call;
 */
X(nothing)
{
	cpu->n_translated_instrs --;
	cpu->cd.mips.next_ic --;
}

#ifdef DYNTRANS_VARIABLE_INSTRUCTION_LENGTH
static struct mips_instr_call nothing_call = { instr(nothing), {0,0,0} };
#else
static struct mips_instr_call nothing_call = { instr(nothing), {0,0,0} };
#endif

