#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspgu.h>

PSP_MODULE_INFO("SceGu Cube", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define printf	pspDebugScreenPrintf

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
	unsigned int color;
	float x,y,z;
};

struct Vertex __attribute__((aligned(16))) vertices[12*3] =
{
	{ 0xff0000ff,-1,-1,-1}, // 0
	{ 0xff0000ff, 1,-1,-1}, // 1
	{ 0xff0000ff, 1,-1, 1}, // 2

	{ 0xff0000ff,-1,-1,-1}, // 0
	{ 0xff0000ff, 1,-1, 1}, // 2
	{ 0xff0000ff,-1,-1, 1}, // 3

	{ 0xffff0000,-1,-1,-1}, // 0
	{ 0xffff0000,-1, 1,-1}, // 4
	{ 0xffff0000, 1, 1,-1}, // 5

	{ 0xffff0000,-1,-1,-1}, // 0
	{ 0xffff0000, 1, 1,-1}, // 5
	{ 0xffff0000, 1,-1,-1}, // 1

	{ 0xff00ff00, 1,-1,-1}, // 1
	{ 0xff00ff00, 1, 1,-1}, // 5
	{ 0xff00ff00, 1, 1, 1}, // 6

	{ 0xff00ff00, 1,-1, 1}, // 2
	{ 0xff00ff00, 1,-1,-1}, // 1
	{ 0xff00ff00, 1, 1, 1}, // 6

	{ 0xffff0000,-1,-1, 1}, // 3
	{ 0xffff0000, 1,-1, 1}, // 2
	{ 0xffff0000, 1, 1, 1}, // 6

	{ 0xffff0000,-1,-1, 1}, // 3
	{ 0xffff0000, 1, 1, 1}, // 6
	{ 0xffff0000,-1, 1, 1}, // 7

	{ 0xff00ff00,-1,-1,-1}, // 0
	{ 0xff00ff00,-1,-1, 1}, // 3
	{ 0xff00ff00,-1, 1, 1}, // 7

	{ 0xff00ff00,-1,-1,-1}, // 0
	{ 0xff00ff00,-1, 1, 1}, // 7
	{ 0xff00ff00,-1, 1,-1}, // 4

	{ 0xff0000ff,-1, 1,-1}, // 4
	{ 0xff0000ff,-1, 1, 1}, // 7
	{ 0xff0000ff, 1, 1, 1}, // 6

	{ 0xff0000ff,-1, 1,-1}, // 4
	{ 0xff0000ff, 1, 1, 1}, // 6
	{ 0xff0000ff, 1, 1,-1}  // 5
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
	sceGuEnable(GU_STATE_DEPTH_TEST);
	sceGuFrontFace(0);
	sceGuShadeModel(1);
	sceGuEnable(GU_STATE_CULLING);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(1);

	float projection[16];
	float view[16];
	float world[16];

	int val = 0;

	while (!done)
	{
		sceGuStart(0,list);

		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(1 + 4);

		val++;

		matrix_identity(projection);
		matrix_projection(projection,75.0f,16.0/9.0f,0.01f,1000.0f);
		sceGuSetMatrix(0,projection);

		matrix_identity(view);
		sceGuSetMatrix(1,view);

		matrix_identity(world);
		matrix_translate(world,0,0,-3.0f);
		matrix_rotate(world,val * 0.79f * (M_PI/180.0f), val * 0.98f * (M_PI/180.0f), val * 1.32f * (M_PI/180.0f));
		sceGuSetMatrix(2,world);

		sceGuDrawArray(GU_PRIM_TRIANGLES,GE_SETREG_VTYPE(0,GE_CT_8888,0,GE_MT_32BITF,0,0,0,0,0),12*3,0,vertices);

		sceGuFinish();
		sceGuSync(0,0);

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
