#include "pspgl_internal.h"
#include "pspgl_dlist.h"

struct clear_vertex {
	unsigned long color;
	short x,y,z;
	short _pad;
};


void glClear (GLbitfield mask)
{
	struct clear_vertex *vbuf;
	struct pspgl_surface *s = pspgl_curctx->draw;
	unsigned long clearmask = pspgl_curctx->clear.color;
	unsigned long clearmode = 0;

	if (mask & ~(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)) {
		GLERROR(GL_INVALID_VALUE);
		return;
	}

	/* make room for 2 embedded vertices in cmd_buf, aligned to 16byte boundary */
	vbuf = __pspgl_dlist_insert_space(2 * sizeof(struct clear_vertex));

	if (!vbuf) {
		GLERROR(GL_OUT_OF_MEMORY);
		return;
	}

	if (mask & GL_COLOR_BUFFER_BIT) {
		clearmode |= GU_COLOR_BUFFER_BIT;
		if (s->alpha_mask)
			clearmode |= GU_STENCIL_BUFFER_BIT; /* really alpha */
	}

	if (s->stencil_mask && (mask & GL_STENCIL_BUFFER_BIT)) {
		static const unsigned char stencil_shift [] = { 32-1, 32-4, 32-8 };
		clearmask &= 0x00ffffff;
		clearmask |= (pspgl_curctx->clear.stencil) << stencil_shift[s->pixfmt-1];
		clearmode |= GU_STENCIL_BUFFER_BIT;
	}

	if (s->depth_buffer && (mask & GL_DEPTH_BUFFER_BIT))
		clearmode |= GU_DEPTH_BUFFER_BIT;

	vbuf[0].color = clearmask;
	vbuf[0].x = 0;
	vbuf[0].y = 0;
	vbuf[0].z = pspgl_curctx->clear.depth;

	vbuf[1].color = clearmask;
	vbuf[1].x = s->width;
	vbuf[1].y = s->height;
	vbuf[1].z = pspgl_curctx->clear.depth;

	/* enable clear mode */
	sendCommandi(CMD_CLEARMODE, (clearmode << 8) | 1);

	/* draw array */
	__pspgl_context_render_prim(pspgl_curctx, GE_SPRITES, 2, 
				    GE_COLOR_8888 | GE_VERTEX_16BIT | GE_TRANSFORM_2D, vbuf, NULL);

	/* leave clear mode */
	sendCommandi(CMD_CLEARMODE, 0);
}

