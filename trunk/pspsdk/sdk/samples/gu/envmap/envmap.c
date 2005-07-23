/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * envmap.c - Sample to desmonstrate environment mapping functionality
 *
 * Copyright (c) 2005 Jesper Svennevid
 * Copyright (c) 2005 Renaldas Zioma <rej@scene.lt>
 *
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pspctrl.h>

#include <pspgu.h>

PSP_MODULE_INFO("EnvMap Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];
extern unsigned char env0_start[];

typedef struct Vertex
{
	float nx,ny,nz;
 	float x,y,z;
} Vertex;

int SetupCallbacks();

void genTorus( unsigned slices, unsigned rows, float radius, float thickness,
	Vertex* dstVertices, unsigned short* dstIndices );

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

#define TORUS_SLICES 48 // numc
#define TORUS_ROWS 48 // numt
#define TORUS_RADIUS 1.0f
#define TORUS_THICKNESS 0.5f

#define LIGHT_DISTANCE 3.0f

Vertex __attribute__((aligned(16))) torus_vertices[TORUS_SLICES*TORUS_ROWS];
unsigned short __attribute__((aligned(16))) torus_indices[TORUS_SLICES*TORUS_ROWS*6];

int main(int argc, char* argv[])
{
	pspDebugScreenInit();
	SetupCallbacks();

	// generate geometry
	genTorus( TORUS_ROWS, TORUS_SLICES, TORUS_RADIUS, TORUS_THICKNESS, torus_vertices, torus_indices );		

	// flush cache so that no stray data remains

	sceKernelDcacheWritebackAll();

    //setup Pad

    SceCtrlData pad;
    u32 oldButtons = 0;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(0);

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
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	sceGuFinish();
	sceGuSync(0,0);
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// run sample

	ScePspFMatrix4 projection;
	ScePspFMatrix4 view;
	ScePspFMatrix4 world;

	int valTorus = 0;
	int valEnvMap = 0;
	int rotateTorus = 1;
	int rotateEnvMap = 1;

	for(;;)
	{
		sceGuStart(GU_DIRECT,list);

		// clear screen

		sceGuClearColor(0x554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		// setup a light

		ScePspFVector3 dir = { 0, 0, 1 };
		sceGuLight(0,GU_DIRECTIONAL,GU_DIFFUSE,&dir);
		sceGuLightColor(0,GU_DIFFUSE,0x00ff4040 );
		sceGuLightAtt(0,1.0f,0.0f,0.0f);
		sceGuAmbient(0x00202020);

		// setup proj/view matrices

		matrix_identity((float*)&projection);
		matrix_projection((float*)&projection,75.0f,16.0/9.0f,1.0f,1000.0f);
		sceGuSetMatrix(GU_PROJECTION,&projection);

		matrix_identity((float*)&view);
		sceGuSetMatrix(GU_VIEW,&view);

		// setup envmap texture

		sceGuTexMode(GU_PSM_4444,0,0,0);
		sceGuTexImage(0,64,64,64,env0_start);
		sceGuTexFunc(GU_TFX_MODULATE,GU_TCC_RGB);
		sceGuTexFilter(GU_LINEAR,GU_LINEAR);
		sceGuAmbientColor(0xffffffff);
	
		// setup envmap matrix (2x3)
		// 2d rotation/translation matrix
		// [ cosa  -sina ]
		// [ sina   cosa ]
		// [  tx     ty  ]

		// envmap matrix is transposed
		// since it is passed to GU as columns
		float angle = -2.0f * valEnvMap * (M_PI/180.0f);
		float cs = cosf(angle);
		float sn = sinf(angle);
		ScePspFVector3 envmapMatrixColumns[2] = {
			{ cs,  sn, 0.0f },
			{ -sn, cs, 0.0f }
		};
		sceGuLight( 2, GU_DIRECTIONAL, GU_DIFFUSE, &envmapMatrixColumns[0] );
		sceGuLight( 3, GU_DIRECTIONAL, GU_DIFFUSE, &envmapMatrixColumns[1] );

		// setup envmap texture coord generation
		sceGuTexMapMode(
			GU_ENVIRONMENT_MAP,	// envmap mode on
			2,	// use 2nd light position as an envmap matrix 1st column
			3	// use 3rd light position as an envmap matrix 2nd column
			);

		// draw torus

		matrix_identity((float*)&world);
		matrix_translate((float*)&world,0,0,-2.5f);
		matrix_rotate((float*)&world,valTorus * 0.79f * (M_PI/180.0f), valTorus * 0.98f * (M_PI/180.0f), valTorus * 1.32f * (M_PI/180.0f));
		sceGuSetMatrix(GU_MODEL,&world);

		sceGuColor(0xffffff);
		sceGuDrawArray(GU_TRIANGLES,GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D,sizeof(torus_indices)/sizeof(unsigned short),torus_indices,torus_vertices);

		pspDebugScreenSetXY(0,0);
		printf( "Press X to toggle environment map rotation" );
		pspDebugScreenSetXY(0,1);
		printf( "Press O to toggle torus rotation" );

		sceCtrlReadBufferPositive(&pad, 1);
		if(oldButtons != pad.Buttons)
		{
			if(pad.Buttons & PSP_CTRL_CROSS)
				rotateTorus ^= 0x01;
			if(pad.Buttons & PSP_CTRL_CIRCLE)
				rotateEnvMap ^= 0x01;
		}
		oldButtons = pad.Buttons;

		sceGuFinish();
		sceGuSync(0,0);

//		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

		if(rotateTorus) valTorus++;
		if(rotateEnvMap) valEnvMap++;
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

/* usefull geometry functions */
void genTorus( unsigned slices, unsigned rows, float radius, float thickness, Vertex* dstVertices, unsigned short* dstIndices )
{
	unsigned int i,j;

	// generate torus (TODO: tri-strips)
	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			struct Vertex* curr = &dstVertices[i+j*rows];
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;

			cs = cosf(s * (2*M_PI)/slices);
			ct = cosf(t * (2*M_PI)/rows);
			ss = sinf(s * (2*M_PI)/slices);
			st = sinf(t * (2*M_PI)/rows);

			curr->nx = cs * ct;
			curr->ny = cs * st;
			curr->nz = ss;

			curr->x = (radius + thickness * cs) * ct;
			curr->y = (radius + thickness * cs) * st;
			curr->z = thickness * ss;
		}
	}

	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			unsigned short* curr = &dstIndices[(i+(j*rows))*6];
			unsigned int i1 = (i+1)%rows, j1 = (j+1)%slices;

			*curr++ = i + j * rows;
			*curr++ = i1 + j * rows;
			*curr++ = i + j1 * rows;

			*curr++ = i1 + j * rows;
			*curr++ = i1 + j1 * rows;
			*curr++ = i + j1 * rows;
		}
	}
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
