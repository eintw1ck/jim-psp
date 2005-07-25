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

PSP_MODULE_INFO("CopyImage Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

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

static unsigned int __attribute__((aligned(16))) pixels[512*272];

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
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	int val = 0;

	// generate dummy image to blit

	for (y = 0; y < 272; ++y)
	{
		unsigned int* row = &pixels[y * 512];
		for (x = 0; x < 480; ++x)
		{
			row[x] = x * y;
		}
	}

	sceKernelDcacheWritebackAll();

	float curr_ms = 1.0f;
	struct timeval time_slices[16];

	void* framebuffer = 0;

	while (!done)
	{
		unsigned int j;
		struct Vertex* vertices;

		sceGuStart(GU_DIRECT,list);

		// copy image from ram to vram

		sceGuCopyImage(GU_PSM_8888,0,0,480,272,512,pixels,0,0,512,(void*)(0x04000000+(u32)framebuffer));

		sceGuFinish();
		sceGuSync(0,0);

		float curr_fps = 1.0f / curr_ms;

//		sceDisplayWaitVblankStart();
		framebuffer = sceGuSwapBuffers();

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
