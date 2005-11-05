#include <stdlib.h>
#include <psputils.h>

#include "pspgl_internal.h"
#include "pspgl_buffers.h"

struct pspgl_bufferobj *__pspgl_bufferobj_new(struct pspgl_buffer *data)
{
	struct pspgl_bufferobj *bufp;

	bufp = malloc(sizeof(*bufp));

	if (bufp) {
		bufp->refcount = 1;
		bufp->usage = 0;
		bufp->access = 0;
		bufp->mapped = GL_FALSE;

		bufp->data = data;

		if (data != NULL)
			data->refcount++;
	}

	return bufp;
}

void __pspgl_bufferobj_free(struct pspgl_bufferobj *bufp)
{
	assert(bufp->refcount > 0);

	if (--bufp->refcount)
		return;

	if (bufp->data)
		__pspgl_buffer_free(bufp->data);

	free(bufp);
}

void *__pspgl_bufferobj_deref(const struct pspgl_bufferobj *bufp, void *off)
{
	if (bufp == NULL || bufp->data == NULL)
		return off;

	return bufp->data->base + (off - NULL);
}

void *__pspgl_bufferobj_map(const struct pspgl_bufferobj *buf, GLenum access, void *off)
{
	if (buf && buf->data)
		off += __pspgl_buffer_map(buf->data, access) - NULL;

	return off;
}

void __pspgl_bufferobj_unmap(const struct pspgl_bufferobj *buf, GLenum access)
{
	if (buf && buf->data)
		__pspgl_buffer_unmap(buf->data, access);
}

struct pspgl_buffer *__pspgl_buffer_new(void *base, GLsizeiptr size,
						void (*free)(struct pspgl_buffer *))
{
	struct pspgl_buffer *ret;

	ret = malloc(sizeof(*ret));

	if (ret != NULL) {
		ret->refcount = 1;
		ret->mapped = 0;
		ret->dlist_usage = 0;

		ret->base = base;
		ret->size = size;

		ret->free = free;
	}

	return ret;
}

void __pspgl_buffer_free(struct pspgl_buffer *data)
{
	assert(data->refcount > 0);

	if (--data->refcount)
		return;

	if (data->free)
		(*data->free)(data);

	free(data);
}

struct pspgl_bufferobj **__pspgl_bufferobj_for_target(GLenum target)
{
	struct pspgl_bufferobj **ret = NULL;

	switch(target) {
	case GL_ARRAY_BUFFER_ARB:
		ret = &pspgl_curctx->vertex_array.arraybuffer;
		break;

	case GL_ELEMENT_ARRAY_BUFFER_ARB:
		ret = &pspgl_curctx->vertex_array.indexbuffer;
		break;

	default:
		GLERROR(GL_INVALID_ENUM);
		break;
	}

	return ret;
}

void *__pspgl_buffer_map(struct pspgl_buffer *data, GLenum access)
{
	void *p = data->base;

	assert(data->mapped >= 0);

	switch(access) {
	case GL_READ_WRITE_ARB:
		/* FALLTHROUGH */

	case GL_READ_ONLY_ARB:
		/* Need to invalidate if written by hardware, but only the first time */
		if (!data->mapped)
			sceKernelDcacheInvalidateRange(data->base, data->size);
		break;

	case GL_WRITE_ONLY_ARB:
		/* Write-only streams can be uncached to prevent cache
		   pollution.  If data->mapped != 0, this should be a
		   no-op. */
		p = __pspgl_uncached(p, data->size);
		break;
	}

	data->mapped++;

	return p;
}

void __pspgl_buffer_unmap(struct pspgl_buffer *data, GLenum access)
{
	assert(data->mapped > 0);

	if (--data->mapped > 0)
		return;

	switch(access) {
	case GL_READ_ONLY_ARB:
		/* do nothing; no dirty cache lines */
		break;

	case GL_READ_WRITE_ARB:
		sceKernelDcacheWritebackInvalidateRange(data->base, data->size);
		break;

	case GL_WRITE_ONLY_ARB:
		/* do nothing; all uncached */
		break;
	}
}

static void dlist_cleanup_buffer(void *v)
{
	struct pspgl_buffer *data = v;

	assert(data->dlist_usage > 0);
	--data->dlist_usage;

	__pspgl_buffer_free(data);
}

/* Mark buffer as being in use by the hardware.  Increments the
   refcount and the dlist usage count. */
void __pspgl_buffer_dlist_use(struct pspgl_buffer *data)
{
	data->dlist_usage++;
	data->refcount++;

	__pspgl_dlist_set_cleanup(dlist_cleanup_buffer, data);
}

/* Wait until the last hardware use of a databuffer has happened. If
   the caller wants to use the buffer after this call, it must
   increment the refcount to prevent it from being (potentially)
   freed. */
void __pspgl_buffer_dlist_sync(struct pspgl_buffer *data)
{
	data->refcount++;	/* prevent freeing */

	/* XXX This is overkill; we can wait for each dlist until the
	   dlist_use count drops to 0  */
	if (data->dlist_usage > 0)
		glFinish();

	assert(data->dlist_usage == 0);

	__pspgl_buffer_free(data); /* drop refcount */
}
