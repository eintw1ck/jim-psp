#include "psp_hle.h"

SYSCALL(0x206d,0x446d8de6,0x00000000,"sceKernelCreateThread",HLE_sceKernelCreateThread,4);
SYSCALL(0x206e,0x9fa03cd3,0x00000000,"sceKernelDeleteThread",HLE_unknown,4);
SYSCALL(0x206f,0xf475845d,0x00000000,"sceKernelStartThread",HLE_sceKernelStartThread,3);
SYSCALL(0x2070,0x532a522e,0x00000000,"_sceKernelExitThread",HLE_unknown,4);
SYSCALL(0x2071,0xaa73c935,0x00000000,"sceKernelExitThread",HLE_unknown,4);
SYSCALL(0x2072,0x809ce29b,0x00000000,"sceKernelExitDeleteThread",HLE_sceKernelExitDeleteThread,1);
SYSCALL(0x2073,0x616403ba,0x00000000,"sceKernelTerminateThread",HLE_unknown,4);
SYSCALL(0x2074,0x383f7bcc,0x00000000,"sceKernelTerminateDeleteThread",HLE_unknown,4);
SYSCALL(0x2075,0x3ad58b8c,0x00000000,"sceKernelSuspendDispatchThread",HLE_unknown,4);
SYSCALL(0x2076,0x27e22ec2,0x00000000,"sceKernelResumeDispatchThread",HLE_unknown,4);
SYSCALL(0x2077,0xea748e31,0x00000000,"sceKernelChangeCurrentThreadAttr",HLE_unknown,4);
SYSCALL(0x2078,0x71bc9871,0x00000000,"sceKernelChangeThreadPriority",HLE_unknown,4);
SYSCALL(0x2079,0x912354a7,0x00000000,"sceKernelRotateThreadReadyQueue",HLE_unknown,4);
SYSCALL(0x207a,0x2c34e053,0x00000000,"sceKernelReleaseWaitThread",HLE_unknown,4);
SYSCALL(0x207b,0x293b45b8,0x00000000,"sceKernelGetThreadId",HLE_unknown,4);
SYSCALL(0x207c,0x94aa61ee,0x00000000,"sceKernelGetThreadCurrentPriority",HLE_unknown,4);
SYSCALL(0x207d,0x3b183e26,0x00000000,"sceKernelGetThreadExitStatus",HLE_unknown,4);
SYSCALL(0x207e,0xd13bde95,0x00000000,"sceKernelCheckThreadStack",HLE_unknown,4);
SYSCALL(0x207f,0x52089ca1,0x00000000,"sceKernelGetThreadStackFreeSize",HLE_unknown,4);
SYSCALL(0x2080,0x17c1684e,0x00000000,"sceKernelReferThreadStatus",HLE_unknown,4);
SYSCALL(0x2081,0xffc36a14,0x00000000,"sceKernelReferThreadRunStatus",HLE_unknown,4);
SYSCALL(0x2082,0x627e6f3a,0x00000000,"sceKernelReferSystemStatus",HLE_unknown,4);
SYSCALL(0x2083,0x94416130,0x00000000,"sceKernelGetThreadmanIdList",HLE_sceKernelGetThreadmanIdList,4);
SYSCALL(0x2084,0x57cf62dd,0x00000000,"sceKernelGetThreadmanIdType",HLE_unknown,4);
SYSCALL(0x2085,0x64d4540e,0x00000000,"sceKernelReferThreadProfiler",HLE_unknown,4);
SYSCALL(0x2086,0x8218b4dd,0x00000000,"sceKernelReferGlobalProfiler",HLE_unknown,4);

typedef struct
{
	char *name;
	int32_t func;
	int32_t prio;
	int32_t stacksize;
} PSP_Thread; 

PSP_Thread threads[10];
int        numthreads=0;


void HLE_sceKernelCreateThread(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
char *name;
	name=get_userland_string(hle_cpu, arg0);
	threads[numthreads].name=name;
	threads[numthreads].func=arg1;
	threads[numthreads].prio=arg2;
	threads[numthreads].stacksize=arg3;
	debug("HLE_sceKernelCreateThread(Name:%s Func:%08x Priority:%08x Stacksize:%08x) ",
		threads[numthreads].name,threads[numthreads].
		func,threads[numthreads].prio,threads[numthreads].stacksize);
	numthreads++;
	HLE_RETURN_INT(numthreads-1);
//	free(name);
}
void HLE_sceKernelStartThread(int32_t thid,int32_t args,int32_t argp)
{
	debug("HLE_sceKernelStartThread(thid:%08x args:%08x argp:%08x) ",thid,args,argp);
	if(thid==0)
	{
		hle_cpu->pc=threads[0].func;
		hle_cpu->cd.mips.pc_last=threads[0].func;
		hle_cpu->cd.mips.gpr[MIPS_GPR_RA]=threads[0].func;
		hle_cpu->cd.mips.delay_jmpaddr=threads[0].func;
	
		hle_cpu->cd.mips.gpr[MIPS_GPR_A0]=args;
		hle_cpu->cd.mips.gpr[MIPS_GPR_A1]=argp;
	}
	HLE_RETURN_INT(0);
}
 
//int sceKernelExitDeleteThread(int status);
void HLE_sceKernelExitDeleteThread(int32_t arg0)
{
	debug("HLE_sceKernelExitDeleteThread(status:%08x) ",arg0);
	HLE_RETURN_INT(0);
}

//int sceKernelGetThreadmanIdList(enum SceKernelIdListType type, SceUID *readbuf, int readbufsize, int *idcount);
void HLE_sceKernelGetThreadmanIdList(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
	debug("HLE_sceKernelGetThreadmanIdList(SceKernelIdListType:%08x readbuf:%08x readbufsize:%08x idcount:%08x) ",
		arg0,arg1,arg2,arg3);
	HLE_RETURN_INT(0);
//	free(name);
}
