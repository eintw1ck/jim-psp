#include <stdlib.h>
#include <string.h>
#include "pspgl_internal.h"


EGLContext eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
	struct pspgl_context *ctx = malloc(sizeof(struct pspgl_context));
	int i;

	if (!ctx) {
		EGLERROR(EGL_BAD_ALLOC);
		return EGL_NO_CONTEXT;
	}

	memset(ctx, 0, sizeof(*ctx));

	for(i = 0; i < NUM_CMDLISTS; i++)
		ctx->dlist[i] = pspgl_dlist_create(1, pspgl_dlist_swap);

	ctx->dlist_current = ctx->dlist[0];
	ctx->dlist_idx = 0;

	return (EGLContext) ctx;
}


