/*
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>

//#include "psp_bios.h"
#include "cop0.h"
#include "console.h"
#include "cpu.h"
#include "cpu_mips.h"
#include "diskimage.h"
#include "machine.h"
#include "memory.h"
#include "misc.h"
#include "symbol.h"


extern int quiet_mode;

/*
 *  pspbios_init():
 */
void pspbios_init(struct machine *machine, struct cpu *cpu)
{
	FILE *f;
	int len;
	char c;
	int ptr;

	debug("pspbios_init\n");

	cpu->cd.mips.coproc[0]->reg[0] = 0;
	cpu->cd.mips.coproc[0]->reg[1] = 0;
	cpu->cd.mips.coproc[0]->reg[2] = 0;
	cpu->cd.mips.coproc[0]->reg[3] = 0;
	cpu->cd.mips.coproc[0]->reg[4] = 0;
	cpu->cd.mips.coproc[0]->reg[5] = 0;
	cpu->cd.mips.coproc[0]->reg[6] = 0;
	cpu->cd.mips.coproc[0]->reg[7] = 0;
	cpu->cd.mips.coproc[0]->reg[COP0_BADVADDR] = 0xe3fc4cc7;
	cpu->cd.mips.coproc[0]->reg[COP0_COUNT] = 0x18e71a74;
	cpu->cd.mips.coproc[0]->reg[COP0_ENTRYHI] = 0;
	cpu->cd.mips.coproc[0]->reg[11] = 0;
	cpu->cd.mips.coproc[0]->reg[COP0_STATUS] = 0x20008601;
	cpu->cd.mips.coproc[0]->reg[COP0_CAUSE] = 0x80000020;
	cpu->cd.mips.coproc[0]->reg[COP0_EPC] = 0x089001b8;
	cpu->cd.mips.coproc[0]->reg[COP0_PRID] = 0x31040125;
	cpu->cd.mips.coproc[0]->reg[COP0_CONFIG] = 0x480;
	cpu->cd.mips.coproc[0]->reg[17] = 0;
	cpu->cd.mips.coproc[0]->reg[18] = 0;
	cpu->cd.mips.coproc[0]->reg[19] = 0;
	cpu->cd.mips.coproc[0]->reg[20] = 0;
	cpu->cd.mips.coproc[0]->reg[COP0_FRAMEMASK] = 0x8200;
	cpu->cd.mips.coproc[0]->reg[22] = 0;
	cpu->cd.mips.coproc[0]->reg[23] = 0;
	cpu->cd.mips.coproc[0]->reg[24] = 0xec400000;
	cpu->cd.mips.coproc[0]->reg[25] = 0x88019de0;
	cpu->cd.mips.coproc[0]->reg[26] = 0;
	cpu->cd.mips.coproc[0]->reg[27] = 0;
	cpu->cd.mips.coproc[0]->reg[28] = 0x184fff;
	cpu->cd.mips.coproc[0]->reg[29] = 0x440cf;
	cpu->cd.mips.coproc[0]->reg[30] = 0xc43fc;
	cpu->cd.mips.coproc[0]->reg[31] = 0;

	/* v1.0 */
/*
void add_symbol_name(struct symbol_context *sc,
	uint64_t addr, uint64_t len, char *name, int type, int n_args)
*/
	/* SysMemForKernel */
	add_symbol_name(&machine->symbol_context, 0x880001C8, 0, "sceKernelCreateHeap", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880004A8, 0, "sceKernelDeleteHeap", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880006F0, 0, "sceKernelAllocHeapMemoryWithOption", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88000890, 0, "sceKernelFreeHeapMemory", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88000980, 0, "sceKernelHeapTotalFreeSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88000A04, 0, "sceKernelGetHeapTypeCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88000AD0, 0, "sceKernelIsValidHeap", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88000FB0, 0, "sceKernelAllocHeapMemory", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88001668, 0, "sceKernelQueryMemoryPartitionInfo", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88001858, 0, "sceKernelPartitionMaxFreeMemSize", 0, 0);
/* U */	add_symbol_name(&machine->symbol_context, 0x880018A8, 0, "sceKernelMaxFreeMemSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88001918, 0, "sceKernelPartitionTotalFreeMemSize", 0, 0);
/* U */	add_symbol_name(&machine->symbol_context, 0x88001968, 0, "sceKernelTotalFreeMemSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880019BC, 0, "sceKernelFillFreeBlock", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88001FEC, 0, "sceKernelAllocPartitionMemory", 0, 0);
/* U */	add_symbol_name(&machine->symbol_context, 0x88002190, 0, "sceKernelAllocPartitionMemory", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800225C, 0, "sceKernelSizeLockMemoryBlock", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880022FC, 0, "sceKernelResizeMemoryBlock", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880029A8, 0, "sceKernelJointMemoryBlock", 0, 0);
/* U */	add_symbol_name(&machine->symbol_context, 0x88002A80, 0, "sceKernelFreePartitionMemory", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88002B8C, 0, "sceKernelQueryMemoryInfo", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88002C0C, 0, "sceKernelQueryBlockSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88002CFC, 0, "sceKernelQueryMemoryBlockInfo", 0, 0);
/* U */	add_symbol_name(&machine->symbol_context, 0x88002E64, 0, "sceKernelGetBlockHeadAddr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88003F14, 0, "sceKernelFreePartitionMemory", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88003FBC, 0, "sceKernelGetBlockHeadAddr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88004FA4, 0, "sceKernelCallUIDFunction", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005090, 0, "sceKernelCallUIDObjFunction", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880051E8, 0, "sceKernelLookupUIDFunction", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880056DC, 0, "sceKernelCreateUIDtype", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005720, 0, "sceKernelDeleteUIDtype", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880057DC, 0, "sceKernelGetUIDname", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005890, 0, "sceKernelRenameUID", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005948, 0, "sceKernelGetUIDtype", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005A14, 0, "sceKernelCreateUID", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005B18, 0, "sceKernelDeleteUID", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005B38, 0, "sceKernelSearchUIDbyName", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88005C5C, 0, "sceKernelGetUIDcontrolBlock", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880061A0, 0, "sceKernelIsHold", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880062B0, 0, "sceKernelHoldUID", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88006520, 0, "sceKernelReleaseUID", 0, 0);

	/* KDebugForKernel */
	add_symbol_name(&machine->symbol_context, 0x88007580, 0, "sceKernelGetDebugPutchar", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800758C, 0, "sceKernelRegisterDebugPutchar", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007598, 0, "sceKernelRegisterKprintfHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007D4C, 0, "Kprintf", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007DD8, 0, "sceKernelDebugWrite", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E08, 0, "sceKernelRegisterDebugWrite", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E18, 0, "sceKernelDebugRead", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E48, 0, "sceKernelRegisterDebugRead", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E58, 0, "sceKernelDebugEcho", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E64, 0, "sceKernelDebugEchoSet", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E74, 0, "sceKernelRegisterAssertHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007E80, 0, "sceKernelAssert", 0, 0);
/* ? */	add_symbol_name(&machine->symbol_context, 0x88007F1C, 0, "sceKernelUNKNOWN", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88007F48, 0, "sceKernelRemoveByDebugSection", 0, 0);

	/* ...SysMemForKernel */
	add_symbol_name(&machine->symbol_context, 0x88008ACC, 0, "sceKernelSysmemIsValidAccess", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880090E4, 0, "sceKernelIsValidUserAccess", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88009108, 0, "sceKernelSysMemCheckCtlBlk", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800933C, 0, "sceKernelSysMemDump", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88009430, 0, "sceKernelSysMemDumpBlock", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880094A0, 0, "sceKernelSysMemDumpTail", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88009AFC, 0, "sceKernelSysMemInit", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800A75C, 0, "sceKernelSysMemMemSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800A7E0, 0, "sceKernelSysMemMaxFreeMemSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800A890, 0, "sceKernelSysMemTotalFreeMemSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8800A930, 0, "sceKernelGetSysMemoryInfo", 0, 0);

	/* ...KDebugForKernel */
	add_symbol_name(&machine->symbol_context, 0x8800AA70, 0, "sceKernelAcceptMbogoSig", 0, 0);

	/* ...SysMemForKernel */
	add_symbol_name(&machine->symbol_context, 0x8800AA9C, 0, "sceKernelDevkitVersion", 0, 0);

	/* ? */
	add_symbol_name(&machine->symbol_context, 0x8800AB00, 0, "WeirdOpcodeStuff", 0, 0);

	/* LoadCoreForKernel */
	add_symbol_name(&machine->symbol_context, 0x88010E50, 0, "sceKernelRegisterLibrary", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88010E6C, 0, "sceKernelRegisterLibraryForUser", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88011034, 0, "sceKernelReleaseLibrary", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880110CC, 0, "sceKernelCanReleaseLibrary", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880112E4, 0, "sceKernelLinkLibraryEntries", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88011300, 0, "sceKernelLinkLibraryEntriesForUser", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88011458, 0, "sceKernelUnLinkLibraryEntries", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880114C0, 0, "sceKernelQueryLoadCoreCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88011F60, 0, "sceKernelSetBootCallbackLevel", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88011FE8, 0, "sceKernelCheckPspConfig", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88012CD8, 0, "sceKernelCheckExecFile", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88012F78, 0, "sceKernelProbeExecutableObject", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88013158, 0, "sceKernelLoadExecutableObject", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88013C40, 0, "sceKernelApplyElfRelSection", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88013E84, 0, "LoadCoreForKernel_Unkonow00", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88014318, 0, "sceKernelModuleFromUID", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880143D0, 0, "sceKernelCreateModule", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801445C, 0, "sceKernelDeleteModule", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880144A8, 0, "sceKernelModuleAssign", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88014670, 0, "sceKernelAllocModule", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880146BC, 0, "sceKernelFreeModule", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880146D8, 0, "sceKernelRegisterModule", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88014758, 0, "sceKernelReleaseModule", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880147E8, 0, "sceKernelFindModuleByName", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88014830, 0, "sceKernelFindModuleByAddress", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801488C, 0, "sceKernelFindModuleByUID", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880148F0, 0, "sceKernelModuleCount", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880148FC, 0, "sceKernelGetModuleList", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801496C, 0, "sceKernelDcacheWBinvAll", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880149B0, 0, "sceKernelIcacheClearAll", 0, 0);

	/* ExceptionManagerForKernel */
	add_symbol_name(&machine->symbol_context, 0x88019940, 0, "sceKernelRegisterExceptionHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88019960, 0, "sceKernelRegisterPriorityExceptionHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88019A5C, 0, "sceKernelRegisterDefaultExceptionHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88019AF0, 0, "sceKernelReleaseExceptionHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88019BB4, 0, "sceKernelGetActiveDefaultExceptionHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88019BDC, 0, "sceKernelReleaseDefaultExceptionHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88019FD4, 0, "sceKernelRegisterNmiHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801A03C, 0, "sceKernelReleaseNmiHandler", 0, 0);

	/* InterruptManagerForKernel */
	add_symbol_name(&machine->symbol_context, 0x8801BBC4, 0, "sceKernelCpuEnableIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801BD70, 0, "sceKernelRegisterIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C0EC, 0, "sceKernelReleaseIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C1B4, 0, "sceKernelSetIntrLevel", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C3B4, 0, "sceKernelIsInterruptOccurred", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C454, 0, "sceKernelEnableIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C520, 0, "sceKernelSuspendIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C63C, 0, "sceKernelDisableIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C658, 0, "sceKernelResumeIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C768, 0, "RegisterContextHooks", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C7B0, 0, "ReleaseContextHooks", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C7F4, 0, "sceKernelWaitModuleManagerEnabled", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801C90C, 0, "sceKernelRegisterDebuggerIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801CA80, 0, "sceKernelReleaseDebuggerIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801CBC8, 0, "sceKernelCallSubIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801CCC0, 0, "sceKernelGetUserIntrStack", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801CCF0, 0, "sceKernelCallUserIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801CE0C, 0, "sceKernelRegisterSubIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D044, 0, "sceKernelReleaseSubIntrHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D1B8, 0, "sceKernelEnableSubIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D288, 0, "sceKernelDisableSubIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D358, 0, "sceKernelSuspendSubIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D440, 0, "sceKernelResumeSubIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D520, 0, "sceKernelIsSubInterruptOccurred", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801D5F0, 0, "QueryIntrHandlerInfo", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801DA68, 0, "sceKernelGetCpuClockCounter", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801DA74, 0, "sceKernelGetCpuClockCounterWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801DBC8, 0, "sceKernelRegisterSystemCallTable", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801DC7C, 0, "sceKernelQuerySystemCall", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801E498, 0, "ReturnToThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801E924, 0, "sceKernelIsIntrContext", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801E93C, 0, "sceKernelGetInterruptExitCount", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801E948, 0, "SaveThreadContext", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801EB20, 0, "sceKernelCpuSuspendIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801EB4C, 0, "sceKernelCpuResumeIntr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8801EB74, 0, "sceKernelCpuResumeIntrWithSync", 0, 0);

	/* SysclibForKernel */
	add_symbol_name(&machine->symbol_context, 0x88027E10, 0, "strcat", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027EB0, 0, "strcspn", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027F1C, 0, "index", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027F4C, 0, "rindex", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027F94, 0, "strnlen", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027FDC, 0, "strpbrk", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028034, 0, "strspn", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880280A0, 0, "strstr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028104, 0, "strtok", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028128, 0, "strtok_r", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880281FC, 0, "strtol", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880283D8, 0, "atob", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802840C, 0, "strtoul", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880285E0, 0, "strcmp", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028660, 0, "strcpy", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880285B0, 0, "strchr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028748, 0, "strrchr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880287F8, 0, "strncmp", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028698, 0, "strncpy", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028714, 0, "strlen", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028790, 0, "strncat", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028890, 0, "memchr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028908, 0, "memcpy", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028970, 0, "memset", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880288C8, 0, "memcmp", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880289E0, 0, "memmove", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802856C, 0, "bcopy", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028550, 0, "bcmp", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88028590, 0, "bzero", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027D14, 0, "toupper", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027D50, 0, "tolower", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027D8C, 0, "look_ctype_table", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027D9C, 0, "get_ctype_table", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88027600, 0, "prnt", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880290E0, 0, "sprintf", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88029184, 0, "setjmp", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880291C0, 0, "longjmp", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88029278, 0, "wmemset", 0, 0);

	/* ThreadManForUser */
	add_symbol_name(&machine->symbol_context, 0x8802A330, 0, "_sceKernelReturnFromCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802A59C, 0, "sceKernelRegisterThreadEventHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802A8B4, 0, "sceKernelReleaseThreadEventHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802AD84, 0, "sceKernelReferThreadEventHandlerStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802AF8C, 0, "sceKernelCreateCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802B130, 0, "sceKernelDeleteCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802B2E4, 0, "sceKernelNotifyCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802B4B0, 0, "sceKernelCancelCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802B5C4, 0, "sceKernelGetCallbackCount", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802B6D4, 0, "sceKernelCheckCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802B9B4, 0, "sceKernelReferCallbackStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802BF2C, 0, "sceKernelSleepThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802C068, 0, "sceKernelSleepThreadCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802C1CC, 0, "sceKernelWakeupThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802C3A4, 0, "sceKernelCancelWakeupThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802C4F0, 0, "sceKernelSuspendThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802C70C, 0, "sceKernelResumeThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CA94, 0, "sceKernelWaitThreadEnd", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CA9C, 0, "sceKernelWaitThreadEndCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CD78, 0, "sceKernelDelayThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CD80, 0, "sceKernelDelayThreadCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CF80, 0, "sceKernelDelaySysClockThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CF88, 0, "sceKernelDelaySysClockThreadCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D1BC, 0, "sceKernelCreateSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D398, 0, "sceKernelDeleteSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D4F4, 0, "sceKernelSignalSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D738, 0, "sceKernelWaitSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D740, 0, "sceKernelWaitSemaCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802DA68, 0, "sceKernelPollSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802DC24, 0, "sceKernelCancelSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802DDDC, 0, "sceKernelReferSemaStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E148, 0, "sceKernelCreateEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E2E0, 0, "sceKernelDeleteEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E43C, 0, "sceKernelSetEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E6A4, 0, "sceKernelClearEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E7D0, 0, "sceKernelWaitEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E7D8, 0, "sceKernelWaitEventFlagCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802EBC8, 0, "sceKernelPollEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802EE38, 0, "sceKernelCancelEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802EFB8, 0, "sceKernelReferEventFlagStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802F26C, 0, "sceKernelCreateMbx", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802F3F0, 0, "sceKernelDeleteMbx", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802F618, 0, "sceKernelSendMbx", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802F7D0, 0, "sceKernelReceiveMbx", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802F7D8, 0, "sceKernelReceiveMbxCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802FB14, 0, "sceKernelPollMbx", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802FD44, 0, "sceKernelCancelReceiveMbx", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802FE9C, 0, "sceKernelReferMbxStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88030158, 0, "sceKernelCreateMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880303D0, 0, "sceKernelDeleteMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803052C, 0, "sceKernelSendMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88030534, 0, "sceKernelSendMsgPipeCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88030AD8, 0, "sceKernelTrySendMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88030F4C, 0, "sceKernelReceiveMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88030F54, 0, "sceKernelReceiveMsgPipeCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88031554, 0, "sceKernelTryReceiveMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88031A24, 0, "sceKernelCancelMsgPipe", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88031C08, 0, "sceKernelReferMsgPipeStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88032288, 0, "sceKernelCreateVpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803252C, 0, "sceKernelDeleteVpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88032688, 0, "sceKernelAllocateVpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88032690, 0, "sceKernelAllocateVplCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880329A0, 0, "sceKernelTryAllocateVpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88032B64, 0, "sceKernelFreeVpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88032D44, 0, "sceKernelCancelVpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88032E9C, 0, "sceKernelReferVplStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880331B0, 0, "sceKernelCreateFpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880334C0, 0, "sceKernelDeleteFpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803361C, 0, "sceKernelAllocateFpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88033624, 0, "sceKernelAllocateFplCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88033900, 0, "sceKernelTryAllocateFpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88033AC0, 0, "sceKernelFreeFpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88033CE4, 0, "sceKernelCancelFpl", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88033E3C, 0, "sceKernelReferFplStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034C58, 0, "sceKernelUSec2SysClock", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034C9C, 0, "sceKernelUSec2SysClockWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034CA8, 0, "sceKernelSysClock2USec", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034D78, 0, "sceKernelSysClock2USecWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034E84, 0, "sceKernelGetSystemTime", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034F54, 0, "sceKernelGetSystemTimeWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88034FF4, 0, "sceKernelGetSystemTimeLow", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803521C, 0, "sceKernelSetAlarm", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880352F8, 0, "sceKernelSetSysClockAlarm", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88035410, 0, "sceKernelCancelAlarm", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880358C8, 0, "sceKernelReferAlarmStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88035B0C, 0, "sceKernelCreateVTimer", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88035C4C, 0, "sceKernelDeleteVTimer", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88035DB0, 0, "sceKernelGetVTimerBase", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88035F20, 0, "sceKernelGetVTimerBaseWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803606C, 0, "sceKernelGetVTimerTime", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88036224, 0, "sceKernelGetVTimerTimeWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803639C, 0, "sceKernelSetVTimerTime", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88036690, 0, "sceKernelSetVTimerTimeWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803690C, 0, "sceKernelStartVTimer", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88036B34, 0, "sceKernelStopVTimer", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88036D00, 0, "sceKernelSetVTimerHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88036F9C, 0, "sceKernelSetVTimerHandlerWide", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88037224, 0, "sceKernelCancelVTimerHandler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88037384, 0, "sceKernelReferVTimerStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88039194, 0, "sceKernelCreateThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803987C, 0, "sceKernelDeleteThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88039B94, 0, "sceKernelStartThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803A098, 0, "_sceKernelExitThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803A0DC, 0, "sceKernelExitThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803A190, 0, "sceKernelExitDeleteThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803A6F0, 0, "sceKernelTerminateThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803A814, 0, "sceKernelTerminateDeleteThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803AA5C, 0, "sceKernelSuspendDispatchThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803AB40, 0, "sceKernelResumeDispatchThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803ACB4, 0, "sceKernelChangeCurrentThreadAttr", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803AEEC, 0, "sceKernelChangeThreadPriority", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803B248, 0, "sceKernelRotateThreadReadyQueue", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803B414, 0, "sceKernelReleaseWaitThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803B618, 0, "sceKernelGetThreadId", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803B69C, 0, "sceKernelGetThreadCurrentPriority", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803B720, 0, "sceKernelGetThreadExitStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803BECC, 0, "sceKernelCheckThreadStack", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803C088, 0, "sceKernelGetThreadStackFreeSize", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803C384, 0, "sceKernelReferThreadStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803C610, 0, "sceKernelReferThreadRunStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803CC28, 0, "sceKernelReferSystemStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803CD2C, 0, "sceKernelGetThreadmanIdList", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803D0D4, 0, "sceKernelGetThreadmanIdType", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803D2A0, 0, "sceKernelReferThreadProfiler", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803D300, 0, "sceKernelReferGlobalProfiler", 0, 0);

	/* InitForKernel */
	add_symbol_name(&machine->symbol_context, 0x8805DF28, 0, "sceKernelGetChunk", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8805DF7C, 0, "sceKernelRegisterChunk", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8805DFDC, 0, "sceKernelReleaseChunk", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8805F98C, 0, "sceKernelInitApitype", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8805F998, 0, "sceKernelBootFrom", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8805F9E8, 0, "sceKernelInitFileName", 0, 0);

	/* LoadExecForKernel */
	add_symbol_name(&machine->symbol_context, 0x88063FC0, 0, "sceKernelLoadExec", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064118, 0, "sceKernelExitGameWithStatus", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064194, 0, "sceKernelExitGame", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880647B0, 0, "sceKernelExitVSHVSH", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064A68, 0, "sceKernelPrepareRegionFrame", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064AB4, 0, "sceKernelLoadExecBufferPlain", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064B50, 0, "sceKernelLoadExecFromHost", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064BF4, 0, "sceKernelRegisterExitCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064C04, 0, "sceKernelUnregisterExitCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064C20, 0, "sceKernelCheckExitCallback", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88064C2C, 0, "sceKernelInvokeExitCallback", 0, 0);

	/* misc */
/*
	add_symbol_name(&machine->symbol_context, 0x88006D10, 0, "sceKernelPowerRebootStart", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802C90C, 0, "sceKernelSuspendAllUserThreads", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802CA94, 0, "sceKernelWaitThreadEnd", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D738, 0, "sceKernelWaitSema", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802D740, 0, "sceKernelWaitSemaCB", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8802E6A4, 0, "sceKernelClearEventFlag", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x88039B94, 0, "sceKernelStartThread", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x8803B618, 0, "sceKernelGetThreadId", 0, 0);
	add_symbol_name(&machine->symbol_context, 0x880495D0, 0, "sceIoDevctl", 0, 0);
*/


//	debug("sb.bin: 0x00000000\n");
//	f = fopen("sb.bin", "r");
//	ptr = 0x00000000;
#define BINFILE(addr,filename) \
{ \
 	ptr = addr; \
	debug("%s: 0x%02x\n", filename, ptr); \
	f = fopen(filename, "r"); \
\
	if (!f) { \
		fatal("Could not open %s\n", filename); \
		exit(1); \
	} \
\
	while((len = fread(&c, 1, 1, f)) > 0) { \
		store_byte(cpu, ptr++, c); \
	} \
	fclose(f); \
}

	BINFILE(0x88000000,"kmem.bin");
	BINFILE(0xbfc00000,"boot.bin");

}

