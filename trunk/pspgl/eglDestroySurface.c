#include <stdlib.h>
#include "pspgl_internal.h"
#include "pspgl_buffers.h"

EGLBoolean eglDestroySurface (EGLDisplay dpy, EGLSurface surface)
{
	struct pspgl_surface *s = (struct pspgl_surface*) surface; 

	if (!s)
		return EGL_FALSE;

	/* Even if single-buffered, both front and back are initialized */
	__pspgl_buffer_free(s->color_buffer[0]);
	__pspgl_buffer_free(s->color_buffer[1]);

	if (s->depth_buffer)
		__pspgl_buffer_free(s->depth_buffer);

	free(s);

	return EGL_TRUE;
}
