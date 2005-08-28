#include "pspgl_internal.h"


void glGetFloatv (GLenum pname, GLfloat *params)
{
	switch (pname) {
	case GL_LINE_WIDTH:
		params[0] = 1.0f;
		break;
	case GL_ALIASED_POINT_SIZE_RANGE:
	case GL_SMOOTH_POINT_SIZE_RANGE:
	case GL_SMOOTH_POINT_SIZE_GRANULARITY:
	case GL_ALIASED_LINE_WIDTH_RANGE:
	case GL_SMOOTH_LINE_WIDTH_RANGE:
	case GL_SMOOTH_LINE_WIDTH_GRANULARITY:
		params[0] = 1.0f;
		params[1] = 1.0f;
		break;
	case GL_COLOR_CLEAR_VALUE:
		params[0] = pspgl_curctx->clear.color[0];
		params[1] = pspgl_curctx->clear.color[1];
		params[2] = pspgl_curctx->clear.color[2];
		params[3] = pspgl_curctx->clear.color[3];
		break;
	default:
		GLERROR(GL_INVALID_ENUM);
	}
}

