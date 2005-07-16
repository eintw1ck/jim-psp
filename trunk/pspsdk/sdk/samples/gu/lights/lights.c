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

void matrix_identity(float* matrix);
void matrix_rotate(float* matrix, float x, float y, float z);
void matrix_projection(float* matrix, float fovy, float aspect, float near, float far);
void matrix_multiply(float* result, float* a, float* b);
void matrix_setrotatex(float* matrix, float angle);
void matrix_setrotatey(float* matrix, float angle);
void matrix_setrotatez(float* matrix, float angle);
void matrix_rotate(float* matrix, float x, float y, float z);
void matrix_translate(float* matrix, float x, float y, float z);
void matrix_fastinverse(float* dest, float* source);

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

			cs = cosf(s * (2*M_PI)/TORUS_SLICES);
			ct = cosf(t * (2*M_PI)/TORUS_ROWS);
			ss = sinf(s * (2*M_PI)/TORUS_SLICES);
			st = sinf(t * (2*M_PI)/TORUS_ROWS);

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
			ScePspFVector3 pos = { cosf(i*(M_PI/2) + val * (M_PI/180)) * LIGHT_DISTANCE, 0, sinf(i*(M_PI/2) + val * (M_PI/180)) * LIGHT_DISTANCE - 5.0f };
			sceGuLight(i,GU_POINTLIGHT,GU_DIFFUSE_AND_SPECULAR,&pos);
			sceGuLightColor(i,GU_DIFFUSE,colors[i]);
			sceGuLightColor(i,GU_SPECULAR,0xffffffff);
			sceGuLightAtt(i,0.0f,1.0f,0.0f);
		}

		sceGuSpecular(12.0f);
		sceGuAmbient(0x00222222);

		// setup matrices for cube

		matrix_identity((float*)&projection);
		matrix_projection((float*)&projection,75.0f,16.0/9.0f,1.0f,1000.0f);
		sceGuSetMatrix(GU_PROJECTION,&projection);

		matrix_identity((float*)&view);
		sceGuSetMatrix(GU_VIEW,&view);

		matrix_identity((float*)&world);
		matrix_translate((float*)&world,0,-1.5,-7.5f);
		sceGuSetMatrix(GU_MODEL,&world);

		// draw grid

		sceGuColor(0xff7777);
		sceGuDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(grid_indices)/sizeof(unsigned short),grid_indices,grid_vertices);

		// draw torus

		matrix_identity((float*)&world);
		matrix_translate((float*)&world,0,0,-5.0f);
		matrix_rotate((float*)&world,val * 0.79f * (M_PI/180.0f), val * 0.98f * (M_PI/180.0f), val * 1.32f * (M_PI/180.0f));
		sceGuSetMatrix(GU_MODEL,&world);

		sceGuColor(0xffffff);
		sceGuDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

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
int exit_callback(void)
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


/* small matrix library */

void matrix_identity(float* matrix)
{
	matrix[(0<<2)+0] = 1.0f;
	matrix[(0<<2)+1] = 0.0f;
	matrix[(0<<2)+2] = 0.0f;
	matrix[(0<<2)+3] = 0.0f;

	matrix[(1<<2)+0] = 0.0f;
	matrix[(1<<2)+1] = 1.0f;
	matrix[(1<<2)+2] = 0.0f;
	matrix[(1<<2)+3] = 0.0f;

	matrix[(2<<2)+0] = 0.0f;
	matrix[(2<<2)+1] = 0.0f;
	matrix[(2<<2)+2] = 1.0f;
	matrix[(2<<2)+3] = 0.0f;

	matrix[(3<<2)+0] = 0.0f;
	matrix[(3<<2)+1] = 0.0f;
	matrix[(3<<2)+2] = 0.0f;
	matrix[(3<<2)+3] = 1.0f;
}

void matrix_projection(float* matrix, float fovy, float aspect, float near, float far)
{
	matrix_identity(matrix);

	float angle = (fovy / 2.0f) * (M_PI/180.0f);
	float cotangent = cosf(angle) / sinf(angle);

	matrix[(0<<2)+0] = cotangent / aspect;
	matrix[(1<<2)+1] = cotangent;
	matrix[(2<<2)+2] = (far + near) / (near - far);
	matrix[(3<<2)+2] = 2.0f * (far * near) / (near - far);
	matrix[(2<<2)+3] = -1;
	matrix[(3<<2)+3] = 0.0f;
}

void matrix_multiply(float* result, float* a, float* b)
{
	unsigned int i,j,k;
	float temp[16];

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			float t = 0.0f;
			for (k = 0; k < 4; ++k)
				t += a[(k << 2)+j] * b[(i << 2)+k];
			temp[(i << 2)+j] = t;
		}
	}

	memcpy(result,temp,sizeof(float)*16);
}

void matrix_translate(float* matrix, float x, float y, float z)
{
	float temp[16];

	matrix_identity(temp);
	temp[(3 << 2)+0] = x;
	temp[(3 << 2)+1] = y;
	temp[(3 << 2)+2] = z;

	matrix_multiply(matrix,matrix,temp);
}

void matrix_setrotatex(float* matrix, float angle)
{
	float cs = cosf(angle);
	float sn = sinf(angle);

	matrix_identity(matrix);
	matrix[(1<<2)+1] = cs;
	matrix[(1<<2)+2] = sn;
	matrix[(2<<2)+1] = -sn;
	matrix[(2<<2)+2] = cs;
}

void matrix_setrotatey(float* matrix, float angle)
{
	float cs = cosf(angle);
	float sn = sinf(angle);

	matrix_identity(matrix);
	matrix[(0<<2)+0] = cs;
	matrix[(0<<2)+2] = -sn;
	matrix[(2<<2)+0] = sn;
	matrix[(2<<2)+2] = cs;
}

void matrix_setrotatez(float* matrix, float angle)
{
	float cs = cosf(angle);
	float sn = sinf(angle);

	matrix_identity(matrix);
	matrix[(0<<2)+0] = cs;
	matrix[(0<<2)+1] = sn;
	matrix[(1<<2)+0] = -sn;
	matrix[(1<<2)+1] = cs;
}

void matrix_rotate(float* matrix, float x, float y, float z)
{
	float temp[16];

	matrix_setrotatex(temp,x);
	matrix_multiply(matrix,matrix,temp);

	matrix_setrotatey(temp,y);
	matrix_multiply(matrix,matrix,temp);

	matrix_setrotatez(temp,z);
	matrix_multiply(matrix,matrix,temp);
}

#define SIN_ITERATOR 20

float sinf(float v)
{
	float res,w;
	int t;
	float fac;
	int i=(int)((v)/(2.0f*M_PI));
	v-=i*2.0f*M_PI;

	fac=1.0f;
	res=0.0f;
	w=v;
	for(t=1;t<SIN_ITERATOR;)
	{
		res+=fac*w;
		w*=v*v;
		t++;
		fac/=t;
		t++;
		fac/=t;

		res-=fac*w;
		w*=v*v;
		t++;
		fac/=t;
		t++;
		fac/=t;
	}
	return res;
}

float cosf(float v)
{
	float res,w;
	int t;
	float fac;
	int i=(int)((v)/(2.0f*M_PI));
	v-=i*2.0f*M_PI;

	fac=1.0f;
	res=0.0f;
	w=1.0f;
	for(t=0;t<SIN_ITERATOR;)
	{
		res+=fac*w;
		w*=v*v;
		t++;
		fac/=t;
		t++;
		fac/=t;

		res-=fac*w;
		w*=v*v;
		t++;
		fac/=t;
		t++;
		fac/=t;
	}
	return res;
}
