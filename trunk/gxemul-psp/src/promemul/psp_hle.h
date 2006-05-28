#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "cpu_mips.h"
#include "emul.h"
#include "machine.h"
#include "memory.h"
#include "misc.h"

typedef struct
{
	int32_t w00;
	int32_t w01;
	int32_t w02;
	int32_t w03;
	int32_t w04;
	int32_t w05;
	int32_t w06;
	int32_t w07;
	int32_t w08;
	int32_t lib_ent;
	int32_t lib_ent_btm;
	int32_t lib_stub;
	int32_t lib_stub_btm;
}PSP_sceModuleInfo;
 
typedef struct
{
	int32_t modulestr;
	int32_t w01;
	int32_t w02;
	int32_t nidtable;
	int32_t stub;
}PSP_sceStubInfo;

typedef struct
{
	int32_t w00;	// jr $ra
	int32_t w01;    // nop
}PSP_Stub;

// functions in psp_syscalls.c
typedef struct
{
	int32_t idx;
	int32_t nid;
	int32_t addr;
	char *name;
	void (*func)();
	int32_t argn;
} PSP_Syscall; 

extern PSP_Syscall pspsyscalls[];

void HLE_unknown(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3);
char *PSP_syscall_getname(int32_t idx);

// functions in psp_hooks.c
typedef struct
{
	int32_t addr;
	char *name;
	void (*func)();
	int32_t argn;
} PSP_Hook; 

extern PSP_Hook pspmemhooks[];

void HLE_nohook(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3);
char *PSP_hook_getname(int32_t idx);
int32_t PSP_hook_getargn(int32_t idx);
int32_t PSP_findhook_byname(char *s);

void hookemul__psp_setup(struct cpu *cpu);
int hookemul__psp(struct cpu *cpu,uint32_t idx);

// functions from useremul.c
extern unsigned char *get_userland_string(struct cpu *cpu, uint64_t baseaddr);
extern unsigned char *get_userland_buf(struct cpu *cpu,	uint64_t baseaddr, uint64_t len);

// data in psp_syscalls.c
extern struct cpu *hle_cpu;

extern int32_t hle_numargs;

extern int32_t hle_arg0;
extern int32_t hle_arg1;
extern int32_t hle_arg2;
extern int32_t hle_arg3;
extern int32_t hle_arg4;
extern int32_t hle_arg5;
extern int32_t hle_arg6;
extern int32_t hle_arg7;
extern int32_t hle_arg8;
extern int32_t hle_arg9;
extern int32_t hle_arg10;


#define SYSCALL(_a,_b,_c,_d,_e,_f)
#define MEMHOOK(_c,_d,_e,_f)
#include "psp_autohle.h"


//#define HLE_RETURN_INT(_x)	return ((void*)((unsigned long)((_x))))
//#define HLE_RETURN_INT(_x)	hle_cpu->cd.mips.gpr[MIPS_GPR_V0]=((unsigned long)((_x)))
//#define HLE_RETURN_INT(_x)	hle_cpu->cd.mips.gpr[MIPS_GPR_V0]=(_x)

#define HLE_RETURN_INT(_x) { \
		if((_x)&0x80000000) hle_cpu->cd.mips.gpr[MIPS_GPR_V0]=0xffffffff00000000|(_x); \
		else hle_cpu->cd.mips.gpr[MIPS_GPR_V0]=(_x); \
	}
#define HLE_RETURN_PTR(_x) { \
		if((_x)&0x80000000) hle_cpu->cd.mips.gpr[MIPS_GPR_V0]=0xffffffff00000000|(_x); \
		else hle_cpu->cd.mips.gpr[MIPS_GPR_V0]=(_x); \
	}

#define HLE_RETURN_CALL3ARGS(_a,_a1,_a2,_a3) { \
	hle_cpu->cd.mips.gpr[MIPS_GPR_A0]=_a1; \
	hle_cpu->cd.mips.gpr[MIPS_GPR_A1]=_a2; \
	hle_cpu->cd.mips.gpr[MIPS_GPR_A2]=_a3; \
	hle_cpu->cd.mips.delay_jmpaddr=_a;     \
	hle_cpu->pc=_a;                        \
        }
//		hle_cpu->cd.mips.pc_last=_a;
