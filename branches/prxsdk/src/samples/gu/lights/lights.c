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

PSP_MODULE_INFO("Lights Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float nx,ny,nz;
 	float x,y,z;
};

int SetupCallbacks();

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define GRID_COLUMNS 32
#define GRID_ROWS 32
#define GRID_SIZE 10.0f

struct Vertex __attribute__((aligned(16))) grid_vertices[GRID_COLUMNS*GRID_ROWS];
unsigned short __attribute__((aligned(16))) grid_indices[(GRID_COLUMNS-1)*(GRID_ROWS-1)*6];

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

#define LIGHT_DISTANCE 3.0f

struct Vertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

unsigned int colors[4] =
{
	0xffff0000,
	0xff00ff00,
	0xff0000ff,
	0xffff00ff
};

int main(int argc, char* argv[])
{
	unsigned int i,j;

	SetupCallbacks();

	// generate grid (TODO: tri-strips)

	for (j = 0; j < GRID_ROWS; ++j)
	{
		for (i = 0; i < GRID_COLUMNS; ++i)
		{
			struct Vertex* curr = &grid_vertices[i+j*GRID_COLUMNS];

			curr->nx = 0.0f;
			curr->ny = 1.0f;
			curr->nz = 0.0f;

			curr->x = ((i * (1.0f/((float)GRID_COLUMNS)))-0.5f) * GRID_SIZE;
			curr->y = 0;
			curr->z = ((j * (1.0f/((float)GRID_COLUMNS)))-0.5f) * GRID_SIZE;
		}
	}

	for (j = 0; j < GRID_ROWS-1; ++j)
	{
		for (i = 0; i < GRID_COLUMNS-1; ++i)
		{
			unsigned short* curr = &grid_indices[(i+(j*(GRID_COLUMNS-1)))*6];

			*curr++ = i + j * GRID_COLUMNS;
			*curr++ = (i+1) + j * GRID_COLUMNS;
			*curr++ = i + (j+1) * GRID_COLUMNS;

			*curr++ = (i+1) + j * GRID_COLUMNS;
			*curr++ = (i+1) + (j+1) * GRID_COLUMNS;
			*curr++ = i + (j + 1) * GRID_COLUMNS;
		}
	}

	// generate torus (TODO: tri-strips)

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

			curr->nx = cs * ct;
			curr->ny = cs * st;
			curr->nz = ss;

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

	// flush cache so that no stray data remains

	sceKernelDcacheWritebackAll();

	// setup GU

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	sceGuEnable(GU_LIGHT1);
	sceGuEnable(GU_LIGHT2);
	sceGuEnable(GU_LIGHT3);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;
	ScePspFMatrix4 world;

	int val = 0;

	for(;;)
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0x554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup a light
	
		for (i = 0; i < 4; ++i)
		{
			ScePspFVector3 pos = { cosf(i*(GU_PI/2) + val * (GU_PI/180)) * LIGHT_DISTANCE, 0, sinf(i*(GU_PI/2) + val * (GU_PI/180)) * LIGHT_DISTANCE };
			sceGuLight(i,GU_POINTLIGHT,GU_DIFFUSE_AND_SPECULAR,&pos);
			sceGuLightColor(i,GU_DIFFUSE,colors[i]);
			sceGuLightColor(i,GU_SPECULAR,0xffffffff);
			sceGuLightAtt(i,0.0f,1.0f,0.0f);
		}

		sceGuSpecular(12.0f);
		sceGuAmbient(0x00222222);

		// setup matrices for cube

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,1.0f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos = {0,0,-3.5f};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
		}

		// draw grid

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 pos = {0,-1.5f,0};

			sceGumLoadIdentity();
			sceGumTranslate(&pos);
		}

		sceGuColor(0xff7777);
		sceGumDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(grid_indices)/sizeof(unsigned short),grid_indices,grid_vertices);

		// draw torus

		sceGumMatrixMode(GU_MODEL);
		{
			ScePspFVector3 rot = {val * 0.79f * (GU_PI/180.0f), val * 0.98f * (GU_PI/180.0f), val * 1.32f * (GU_PI/180.0f)};

			sceGumLoadIdentity();
			sceGumRotateXYZ(&rot);
		}

		sceGuColor(0xffffff);
		sceGumDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

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
