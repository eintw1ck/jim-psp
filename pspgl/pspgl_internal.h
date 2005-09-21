#ifndef __pspgl_internal_h__
#define __pspgl_internal_h__

#include <GL/gl.h>
#include <GLES/egl.h>

#include "pspgl_dlist.h"
#include "pspgl_hash.h"
#include "pspgl_misc.h"
#include "pspgl_texobj.h"


#define NUM_CMDLISTS	4

struct pspgl_vertex_array {
	GLenum enabled;
	GLint size;
	GLenum type;
	GLsizei stride;
	const GLvoid *ptr;
};


struct pspgl_shared_context {
	int refcount;
	struct hashtable texture_objects;
	struct hashtable display_lists;
};


struct pspgl_context {
	uint32_t ge_reg [256];
	uint32_t ge_reg_touched [256/32];

	struct {
		GLenum primitive;
		unsigned long vertex_count;
		void *vbuf_adr;
		GLfloat texcoord [4];
		unsigned long color;
		GLfloat normal [3];
	} current;

	struct {
		struct pspgl_vertex_array vertex;
		struct pspgl_vertex_array normal;
		struct pspgl_vertex_array color;
		struct pspgl_vertex_array texcoord;
	} vertex_array;

	struct {
		GLclampf color [4];
		GLclampf depth;
		GLint stencil;
	} clear;

	struct {
		GLenum enabled;
		GLint x, y, width, height;
	} scissor_test;

	struct {
		unsigned char alpha;
		unsigned char stencil;
	} write_mask;

	GLfloat depth_offset;

	unsigned long matrix_touched;  /* bitfield */
	GLenum matrix_mode;
	GLint matrix_stack_depth[3];
	GLfloat (* (matrix_stack [3])) [16];

	struct pspgl_texobj texobj0;
	struct pspgl_texobj *texobj_current;

	struct pspgl_shared_context *shared;

	struct pspgl_surface *read;
	struct pspgl_surface *draw;
	
	struct pspgl_dlist *dlist[NUM_CMDLISTS];
	struct pspgl_dlist *dlist_current;
	int dlist_idx;

	GLenum glerror;
	unsigned int swap_interval;
	int initialized;
	int refcount;

	/* XXX IMPROVE Do we really need to store anything below? these are hardware states, stored in ge_reg[]... */
	uint32_t ge_ctx [512];
	struct {
		GLint x, y, width, height;
	} viewport;
	struct {
		GLenum equation;
		GLenum sfactor, dfactor;
	} blend;
	struct {
		GLfloat near, far;
	} fog;
	struct {
		GLenum enabled;
		GLenum wrap_s;
		GLenum wrap_t;
		GLenum mag_filter;
		GLenum min_filter;
	} texture;
};


struct pspgl_surface {
	int pixfmt;
	unsigned long width;
	unsigned long height;
	unsigned long pixelperline;
	void *color_buffer [2];
	void *depth_buffer;
	int current_front;
	int displayed;
};


/* pspgl_ge_init.c */
extern void pspgl_ge_init (struct pspgl_context *c);


/* pspgl_vidmem.c */
extern EGLint eglerror;
extern struct pspgl_context *pspgl_curctx;

extern void* pspgl_vidmem_alloc (unsigned long size);
extern void  pspgl_vidmem_free (void * ptr);
extern EGLBoolean pspgl_vidmem_setup_write_and_display_buffer (struct pspgl_surface *s);


/* pspgl_varray.c */
extern long glprim2geprim (GLenum glprim);
extern void pspgl_varray_draw (GLenum mode, GLenum index_type, const GLvoid *indices, GLint first, GLsizei count);


/* glEnable.c */
extern void pspgl_enable_state (GLenum cap, int enable);


#define GLERROR(errcode)					\
do {								\
	psp_log("*** GL error 0x%04x ***\n", errcode);		\
	if (pspgl_curctx)					\
		pspgl_curctx->glerror = errcode;		\
} while (0)


#define EGLERROR(errcode)					\
do {								\
	psp_log("*** EGL error 0x%04x ***\n",	errcode);	\
	eglerror = errcode;					\
} while (0)


static inline GLclampf CLAMPF (GLfloat x)
{
	return (x < 0.0 ? 0.0 : x > 1.0 ? 1.0 : x);
}


static inline
unsigned long COLOR3 (const GLfloat c[3])
{
	return ((((int) (255.0 * CLAMPF(c[2]))) << 16) |
		(((int) (255.0 * CLAMPF(c[1]))) << 8) |
		 ((int) (255.0 * CLAMPF(c[0]))));
}


static inline
unsigned long COLOR4 (const GLfloat c[4])
{
	return ((((int) (255.0 * CLAMPF(c[3]))) << 24) |
		(((int) (255.0 * CLAMPF(c[2]))) << 16) |
		(((int) (255.0 * CLAMPF(c[1]))) << 8) |
		 ((int) (255.0 * CLAMPF(c[0]))));
}


extern void pspgl_context_writereg (struct pspgl_context *c, unsigned long cmd, unsigned long argi);
extern void pspgl_context_writereg_masked (struct pspgl_context *c, unsigned long cmd, unsigned long argi, unsigned long mask);
extern void pspgl_context_flush_pending_state_changes (struct pspgl_context *c);
extern void pspgl_context_writereg_uncached (struct pspgl_context *c, unsigned long cmd, unsigned long argi);

extern void pspgl_context_flush_pending_matrix_changes (struct pspgl_context *c);

#define sendCommandi(cmd,argi)		pspgl_context_writereg(pspgl_curctx, cmd, argi)
#define sendCommandiUncached(cmd,argi)	pspgl_context_writereg_uncached (pspgl_curctx, cmd, argi)

#define sendCommandf(cmd,argf)						\
do {									\
	union { float f; int i; } arg = { .f = argf };			\
	sendCommandi(cmd, arg.i >> 8);					\
} while (0)


#endif

