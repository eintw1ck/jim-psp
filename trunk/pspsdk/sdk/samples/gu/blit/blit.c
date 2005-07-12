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

#include <pspgu.h>

PSP_MODULE_INFO("Blit Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

#define SLICE_SIZE 64 // change this to experiment with different page-cache sizes

static unsigned int __attribute__((aligned(16))) list[262144];

int done = 0;
/* Exit callback */
int exit_callback(void)
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

int main(int argc, char* argv[])
{
	unsigned int x,y;

	pspDebugScreenInit();
	SetupCallbacks();

	sceGuInit();

	// setup
	sceGuStart(0,list);
	sceGuDrawBuffer(GE_PSM_4444,(void*)0,512);
	sceGuDispBuffer(480,272,(void*)0x88000,512);
	sceGuDepthBuffer((void*)0x110000,512);
	sceGuOffset(2048 - (480/2),2048 - (272/2));
	sceGuViewport(2048,2048,480,272);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,480,272);
	sceGuEnable(GU_STATE_SCISSOR);
	sceGuFrontFace(GE_FACE_CW);
	sceGuEnable(GU_STATE_TEXTURE);
	sceGuClear(GE_CLEAR_COLOR|GE_CLEAR_DEPTH);
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

	float curr_ms = 1.0f;
	struct timeval time_slices[16];

	while (!done)
	{
		unsigned int j;
		struct Vertex* vertices;

		sceGuStart(0,list);

		// setup the source buffer as a 512x512 texture, but only copy 480x272
		sceGuTexMode(GE_TPSM_4444,0,0,0);
		sceGuTexImage(0,512,512,512,pixels);
		sceGuTexFunc(GE_TFX_REPLACE,0);
		sceGuTexFilter(GE_FILTER_POINT,GE_FILTER_POINT);
		sceGuTexScale(1.0f/512.0f,1.0f/512.0f); // scale UVs to 0..1
		sceGuTexOffset(0,0);
		sceGuAmbientColor(0xffffffff);

		// do a striped blit (takes the page-cache into account)

		for (j = 0; j < 480; j = j+SLICE_SIZE)
		{
			vertices = (struct Vertex*)sceGuGetMemory(2 * sizeof(struct Vertex));

			vertices[0].u = j; vertices[0].v = 0;
			vertices[0].color = 0;
			vertices[0].x = j; vertices[0].y = 0; vertices[0].z = 0;
			vertices[1].u = j+SLICE_SIZE; vertices[1].v = 272;
			vertices[1].color = 0;
			vertices[1].x = j+SLICE_SIZE; vertices[1].y = 272; vertices[1].z = 0;

			sceGuDrawArray(GU_PRIM_SPRITES,GE_SETREG_VTYPE(GE_TT_16BIT,GE_CT_4444,0,GE_MT_16BIT,0,0,0,0,GE_BM_2D),2,0,vertices);
		}

		sceGuFinish();
		sceGuSync(0,0);

		float curr_fps = 1.0f / curr_ms;

//		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("%d.%03d",(int)curr_fps,(int)((curr_fps-(int)curr_fps) * 1000.0f));

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
