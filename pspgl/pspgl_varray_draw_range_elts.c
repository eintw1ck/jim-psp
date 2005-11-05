#include <string.h>
#include <limits.h>

#include "pspgl_internal.h"
#include "pspgl_buffers.h"

static unsigned getidx(const void *elts, GLenum idx_type, unsigned idx)
{
	unsigned ret = 0;

	switch(idx_type) {
	case GL_UNSIGNED_BYTE:
		ret = ((GLubyte *)elts)[idx];
		break;

	case GL_UNSIGNED_SHORT:
		ret = ((GLushort *)elts)[idx];
		break;

	case GL_UNSIGNED_INT:
		ret = ((GLuint *)elts)[idx];
		break;
	}

	return ret;
}


/*
   Like gen_varray(), but the vertices are indexed by the "elts" array.
   Assumes elts is a mapped pointer which we can directly use.
 */
static int gen_varray_elts(const struct vertex_format *vfmt, int first, int count, 
			   GLenum idx_type, const void *elts, void *to, int space)
{
	int i;
	unsigned char *dest = to;
	int nvtx = space / vfmt->vertex_size;
	void *ptrs[MAX_ATTRIB];

	if (nvtx > count)
		nvtx = count;

	for(i = 0; i < vfmt->nattrib; i++) {
		struct pspgl_vertex_array *a = vfmt->attribs[i].array;
		ptrs[i] = __pspgl_bufferobj_map(a->buffer, GL_READ_ONLY_ARB, (void *)a->ptr);
		psp_log("a->ptr=%p mapped to %p\n", a->ptr, ptrs[i]);
	}

	psp_log("mapped elts=%p\n", elts);

	for(i = 0; i < nvtx; i++) {
		int j;
		unsigned idx = getidx(elts, idx_type, first + i);

		for(j = 0; j < vfmt->nattrib; j++) {
			const struct attrib *attr = &vfmt->attribs[j];
			struct pspgl_vertex_array *a = attr->array;
			const unsigned char *ptr;

			ptr = ptrs[j] + (idx * a->stride);

			if (attr->convert)
				(*attr->convert)(&dest[attr->offset], ptr, attr);
			else
				memcpy(&dest[attr->offset], ptr, attr->size);
		}
		dest += vfmt->vertex_size;
	}

	for(i = 0; i < vfmt->nattrib; i++) {
		struct pspgl_vertex_array *a = vfmt->attribs[i].array;
		__pspgl_bufferobj_unmap(a->buffer, GL_READ_ONLY_ARB);
	}

	return nvtx;
}

/*
   Fallback indexed vertex rendering.  We can't use the hardware
   indexing, so we need to manually index each vertex and emit
   vertices into the command buffer memory.

   Expects indices to be a mapped pointer.
 */
