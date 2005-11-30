#include <stdlib.h>
#include <string.h>
#include <pspdisplay.h>
#include <pspge.h>
#include "pspgl_internal.h"
#include "pspgl_buffers.h"

GLint __pspgl_eglerror = EGL_SUCCESS;
struct pspgl_context *__pspgl_curctx = NULL;


static struct pspgl_buffer **vidmem_map = NULL;
static unsigned long vidmem_map_len = 0, vidmem_map_size = 0;
static size_t vidmem_used = 0;

size_t __pspgl_vidmem_avail(void)
{
	return sceGeEdramGetSize() - vidmem_used;
}

static int vidmem_map_insert_new (unsigned long idx, struct pspgl_buffer *buf)
{
	/* grow map if necessary */
	if ((vidmem_map_len+1) > vidmem_map_size) {
		void *tmp;

		if (vidmem_map_size == 0)
			vidmem_map_size = 4;
		else
			vidmem_map_size *= 2;

		tmp = realloc(vidmem_map, vidmem_map_size * sizeof(vidmem_map[0]));

		if (!tmp)
			return 0;
		vidmem_map = tmp;
	}

	psp_log("alloc vidmem %lu: adr %08p - size 0x%08x\n",
		idx, buf->base, (unsigned int) buf->size);

	memmove(&vidmem_map[idx+1], &vidmem_map[idx],
		(vidmem_map_len-idx) * sizeof(vidmem_map[0]));
	vidmem_map_len++;
	vidmem_map[idx] = buf;
	vidmem_used += buf->size;

	return 1;
}


int __pspgl_vidmem_alloc (struct pspgl_buffer *buf)
{
	void *start = sceGeEdramGetAddr();
	void *adr = start;
	unsigned long i;
	unsigned size;

	/* make sure eveything is usefully aligned */
	size = ROUNDUP(buf->size, CACHELINE_SIZE);

	for(i = 0; i < vidmem_map_len; i++) {
		void *new_adr = vidmem_map[i]->base;

		if ((adr+size) <= new_adr) {
			buf->base = adr;
			buf->size = size;
			return vidmem_map_insert_new(i, buf);
		}

		adr = new_adr + vidmem_map[i]->size;
	}

	if ((adr + size) > (start + sceGeEdramGetSize())) {
		psp_log("vidmem alloc failed for %d bytes, %d avail\n",
			size, __pspgl_vidmem_avail());
		return 0;
	}

	buf->base = adr;
	buf->size = size;
	return vidmem_map_insert_new(vidmem_map_len, buf);
}

static int addr_cmp(const void *key, const void *b)
{
	const void *k = *(void **)key;
	struct pspgl_buffer **kb = (struct pspgl_buffer **)b;

	if (k < (*kb)->base)
		return -1;
	if (k == (*kb)->base)
		return 0;
	return 1;
}

void  __pspgl_vidmem_free (struct pspgl_buffer *buf)
{
	struct pspgl_buffer **chunk;

	chunk = bsearch(&buf->base, vidmem_map, vidmem_map_len, 
			sizeof(*vidmem_map), addr_cmp);

	if (chunk) {
		int i = chunk - vidmem_map;
		psp_log("free vidmem %d: adr 0x%08p - size 0x%08x\n", i,
			buf->base, buf->size);
			
		vidmem_map_len--;
		memmove(&vidmem_map[i], &vidmem_map[i+1],
			(vidmem_map_len-i) * sizeof(vidmem_map[0]));

		assert((vidmem_used - buf->size) < vidmem_used);
		vidmem_used -= buf->size;
	} else
		__pspgl_log("%s: didn't find chunk for buf=%p base=%p\n",
			    __FUNCTION__, buf, buf->base);
}


