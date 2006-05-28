
#include "psp_hle.h"




int32_t hle_syscall;
int32_t hle_numargs;

int32_t hle_arg0;
int32_t hle_arg1;
int32_t hle_arg2;
int32_t hle_arg3;
int32_t hle_arg4;
int32_t hle_arg5;
int32_t hle_arg6;
int32_t hle_arg7;
int32_t hle_arg8;
int32_t hle_arg9;
int32_t hle_arg10;
/*
int32_t hle_stack0;
int32_t hle_stack1;
int32_t hle_stack2;
int32_t hle_stack3;
*/
//int32_t hle_ret;
//int32_t hle_pc;
struct cpu *hle_cpu;


void HLE_unknown(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
	debug("unimplemented syscall: %s(%08x %08x %08x %08x) ",PSP_syscall_getname(hle_syscall),arg0,arg1,arg2,arg3);
//	return -1;
	HLE_RETURN_INT(0x80000000);
}



/**
 * Get the firmware version.
 * 
 * @returns The firmware version.
 * 0x01000300 on v1.00 unit
 * 0x01050001 on v1.50 unit
 */

// v1.0: 0x20db
void HLE_sceKernelDevkitVersion(void)
{
	debug("HLE_sceKernelDevkitVersion() ");
	HLE_RETURN_INT(0x02000000);
}

#include "psp_autohle.c"

char *PSP_syscall_getname(int32_t idx)
{
	if(idx==0) return "unknown";
	return pspsyscalls[idx-0x2000].name;
}
int32_t PSP_syscall_getargn(int32_t idx)
{
	if(idx==0) return 0;
	return pspsyscalls[idx-0x2000].argn;
}

int32_t PSP_findsyscall_bynid(int32_t nid)
{
int i;
	for(i=0;i<(sizeof(pspsyscalls)/sizeof(PSP_Syscall));i++)
	{
		if(nid==pspsyscalls[i].nid)
		{
			return pspsyscalls[i].idx;
		}
	}
	return 0;
}
int32_t PSP_findsyscall_byname(char *s)
{
int i;
	for(i=0;i<(sizeof(pspsyscalls)/sizeof(PSP_Syscall));i++)
	{
		if(!strcmp(s,pspsyscalls[i].name))
		{
			return pspsyscalls[i].idx;
		}
	}
	return 0;
}

void PSP_syscall_hle(int32_t idx)
{

//	debug("numsyscalls: %08x\n",(sizeof(pspsyscalls)/sizeof(PSP_Syscall)));

	hle_syscall=idx;
//	hle_ret=0;

//	debug("HLE PC:%08x (syscall %04x) ",hle_cpu->pc,idx);
	debug("HLE RA:%08x (syscall %04x) ",hle_cpu->cd.mips.gpr[MIPS_GPR_RA],idx);

	if((idx>=0x2000)&(idx<(0x2000+(sizeof(pspsyscalls)/sizeof(PSP_Syscall)))))
	{

		hle_numargs=pspsyscalls[idx-0x2000].argn;
	
		switch(hle_numargs)
		{
			case 0:
				pspsyscalls[idx-0x2000].func();
			break;
			case 1:
				pspsyscalls[idx-0x2000].func(hle_arg0);
			break;
			case 2:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1);
			break;
			case 3:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2);
			break;
			case 4:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2,hle_arg3);
			break;
			case 5:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4);
			break;
			case 6:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5);
			break;
			case 7:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5,hle_arg6);
			break;
			case 8:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5,hle_arg6,hle_arg7);
			break;
			case 9:
				pspsyscalls[idx-0x2000].func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5,hle_arg6,hle_arg7,hle_arg8);
			break;
		}

	}
	else
	{
		HLE_unknown(hle_arg0,hle_arg1,hle_arg2,hle_arg3);
	}

	if((hle_cpu->cd.mips.gpr[MIPS_GPR_V0]==0xffffffff)|((hle_cpu->cd.mips.gpr[MIPS_GPR_V0]>-1)&(hle_cpu->cd.mips.gpr[MIPS_GPR_V0]<10)))
	{
		debug("retcode: %d\n",hle_cpu->cd.mips.gpr[MIPS_GPR_V0]);
	}	
	else
	{
		debug("retcode: %08x\n",hle_cpu->cd.mips.gpr[MIPS_GPR_V0]);
	}	

//	return hle_ret;
}

/* for a user program */
/*
struct SceKernelLoadExecParam 
{
         SceSize     size;
         SceSize     args;
         void *  argp;
         const char *    key;
};
int sceKernelLoadExec(const char *file, struct SceKernelLoadExecParam *param)
*/

