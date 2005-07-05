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

PSP_MODULE_INFO("Sprite Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char ball_start[];

struct InputVertex
{
	float x,y,z;
};

struct Vertex
{
	float u, v;
	unsigned int color;
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

void create_torus_billboards(struct Vertex* vertices, float* world);

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

#define NUM_SLICES 128
#define NUM_ROWS 128
#define RING_SIZE 2.0f
#define RING_RADIUS 1.0f
#define SPRITE_SIZE 0.025f

unsigned int colors[8] = 
{
	0xffff0000,
	0xffff00ff,
	0xff0000ff,
	0xff00ffff,
	0xff00ff00,
	0xffffff00,
	0xffffffff,
	0xff101010
};

struct InputVertex torus_vertices[NUM_SLICES * NUM_ROWS];

int main(int argc, char* argv[])
{
	unsigned int i,j;

	SetupCallbacks();

	// initialize torus

	for (i = 0; i < NUM_SLICES; ++i)
	{
		for (j = 0; j < NUM_ROWS; ++j)
		{
			float s = i + 0.5f, t = j;
			float x,y,z;

			x = (RING_SIZE + RING_RADIUS * cosf(s * ((M_PI*2)/NUM_SLICES))) * cosf(t * ((M_PI*2)/NUM_ROWS));
			y = (RING_SIZE + RING_RADIUS * cosf(s * ((M_PI*2)/NUM_SLICES))) * sinf(t * ((M_PI*2)/NUM_ROWS));
			z = RING_RADIUS * sinf(s * ((M_PI*2)/NUM_SLICES));

			torus_vertices[j + i * NUM_ROWS].x = x;
			torus_vertices[j + i * NUM_ROWS].y = y;
			torus_vertices[j + i * NUM_ROWS].z = z;
		}
	}

	// setup GU

	sceGuInit();
	sceGuStart(0,list);

	sceGuDrawBuffer(GE_PSM_8888,(void*)0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)0x88000,BUF_WIDTH);
	sceGuDepthBuffer((void*)0x110000,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);

	sceGuDepthRange(0xc350,0x2710);

	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_STATE_SCISSOR);

	sceGuAlphaFunc(GE_TEST_GREATER,0,0xff);
	sceGuEnable(GU_STATE_ATE);

	sceGuDepthFunc(GE_TEST_GEQUAL);
	sceGuEnable(GU_STATE_ZTE);

	sceGuFrontFace(GE_FACE_CW);

	sceGuShadeModel(GE_SHADE_GOURAUD);

	sceGuEnable(GU_STATE_CULL);
	sceGuEnable(GU_STATE_TEXTURE);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_DISPLAY_ON);

	// run sample

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;
	ScePspFMatrix4 world;

	float val = 0;

	for(;;)
	{
		struct Vertex* vertices;

		sceGuStart(0,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GE_CLEAR_COLOR|GE_CLEAR_DEPTH);

		matrix_identity((float*)&projection);
		matrix_projection((float*)&projection,75.0f,16.0/9.0f,0.01f,1000.0f);
		sceGuSetMatrix(GU_MATRIX_PROJECTION,&projection);

		matrix_identity((float*)&view);
		sceGuSetMatrix(GU_MATRIX_VIEW,&view);

		matrix_identity((float*)&world);
		matrix_translate((float*)&world,0,0,-5.0f);
		matrix_rotate((float*)&world,val * 0.3f * (M_PI/180.0f), val * 0.7f * (M_PI/180.0f), val * 1.3f * (M_PI/180.0f));
		sceGuSetMatrix(2,&world);

		// setup texture

		sceGuTexMode(GE_TPSM_5551,0,0,0);
		sceGuTexImage(0,32,32,32,ball_start); // width, height, buffer width, tbp
		sceGuTexFunc(GE_TFX_MODULATE,GE_TCC_RGBA); // NOTE: this enables reads of the alpha-component from the texture, otherwise blend/test won't work
		sceGuTexFilter(GE_FILTER_POINT,GE_FILTER_POINT);
		sceGuTexWrap(GE_WRAP_CLAMP,GE_WRAP_CLAMP);
		sceGuTexScale(1,1);
		sceGuTexOffset(0,0);
		sceGuAmbientColor(0xffffffff);

		// render torus

		vertices = sceGuGetMemory(NUM_SLICES * NUM_ROWS * 2 * sizeof(struct Vertex));
		create_torus_billboards(vertices,(float*)&world);

		sceGuDrawArray(GU_PRIM_SPRITES,GE_SETREG_VTYPE(GE_TT_32BITF,GE_CT_8888,0,GE_MT_32BITF,0,0,0,0,0),NUM_SLICES * NUM_ROWS * 2,0,vertices);

		// wait for next frame

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		val += 0.6f;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}

/* this function generates the billboards rendered by sceGuDrawArray() */
void create_torus_billboards(struct Vertex* vertices, float* world)
{
	unsigned int i,j;
	float sx, sy, sz;

	// calculate billboard world offsets

	sx = SPRITE_SIZE * world[(0 << 2)+0] + SPRITE_SIZE * world[(0 << 2)+1];
	sy = SPRITE_SIZE * world[(1 << 2)+0] + SPRITE_SIZE * world[(1 << 2)+1];
	sz = SPRITE_SIZE * world[(2 << 2)+0] + SPRITE_SIZE * world[(2 << 2)+1];

	for (i = 0; i < NUM_SLICES; ++i)
	{
		struct Vertex* row = &vertices[i * NUM_ROWS * 2];
		struct InputVertex* inrow = &torus_vertices[i * NUM_ROWS];

		for (j = 0; j < NUM_ROWS; ++j)
		{
			struct Vertex* curr = &row[j << 1];
			struct InputVertex* incurr = &inrow[j];
			float x, y, z;

			x = incurr->x;
			y = incurr->y;
			z = incurr->z;

			curr[0].u = 0;
			curr[0].v = 0;
			curr[0].color = colors[(i+j)&7];
			curr[0].x = x - sx;
			curr[0].y = y - sy;
			curr[0].z = z - sz;

			curr[1].u = 1;
			curr[1].v = 1;
			curr[1].color = colors[(i+j)&7];
			curr[1].x = x + sx;
			curr[1].y = y + sy;
			curr[1].z = z + sz;
		}
	}
}

/* Exit callback */
int exit_callback(void)
{
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
void CallbackThread(void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
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
