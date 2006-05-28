
/*
 *  AUTOMATICALLY GENERATED! Do not edit.
 */

#ifdef DYNTRANS_32
#define MODE32
#endif
#define DYNTRANS_FUNCTION_TRACE mips_cpu_functioncall_trace
#include "cpu_dyntrans.c"
#undef DYNTRANS_FUNCTION_TRACE

#define DYNTRANS_TC_ALLOCATE_DEFAULT_PAGE mips_tc_allocate_default_page
#include "cpu_dyntrans.c"
#undef DYNTRANS_TC_ALLOCATE_DEFAULT_PAGE

#define DYNTRANS_INVAL_ENTRY
#include "cpu_dyntrans.c"
#undef DYNTRANS_INVAL_ENTRY

#define DYNTRANS_INVALIDATE_TC mips_invalidate_translation_caches
#include "cpu_dyntrans.c"
#undef DYNTRANS_INVALIDATE_TC

#define DYNTRANS_INVALIDATE_TC_CODE mips_invalidate_code_translation
#include "cpu_dyntrans.c"
#undef DYNTRANS_INVALIDATE_TC_CODE

#define DYNTRANS_UPDATE_TRANSLATION_TABLE mips_update_translation_table
#include "cpu_dyntrans.c"
#undef DYNTRANS_UPDATE_TRANSLATION_TABLE

#define MEMORY_RW mips_memory_rw
#define MEM_MIPS
#include "../memory_rw.c"
#undef MEM_MIPS
#undef MEMORY_RW

#define DYNTRANS_PC_TO_POINTERS_FUNC mips_pc_to_pointers
#define DYNTRANS_PC_TO_POINTERS_GENERIC mips_pc_to_pointers_generic
#include "cpu_dyntrans.c"
#undef DYNTRANS_PC_TO_POINTERS_FUNC

#undef DYNTRANS_PC_TO_POINTERS_GENERIC

#define COMBINE_INSTRUCTIONS mips_combine_instructions
#ifndef DYNTRANS_32
#define reg(x) (*((uint64_t *)(x)))
#define MODE_uint_t uint64_t
#define MODE_int_t int64_t
#else
#define reg(x) (*((uint32_t *)(x)))
#define MODE_uint_t uint32_t
#define MODE_int_t int32_t
#endif
#define COMBINE(n) mips_combine_ ## n
#include "quick_pc_to_pointers.h"
#include "cpu_mips_instr.c"

#ifdef DYNTRANS_DUALMODE_32
#undef COMBINE_INSTRUCTIONS
#define COMBINE_INSTRUCTIONS mips32_combine_instructions
#undef X
#undef instr
#undef reg
#define X(n) void mips32_instr_ ## n(struct cpu *cpu, \
	struct mips_instr_call *ic)
#define instr(n) mips32_instr_ ## n
#ifdef HOST_LITTLE_ENDIAN
#define reg(x) ( *((uint32_t *)(x)) )
#else
#define reg(x) ( *((uint32_t *)(x)+1) )
#endif
#define MODE32
#undef MODE_uint_t
#undef MODE_int_t
#define MODE_uint_t uint32_t
#define MODE_int_t int32_t
#define DYNTRANS_INVAL_ENTRY
#undef DYNTRANS_INVALIDATE_TLB_ENTRY
#define DYNTRANS_INVALIDATE_TLB_ENTRY mips32_invalidate_tlb_entry
#include "cpu_dyntrans.c"
#undef DYNTRANS_INVAL_ENTRY

#define DYNTRANS_INVALIDATE_TC mips32_invalidate_translation_caches
#include "cpu_dyntrans.c"
#undef DYNTRANS_INVALIDATE_TC

#define DYNTRANS_INVALIDATE_TC_CODE mips32_invalidate_code_translation
#include "cpu_dyntrans.c"
#undef DYNTRANS_INVALIDATE_TC_CODE

#define DYNTRANS_UPDATE_TRANSLATION_TABLE mips32_update_translation_table
#include "cpu_dyntrans.c"
#undef DYNTRANS_UPDATE_TRANSLATION_TABLE

#define DYNTRANS_PC_TO_POINTERS_FUNC mips32_pc_to_pointers
#define DYNTRANS_PC_TO_POINTERS_GENERIC mips32_pc_to_pointers_generic
#undef DYNTRANS_PC_TO_POINTERS
#define DYNTRANS_PC_TO_POINTERS mips32_pc_to_pointers
#include "cpu_dyntrans.c"
#undef DYNTRANS_PC_TO_POINTERS_FUNC

#undef DYNTRANS_PC_TO_POINTERS_GENERIC

#undef COMBINE
#define COMBINE(n) mips32_combine_ ## n
#include "quick_pc_to_pointers.h"
#include "cpu_mips_instr.c"

#undef DYNTRANS_PC_TO_POINTERS
#define DYNTRANS_PC_TO_POINTERS mips_pc_to_pointers
#define DYNTRANS_PC_TO_POINTERS32 mips32_pc_to_pointers

#endif /*  DYNTRANS_DUALMODE_32  */


#define DYNTRANS_CPU_RUN_INSTR mips_cpu_run_instr
#include "cpu_dyntrans.c"
#undef DYNTRANS_CPU_RUN_INSTR

#define CPU_RUN mips_cpu_run
#define CPU_RINSTR mips_cpu_run_instr
#define CPU_RUN_MIPS
#include "cpu_run.c"
#undef CPU_RINSTR
#undef CPU_RUN_MIPS
#undef CPU_RUN

CPU_FAMILY_INIT(mips,"MIPS")

