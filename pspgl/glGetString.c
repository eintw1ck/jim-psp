#include <stdlib.h>
#include "pspgl_internal.h"


static const
char *gl_strings [] = {
	/* GL_VENDOR */
	"pspGL",
	/* GL_RENDERER */
	"OpenGL ES-CM 1.1",
	/* GL_VERSION */
	"(pspGL build " __DATE__ ", " __TIME__ ")",
	/* GL_EXTENSIONS */
	"GL_EXT_texture_env_add "
	"GL_ARB_texture_env_add "
	"GL_EXT_blend_minmax "
	"GL_EXT_blend_subtract "
 	"GL_EXT_paletted_texture "
};


const GLubyte * glGetString (GLenum name)
{
	unsigned long idx = name - GL_VENDOR;
	const char *s;

	if (idx >= sizeof(gl_strings)/sizeof(gl_strings[0])) {
		GLERROR(GL_INVALID_ENUM);
		s = NULL;
	} else {
		s = gl_strings[idx];
	}

	return (const GLubyte *) s;
}