void useremul__psp_setup(struct cpu *cpu, int argc, char **host_argv)
{
	int i;
	uint32_t func_stacktop,func_stackframe,func_stacksize,func_stackptr;
	uint32_t thread_stacktop,thread_stackframe,thread_stacksize,thread_stackptr;


	uint64_t cur_argv,cur_argv1;
	uint64_t stack_top = 0x09fff000;
	uint64_t stacksize = 1 * 1048576;
	uint64_t stack_margin = 16384;
	int envc = 1;
	int i2;

	thread_stacktop=0x09fffff0;
	thread_stacksize=16384;
	thread_stackframe=thread_stacktop-thread_stacksize;
	thread_stackptr=thread_stackframe;

	func_stacktop   = (thread_stackptr);
	func_stacksize  = (64*1024);
	func_stackframe = (func_stacktop-func_stacksize);

	/*  Stack contents:  (TODO: is this correct?)  */
//	store_32bit_word(cpu, stack_top - stack_margin, argc);

	/*  Store all environment strings:  */
	cur_argv1 = cur_argv = stack_top - stack_margin + 128 + (argc + envc) * sizeof(uint32_t);
	for (i=0; i<argc; i++) {
		debug("adding argv[%i] at %08x: '%s'\n",i,cur_argv,host_argv[i]);
/*
		store_32bit_word(cpu, 
		stack_top - stack_margin + 4 + i*sizeof(uint32_t), 
                cur_argv);
*/
		store_string(cpu, cur_argv, host_argv[i]);
		cur_argv += strlen(host_argv[i]) + 1;
	}
	/*  Store a NULL value between the args and the environment strings:  */
	store_32bit_word(cpu, stack_top - stack_margin + 4 + i*sizeof(uint32_t), 0);  i++;

	cpu->cd.mips.gpr[MIPS_GPR_A0] = 1; // length of argstring in bytes
	cpu->cd.mips.gpr[MIPS_GPR_A1] = cur_argv1; // length of argstring in bytes

/* 
	generic
*/

	cpu->cd.mips.gpr[25] = cpu->pc;		/*  reg. t9  */
	cpu->cd.mips.gpr[MIPS_GPR_SP] = (int32_t)func_stackframe;

	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A0],4, "arg0", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A1],4, "arg1", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A2],4, "arg2", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A3],4, "arg3", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,func_stackframe,func_stacksize, "func_stackframe", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,thread_stackframe,thread_stacksize, "thread_stackframe", 0, 0);

	hookemul__psp_registerhooksymbols(cpu);
	hookemul__psp_setup(cpu);

}

/* for the loadexec payload */
/*
sub_88c00000($s2,$s1,$s3);
*/

void useremul__psp_loadexecpayload_setup(struct cpu *cpu, int argc, char **host_argv)
{
	int i;
	uint32_t func_stacktop,func_stackframe,func_stacksize,func_stackptr;
	uint32_t thread_stacktop,thread_stackframe,thread_stacksize,thread_stackptr;

	thread_stacktop=0x89000000;
	thread_stacksize=16384;
	thread_stackframe=thread_stacktop-thread_stacksize;
	thread_stackptr=thread_stackframe;

	func_stacktop   = (0x89000000);
	func_stacksize  = (64);
	func_stackframe = (func_stacktop-func_stacksize);

	for(i=0;i<32;i++)
	{
		char name[10];
		cpu->cd.mips.gpr[i] = (int)(0xde008000+(i<<16));
		sprintf(name,"dead_%s",allegrex_regname(cpu->machine,i));
		add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[i],0x7fff,name, 0, 0);
	}

	cpu->cd.mips.gpr[MIPS_GPR_RA] =  cpu->pc;	/* put calling function in RA, since there is no,
								we use PC - that will just restart the
								function again */
	/* 0x30 bytes */
	cpu->cd.mips.gpr[MIPS_GPR_A0] =  (int32_t)thread_stackptr;	/* arg at a0+...0x2c */

	add_symbol_name(&cpu->machine->symbol_context,thread_stackptr,0x30, "arg0_data", 0, 0);
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x00, 0x00000000);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x04, 0x10000001);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x08, 0x10000002);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x0c, 0x10000003);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x10, 0x10000004);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x14, 0x10000005);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x18, 0x10000006);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x1c, 0x10000007);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x20, 0x10000008);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x24, 0x10000009);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x28, 0x1000000a);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x2c, 0x1000000b);	
	thread_stackptr+=0x30;

	/* 0x24 bytes */
	cpu->cd.mips.gpr[MIPS_GPR_A1] =  (int32_t)thread_stackptr;	/* arg at a1+...0x24 */

	add_symbol_name(&cpu->machine->symbol_context,thread_stackptr,0x24, "arg1_data", 0, 0);
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x00, 0x20000000);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x04, 0x20000001);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x08, 0x20000002);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x0c, 0x20000003);	// ptr to 0x100 bytes	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x10, 0x20000004);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x14, 0x20000005);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x18, 0x20000006);	// ptr to 0x100 bytes
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x1c, 0x20000007);	// ptr to 0x100 bytes	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x20, 0x20000008);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x24, 0x20000009);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x28, 0x2000000a);	
	store_32bit_word(cpu, (int32_t)thread_stackptr+0x2c, 0x2000000b);	
	thread_stackptr+=0x24;

