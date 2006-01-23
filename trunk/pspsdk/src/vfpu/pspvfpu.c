#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "pspthreadman.h"
#include "pspvfpu.h"

#define ALIGNMENT	(sizeof(float)*4)

#define NMAT	8

struct pspvfpu_context {
	float fpregs[4*4*NMAT] __attribute__((aligned(ALIGNMENT)));

	/* 
	   States a matrix can be in:
	   owned   valid
	     0       X		context has no knowledge of the matrix
	     1       1		context is using matrix, and wants it preserved
	     1       0          context is used matrix temporarily
	 */
	vfpumatrixset_t valid;	/* which matrices are valid in this context */
	vfpumatrixset_t owned;	/* which matrices are in the VFPU at the moment */
};

/* XXX This should be per-thread info */
static struct pspvfpu_context *users[NMAT];

static void save_matrix(struct pspvfpu_context *c, int mat)
{
#define SV(N)					\
	asm("sv.q	c"#N"00,  0 + %0\n"	\
	    "sv.q	c"#N"10, 16 + %0\n"	\
	    "sv.q	c"#N"20, 32 + %0\n"	\
	    "sv.q	c"#N"30, 48 + %0\n"	\
	    : "=m" (c->fpregs[N * 4*4])		\
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

static void load_matrix(const struct pspvfpu_context *c, int mat)
{
#define LV(N)					\
	asm("lv.q	c"#N"00,  0 + %0\n"	\
	    "lv.q	c"#N"10, 16 + %0\n"	\
	    "lv.q	c"#N"20, 32 + %0\n"	\
	    "lv.q	c"#N"30, 48 + %0\n"	\
	    : : "m" (c->fpregs[N * 4*4])	\
	    : "memory")
	switch(mat) {
	case 0:	LV(0); break;
	case 1:	LV(1); break;
	case 2:	LV(2); break;
	case 3:	LV(3); break;
	case 4:	LV(4); break;
	case 5:	LV(5); break;
	case 6:	LV(6); break;
	case 7:	LV(7); break;
	}
#undef LV
}

/* 
   Switch the VFPU's register state for the current context.  This means:

   1. save any other context's matrices in the set (keepset | tempset)
   2. load the current context's valid keepset (keepset & c->valid)
   3. mark the current context as owning (keepset | tempset), and having keepset valid
 */
void pspvfpu_use_matrices(struct pspvfpu_context *c, vfpumatrixset_t keepset, vfpumatrixset_t tempset)
{
	/* If a matrix is both in the keepset and tempset, drop it
	   from tempset */
	tempset &= ~keepset;

	/* If the context already has a matrix owned, we
	   don't need to handle it */
	keepset &= ~c->owned;
	tempset &= ~c->owned;

	vfpumatrixset_t saveset = keepset | tempset;	/* save everything we use */
	vfpumatrixset_t loadset = keepset & c->valid;	/* only reload valid matrices */

	c->owned |= saveset;	/* will be true by the time we're done */
	c->valid |= keepset;	/* likewise */
	c->valid &= ~tempset;	/* temporaries aren't valid */

	int m = 0;
	while(saveset) {
		/* skip to the next member of the matrix set
		   (ctz -> count trailing zeros; the number of zeros in the LSB) */
		int skip = __builtin_ctz(saveset);
		m += skip;
		saveset >>= skip;
		loadset >>= skip;

		/* we need to save everyone else's use of saveset
		   matrices  */
		if (users[m] != NULL) {
			struct pspvfpu_context *other = users[m];

			assert(other != c);

			if (other->valid & (1 << m))
				save_matrix(other, m);
			other->owned &= ~(1 << m);
			other->valid &= ~(1 << m);
		}

		/* reload matrix values if necessary */
		if (loadset & 1)
			load_matrix(c, m);

		/* we own all the matrices we're about to use */
		users[m] = c;

		saveset &= ~1; /* that one's done */
	}
}

/*
   Create a new context, and make sure the matrices in matrixset are
   ready for use.
 */
struct pspvfpu_context *pspvfpu_initcontext(void)
{
	struct pspvfpu_context *c;

	/* Make sure the kernel preserves this thread's VFPU state */
	if (sceKernelChangeCurrentThreadAttr(0, PSP_THREAD_ATTR_VFPU) < 0)
		return NULL;

	c = memalign(sizeof(*c), ALIGNMENT);
	if (c == NULL)
		return c;

	c->owned = 0;
	c->valid = 0;

	return c;
}

void pspvfpu_deletecontext(struct pspvfpu_context *c)
{
	for(int i = 0; i < NMAT; i++)
		if (users[i] == c)
			users[i] = NULL;

	free(c);
}
