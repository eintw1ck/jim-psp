#include "pspgl_internal.h"


void glEnd (void)
{
	if (pspgl_curctx->current.vertex_count > 0) {
		long prim = __pspgl_glprim2geprim(pspgl_curctx->current.primitive);

		if (prim < 0) {
			GLERROR(GL_INVALID_ENUM);
		} else {
			__pspgl_context_render_prim(pspgl_curctx, prim, pspgl_curctx->current.vertex_count,
						    GE_TEXTURE_32BITF | GE_COLOR_8888 | GE_NORMAL_32BITF | GE_VERTEX_32BITF,
						    pspgl_curctx->current.vbuf_adr, NULL);
		}
	}

	pspgl_curctx->current.primitive = -1;
}
