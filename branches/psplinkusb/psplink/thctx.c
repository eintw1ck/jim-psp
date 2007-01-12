/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * thctx.c - Thread context library code for psplink.
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL$
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsysmem_kernel.h>
#include <psputilsforkernel.h>
#include <pspmoduleexport.h>
#include <psploadcore.h>
#include <pspthreadman_kernel.h>
#include <pspsdk.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "psplink.h"
#include "libs.h"
#include "memoryUID.h"
#include "exception.h"

int threadFindContext(SceUID uid)
{
	SceKernelThreadKInfo info;
	struct SceThreadContext ctxCopy;
	int found = 0;
	int intc;

	SHELL_PRINT("Size: %x\n", sizeof(info));
	memset(&ctxCopy, 0, sizeof(ctxCopy));
	memset(&info, 0, sizeof(info));
	info.size = sizeof(info);

	intc = pspSdkDisableInterrupts();
	if(ThreadManForKernel_2D69D086(uid, &info) == 0)
	{
		found = 1;
		if(info.thContext)
		{
			memcpy(&ctxCopy, info.thContext, sizeof(ctxCopy));
		}
	}
	pspSdkEnableInterrupts(intc);

	if(found)
	{
		SHELL_PRINT("kstack 0x%08X kstacksize 0x%08X\n", (u32) info.kstack, info.kstackSize);
		SHELL_PRINT("stack  0x%08X stacksize  0x%08X\n", (u32) info.stack,  info.stackSize);
		SHELL_PRINT("context 0x%08X, vfpu 0x%08X\n", (u32) info.thContext, (u32) info.vfpuContext);
		SHELL_PRINT("Context EPC 0x%08X, Real EPC 0x%08X\n", ctxCopy.EPC, info.retAddr);
		exceptionPrintCPURegs((u32 *) &ctxCopy);
		return 0;
	}

	return -1;
}

/* Get the thread context of a user thread, trys to infer the real address */
int psplinkFindUserThreadContext(SceUID uid, struct PsplinkContext *ctx)
{
#if 0
	int intc;
	TCB *tcb;
	int ret = 1;

	intc = pspSdkDisableInterrupts();

	tcb = find_thread_tcb(uid);

	if(tcb)
	{
		if(tcb->attribute & PSP_THREAD_ATTR_USER)
		{
			CONTEXT *th = tcb->context;

			memset(ctx, 0, sizeof(struct PsplinkContext));
			ctx->thid = uid;
			memcpy(&ctx->regs.r[1], th->gpr, 31 * sizeof(u32));
			memcpy(&ctx->regs.fpr[0], th->fpr, 32 * sizeof(float));
			ctx->regs.hi = th->hi;
			ctx->regs.lo = th->lo;
			/* If thread context in kernel mode (i.e. in a syscall) */
			if(th->gpr[28] & 0x80000000)
			{
				struct ThreadKContext *kth;

				kth = (struct ThreadKContext *) (tcb->kstack + tcb->kstacksize - sizeof(struct ThreadKContext));
				ctx->regs.epc = kth->epc;
				ctx->regs.status = kth->status;
				ctx->regs.frame_ptr = kth->sp;
				ctx->regs.r[29] = kth->sp;
				ctx->regs.r[31] = kth->ra;
				ctx->regs.r[27] = kth->k1;
			}
			else
			{
				ctx->regs.epc = th->EPC;
				ctx->regs.status = th->SR;
				ctx->regs.frame_ptr = th->gpr[28];
			}
		}
	}

	pspSdkEnableInterrupts(intc);

	return ret;
#endif

	return 0;
}