//add_symbol_name(struct symbol_context *sc,uint64_t addr, uint64_t len, char *name, int type, int n_args)
	add_symbol_name(&cpu->machine->symbol_context,0x88c001e0,0, "start", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c00400,0, "sub_88c00400", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c0058c,0, "bootprx", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c00e80,0, "kactivate", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c011ec,0, "sub_88c011ec", 0, 4);
//	add_symbol_name(&cpu->machine->symbol_context,0x88c01bb0,0, "kprintf", 0, 8);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01c4c,0, "set_funcptr_88c16d54", 0, 1);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01c9c,0, "set_funcptr_88c16d58", 0, 1);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01cdc,0, "set_funcptr_88c16d5c", 0, 1);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01cf8,0, "set_dword_88C16994", 0, 1);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01d08,0, "sub_88c01d08", 0, 2);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01d20,0, "sub_88c01d20", 0, 1);
	add_symbol_name(&cpu->machine->symbol_context,0x88c01d4c,0, "get_dword_88C16D60", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c02c64,0, "irqstuff_88c02c64", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c02c90,0x24, "irqstuff_88c02c90", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c02e00,0, "sub_88c02e00", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c02e68,0, "sub_88c02e68", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c03014,0, "sub_88c03014", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c03090,0, "sub_88c03090", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c031f0,0, "memcpy", 0, 3);
	add_symbol_name(&cpu->machine->symbol_context,0x88c03b80,0, "instruction_cache_stuff_88C03B80", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c03f50,0, "instruction_cache_stuff_88c03f50", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c04104,0, "exception_and_uart4_stuff_88c04104", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c041d8,0, "sub_88c041d8", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c04484,0, "uart4_stuff_88c04484", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c044f4,0, "sub_88c044f4", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c05060,0, "sceKernelCheckExecFile", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c05394,0, "sceKernelProbeExecuteableObject", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c05e9c,0, "sub_88c05e9c", 0, 4);
	add_symbol_name(&cpu->machine->symbol_context,0x88c06314,0, "CheckPspCompress", 0, 4);


	add_symbol_name(&cpu->machine->symbol_context,0x88C1404C,0, ".binfile.data", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88C1404C,0, ".binfile.data.strings", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88C1428c,0, ".binfile.data.pointer", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c04434,0, ".binfile.data.1", 0, 0);	// loc_88C013A4
	add_symbol_name(&cpu->machine->symbol_context,0x88c04454,0, ".binfile.data.2", 0, 0);	// loc_88C01420

	add_symbol_name(&cpu->machine->symbol_context,0x88C14470,0, ".binfile.data.strings2", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c04508,0, ".binfile.data.3", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88C14530,0, ".binfile.data.pointer2", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88C14778,0, ".binfile.nids", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88C14808,0, ".binfile.nids2", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88C1490c,0, ".binfile.data.strings3", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88C16878,0, ".binfile.data.sometable", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88C16c30,0, ".binfile.data.flashfattable", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88c187fc,0, ".binfile.data.4", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88c18820,0, ".binfile.data.5", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c18920,0, ".binfile.data.6", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c18a20,0, ".binfile.data.7", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88c18b20,0, ".binfile.data.8", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c18d20,0, ".binfile.data.9", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x88c18d24,0, ".binfile.data.a", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,0x88c19028,0, ".binfile.data.b", 0, 0);

/* 
	generic
*/

	cpu->cd.mips.gpr[25] = cpu->pc;		/*  reg. t9  */
	cpu->cd.mips.gpr[MIPS_GPR_SP] = (int32_t)func_stackframe;

	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A0],4, "arg0", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A1],4, "arg1", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A2],4, "arg2", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A3],4, "arg3", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,func_stackframe,func_stacksize, "func_stackframe", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,thread_stackframe,thread_stacksize, "thread_stackframe", 0, 0);

	hookemul__psp_registerhooksymbols(cpu);
	hookemul__psp_setup(cpu);
/*
	hookemul__psp_registerhook(cpu,PSP_findhook_ptr_byname("kprintf"),0x88c01bb0);
	hookemul__psp_registerhook(cpu,PSP_findhook_ptr_byname("memcpy"),0x88c031f0);

	hookemul__psp_registerhook(cpu,PSP_findhook_ptr_byname("sceKernelCheckExecFile"),0x88c05060);
*/
}

