/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * fdprintf.c - PSPLINK implementation of fdprintf since sony broke it in 3.5X
 *
 * Copyright (c) 2007 TyRaNiD
 *
 * $HeadURL$
 * $Id$
 */
#include <pspkernel.h>
#include <pspsysclib.h>

#define CTX_BUF_SIZE 128

struct prnt_ctx 
{
	unsigned short fd;
	unsigned short len;
	unsigned char buf[CTX_BUF_SIZE];
};

static void cb(struct prnt_ctx *ctx, int type)
{
	if(type == 0x200) 
	{
		ctx->len = 0;
	}
	else if(type == 0x201)
	{
		sceIoWrite(ctx->fd, ctx->buf, ctx->len);
		ctx->len = 0;
	}
	else
	{
		if(type == '\n')
		{
			cb(ctx, '\r');
		}
		
		ctx->buf[ctx->len++] = type;
		if(ctx->len == CTX_BUF_SIZE)
		{
			sceIoWrite(ctx->fd, ctx->buf, ctx->len);
			ctx->len = 0;
		}
	}
}

int fdprintf(int fd, const char *fmt, ...)
{
	struct prnt_ctx ctx;
	va_list opt;

	ctx.fd = fd;
	ctx.len = 0;

	va_start(opt, fmt);

	prnt((prnt_callback) cb, (void*) &ctx, fmt, opt);

	va_end(opt);

	return 0;
}