EGLBoolean __pspgl_vidmem_setup_write_and_display_buffer (struct pspgl_surface *s)
{
	int current_back = (s->color_buffer[1] == NULL) ? 0 : (s->current_front ^ 1);
	unsigned long adr;

	s->flip_start = now();

	psp_log("current_front %d\n", s->current_front);

	if (!s) {
		EGLERROR(EGL_BAD_SURFACE);
		return EGL_FALSE;
	}

	psp_log("pixfmt %u\n", s->pixfmt);

	sendCommandi(CMD_PSM, s->pixfmt);

	adr = (unsigned long) s->color_buffer[current_back]->base;
	psp_log("color buffer adr 0x%08x\n", adr);
	sendCommandi(CMD_DRAWBUF, ((adr & 0x00ffffff)));
	sendCommandi(CMD_DRAWBUFWIDTH, ((adr & 0xff000000) >> 8) | s->pixelperline);

	if (s->depth_buffer) {
		adr = (unsigned long) s->depth_buffer->base;
		psp_log("depth buffer adr 0x%08x\n", adr);
		sendCommandi(CMD_DEPTHBUF, ((adr & 0x00ffffff)));
		sendCommandi(CMD_DEPTHBUFWIDTH, ((adr & 0xff000000) >> 8) | s->pixelperline);
	}

	if (s->displayed) {
		/* wait for completion of pending render operations before display */
		__pspgl_buffer_dlist_sync(s->color_buffer[s->current_front]);

		sceDisplaySetFrameBuf(s->color_buffer[s->current_front]->base,
				      s->pixelperline,
				      s->pixfmt,
				      PSP_DISPLAY_SETBUF_NEXTFRAME);

		/* wait for sync if needed */
		if (pspgl_curctx->swap_interval > 0) {
			do {
				sceDisplayWaitVblankStart();
			} while ((sceDisplayGetVcount() % pspgl_curctx->swap_interval) != 0);
		}

		psp_log("display @ adr 0x%08p\n", s->color_buffer[s->current_front]->base);
	}

	s->prev_end = s->flip_end;
	s->flip_end = now();

	return EGL_TRUE;
}

/* 
 * Compact video memory, to eliminate fragmentation.
 * 
 * This walks through all the allocated blocks freeing and
 * reallocating each one, and emitting a GE copy command to transfer
 * the data.  This assumes that vidmem_free/alloc is
 * non-data-destructive.  It also assumes vidmem_alloc finds the
 * lowest suitable address (ie, first fit).
 *
 * This function is synchronous for now: it waits for all copying to
 * finish before returning.
 *
 */
void __pspgl_vidmem_compact(GLboolean sync)
{
	int i;
	struct pspgl_buffer **bufs;
	int nbufs = vidmem_map_len;
	int needsync = 0;

	bufs = malloc(sizeof(*bufs) * vidmem_map_len);
	if (bufs == NULL)
		return;

	/* Make a working copy while we play with the real one */
	memcpy(bufs, vidmem_map, vidmem_map_len * sizeof(*bufs));

	psp_log("compacting vidmem\n");

	for(i = 0; i < nbufs; i++) {
		struct pspgl_buffer *b = bufs[i];
		void *orig, *dest;
		unsigned size, xfersize;

		psp_log("  %d: %p %d  (flags %x)\n", 
			i, b->base, b->size, b->flags);

		/* Can't move buffer if it is mapped or fixed-pinned.
		   We don't really care if it's pinned for GE use,
		   because the GE will be finished with it by the time
		   it gets around to moving it. */
		if ((b->flags & BF_PINNED_FIXED) || b->mapped)
			continue;

		orig = b->base;

		/* Free chunk first... */
		__pspgl_vidmem_free(b);

		/* ...then find a new location for it */
		if (!__pspgl_vidmem_alloc(b)) {
			/* Should never happen, since we just freed a
			   space big enough for this buffer. */
			__pspgl_log("%s: lost buffer %p at %p\n",
				    __FUNCTION__, b, orig);
			break;
		}

		if (b->base == orig)
			continue;

		dest = b->base;

		psp_log("copying buffer %p (%u bytes) from %p->%p\n",
			b, b->size, orig, dest);

		size = b->size;
		size /= 4;	/* copy 32bpp "pixels" */
		xfersize = size;

		if ((dest < orig && dest+b->size > orig) ||
		    (orig < dest && orig+b->size > dest)) {
			if (dest < orig)
				xfersize = orig - dest;
			else
				xfersize = dest - orig;
			psp_log("   OVERLAPPING: xfersize=%u\n",
				xfersize);
		}

		/* Use pixel-copying to move the data, on the
		   assumption that since we're dealing with the GE's
		   local memory, it will be the fastest thing to copy
		   it.  Also, copying is synchronous with respect to
		   other GE commands.  The xfersize is small enough to
		   avoid overlapping copies. */
		while(size > 0) {
			unsigned w, h;
			unsigned chunk = size;

			if (chunk > xfersize)
				chunk = xfersize;

			if (chunk < 512) {
				w = chunk;
				h = 1;
			} else {
				w = 512;
				h = chunk / 512;
			}

			psp_log("  chunk %p->%p %dx%d\n",
				orig, dest, w, h);

			__pspgl_copy_pixels(orig, w, 0, 0,
					    dest, w, 0, 0,
					    w, h, GE_RGBA_8888);
			__pspgl_dlist_pin_buffer(b, BF_PINNED);

			needsync = 1;
			size -= w * h;
			orig += w * h;
			dest += w * h;
		}
	}

	free(bufs);

	if (sync && needsync)
		glFinish();
}
