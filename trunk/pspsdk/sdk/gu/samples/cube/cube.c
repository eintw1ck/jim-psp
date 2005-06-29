#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <gu.h>

PSP_MODULE_INFO("SceGu Cube", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	float x,y,z;
};

struct Vertex __attribute__((aligned(16))) vertices[8*3] =
{
	{-1,-1,-1},
	{ 1,-1,-1},
	{ 1,-1, 1},
	{-1,-1, 1},
	{-1, 1,-1},
	{ 1, 1,-1},
	{ 1, 1, 1},
	{-1, 1, 1}
};

unsigned short __attribute__((aligned(16))) indices[12*3] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 5,
	0, 5, 1,
	1, 5, 6,
	1, 6, 2,
	3, 2, 6,
	3, 6, 7,
	0, 3, 7,
	0, 7, 4,
	4, 7, 6,
	4, 6, 5,
};

int done = 0;
/* Exit callback */
int exit_callback(void)
{
	done = 1;
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

	float cotangent = cosf(fovy / 2.0f) * sinf(fovy / 2.0f);

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

int main(int argc, char* argv[])
{

	pspDebugScreenInit();
	printf("Bootpath: %s\n", g_elf_name);
	SetupCallbacks();

	sceGuInit();

	printf("INIT OK\n");

	// setup
	sceGuStart(0,list);
	sceGuDrawBuffer(3,(void*)0,512);
	sceGuDispBuffer(480,272,(void*)0x88000,512);
	sceGuDepthBuffer((void*)0x110000,512);
	sceGuOffset(2048 - (480/2),2048 - (272/2));
	sceGuViewport(2048,2048,480,272);
	sceGuDepthRange(0xc350,10000);
	sceGuScissor(0,0,480,272);
	sceGuEnable(GU_STATE_SCISSOR);
	sceGuBlendFunc(0,2,3,0,0);
	sceGuEnable(GU_STATE_BLEND);
	sceGuDepthFunc(7);
	sceGuDisable(GU_STATE_DEPTH_TEST);
	sceGuFrontFace(0);
	sceGuShadeModel(1);
//	sceGuEnable(GU_STATE_UNKNOWN8);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	int i = 0;

	float projection[16];
	float view[16];
	float world[16];

	float xc = 24.0f;
	float yc = 13.6f;
	float sz = 20.0f;

	int val = 0;

	while (!done)
	{
		unsigned int x,y;

		sceGuStart(0,list);

		sceGuClearColor(val);
		sceGuClear(1);

		val++;

		float cs1 = cosf((val % 360) * (M_PI/180));
		float sn1 = sinf((val % 360) * (M_PI/180));

		float cs2 = cosf(((val+120) % 360) * (M_PI/180));
		float sn2 = sinf(((val+120) % 360) * (M_PI/180));

		float cs3 = cosf(((val+240) % 360) * (M_PI/180));
		float sn3 = sinf(((val+240) % 360) * (M_PI/180));

		for (y = 0; y < 20; ++y)
		{
			for (x = 0; x < 20; ++x)
			{
				short* vertices = sceGuGetMemory((4*3)*sizeof(short));

				vertices[0] = (short)(0x0f00) + ((int)(((x+y) / 40.0f) * 15.0f));
				vertices[1] = (short)(xc*x+cs1 * sz);
				vertices[2] = (short)(yc*y+sn1 * sz);
				vertices[3] = (short)(0);

				vertices[4] = (short)(0x00f0) + ((int)((x / 20.0f) * 15.0f)) << 8;
				vertices[5] = (short)(xc*x+cs2 * sz);
				vertices[6] = (short)(yc*y+sn2 * sz);
				vertices[7] = (short)(0);

				vertices[8] = (short)(0x000f) + ((int)((x / 20.0f) * 15.0f)) << 4;
				vertices[9] = (short)(xc*x+cs3 * sz);
				vertices[10] = (short)(yc*y+sn3 * sz);
				vertices[11] = (short)(0);
		/*
				matrix_identity(projection);
				matrix_projection(projection,480,272,3.0f,1.0f,0.01f,1000.0f);
				sceGuSetMatrix(0,projection);

				matrix_identity(view);
				sceGuSetMatrix(1,view);

				matrix_identity(world);
				matrix_translate(world,0,0,10.0f);
				sceGuSetMatrix(2,world);
		*/

				sceGuDrawArray(3,0x800118,3,0,vertices);
			}
		}

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
