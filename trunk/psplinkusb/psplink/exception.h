#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <psptypes.h>

/* Define maximum number of thread exception context */
#define PSPLINK_MAX_CONTEXT 8

#define PSPLINK_EXTYPE_NORMAL 0
#define PSPLINK_EXTYPE_DEBUG  1

/* Define continue flags */
#define PSP_EXCEPTION_EXIT        0
#define PSP_EXCEPTION_CONTINUE    1
#define PSP_EXCEPTION_STEP        2
#define PSP_EXCEPTION_SKIP        3
#define PSP_EXCEPTION_NOT_HANDLED 4

/** Structure to hold the register data associated with an exception */
typedef struct _PsplinkRegBlock
{
	u32 frame[6];
	/** Array of the 32 GPRs */
	u32 r[32];
	/** The status register */
	u32 status;
	/** lo */
	u32 lo;
	u32 hi;
	u32 badvaddr;
	u32 cause;
	u32 epc;
	float fpr[32];
	u32 fsr;
	u32 fir;
	u32 frame_ptr;
	u32 unused;
	/* Unused on PSP */
	u32 index;
	u32 random;
	u32 entrylo0;
	u32 entrylo1;
	u32 context;
	u32 pagemask;
	u32 wired;
	u32 cop0_7;
	u32 cop0_8;
	u32 cop0_9;
	u32 entryhi;
	u32 cop0_11;
	u32 cop0_12;
	u32 cop0_13;
	u32 cop0_14;
	/* PRId should still be okay */
	u32 prid;
	/* Type of exception (normal or debug) */
	u32 type;
	/* Pad vfpu to 128bit boundary */
	int pad;
	float vfpu[128];
} PsplinkRegBlock;

/* A thread context during an exception */
struct PsplinkContext
{
	int valid;
	struct PsplinkContext *pNext;
	PsplinkRegBlock regs;
	SceUID thid;
	unsigned int drcntl;
	/* Continue type */
	int cont;
	/* Indicates whether this was an error or planned */
	int error;
};

#define VFPU_PRINT_SINGLE 0
#define VFPU_PRINT_COL    1
#define VFPU_PRINT_ROW    2
#define VFPU_PRINT_MATRIX 3
#define VFPU_PRINT_TRANS  4

extern struct PsplinkContext *g_currex;

void exceptionInit(void);
void exceptionPrint(struct PsplinkContext *ctx);
void exceptionFpuPrint(struct PsplinkContext *ctx);
void exceptionVfpuPrint(struct PsplinkContext *ctx, int mode);
u32 *exceptionGetReg(const char *reg);
void exceptionResume(struct PsplinkContext *ctx, int cont);
void exceptionPrintFPURegs(float *pFpu, unsigned int fsr, unsigned int fir);
void exceptionPrintCPURegs(u32 *pRegs);
void exceptionList(void);
void exceptionSetCtx(int ex);

#endif
