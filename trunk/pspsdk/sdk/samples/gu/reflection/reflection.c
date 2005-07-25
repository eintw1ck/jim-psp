/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 * Copyright (c) 2005 McZonk <mczonk@gmx.net>
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspgu.h>

PSP_MODULE_INFO("Reflection Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char logo_start[];

struct Vertex
{
	float u, v;
	unsigned int color;
	float x,y,z;
};

struct Vertex __attribute__((aligned(16))) obj[36] = {
	{0, 0, 0xff6666ff,-1,-1, 1},
	{1, 0, 0xff6666ff, 1,-1, 1},
	{1, 1, 0xff6666ff, 1, 1, 1},
	{0, 0, 0xff6666ff,-1,-1, 1},
	{1, 1, 0xff6666ff, 1, 1, 1},
	{0, 1, 0xff6666ff,-1, 1, 1},
	
	{1, 1, 0xff66ff66, 1, 1, 1},
	{0, 1, 0xff66ff66, 1,-1, 1},
	{0, 0, 0xff66ff66, 1,-1,-1},
	{1, 1, 0xff66ff66, 1, 1, 1},
	{0, 0, 0xff66ff66, 1,-1,-1},
	{1, 0, 0xff66ff66, 1, 1,-1},
	
	{0, 1, 0xffff6666,-1, 1, 1},
	{0, 0, 0xffff6666, 1, 1, 1},
	{1, 0, 0xffff6666, 1, 1,-1},
	{0, 1, 0xffff6666,-1, 1, 1},
	{1, 0, 0xffff6666, 1, 1,-1},
	{1, 1, 0xffff6666,-1, 1,-1},
	
	
	{1, 1, 0xff6666ff, 1,-1,-1},
	{0, 1, 0xff6666ff,-1,-1,-1},
	{0, 0, 0xff6666ff,-1, 1,-1},
	{1, 1, 0xff6666ff, 1,-1,-1},
	{0, 0, 0xff6666ff,-1, 1,-1},
	{1, 0, 0xff6666ff, 1, 1,-1},
	
	{1, 0, 0xff66ff66,-1,-1,-1},
	{1, 1, 0xff66ff66,-1,-1, 1},
	{0, 1, 0xff66ff66,-1, 1, 1},
	{1, 0, 0xff66ff66,-1,-1,-1},
	{0, 1, 0xff66ff66,-1, 1, 1},
	{0, 0, 0xff66ff66,-1, 1,-1},
	
	{0, 1, 0xffff6666,-1,-1,-1},
	{0, 0, 0xffff6666, 1,-1,-1},
	{1, 0, 0xffff6666, 1,-1, 1},
	{0, 1, 0xffff6666,-1,-1,-1},
	{1, 0, 0xffff6666, 1,-1, 1},
	{1, 1, 0xffff6666,-1,-1, 1},
};

struct Vertex __attribute__((aligned(16))) mirror[6] = {
	{0, 0, 0xaa000000, -2.0f,  0, -2.0f},
	{2, 2, 0xaa000000,  2.0f,  0,  2.0f},
	{2, 0, 0xaa000000,  2.0f,  0, -2.0f},
	
	{0, 0, 0xaa000000, -2.0f,  0, -2.0f},
	{0, 2, 0xaa000000, -2.0f,  0,  2.0f},
	{2, 2, 0xaa000000,  2.0f,  0,  2.0f}
};

struct Vertex __attribute__((aligned(16))) border[6] = {
	{0, 0, 0xff0055aa, -2.125f,  -0.01, -2.125f},
	{2, 2, 0xff0055aa,  2.125f,  -0.01,  2.125f},
	{2, 0, 0xff0055aa,  2.125f,  -0.01, -2.125f},
	
	{0, 0, 0xff0055aa, -2.125f,  -0.01, -2.125f},
	{0, 2, 0xff0055aa, -2.125f,  -0.01,  2.125f},
	{2, 2, 0xff0055aa,  2.125f,  -0.01,  2.125f}
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
void matrix_scale(float* matrix, float x, float y, float z);
void matrix_copy(float* a, float* b); // a = b; Copy b to a

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

int main(int argc, char* argv[])
{
	SetupCallbacks();

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
	sceGuFrontFace(GU_CCW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;
	ScePspFMatrix4 world;
	ScePspFMatrix4 mworld; // mirrored world

	int val = 0;

	for(;;)
	{
		float move = sinf(((float)val / 180.0f) * M_PI);
		if(move < 0) {
			move *= -1;
		}
		move += 1;
		
		float rot = ((float)val / 180) * M_PI;
	
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClearStencil(0);
		sceGuClear(GU_COLOR_BUFFER_BIT | GU_STENCIL_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

		// setup matrices for cube

		matrix_identity((float*)&projection);
		matrix_projection((float*)&projection, 60.0f, 16.0/9.0f, 0.5f, 1000.0f);
		sceGuSetMatrix(GU_PROJECTION,&projection);

		matrix_identity((float*)&view);
		matrix_translate((float*)&view, 0, -0.5f, -5.5f);
		matrix_rotate((float*)&view, (30.0f * M_PI) / 180.0f, (val * 0.2 * M_PI) / 180.0f, 0.0f);
		sceGuSetMatrix(GU_VIEW,&view);

		matrix_identity((float*)&world);
		
		matrix_copy((float*)&mworld, (float*)&world);
		matrix_scale((float*)&mworld, 1.0f, -1.0f, 1.0f); // Mirror y axis
		
		// draw mirrored view
		sceGuFrontFace(GU_CCW);
		sceGuEnable(GU_STENCIL_TEST); // Stencil test
		sceGuDepthMask(GU_TRUE);
		sceGuStencilFunc(GU_ALWAYS, 1, 1); // always set 1 bit in 1 bit mask
		sceGuStencilOp(GU_KEEP, GU_KEEP, GU_REPLACE); // keep value on failed test (fail and zfail) and replace on pass
		sceGuSetMatrix(GU_MODEL, &world);
		sceGuDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, mirror);
		sceGuDepthMask(GU_FALSE);
		
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuFrontFace(GU_CW);
		sceGuStencilFunc(GU_EQUAL, 1, 1); // allow drawing where stencil is 1
		sceGuStencilOp(GU_KEEP, GU_KEEP, GU_KEEP); // keep the stencil buffer unchanged
		matrix_translate((float*)&mworld, 0, move, 0);
		matrix_rotate((float*)&mworld, 0, rot * -0.83, 0);
		sceGuSetMatrix(GU_MODEL, &mworld);
		sceGuDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 36, 0, obj);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuDisable(GU_STENCIL_TEST);
		
		// draw normal view
		sceGuEnable(GU_TEXTURE_2D);
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		sceGuFrontFace(GU_CCW);
		sceGuEnable(GU_BLEND);
		sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
		sceGuSetMatrix(GU_MODEL, &world);
		sceGuDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, mirror);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		
		sceGuSetMatrix(GU_MODEL, &world);
		sceGuDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, border);
		
		sceGuEnable(GU_TEXTURE_2D);
		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,logo_start);
		sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuTexScale(1.0f,1.0f);
		sceGuTexOffset(0.0f,0.0f);
		matrix_translate((float*)&world, 0, move, 0);
		matrix_rotate((float*)&world, 0, rot * -0.83, 0);
		sceGuSetMatrix(GU_MODEL, &world);
		sceGuDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 36, 0, obj);
		sceGuDisable(GU_TEXTURE_2D);

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

void matrix_scale(float* matrix, float x, float y, float z) {
	float temp[16];

	matrix_identity(temp);
	temp[(0 << 2) + 0] = x;
	temp[(1 << 2) + 1] = y;
	temp[(2 << 2) + 2] = z;
	
	matrix_multiply(matrix, matrix, temp);
}

void matrix_copy(float* a, float* b) {
	memcpy(a, b, sizeof(float) * 16);
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