/* for the ipl bootstrap */
/*
void _boot(void);
*/

void useremul__psp_iplbootstrap_setup(struct cpu *cpu, int argc, char **host_argv)
{
	int i;
	uint32_t func_stacktop,func_stackframe,func_stacksize,func_stackptr;
	uint32_t thread_stacktop,thread_stackframe,thread_stacksize,thread_stackptr;

	thread_stacktop=0x89000000;
	thread_stacksize=16384;
	thread_stackframe=thread_stacktop-thread_stacksize;
	thread_stackptr=thread_stackframe;

	func_stacktop   = (0x89000000);
	func_stacksize  = (64);
	func_stackframe = (func_stacktop-func_stacksize);

	for(i=0;i<32;i++)
	{
		char name[10];
		cpu->cd.mips.gpr[i] = (int)(0xde008000+(i<<16));
		sprintf(name,"dead_%s",allegrex_regname(cpu->machine,i));
		add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[i],0x7fff,name, 0, 0);
	}

	cpu->cd.mips.gpr[MIPS_GPR_RA] =  cpu->pc;	/* put calling function in RA, since there is no,
								we use PC - that will just restart the
								function again */

//add_symbol_name(struct symbol_context *sc,uint64_t addr, uint64_t len, char *name, int type, int n_args)
	add_symbol_name(&cpu->machine->symbol_context,0x84000000,0, "start", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,0x8400011c,0, "sub_11c", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84000138,0, "sub_138", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84000154,0, "sub_154", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84000180,0, "sub_180", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x840001f0,0, "sub_1f0", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x8400022c,0, "sub_22c", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84000238,0, "sub_238", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84000254,0, "sub_254", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x8400029c,0, "sub_29c", 0,-1);

	add_symbol_name(&cpu->machine->symbol_context,0x84009b4c,0, "sub_9b4c", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84009c20,0, "sub_9c20", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84009c40,0, "sub_9c40", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84009d68,0, "sub_9d68", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84009da8,0, "sub_9da8", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84009de8,0, "sub_9de8", 0,-1);
	add_symbol_name(&cpu->machine->symbol_context,0x84009eb0,0, "sub_9eb0", 0,-1);

//	add_symbol_name(&cpu->machine->symbol_context,0x88C1404C,0, ".binfile.data", 0, 0);

/* 
	generic
*/

	cpu->cd.mips.gpr[25] = cpu->pc;		/*  reg. t9  */
	cpu->cd.mips.gpr[MIPS_GPR_SP] = (int32_t)func_stackframe;

	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A0],4, "arg0", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A1],4, "arg1", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A2],4, "arg2", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A3],4, "arg3", 0, 0);

	add_symbol_name(&cpu->machine->symbol_context,func_stackframe,func_stacksize, "func_stackframe", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,thread_stackframe,thread_stacksize, "thread_stackframe", 0, 0);

	hookemul__psp_registerhooksymbols(cpu);
	hookemul__psp_setup(cpu);

}


void useremul__psp(struct cpu *cpu, uint32_t code)
{
	hle_arg0 = cpu->cd.mips.gpr[MIPS_GPR_A0];
	hle_arg1 = cpu->cd.mips.gpr[MIPS_GPR_A1];
	hle_arg2 = cpu->cd.mips.gpr[MIPS_GPR_A2];
	hle_arg3 = cpu->cd.mips.gpr[MIPS_GPR_A3];

	hle_arg4 = cpu->cd.mips.gpr[MIPS_GPR_T0];
	hle_arg5 = cpu->cd.mips.gpr[MIPS_GPR_T1];
	hle_arg6 = cpu->cd.mips.gpr[MIPS_GPR_T2];
	hle_arg7 = cpu->cd.mips.gpr[MIPS_GPR_T3];

	/*  TODO:  stack arguments? Are these correct?  */
	hle_arg8 = load_32bit_word(cpu, cpu->cd.mips.gpr[MIPS_GPR_SP] + 0);
	hle_arg9 = load_32bit_word(cpu, cpu->cd.mips.gpr[MIPS_GPR_SP] + 4);
	hle_arg10= load_32bit_word(cpu, cpu->cd.mips.gpr[MIPS_GPR_SP] + 8);
/*
we cant add symbols without re-sorting :/
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A0],0, "arg0", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A1],0, "arg1", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A2],0, "arg2", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_A3],0, "arg3", 0, 0);
	add_symbol_name(&cpu->machine->symbol_context,cpu->cd.mips.gpr[MIPS_GPR_SP],0, "func_stackframe", 0, 0);
*/
	hle_cpu=cpu;
	PSP_syscall_hle(code);
}