static void draw_range_elts_fallback(GLenum mode, GLenum idx_type, const void *indices, 
				     const GLsizei count, const struct vertex_format *vfmt)
{
	long prim = __pspgl_glprim2geprim(mode);
	struct prim_info pi = __pspgl_prim_info[prim];
	unsigned first = 0;
	unsigned maxbatch;
	GLsizei remains;

	sendCommandi(CMD_VERTEXTYPE, vfmt->hwformat);

	maxbatch = MAX_VTX_BATCH / vfmt->vertex_size;

	psp_log("prim=%d maxbatch=%d\n", prim, maxbatch);

	remains = count;
	while(remains >= pi.minvtx) {
		unsigned batch = (remains > maxbatch) ? maxbatch : remains;
		unsigned batchsize;
		unsigned char *buf;
		unsigned done;

		batch = (batch / pi.vtxmult) * pi.vtxmult; /* round down to multiple */
		batchsize = batch * vfmt->vertex_size;
		buf = __pspgl_dlist_insert_space(pspgl_curctx->dlist_current, batchsize);

		psp_log("first=%d remains=%d batch=%d batchsize=%d buf=%p\n", 
			first, remains, batch, batchsize, buf);

		if (buf == NULL)
			break;

		if (prim == GE_TRIANGLE_FAN && first != 0) {
			done = gen_varray_elts(vfmt, 0, 1,
					       idx_type, indices,
					       buf, batchsize);
			done += gen_varray_elts(vfmt, first+1, remains-1,
						idx_type, indices,
						buf + vfmt->vertex_size,
						batchsize - vfmt->vertex_size);
		} else
			done = gen_varray_elts(vfmt, first, remains, 
					       idx_type, indices, buf, batchsize);

		remains -= done;
		first += done;

		if ((remains+pi.overlap) > pi.minvtx) {
			remains += pi.overlap;
			first -= pi.overlap;
		} else {
			/* This is the last batch.  XXX deal with line loop? */
		}

		sendCommandi(CMD_VERTEXTYPE, vfmt->hwformat);
		sendCommandiUncached(CMD_BASE, ((unsigned)buf >> 8) & 0x0f0000);
		sendCommandiUncached(CMD_VERTEXPTR, ((unsigned)buf) & 0xffffff);
		sendCommandiUncached(CMD_PRIM, (prim << 16) | done);
	}

	/* Go recursive to draw the final edge of a line loop */
	if (mode == GL_LINE_LOOP) {
		GLushort idx[2] = { count-1, 0 };

		draw_range_elts_fallback(GL_LINES, GL_UNSIGNED_SHORT, idx, 2, vfmt);
	}
}

/* Copy and convert an index array into hardware format; 32-bit
   indices are truncated to 16 bits.  Offset is subtracted from the
   indices if there's a non-0 minidx.  Expects from and to to be
   appropriately mapped pointers.  Returns the appropriate hwformat
   for the index type. */
static unsigned convert_indices(void *to, const void *from, GLenum idx_type, 
				int offset, GLsizei count)
{
	unsigned hwformat = 0;
	unsigned i;

	switch(idx_type) {
	case GL_UNSIGNED_BYTE:
		hwformat = GE_VINDEX_8BIT;
		for(i = 0; i < count; i++) 
			((GLubyte *)to)[i] = ((GLubyte *)from)[i] - offset;
		break;

	case GL_UNSIGNED_SHORT:
		hwformat = GE_VINDEX_16BIT;
		for(i = 0; i < count; i++)
			((GLushort *)to)[i] = ((GLushort *)from)[i] - offset;
		break;

	case GL_UNSIGNED_INT:
		hwformat = GE_VINDEX_16BIT;
		for(i = 0; i < count; i++)
			((GLushort *)to)[i] = ((GLuint *)from)[i] - offset;
		break;

	}

	return hwformat;
}

static int idx_sizeof(GLenum idx_type)
{
	int idxsize;

	switch(idx_type) {
	case GL_UNSIGNED_BYTE:	idxsize = 1; break;
	case GL_UNSIGNED_SHORT:
	case GL_UNSIGNED_INT:	idxsize = 2; break;
	default:		idxsize = 0;
	}

	return idxsize;
}

/* If its possible to directly use indices from a buffer, then return
   a pointer to the buffer (or NULL if there is no useful buffer).
   Updates *hwformat appropriately if we can use the buffer. */
static void *buffered_index(GLenum idxtype, const void *indices, unsigned *hwformat)
{
	const struct pspgl_bufferobj *idxbuf = pspgl_curctx->vertex_array.indexbuffer;
	void *ret = NULL;

	if (idxbuf && (idxtype == GL_UNSIGNED_BYTE || idxtype == GL_UNSIGNED_SHORT)) {
		if (idxbuf->mapped) {
			GLERROR(GL_INVALID_OPERATION);
			return NULL;
		}

		assert(idxbuf->data->mapped == 0);

		if (idxtype == GL_UNSIGNED_BYTE)
			*hwformat |= GE_VINDEX_8BIT;
		else
			*hwformat |= GE_VINDEX_16BIT;

		/* This pointer is for hardware use, so we don't need
		   to (in fact, shouldn't) map the buffer. */
		ret = __pspgl_bufferobj_deref(idxbuf, (void *)indices);
	}

	psp_log("idxtype=%x idxbuf=%p indices=%p hwformat=%x ret=%p\n", 
		idxtype, idxbuf, indices, *hwformat, ret);

	return ret;
}

