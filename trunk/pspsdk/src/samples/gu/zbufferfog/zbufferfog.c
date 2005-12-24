/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * This implements unswizzled depth-fog using the hardware unswizzling
 * figured out by Jeremy Fitzhardinge.
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

PSP_MODULE_INFO("Depth Buffer Fog Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float u, v;
	unsigned int color;
	float x,y,z;
};

int SetupCallbacks();

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

struct Vertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
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

unsigned int fogPalette[256];
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
	SetupCallbacks();

	// generate torus (TODO: tri-strips)

	int i,j;

	for (j = 0; j < TORUS_SLICES; ++j)
	{
		for (i = 0; i < TORUS_ROWS; ++i)
		{
			struct Vertex* curr = &torus_vertices[i+j*TORUS_ROWS];
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;

			cs = cosf(s * (2*GU_PI)/TORUS_SLICES);
			ct = cosf(t * (2*GU_PI)/TORUS_ROWS);
			ss = sinf(s * (2*GU_PI)/TORUS_SLICES);
			st = sinf(t * (2*GU_PI)/TORUS_ROWS);

			curr->u = cs * ct;
			curr->v = cs * st;

			unsigned int r = 128 + (cs * ct) * 127;
			unsigned int g = 128 + (cs * st) * 127;
			unsigned int b = 128 + (ss) * 127;

			curr->color = (0xff<<24)|(b << 16)|(g << 8)|r;

			curr->x = (TORUS_RADIUS + TORUS_THICKNESS * cs) * ct;
			curr->y = (TORUS_RADIUS + TORUS_THICKNESS * cs) * st;
			curr->z = TORUS_THICKNESS * ss;
		}
	}

	for (j = 0; j < TORUS_SLICES; ++j)
	{
		for (i = 0; i < TORUS_ROWS; ++i)
		{
			unsigned short* curr = &torus_indices[(i+(j*TORUS_ROWS))*6];
			unsigned int i1 = (i+1)%TORUS_ROWS, j1 = (j+1)%TORUS_SLICES;

			*curr++ = i + j * TORUS_ROWS;
			*curr++ = i1 + j * TORUS_ROWS;
			*curr++ = i + j1 * TORUS_ROWS;

			*curr++ = i1 + j * TORUS_ROWS;
			*curr++ = i1 + j1 * TORUS_ROWS;
			*curr++ = i + j1 * TORUS_ROWS;
		}
	}

	for (i = 0; i < 256; ++i)
	{
		unsigned int far = (i - ZFAR_LIMIT) < 0 ? 0 : (i - ZFAR_LIMIT);
		unsigned int near = (far * 256) / (ZNEAR_LIMIT-ZFAR_LIMIT);
		unsigned int k = near > 255 ? 255 : near;
		fogPalette[i] = (k<<24)|FOG_COLOR;

		rawPalette[i] = (i << 24)|(i << 16)|(i << 8)|i;
	}

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

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	for(;;)
	{
		sceGuStart(GU_DIRECT,list);

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

		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();
		{
			ScePspFVector3 pos = { 0, 0, -5.0f + sinf(val * (GU_PI/180.0f)) * 2.5f };
			ScePspFVector3 rot = { val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f) };
			sceGumTranslate(&pos);
			sceGumRotateXYZ(&rot);
		}

		// draw cube

		sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

		// fog using the zbuffer

		sceGuEnable(GU_TEXTURE_2D);
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(0xffff);
		sceGuColor(0);

		sceGuClutMode(GU_PSM_8888,0,255,0);
		sceGuClutLoad(256/8,fogPalette);

		sceGuEnable(GU_BLEND);
		sceGuBlendFunc(GU_ADD,GU_ONE_MINUS_SRC_ALPHA,GU_SRC_ALPHA,0,0);

		RenderFog();

		sceGuDisable(GU_BLEND);

		// render raw fog if enabled

		if (split)
		{
			sceGuEnable(GU_SCISSOR_TEST);
			sceGuScissor(SCR_WIDTH/2,0,SCR_WIDTH,SCR_HEIGHT);

			sceGuClutMode(GU_PSM_8888,0,255,0);
			sceGuClutLoad(256/8,rawPalette);

			RenderFog();

			sceGuDisable(GU_SCISSOR_TEST);
		}

		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);	

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

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
