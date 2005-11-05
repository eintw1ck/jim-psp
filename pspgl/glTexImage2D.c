#include <string.h>
#include <malloc.h>

#include "pspgl_internal.h"
#include "pspgl_texobj.h"

static
unsigned long lg2 (unsigned long x)
{
	long i;

	for (i=9; i>=0; i--) {
		if ((1 << i) <= x)
			break;
	}

	return i;
}

static inline unsigned ispow2(unsigned n)
{
	return (n & (n-1)) == 0;
}

static void set_mipmap_regs(unsigned level, struct pspgl_teximg *img)
{
	if (img) {
		unsigned ptr = (unsigned)img->image;
		unsigned w_lg2 = lg2(img->width);
		unsigned h_lg2 = lg2(img->height);

		/* XXX pin image while texture registers refer to it */

		psp_log("set level %d image=%p %dx%d stride=%d\n",
			level, img->image, img->width, img->height,
			img->stride);

		sendCommandi(CMD_TEX_MIPMAP0 + level, ptr);
		sendCommandi(CMD_TEX_STRIDE0 + level, ((ptr >> 8) & 0xf0000) | img->stride);
		sendCommandi(CMD_TEX_SIZE0 + level, (h_lg2 << 8) | w_lg2);
	} else {
		psp_log("set level %d image=NULL", level);

		sendCommandi(CMD_TEX_MIPMAP0 + level, 0);
		sendCommandi(CMD_TEX_STRIDE0 + level, 0);
		sendCommandi(CMD_TEX_SIZE0 + level, 0);
	}
}

static void set_texture_image(struct pspgl_texobj *tobj, unsigned level, struct pspgl_teximg *timg)
{
	if (tobj->images[level] != NULL) {
		psp_log("replacing texture image %p at level %d with %p\n",
			tobj->images[level], level, timg);
		__pspgl_teximg_free(tobj->images[level]);
	}

	if (timg) {
		timg->refcount++;

		/* if we're changing texture formats, then invalidate all the other images */
		if (tobj->texfmt != timg->texfmt) {
			int i;
			for(i = 0; i < MIPMAP_LEVELS; i++)
				if (tobj->images[i] &&
				    tobj->images[i]->texfmt != timg->texfmt) {
					__pspgl_teximg_free(tobj->images[i]);
					tobj->images[i] = NULL;
					set_mipmap_regs(i, NULL);
				}
		}
		tobj->texfmt = timg->texfmt;

		sendCommandi(CMD_TEXFMT, tobj->texfmt->hwformat);
	}
	tobj->images[level] = timg;
	set_mipmap_regs(level, timg);
}

static inline GLboolean mipmap_filter(GLenum filter)
{
	return filter >= GL_NEAREST_MIPMAP_NEAREST && filter <= GL_LINEAR_MIPMAP_LINEAR;
}

#if 0
static GLboolean texobj_is_complete(struct pspgl_texobj *tobj)
{
	if (tobj == NULL) {
		psp_log("incomplete: tobj NULL\n");
		return GL_FALSE;
	}

	if (tobj->images[0] == NULL) {
		psp_log("incomplete: base NULL\n");
		return GL_FALSE;
	}

	if (mipmap_filter(tobj->min_filter)) {
		int i;

		/* XXX check sizes too */
		for(i = 1; i < MIPMAP_LEVELS; i++) {
			if (tobj->images[i] == NULL) {
				psp_log("incomplete: mipmap level %d missing\n", i);
				return GL_FALSE;
			}

			if (tobj->images[i]->texfmt != tobj->texfmt) {
				psp_log("incomplete: level %s mismatched format %d %d\n",
					i, tobj->images[i]->texfmt->hwformat, tobj->texfmt->hwformat);
				return GL_FALSE;
			}
		}
	}

	if (texfmt_is_indexed(tobj->texfmt) && tobj->cmap == NULL)
		return GL_FALSE;

	return GL_TRUE;
}
#endif

void glTexImage2D (GLenum target, GLint level, GLint internalformat, 
		   GLsizei width, GLsizei height, GLint border, 
		   GLenum format, GLenum type, const GLvoid *texels)
{
	struct pspgl_texobj *tobj;
	struct pspgl_teximg *timg;
	const struct pspgl_texfmt *texfmt;

	if (!ispow2(width) || !ispow2(height))
		goto invalid_value;

	if (level < 0 || level > MIPMAP_LEVELS)
		goto invalid_value;

	if (border != 0)
		goto invalid_value;

	if (format != internalformat)
		goto invalid_operation;

	texfmt = __pspgl_hardware_format(internalformat, type);
	if (texfmt == NULL)
		goto invalid_enum;

	psp_log("selected texfmt %d for fmt=%x type=%x\n", texfmt->hwformat, internalformat, type);

	if (!pspgl_curctx->texture.bound)
		glBindTexture(target, 0);

	tobj = pspgl_curctx->texture.bound;
	if (tobj == NULL)
		goto out_of_memory;

	if (texels) {
		timg = __pspgl_teximg_new(texels, width, height, texfmt);
		if (timg == NULL)
			goto out_of_memory;

		set_texture_image(tobj, level, timg);
		__pspgl_teximg_free(timg); /* tobj has reference now */
	} else
		set_texture_image(tobj, level, NULL);

	sendCommandi(CMD_TEXCACHE_FLUSH, getReg(CMD_TEXCACHE_FLUSH)+1);
	__pspgl_update_texenv(tobj);
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

out_of_memory:
	GLERROR(GL_OUT_OF_MEMORY);
}