/*
   We have a locked vertex array, so try to directly use it.  This
   means that we don't have to do any vertex format conversion here;
   we only need to copy the index data into the command buffer (or we
   may be able to use it directly from a buffer object).

   This may fall back to the slow path if we can't allocate enough
   buffer for the index data.
 */
static void draw_range_elts_locked(GLenum mode, GLenum idx_type, const void *indices, 
				   GLsizei count)
{
	struct locked_arrays *l = &pspgl_curctx->vertex_array.locked;
	unsigned extra;
	unsigned prim;
	void *idxbuf;
	unsigned hwformat;
	void *vtxbuf;
	unsigned idxsize;
	GLboolean directidx;

	prim = __pspgl_glprim2geprim(mode);

	idxsize = idx_sizeof(idx_type);

	if (idxsize == 0) {
		GLERROR(GL_INVALID_ENUM);
		return;
	}

	psp_log("drawing locked vertices: mode=%d idxtype=%x count=%d\n",
		mode, idx_type, count);

	/* If this is a line loop, add an extra index for the final
	   edge */
	extra = 0;
	if (mode == GL_LINE_LOOP)
		extra = 1;

	hwformat = l->vfmt.hwformat;

	/* Look to see if we can use an index buffer object */
	idxbuf = NULL;
	if (extra == 0) {
		idxbuf = buffered_index(idx_type, indices, &hwformat);
		psp_log("using index buffer object; idxbuf=%p; hwformat=%x\n", idxbuf, hwformat);
	}

	directidx = GL_TRUE;
	if (__builtin_expect(idxbuf == NULL, 0)) {
		/* Can't directly use an index buffer object, so
		   allocate space to copy+convert the index data. */

		directidx = GL_FALSE;

		idxbuf = __pspgl_dlist_insert_space(pspgl_curctx->dlist_current, 
						    idxsize * (count + extra));

		indices = __pspgl_bufferobj_map(pspgl_curctx->vertex_array.indexbuffer, 
					     GL_READ_ONLY, (void *)indices);

		if (__builtin_expect(idxbuf == NULL, 0)) {
			struct vertex_format vfmt;

			/*
			  SLOW: index data won't fit.
			   
			  Generate a new vertex format in case one of the
			  arrays has changed shape since it was cached.  The
			  spec doesn't require us to this (since changing a
			  locked array results in undefined behaviour), but
			  this is being nice.
			
			  XXX We could generate batches of indices out
			  of the locked array, like we do with normal
			  batched dispatch.  But it would be nice not
			  to have yet another version of the batched
			  array code...  Also, this should be a very
			  rare path.
			*/
			psp_log("can't get idxbuf (%d bytes): falling back to slow path\n",
				idxsize * (count + extra));

			__pspgl_ge_vertex_fmt(pspgl_curctx, &vfmt);
			draw_range_elts_fallback(mode, idx_type, indices, count, &vfmt);

			__pspgl_bufferobj_unmap(pspgl_curctx->vertex_array.indexbuffer, GL_READ_ONLY);
			return;
		}

		hwformat |= convert_indices(idxbuf, indices, idx_type, l->cached_first, count);

		/* Add an extra index for the final edge */
		if (mode == GL_LINE_LOOP)
			convert_indices(idxbuf + (idxsize * count), indices, idx_type, l->cached_first, 1);

		__pspgl_bufferobj_unmap(pspgl_curctx->vertex_array.indexbuffer, GL_READ_ONLY);
	}

	sendCommandi(CMD_VERTEXTYPE, hwformat);

	vtxbuf = l->cached_array->base + l->cached_array_offset;

	sendCommandiUncached(CMD_BASE, ((unsigned)vtxbuf >> 8) & 0xf0000);
	sendCommandiUncached(CMD_VERTEXPTR, ((unsigned)vtxbuf) & 0xffffff);
	sendCommandiUncached(CMD_BASE, ((unsigned)idxbuf >> 8) & 0xf0000);
	sendCommandiUncached(CMD_INDEXPTR, ((unsigned)idxbuf) & 0xffffff);

	sendCommandiUncached(CMD_PRIM, (prim << 16) | count);

	__pspgl_buffer_dlist_use(l->cached_array);
	if (directidx)
		__pspgl_buffer_dlist_use(pspgl_curctx->vertex_array.indexbuffer->data);
}

