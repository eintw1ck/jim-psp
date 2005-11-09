#include <string.h>
#include <psputils.h>

#include "pspgl_internal.h"
#include "pspgl_texobj.h"

static const struct {
	GLenum format, type;
} formats[] = {
	[GE_RGB_565]	= { GL_RGB,  GL_UNSIGNED_SHORT_5_6_5_REV },
	[GE_RGBA_5551]	= { GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV },
	[GE_RGBA_4444]	= { GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4_REV },
	[GE_RGBA_8888]	= { GL_RGBA, GL_UNSIGNED_BYTE },
};

void glCopyTexImage2D(GLenum target,
		      GLint level,
		      GLenum internalformat,
		      GLint x, GLint y,
		      GLsizei width, GLsizei height,
		      GLint border)
{
	GLenum fb_fmt, fb_type;
	struct pspgl_texobj *tobj;
	struct pspgl_teximg *timg;
	struct pspgl_surface *read;
	int dest_x, dest_y;

	read = pspgl_curctx->read;
	fb_fmt = formats[read->pixfmt].format;
	fb_type = formats[read->pixfmt].type;

	/* glTexImage2D does all the hard work... */
	glTexImage2D(target, level, fb_fmt, width, height, border, fb_fmt, fb_type, NULL);
	if (pspgl_curctx->glerror != GL_NO_ERROR)
		return;

	tobj = pspgl_curctx->texture.bound;
	timg = tobj->images[level];

	assert(timg->texfmt->hwformat == read->pixfmt);
	assert(width == timg->width);
	assert(height == timg->height);

	dest_x = 0;
	dest_y = 0;

	if (x < 0) {
		x = -x;
		dest_x += x;
		width -= x;
		x = 0;
	}
	if ((x + width) > read->width)
		width -= (x + width) - read->width;

	if (y < 0) {
		y = -y;
		dest_y += y;
		height -= y;
		y = 0;
	}
	if ((y + height) > read->height)
		height -= (y + height) - read->height;

	if (width <= 0 || height <= 0) {
		GLERROR(GL_INVALID_VALUE);
		return;
	}

	/* The framebuffer and the texture are upside down with
	   respect to each other, so we need to flip the image (in the
	   framebuffer, lower addresses are in the upper-left, but for
	   textures, lower addresses are lower-left).
	*/
	y = read->height - y;

	__pspgl_copy_pixels(read->color_buffer[!read->current_front], -read->pixelperline, x, y,
			    timg->image->base + timg->offset, timg->width, dest_x, dest_y,
			    width, height, read->pixfmt);
	__pspgl_dlist_pin_buffer(timg->image);

	sendCommandi(CMD_TEXCACHE_SYNC, getReg(CMD_TEXCACHE_SYNC)+1);
	sendCommandi(CMD_TEXCACHE_FLUSH, getReg(CMD_TEXCACHE_FLUSH)+1);

	if (level == 0)
		__pspgl_update_mipmaps();

	return;
}
