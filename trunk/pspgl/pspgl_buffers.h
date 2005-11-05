#ifndef _PSPGL_BUFFERS_H
#define _PSPGL_BUFFERS_H

#include "pspgl_internal.h"

struct pspgl_buffer {
	int refcount;

	void *base;
	GLsizeiptr size;

	int mapped;		/* internal map counter */

	void (*free)(struct pspgl_buffer *);
};

struct pspgl_bufferobj {
	int refcount;

	GLenum target;
	GLenum usage, access;
	GLboolean mapped;	/* glMapBuffer called */

	struct pspgl_buffer *data;
};

/* Create new buffer, but does not allocate any storage for it.
   Returns a buffer with a refcount of 1 */
struct pspgl_bufferobj *__pspgl_bufferobj_new(GLenum target, struct pspgl_buffer *data);

/* Decrements refcount, and frees if it hits 0 */
void __pspgl_bufferobj_free(struct pspgl_bufferobj *);

/* Convert a buffer+offset into a pointer; if buffer is NULL, then
   offset is returned as a pointer.  This pointer has not been mapped,
   and should not be dereferenced. */
void *__pspgl_bufferobj_deref(const struct pspgl_bufferobj *buf, void *offset);

/* Helper to map a buffer and return a pointer to an offset; if buffer
   is NULL, then offset is returned as a pointer. */
void *__pspgl_bufferobj_map(const struct pspgl_bufferobj *buf, GLenum access, void *off);
/* Unmap a buffer mapped above.  Should always be paired. */
void __pspgl_bufferobj_unmap(const struct pspgl_bufferobj *buf, GLenum access);

/* Return a buffer ** for a particular target.  Returns NULL if target
   is unknown/invalid, and sets GLERROR appropriately. */
struct pspgl_bufferobj **__pspgl_bufferobj_for_target(GLenum target);


struct pspgl_buffer *__pspgl_buffer_new(void *base, GLsizeiptr size,
						void (*free)(struct pspgl_buffer *));
void __pspgl_buffer_free(struct pspgl_buffer *data);

/* Map a buffer for access type "access".  May be called repeatedly. */
void *__pspgl_buffer_map(struct pspgl_buffer *data, GLenum access);

/* Unmap a buffer and do the appropriate fixups.  Must be paired with
   buffer_map(). */
void  __pspgl_buffer_unmap(struct pspgl_buffer *data, GLenum access);

void __pspgl_dlist_cleanup_buffer(void *);

#endif	/* PSPGL_BUFFERS_H */
