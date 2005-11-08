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
#include <time.h>

#include <pspctrl.h>
#include <pspgu.h>

PSP_MODULE_INFO("Blit Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

#define SLICE_SIZE 64 // change this to experiment with different page-cache sizes

static unsigned int __attribute__((aligned(16))) list[262144];

int done = 0;
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
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

static unsigned short __attribute__((aligned(16))) pixels[512*272];

struct Vertex
{
	unsigned short u, v;
	unsigned short color;
	short x, y, z;
};

void simpleBlit(int sx, int sy, int sw, int sh, int dx, int dy)
{
	// simple blit, this just copies A->B, with all the cache-misses that apply

	struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));

	vertices[0].u = sx; vertices[0].v = sy;
	vertices[0].color = 0;
	vertices[0].x = dx; vertices[0].y = dy; vertices[0].z = 0;

	vertices[1].u = sx+sw; vertices[1].v = sy+sh;
	vertices[1].color = 0;
	vertices[1].x = dx+sw; vertices[1].y = dy+sh; vertices[1].z = 0;

	sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
}

void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy)
{
	int start, end;

	// blit maximizing the use of the texture-cache

	/*
		the texture cache is 8kB. It is used in the following fashions:
		4-bit: 128x128
		8-bit: 128x64
		16-bit: 64x64
		32-bit: 64x32

		swizzling your input will give more than 100% increase in speed
	*/

	for (start = sx, end = sx+sw; start < end; start += SLICE_SIZE, dx += SLICE_SIZE)
	{
		struct Vertex* vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));
		int width = (start + SLICE_SIZE) < end ? SLICE_SIZE : end-start;

		vertices[0].u = start; vertices[0].v = sy;
		vertices[0].color = 0;
		vertices[0].x = dx; vertices[0].y = dy; vertices[0].z = 0;

		vertices[1].u = start + width; vertices[1].v = sy + sh;
		vertices[1].color = 0;
		vertices[1].x = dx + width; vertices[1].y = dy + sh; vertices[1].z = 0;

		sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_COLOR_4444|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
	}
}

int main(int argc, char* argv[])
{
	unsigned int x,y;

	pspDebugScreenInit();
	SetupCallbacks();

	sceGuInit();

	// setup
	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,512);
	sceGuDispBuffer(480,272,(void*)0x88000,512);
	sceGuDepthBuffer((void*)0x110000,512);
	sceGuOffset(2048 - (480/2),2048 - (272/2));
	sceGuViewport(2048,2048,480,272);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,480,272);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuFrontFace(GU_CW);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	int val = 0;

	// generate dummy image to blit

	for (y = 0; y < 272; ++y)
	{
		unsigned short* row = &pixels[y * 512];
		for (x = 0; x < 480; ++x)
		{
			row[x] = x * y;
		}
	}

	sceKernelDcacheWritebackAll();

	float curr_ms = 1.0f;
	struct timeval time_slices[16];
	int blit_method = 0;
	int swizzle = 0;
	SceCtrlData oldPad;
	oldPad.Buttons = 0;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	while (!done)
	{
		SceCtrlData pad;

		sceGuStart(GU_DIRECT,list);

		// switch methods if requested

		if(sceCtrlPeekBufferPositive(&pad, 1))
		{
			if (pad.Buttons != oldPad.Buttons)
			{
				if(pad.Buttons & PSP_CTRL_CROSS)
					blit_method ^= 1;
				if(pad.Buttons & PSP_CTRL_CIRCLE)
					swizzle ^= 1;
			}
			oldPad = pad;
		}

		sceGuTexMode(GU_PSM_4444,0,0,swizzle); // 16-bit RGBA
		sceGuTexImage(0,512,512,512,pixels); // setup texture as a 512x512 texture, even though the buffer is only 512x272 (480 visible)
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA); // don't get influenced by any vertex colors
		sceGuTexFilter(GU_NEAREST,GU_NEAREST); // point-filtered sampling

		if (blit_method)
			advancedBlit(0,0,480,272,0,0);
		else
			simpleBlit(0,0,480,272,0,0);

		sceGuFinish();
		sceGuSync(0,0);

		float curr_fps = 1.0f / curr_ms;

//		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("fps: %d.%03d (%dMB/s) (X = mode, O = swizzle)",(int)curr_fps,(int)((curr_fps-(int)curr_fps) * 1000.0f),(((int)curr_fps * 480 * 272 * 2)/(1024*1024)));

		// simple frame rate counter

		gettimeofday(&time_slices[val & 15],0);

		val++;

		if (!(val & 15))
		{
			struct timeval last_time = time_slices[0];
			unsigned int i;

			curr_ms = 0;
			for (i = 1; i < 16; ++i)
			{
				struct timeval curr_time = time_slices[i];

				if (last_time.tv_usec > curr_time.tv_usec)
				{
					curr_time.tv_sec++;
					curr_time.tv_usec-=1000000;
				}

				curr_ms += ((curr_time.tv_usec-last_time.tv_usec) + (curr_time.tv_sec-last_time.tv_sec) * 1000000) * (1.0f/1000000.0f);

				last_time = time_slices[i];
			}
			curr_ms /= 15.0f;
		}
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
