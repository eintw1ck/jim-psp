#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "pspthreadman.h"
#include "pspvfpu.h"

#define ALIGNMENT	64

#define NMAT	8

struct pspvfpu_context {
	float fpregs[4*4*NMAT] __attribute__((aligned(64)));

	unsigned resident;	/* which matrices are in the VFPU at the moment */
};

/* XXX This should be per-thread info? */
static struct pspvfpu_context *users[NMAT];

static void save_matrix(struct pspvfpu_context *c, int mat)
{
#define SV(N)					\
	asm("sv.q	c" #N "00, %0\n"	\
	    "sv.q	c" #N "10, %1\n"	\
	    "sv.q	c" #N "20, %2\n"	\
	    "sv.q	c" #N "30, %3\n"	\
	    : "=m" (c->fpregs[N * 4*4 +  0]),	\
	      "=m" (c->fpregs[N * 4*4 +  4]),	\
	      "=m" (c->fpregs[N * 4*4 +  8]),	\
	      "=m" (c->fpregs[N * 4*4 + 12])	\
	    : : "memory")

	switch(mat) {
	case 0:	SV(0); break;
	case 1:	SV(1); break;
	case 2:	SV(2); break;
	case 3:	SV(3); break;
	case 4:	SV(4); break;
	case 5:	SV(5); break;
	case 6:	SV(6); break;
	case 7:	SV(7); break;
	}
#undef SV
}

static void load_matrices(const struct pspvfpu_context *c, unsigned mat)
{
#define LV(N)					\
	asm("lv.q	c" #N "00, %0\n"	\
	    "lv.q	c" #N "10, %1\n"	\
	    "lv.q	c" #N "20, %2\n"	\
	    "lv.q	c" #N "30, %3\n"	\
	    : :					\
	      "m" (c->fpregs[N * 4*4 +  0]),	\
	      "m" (c->fpregs[N * 4*4 +  4]),	\
	      "m" (c->fpregs[N * 4*4 +  8]),	\
	      "m" (c->fpregs[N * 4*4 + 12])	\
	    : "memory")

	if (mat & (1<<0))
		LV(0);
	if (mat & (1<<1))
		LV(1);
	if (mat & (1<<2))
		LV(2);
	if (mat & (1<<3))
		LV(3);
	if (mat & (1<<4))
		LV(4);
	if (mat & (1<<5))
		LV(5);
	if (mat & (1<<6))
		LV(6);
	if (mat & (1<<7))
		LV(7);
#undef LV
}

struct pspvfpu_context *pspvfpu_initcontext(unsigned matrixmask)
{
	struct pspvfpu_context *c;

	/* Make sure the kernel preserves this thread's VFPU state */
	if (sceKernelChangeCurrentThreadAttr(0, PSP_THREAD_ATTR_VFPU) < 0)
		return NULL;

	c = memalign(sizeof(*c), ALIGNMENT);
	if (c == NULL)
		return c;

	memset(c->fpregs, 0, sizeof(c->fpregs));

	for(int i = 0; i < NMAT && matrixmask; i++) {
		if (matrixmask & (1 << i)) {
			if (users[i] != NULL) 
				save_matrix(users[i], i);
			users[i] = c;
		}
	}

	c->resident = matrixmask;

	return c;
}

void pspvfpu_deletecontext(struct pspvfpu_context *c)
{
	for(int i = 0; i < NMAT; i++)
		if (users[i] == c)
			users[i] = NULL;

	free(c);
}

void pspvfpu_usecontext(struct pspvfpu_context *c, unsigned matrixmask)
{
	unsigned reloadmask = 0;

	matrixmask &= ~c->resident;

	for(int i = 0; i < NMAT && matrixmask; i++) {
		if (matrixmask & (1<<i)) {
			if (users[i] != NULL) {
				assert(users[i] != c);
				reloadmask |= (1 << i);
				save_matrix(users[i], i);
			}
			users[i] = c;
		}
	}

	c->resident |= matrixmask;

	if (reloadmask)
		load_matrices(c, matrixmask);
}
