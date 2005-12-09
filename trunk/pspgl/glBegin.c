#include "pspgl_internal.h"


void glBegin (GLenum mode)
{
	if (mode >= GL_POINTS && mode <= GL_POLYGON) {
		pspgl_curctx->beginend.primitive = mode;
		pspgl_curctx->beginend.vertex_count = 0;
	} else {
		GLERROR(GL_INVALID_ENUM);
	}
}