/* Find the min and max indices in an element array.  Expects indices
   to be a mapped pointer. */
static void find_minmax_indices(GLenum idx_type, const void *indices, unsigned count,
				int *minidxp, int *maxidxp)
{
	/* find the min and max idx */
	int i;
	int minidx, maxidx;

	minidx = INT_MAX;
	maxidx = 0;

	switch(idx_type) {
	case GL_UNSIGNED_BYTE:
		for(i = 0; i < count; i++) {
			GLuint idx = ((GLubyte *)indices)[i];
			if (idx < minidx)
				minidx = idx;
			if (idx > maxidx)
				maxidx = idx;
		}
		break;

	case GL_UNSIGNED_SHORT:
		for(i = 0; i < count; i++) {
			GLuint idx = ((GLushort *)indices)[i];
			if (idx < minidx)
				minidx = idx;
			if (idx > maxidx)
				maxidx = idx;
		}
		break;

	case GL_UNSIGNED_INT:
		for(i = 0; i < count; i++) {
			GLuint idx = ((GLuint *)indices)[i];
			if (idx < minidx)
				minidx = idx;
			if (idx > maxidx)
				maxidx = idx;
		}
		break;
	}

	*minidxp = minidx;
	*maxidxp = maxidx;
}

/* 
   The hardware has direct support for drawing indexed vertex arrays,
   which we try hard to use.

   There are 4 cases for drawing an indexed array (from best to worst):

   1. Our vertex array is locked, and the index array will fit into
      the command buffer. We don't need to do any format converion, and
      we can directly use hardware indexing.

   2. The array is not locked, but it is small enough to fit into the
      vertex buffer, along with the indices.  Can use hardware indexing.

   3. The array is locked, but the indices are too large to fit in the
      command buffer.  Slow path.

   4. The array is not locked, and the vertex+index data won't fit in
      the command buffer.  Slow path.

   In summary: 1: Whahoo! 2: Yay!  3+4: Boo!
*/
void __pspgl_varray_draw_range_elts(GLenum mode, GLenum idx_type, 
				    const void *const indices, GLsizei count, 
				    int minidx, int maxidx)
{
	long prim;
	struct vertex_format vfmt;
	struct prim_info pi;
	unsigned maxbatch;
	unsigned vtxsize, idxsize;
	unsigned hwformat;
	unsigned extra = 0;
	void *idxmap;

	prim = __pspgl_glprim2geprim(mode);

	if (prim < 0) {
		GLERROR(GL_INVALID_ENUM);
		return;
	}

	if (count == 0)
		return;

	/* Kick these out early, since we assume that we're going to
	   something, and every drawing path needs this done */
	__pspgl_context_flush_pending_matrix_changes(pspgl_curctx);

	if (__pspgl_cache_arrays()) {
		/* We have potentially usable locked+cached arrays */
		draw_range_elts_locked(mode, idx_type, indices, count);
		return;
	}

	psp_log("no locked arrays\n");

	pi = __pspgl_prim_info[prim];
	__pspgl_ge_vertex_fmt(pspgl_curctx, &vfmt);

	if (vfmt.hwformat == 0)
		return;

	idxsize = idx_sizeof(idx_type);

	if (idxsize == 0) {
		GLERROR(GL_INVALID_ENUM);
		return;
	}

	/* If this is a line loop, allocate space for an extra index
	   for the final edge */
	extra = 0;
	if (mode == GL_LINE_LOOP)
		extra = 1;

	void *idxbuf = NULL;

	hwformat = vfmt.hwformat;

	/* Check to see if we can directly use an index array out of a
	   buffer.   */
	if (extra == 0)
		idxbuf = buffered_index(idx_type, (void *)indices, &hwformat);

	if (idxbuf == NULL)
		idxsize *= (count + extra); /* allocate some space for indices */
	else
		idxsize = 0;	/* no need to allocate space */

	maxbatch = (MAX_VTX_BATCH - idxsize - 16);

	if (maxbatch > 0)
		maxbatch /= vfmt.vertex_size;
	else
		maxbatch = 0;

	/* Map indices for use */
	if (pspgl_curctx->vertex_array.indexbuffer && 
	    pspgl_curctx->vertex_array.indexbuffer->mapped) {
		GLERROR(GL_INVALID_OPERATION);
		return;
	}
	idxmap = __pspgl_bufferobj_map(pspgl_curctx->vertex_array.indexbuffer, 
				    GL_READ_ONLY, (void *)indices);

	/* scan for min and max idx, if we weren't given them */
	if (minidx == -1 || maxidx == -1)
		find_minmax_indices(idx_type, idxmap, count, &minidx, &maxidx);

	unsigned numvtx = maxidx - minidx + 1;
	vtxsize = ROUNDUP(numvtx * vfmt.vertex_size, 16);

	psp_log("prim=%d maxbatch=%d numvtx=%d count=%d maxidx=%d minidx=%d\n",
		prim, maxbatch, numvtx, count, maxidx, minidx);

	if (numvtx >= maxbatch) {
		/* SLOW: vertex+index data won't fit in command buffer */
		draw_range_elts_fallback(mode, idx_type, idxmap, count, &vfmt);
		goto out_unmap;
	}


	/* FAST(ish): offload everything in one step */

	unsigned char *buf = __pspgl_dlist_insert_space(pspgl_curctx->dlist_current, 
							vtxsize + idxsize);
	unsigned char *vtxbuf = buf;
	unsigned done;

	if (idxbuf == NULL)
		idxbuf = buf+vtxsize;

	if (buf)
		done = __pspgl_gen_varray(&vfmt, minidx, numvtx, vtxbuf, vtxsize);

	if (!buf || done != numvtx) {
		/* SLOW: couldn't use fast path */
		draw_range_elts_fallback(mode, idx_type, idxmap, count, &vfmt);
		goto out_unmap;
	}

	if (idxsize != 0) {
		hwformat |= convert_indices(idxbuf, idxmap, idx_type, minidx, count);

		/* Add an extra index for the final edge of a line loop */
		if (mode == GL_LINE_LOOP)
			convert_indices(idxbuf + (idxsize * count), idxmap, idx_type, minidx, 1);

	}

	/* Unmap indices before submitting to hardware, since we might
	   be submitting them directly */
	__pspgl_bufferobj_unmap(pspgl_curctx->vertex_array.indexbuffer, GL_READ_ONLY);

	sendCommandi(CMD_VERTEXTYPE, hwformat);

	sendCommandiUncached(CMD_BASE, ((unsigned)vtxbuf >> 8) & 0xf0000);
	sendCommandiUncached(CMD_VERTEXPTR, ((unsigned)vtxbuf) & 0xffffff);
	sendCommandiUncached(CMD_BASE, ((unsigned)idxbuf >> 8) & 0xf0000);
	sendCommandiUncached(CMD_INDEXPTR, ((unsigned)idxbuf) & 0xffffff);

	sendCommandiUncached(CMD_PRIM, (prim << 16) | count);

	if (idxsize == 0)
		__pspgl_buffer_dlist_use(pspgl_curctx->vertex_array.indexbuffer->data);

	return;

  out_unmap:
	__pspgl_bufferobj_unmap(pspgl_curctx->vertex_array.indexbuffer, GL_READ_ONLY);
}
