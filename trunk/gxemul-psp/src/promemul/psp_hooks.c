
#include "psp_hle.h"

PSP_Hook *hle_hook;

void HLE_nohook(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
	debug("unimplemented hook: %s(%08x %08x %08x %08x) ",hle_hook->name,arg0,arg1,arg2,arg3);
	HLE_RETURN_INT(0x80000000);
}

#include "psp_autohle_hooks.c"

char *PSP_hook_getname(int32_t idx)
{
	if(idx<0) return "unknown";
	return pspmemhooks[idx].name;
}
int32_t PSP_hook_getargn(int32_t idx)
{
	if(idx<0) return 0;
	return pspmemhooks[idx].argn;
}

int32_t PSP_findhook_byname(char *s)
{
int i;
	for(i=0;i<(sizeof(pspmemhooks)/
                   sizeof(PSP_Hook));i++)
	{
		if(!strcmp(s,pspmemhooks[i].name))
		{
			return i;
		}
	}
	return -1;
}
PSP_Hook *PSP_findhook_ptr_byname(char *s)
{
int i;
//	debug("PSP_findhook_ptr_byname\n");
	for(i=0;i<(sizeof(pspmemhooks)/
                   sizeof(PSP_Hook));i++)
	{
		if(!strcmp(s,pspmemhooks[i].name))
		{
//			debug("PSP_findhook_ptr_byname end (ok)\n");
			return &pspmemhooks[i];
		}
	}
//	debug("PSP_findhook_ptr_byname end (NULL)\n");
	return NULL;
}


PSP_Hook **hooks;

int hookemul__psp_ishooked(struct cpu *cpu,uint32_t paddr)
{
uint32_t idx;
	paddr&=(0x03ffffff);
	idx=paddr>>2;
	if(hooks[idx])
		return idx;
	else
		return -1;
}

void hookemul__psp_registerhook(struct cpu *cpu,PSP_Hook *hook,uint32_t paddr)
{
uint32_t idx;
	if(paddr==0)
	{
		debug("hookemul__psp_registerhook no address!\n");
		return;
	}
	paddr&=(0x03ffffff);
	idx=paddr>>2;
	hooks[idx]=hook;
	debug("hookemul__psp_registerhook \"%s\" addr:%08x idx:%08x\n",hook->name,paddr,idx);
}

void hookemul__psp_registerhooksymbols(struct cpu *cpu)
{
int i;
	debug("hookemul__psp_registerhooksymbols\n");
	for(i=0;i<(sizeof(pspmemhooks)/sizeof(PSP_Hook));i++)
	{
		if(pspmemhooks[i].addr!=0)
		{
			debug("added symbol: %s\n",pspmemhooks[i].name);
			add_symbol_name(&cpu->machine->symbol_context,pspmemhooks[i].addr,0, pspmemhooks[i].name, 0, pspmemhooks[i].argn);
		}
	}
}

void hookemul__psp_registerallhooks(struct cpu *cpu)
{
int i;
	debug("hookemul__psp_registerallhooks\n");
	for(i=0;i<(sizeof(pspmemhooks)/
                   sizeof(PSP_Hook));i++)
	{
		if(pspmemhooks[i].addr!=0)
		{
			hookemul__psp_registerhook(cpu,PSP_findhook_ptr_byname(pspmemhooks[i].name),pspmemhooks[i].addr);
		}
		else
		{
			uint64_t addr=0;
			if(get_symbol_addr(&cpu->machine->symbol_context,pspmemhooks[i].name, &addr))
			{
				if(addr!=0)
				{
					hookemul__psp_registerhook(cpu,PSP_findhook_ptr_byname(pspmemhooks[i].name),addr);
				}
			}
		}
	}
}

void hookemul__psp_setup(struct cpu *cpu)
{
//	add_symbol_name(&cpu->machine->symbol_context,thread_stackframe,thread_stacksize, "thread_stackframe", 0, 0);
	debug("hookemul__psp_setup\n");
	hooks=malloc(sizeof(PSP_Hook*)*0x02000000);
	if(hooks==NULL)
	{
		fatal("out of memory");
		exit(-1);
	}
	memset(hooks,0,(sizeof(PSP_Hook*)*0x02000000));

	hookemul__psp_registerallhooks(cpu);
}

int hookemul__psp(struct cpu *cpu,uint32_t idx)
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

	hle_cpu=cpu;
	hle_hook=hooks[idx];

	if(hooks[idx]->func)
	{
		hle_numargs=hooks[idx]->argn;
		
	
		switch(hle_numargs)
		{
			case 0:
				hooks[idx]->func();
			break;
			case 1:
				hooks[idx]->func(hle_arg0);
			break;
			case 2:
				hooks[idx]->func(hle_arg0,hle_arg1);
			break;
			case 3:
				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2);
			break;
			case 4:
				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2,hle_arg3);
			break;
			case 5:
				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4);
			break;
			case 6:
				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5);
			break;
			case 7:
				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5,hle_arg6);
			break;
			case 8:
				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5,hle_arg6,hle_arg7);
			break;
			case 9:
 				hooks[idx]->func(hle_arg0,hle_arg1,hle_arg2,hle_arg3,hle_arg4,hle_arg5,hle_arg6,hle_arg7,hle_arg8);
			break;
		}

		if((hle_cpu->cd.mips.gpr[MIPS_GPR_V0]==0xffffffff)|((hle_cpu->cd.mips.gpr[MIPS_GPR_V0]>-1)&(hle_cpu->cd.mips.gpr[MIPS_GPR_V0]<10)))
		{
			debug("ret: %d\n",hle_cpu->cd.mips.gpr[MIPS_GPR_V0]);
		}	
		else
		{
			debug("ret: %08x\n",hle_cpu->cd.mips.gpr[MIPS_GPR_V0]);
		}	
	}

	return (1);
}

