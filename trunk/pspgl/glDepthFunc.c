#include "pspgl_internal.h"

/* 
   Because the PSP's Z coord system is backwards from OpenGL's, we
   need to reverse order of depth comparisons.
 */
static const unsigned char depthfunc_mapping [] = {
	GE_NEVER,		/* GL_NEVER */
	GE_GEQUAL,		/* GL_LESS */
	GE_EQUAL,		/* GL_EQUAL */
	GE_GREATER,		/* GL_LEQUAL */
	GE_LEQUAL,		/* GL_GREATER */
	GE_NOTEQUAL,		/* GL_NOTEQUAL */
	GE_LESS,		/* GL_GEQUAL */
	GE_ALWAYS,		/* GL_ALWAYS */
};

void glDepthFunc (GLenum func)
{
	if (func < GL_NEVER || func > GL_ALWAYS) {
		GLERROR(GL_INVALID_ENUM);
		return;
	}

	sendCommandi(CMD_DEPTH_FUNC, depthfunc_mapping[func - GL_NEVER]);
}
