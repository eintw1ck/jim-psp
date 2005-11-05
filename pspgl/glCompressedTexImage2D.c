#include <stdlib.h>
#include <string.h>

#include "pspgl_internal.h"
#include "pspgl_texobj.h"

/* 
   For compressed formats, convert the whole image; 
   width is the compressed image size in bytes
 */

/* PSP DXT1 hardware format reverses the colors and the per-pixel
   bits, and encodes the color in RGB 565 format */
static void copy_dxt1(const struct pspgl_texfmt *fmt, void *to, const void *from, unsigned size)
{
	const unsigned short *src = from;
	unsigned short *dest = to;

	for(; size >= 8; size -= 8) {
		dest[0] = src[2];
		dest[1] = src[3];
		dest[2] = src[0];
		dest[3] = src[1];

		dest += 4;
		src += 4;
	}
}

/* PSP DXT3 and 5 formats reverse the alpha and color parts of each
   block, and reverse the color and per-pixel terms in the color part. */
static void copy_dxt35(const struct pspgl_texfmt *fmt, void *to, const void *from, unsigned size)
{
	const unsigned short *src = from;
	unsigned short *dest = to;

	for(; size >= 16; size -= 16) {
		/* copy alpha */
		memcpy(&dest[4], &src[0], 8);

		dest[0] = src[6];
		dest[1] = src[7];
		dest[2] = src[4];
		dest[3] = src[5];

		dest += 8;
		src += 8;
	}
}

static const struct pspgl_texfmt comptexformats[] = {
	/* Compressed textures */
	{ GL_COMPRESSED_RGB_S3TC_DXT1_EXT,	GL_UNSIGNED_BYTE,	1, GE_DXT1,	1,	copy_dxt1,	GE_TEXENV_RGB  },
	{ GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,	GL_UNSIGNED_BYTE,	1, GE_DXT1,	1,	copy_dxt1,	GE_TEXENV_RGBA },
	{ GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,	GL_UNSIGNED_BYTE,	1, GE_DXT3,	1,	copy_dxt35,	GE_TEXENV_RGBA },
	{ GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,	GL_UNSIGNED_BYTE,	1, GE_DXT5,	1,	copy_dxt35,	GE_TEXENV_RGBA },

	{ 0, 0 }
};

void glCompressedTexImage2D(GLenum target, GLint level,
			    GLenum internalformat, GLsizei width,
			    GLsizei height, GLint border,
			    GLsizei imageSize, const void *data)
{
	const struct pspgl_texfmt *texfmt;
	struct pspgl_texobj *tobj;
	struct pspgl_teximg *timg;

	if (!ispow2(width) || !ispow2(height))
		goto invalid_value;

	if (level < 0 || level > MIPMAP_LEVELS)
		goto invalid_value;

	if (border != 0)
		goto invalid_value;

	texfmt = __pspgl_hardware_format(comptexformats, internalformat, GL_UNSIGNED_BYTE);
	if (texfmt == NULL)
		goto invalid_enum;

	if (!pspgl_curctx->texture.bound)
		glBindTexture(target, 0);

	tobj = pspgl_curctx->texture.bound;
	if (tobj == NULL)
		goto out_of_memory;

	if (data) {
		timg = __pspgl_teximg_new(data, width, height, imageSize, texfmt);
		if (timg == NULL)
			goto out_of_memory;

		__pspgl_set_texture_image(tobj, level, timg);
		__pspgl_teximg_free(timg); /* tobj has reference now */
	} else
		__pspgl_set_texture_image(tobj, level, NULL);

	__pspgl_update_texenv(tobj);
	return;

invalid_enum:
	GLERROR(GL_INVALID_ENUM);
	return;

invalid_value:
	GLERROR(GL_INVALID_VALUE);
	return;

out_of_memory:
	GLERROR(GL_OUT_OF_MEMORY);

}
