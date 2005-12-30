/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>

#include "../common/callbacks.h"
#include "../common/geometry.h"

PSP_MODULE_INFO("Depth Of Field Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define TORUS_SLICES 24 // numc
#define TORUS_ROWS 24 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

TCPVertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

#define COLOR1_OFFSET 0
#define COLOR2_OFFSET 0x88000
#define ZBUFFER_OFFSET 0x110000
#define ZBUFFER_LINEAR(x) (0x600000 + x)
#define ZBUFFER_SLICE 64
#define VRAM_OFFSET(x) (0x4000000 + x)
#define ZFAR_LIMIT 64
#define ZNEAR_LIMIT 256
#define FOG_COLOR 0x554433

unsigned int __attribute__((aligned(16))) blendPalette[2][256];
unsigned int __attribute__((aligned(16))) maskPalette[2][256];
unsigned int rawPalette[256];

void RenderFog()
{
	int i;

	// split in two passes since the depth buffer won't fit in a 512x512 texture when using 8-bit textures

	for (i = 0; i < 2; ++i)
	{
		int j;

		sceGuTexMode(GU_PSM_T8,0,0,0);
		sceGuTexImage(0,512,512,1024,(void*)VRAM_OFFSET(ZBUFFER_LINEAR(ZBUFFER_OFFSET + i * (256*2))));
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		sceGuTexFilter(GU_NEAREST,GU_NEAREST);
		sceGuColor(0);

		for (j = 0; j < (256/ZBUFFER_SLICE); ++j)
		{
			struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(sizeof(struct Vertex)*2);

			// shift texture 1 pixel to avoid the 8 LSB, since they change very rapidly

			vertices[0].u = 1 + j*(ZBUFFER_SLICE * 2);
			vertices[0].v = 0;
			vertices[0].color = 0;
			vertices[0].x = j*ZBUFFER_SLICE + i * 256;
			vertices[0].y = 0;
			vertices[0].z = 0;

			vertices[1].u = 1 + (j+1)*(ZBUFFER_SLICE * 2);
			vertices[1].v = SCR_HEIGHT;
			vertices[1].color = 0;
			vertices[1].x = (j+1)*ZBUFFER_SLICE + i * 256;
			vertices[1].y = SCR_HEIGHT;
			vertices[1].z = 0;

			sceGuDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D,2,0,vertices);
		}
	}
}

int main(int argc, char* argv[])
{
	int i,j;

	SetupCallbacks();

	// generate palettes

	for (i = 0; i < 256; ++i)
	{
		int distance = i-dofPlane;

		// TODO: scale to maximize 

	}

	for (i = 0; i < 256; ++i)
		rawPalette[i] = (i << 24)|(i << 16)|(i << 8)|i;

	// generate torus

	generateTorusTCP(TORUS_SLICES,TORUS_ROWS,TORUS_RADIUS_TORUS_THICKNESS,torus_vertices,torus_indices);

	sceKernelDcacheWritebackAll();

	// setup GU

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)COLOR1_OFFSET,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)COLOR2_OFFSET,BUF_WIDTH);
	sceGuDepthBuffer((void*)ZBUFFER_OFFSET,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(65535,0);
	sceGuDisable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuDisable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	pspDebugScreenInit();

	// run sample

	int val = 0;
	int split = 0;
	SceCtrlData oldPad;
	oldPad.Buttons = 0;

	float nearPlane = 1.0f;
	float farPlane = 100.0f;
	float distance = 10.0f;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	while(running())
	{
		unsigned int* blendPalettes[2];
		unsigned int* maskPalettes[2];

		sceGuStart(GU_DIRECT,list);

		// generate palettes

		for (i = 0; i < 2; ++i)
		{
			blendPalettes[i] = (unsigned int*)((((unsigned int)sceGuGetMemory(256*4 + 16)) + 15) ~15);
			maskPalettes[i] = (unsigned int*)((((unsigned int)sceGuGetMemory(256*4 + 16)) + 15) ~15);
		}

		// compute dof palettes
		
		int dofPlane = ((int)(65536.0f / (1.0f + ((distance-near) / (far-near)) * 65535.0f))-1) >> 8;

		for (i = 0; i < 256; ++i)
		{
			blendPalettes[0][i] = ((distance > 0 ? 0 : abs(distance)) << 24) | 0xff00ff; // background blend
			blendPalettes[1][i] = ((distance < 0 ? 0 : abs(distance)) << 24) | 0xff00ff; // foreground blend

			maskPalettes[0][i] = ((distance < 0 ? 255 : 0) << 24) | 0xff00ff; // background mask
			maskPalettes[1][i] = ((distance > 0 ? 255 : 0) << 24) | 0xff00ff; // foreground mask
		}

		// switch mode if requested

		SceCtrlData pad;
		if (sceCtrlPeekBufferPositive(&pad,1))
		{
			if (pad.Buttons != oldPad.Buttons)
			{
				if (pad.Buttons & PSP_CTRL_CROSS)
					split ^= 1;
			}
			oldPad = pad;
		}

		// clear screen

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup matrices for cube

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,1.0f,100.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		for (i = 0; i < 3; ++i)
		{
			int ival = val + i * 64;

			sceGumMatrixMode(GU_MODEL);
			sceGumLoadIdentity();
			{
				ScePspFVector3 pos = { -2.5f + i * i * 5.0f, 0, -5.0f + sinf((ival/2.0f) * (GU_PI/180.0f)) * 2.5f - i * 10.0f };
				ScePspFVector3 rot = { ival * 0.79f * (GU_PI/180.0f), ival * 0.98f * (GU_PI/180.0f), ival * 1.32f * (GU_PI/180.0f) };
				sceGumTranslate(&pos);
				sceGumRotateXYZ(&rot);
			}
			sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);
		}

		if (split)
		{
			int size = 64;
			int offset = 240 + (int)(sinf(val * 0.56f * (GU_PI/180.0f)) * (240-size));

			sceGuEnable(GU_TEXTURE_2D);
			sceGuDisable(GU_DEPTH_TEST);
			sceGuDepthMask(0xffff);

			sceGuEnable(GU_BLEND);
			sceGuBlendFunc(GU_ADD,GU_SRC_ALPHA,GU_ONE_MINUS_SRC_ALPHA,0,0);

			sceGuEnable(GU_SCISSOR_TEST);
			sceGuScissor(offset - size,0,offset + size,SCR_HEIGHT);

			sceGuClutMode(GU_PSM_8888,0,255,0);
			sceGuClutLoad(256/8,maskPalette[0]);//rawPalette);

			RenderFog();

			sceGuDisable(GU_SCISSOR_TEST);

			sceGuDisable(GU_BLEND);

			sceGuDisable(GU_TEXTURE_2D);
			sceGuEnable(GU_DEPTH_TEST);
			sceGuDepthMask(0);

			sceGuColor(0xffffff);
			for (i = 0; i < 2; ++i)
			{
				struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));

				vertices[0].u = 0;
				vertices[0].v = 0;
				vertices[0].color = 0xffffff;
				vertices[0].x = offset - size + i * size * 2;
				vertices[0].y = 0;
				vertices[0].z = 0;

				vertices[1].u = 0;
				vertices[1].v = 0;
				vertices[1].color = 0xffffff;
				vertices[1].x = offset - size + i * size * 2;
				vertices[1].y = SCR_HEIGHT;
				vertices[1].z = 0;

				sceGuDrawArray(GU_LINES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D,2,0,vertices);
			}
		}

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("X = normal/split screen");

		val++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
