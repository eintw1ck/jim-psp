#include <string.h>
#include <psputils.h>

#include "pspgl_internal.h"
#include "pspgl_texobj.h"

static void convert_subimage(struct pspgl_teximg *img, void *to, const void *pixels, 
			     int xoffset, int yoffset, unsigned width, unsigned height)
{
	const unsigned pixsz = img->texfmt->hwsize;
	unsigned tostride = img->width * pixsz;
	unsigned fromstride = width * pixsz;
	void (*convert)(const struct pspgl_texfmt *, void *to, const void *from, unsigned width);
	convert = img->texfmt->convert;

	to += (yoffset * img->width + xoffset) * pixsz;

	while(height--) {
		(*convert)(img->texfmt, to, pixels, width);
		to += tostride;
		pixels += fromstride;
	}
}

static void convert_subimage_swizzled(struct pspgl_teximg *img, void *to, const void *pixels,
				      int xoffset, int yoffset,
				      unsigned width, unsigned height)
{
	const int lg2_hwsize = lg2(img->texfmt->hwsize);
	const int lg2_pixsize = lg2(img->texfmt->pixsize);
	const unsigned lg2_w = lg2(img->width << lg2_hwsize);
	const unsigned chunkpix = 16 >> lg2_hwsize;
	unsigned y, src, dst, srcstride, dststride;
	void (*convert)(const struct pspgl_texfmt *, void *to, const void *from, unsigned width);
	convert = img->texfmt->convert;

	src = 0;
	srcstride = 0;		/* = (width-stride) * pixsize, where width==stride */

	dst = (yoffset * img->width + xoffset) << lg2_hwsize;
	dststride = (img->width - width) << lg2_hwsize;

	for(y = 0; y < height; y++, src += srcstride, dst += dststride) {
		unsigned x, remains;

		x = xoffset;
		remains = width;

		while(remains) {
			unsigned dstswiz = swizzle(dst, lg2_w);
			unsigned span;

			span = chunkpix - (x & (chunkpix - 1));
			if (span > remains)
				span = remains;

			(*convert)(img->texfmt, to + dstswiz, pixels + src, span);

			remains -= span;
			x += span;

			dst += span << lg2_hwsize;
			src += span << lg2_pixsize;
		}
	}
}

void glTexSubImage2D( GLenum target, GLint level,
		      GLint xoffset, GLint yoffset,
		      GLsizei width, GLsizei height,
		      GLenum format, GLenum type,
		      const GLvoid *pixels )
{
	struct pspgl_texobj *tobj;
	struct pspgl_teximg *timg;
	const struct pspgl_texfmt *texfmt;
	void *p;

	if (!pspgl_curctx->texture.bound)
		glBindTexture(target, 0);

	tobj = pspgl_curctx->texture.bound;

	if (tobj == NULL)
		goto out_of_memory;

	if (tobj->target != target)
		goto invalid_enum;

	if (tobj->texfmt == NULL)
		goto invalid_operation;

	if (level < 0 || level >= MIPMAP_LEVELS)
		goto invalid_value;

	if (width < 0 || height < 0 || xoffset < 0 || yoffset < 0)
		goto invalid_value;

	timg = tobj->images[level];
	if (timg == NULL)
		goto invalid_operation;

	if (xoffset+width > timg->width || yoffset+height > timg->height)
		goto invalid_value;

	texfmt = __pspgl_hardware_format(__pspgl_texformats, format, type);
	if (texfmt != tobj->texfmt)
		goto invalid_enum;

	/* Can't handle compressed images yet */
	if (texfmt->hwformat >= GE_DXT1 || texfmt->hwformat == GE_INDEX_4BIT)
		goto invalid_operation;

	assert(timg->image->refcount > 0);

	__pspgl_buffer_dlist_sync(timg->image);
	p = __pspgl_buffer_map(timg->image, GL_WRITE_ONLY_ARB) + timg->offset;

	if (tobj->flags & TOF_SWIZZLED)
		convert_subimage_swizzled(timg, p, pixels, xoffset, yoffset, width, height);
	else
		convert_subimage(timg, p, pixels, xoffset, yoffset, width, height);

	__pspgl_buffer_unmap(timg->image, GL_WRITE_ONLY_ARB);

	if (level == 0 && (tobj->flags & TOF_GENERATE_MIPMAPS))
		__pspgl_update_mipmaps();

	return;

  out_of_memory:
	GLERROR(GL_OUT_OF_MEMORY);
	return;

  invalid_enum:
	GLERROR(GL_INVALID_ENUM);
	return;

  invalid_value:
	GLERROR(GL_INVALID_VALUE);
	return;

  invalid_operation:
	GLERROR(GL_INVALID_OPERATION);
	return;
}
