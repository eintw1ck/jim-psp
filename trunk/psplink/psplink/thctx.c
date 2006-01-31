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
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "psplink.h"
#include "libs.h"
#include "memoryUID.h"
#include "exception.h"

/* Structues for the thread context taken from florinsasu's post on the forums */
typedef struct tag_CONTEXT{
u32   type;            //+000
u32   gpr[31];         //+004
u32   fpr[32];         //+080
u32   fc31;            //+100
u32   hi;               //+104
u32   lo;               //+108
u32   SR;               //+10C
u32   EPC;            //+110
u32   field_114;         //+114
u32   field_118;         //+118
} CONTEXT; 

typedef struct tag_TCB{
	void  *link1, *link2;   //+00
	SceUID   thid;         //+08
	u32   status;         //+0C
	u32   currentPriority;//+10
	u32   wakeupCount;   //+14
	u32   exitStatus;      //+18
	u32   waitType;      //+1C
	void  *waitObject;   //+20
	u32   unk1[10];      //+24
	void  *cb_next;      //+4C
	void  *cb_prev;      //+50
	u32   unk2[3];      //+54
	u32   initPriority;   //+60
	u32   runClocks_lo;   //+64
	u32   runClocks_hi;   //+68
	u32   entry;         //+6C
	u32   stack;         //+70
	u32   stacksize;      //+74
	u32   sp;            //+78
	u32   kstack;         //+7C
	u32   kstacksize;      //+80
	u32   unk3;         //+84
	u32   gpReg;         //+88
	u32   unk4;         //+8C
	void  *klts;         //+90
	u32   unk5[15];      //+94
	u32   attribute;      //+D0
	u32   attribute_;      //+D4
	u32   argSize;      //+D8
	void  *argBlock;      //+DC
	u32   unk6[2];      //+E0
	u32   initPreemptCount;//+E8
	u32   threadPreemptCount;//+EC
	u32   releaseCount;   //+F0
	CONTEXT   *context;      //+F4
	u32    unk7;         //+F8
	void   *vfpu_context;   //+FC
} TCB;
 
static TCB *find_thread_tcb(SceUID uid)
{
	void *pUid;
	TCB *tcb = NULL;

	pUid = (void *) findObjectByUID(uid);
	if(pUid)
	{
		tcb = (TCB *) (pUid + 0x30);
	}

	return tcb;
}

int threadFindContext(SceUID uid)
{
	TCB *tcb = find_thread_tcb(uid);

	if(tcb)
	{
		TCB tcbCopy;
		CONTEXT ctxCopy;

		memcpy(&tcbCopy, tcb, sizeof(tcbCopy));
		memcpy(&ctxCopy, tcb->context, sizeof(ctxCopy));
		printf("TCB 0x%p\n", tcb);
		printf("kstack 0x%08X kstacksize 0x%08X\n", tcbCopy.kstack, tcbCopy.kstacksize);
		printf("stack  0x%08X stacksize  0x%08X\n", tcbCopy.stack, tcbCopy.stacksize);
		printf("context 0x%p, vfpu 0x%p\n", tcbCopy.context, tcbCopy.vfpu_context);
		printf("EPC 0x%08X\n", ctxCopy.EPC);
		exceptionPrintCPURegs((u32 *) &ctxCopy);
		return 1;
	}

	return 0;
}
