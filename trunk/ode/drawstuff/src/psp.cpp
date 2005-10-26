#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GLES/egl.h>

#include <pspctrl.h>
#include <pspdebug.h>

#include <drawstuff/drawstuff.h>
#include "internal.h"

static int run=1;			// 1 if simulation running
static int pause=0;			// 1 if in `pause' mode
static int singlestep=0;		// 1 if single step key pressed

static void printMessage (char *msg1, char *msg2, va_list ap)
{
	char buf[200];
	char *p = buf;

	p += sprintf(buf, "%s", msg1);

	vsprintf(p, msg2, ap);

	pspDebugScreenPrintf("%s", buf);
}

extern "C" void dsError (char *msg, ...)
{
  va_list ap;
  va_start (ap,msg);
  printMessage ("Error",msg,ap);
  exit (1);
}


extern "C" void dsDebug (char *msg, ...)
{
  va_list ap;
  va_start (ap,msg);
  printMessage ("INTERNAL ERROR",msg,ap);
  // *((char *)0) = 0;	 ... commit SEGVicide ?
  abort();
}


extern "C" void dsPrint (char *msg, ...)
{
  va_list ap;
  va_start (ap,msg);
  vprintf (msg,ap);
}

static const EGLint attrib_list [] = {
	EGL_RED_SIZE, 1,
	EGL_GREEN_SIZE, 1,
	EGL_BLUE_SIZE, 1,
	EGL_ALPHA_SIZE, 0,
	EGL_DEPTH_SIZE, 1,
	EGL_NONE
};

static EGLDisplay dpy;
static EGLSurface surface;

static void createContext(int width, int height)
{
	EGLConfig config;
	EGLint num_configs;
	EGLContext ctx;

	dpy = eglGetDisplay(0);
	if (dpy == EGL_NO_DISPLAY)
		dsDebug("eglGetDisplay failed: %x\n", eglGetError());
	eglInitialize(dpy, NULL, NULL);

	eglChooseConfig(dpy, attrib_list, &config, 1, &num_configs);

	if (num_configs == 0)
		dsDebug("no EGL configs found\n");

	ctx = eglCreateContext(dpy, config, NULL, NULL);
	if (ctx == EGL_NO_CONTEXT)
		dsDebug("eglCreateContext failed: %x\n", eglGetError());

	surface = eglCreateWindowSurface(dpy, config, 0, NULL);
	if (surface == EGL_NO_SURFACE)
		dsDebug("eglCreateWindowSurface failed\n", eglGetError());

	if (!eglMakeCurrent(dpy, surface, surface, ctx))
		dsError("eglMakeCurrent failed: %x\n", eglGetError());
}

void dsPlatformSimLoop (int window_width, int window_height, dsFunctions *fn,
			int initial_pause)
{
	window_width = 480;
	window_height = 272;

	dsPrint("entering simloop");

	//pspDebugInstallErrorHandler(0);

	createContext(window_width, window_height);

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	dsStartGraphics(window_width, window_height, fn);

	if (fn->start)
		(*fn->start)();

	while(run) {
		struct SceCtrlData pad;
		int dx, dy;
		static unsigned buttons;

		for(;;) {
			struct SceCtrlLatch latch;
			sceCtrlReadLatch(&latch);

			if (latch.uiMake == 0 && latch.uiBreak == 0)
				break;
			if (latch.uiMake & PSP_CTRL_CIRCLE) {
				pause = !pause;
				singlestep = 0;
			}
			if (fn->command) {
				if (latch.uiMake & PSP_CTRL_CROSS)
					(*fn->command)('x');
				if (latch.uiMake & PSP_CTRL_UP)
					(*fn->command)('1');
				if (latch.uiMake & PSP_CTRL_DOWN)
					(*fn->command)('2');
				if (latch.uiMake & PSP_CTRL_LEFT)
					(*fn->command)('[');
				if (latch.uiMake & PSP_CTRL_RIGHT)
					(*fn->command)(']');
			}

			if (latch.uiMake & PSP_CTRL_RTRIGGER)
				buttons |= 4;
			if (latch.uiMake & PSP_CTRL_LTRIGGER)
				buttons |= 1;
			if (latch.uiBreak & PSP_CTRL_RTRIGGER)
				buttons &= ~4;
			if (latch.uiBreak & PSP_CTRL_LTRIGGER)
				buttons &= ~1;
		}


		sceCtrlReadBufferPositive(&pad, 1);

		dx = (pad.Lx - 128) / 10;
		dy = (pad.Ly - 128) / 10;
		if (1 && (abs(dx) > 2 || abs(dy) > 2))
			dsMotion(buttons, dx, dy);

		dsDrawFrame(window_width, window_height, fn, pause && !singlestep);
		singlestep = 0;

		eglSwapBuffers(dpy, surface);
	}

	if (fn->stop)
		fn->stop();
	dsStopGraphics();
}

extern "C" void dsStop()
{
  run = 0;
}


#include <pspkerneltypes.h>
#include <pspkernel.h>
#include <pspuser.h>

#define MODULE_NAME "ODE"

#if !defined(MODULE_NAME)
	#define MODULE_NAME NONAME
#endif


#if !defined(MODULE_VERSION_MAJOR)
	#define MODULE_VERSION_MAJOR 1
#endif


#if !defined(MODULE_VERSION_MINOR)
	#define MODULE_VERSION_MINOR 0
#endif


#if !defined(MODULE_ATTR)
	#define MODULE_ATTR 0
#endif


#define __stringify(s)	__tostring(s)
#define __tostring(s)	#s

PSP_MODULE_INFO(__stringify(MODULE_NAME), MODULE_ATTR, MODULE_VERSION_MAJOR, MODULE_VERSION_MINOR);


static
int exit_callback (int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}


static
int update_thread (SceSize args, void *argp)
{
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, (void *) 0);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}


static void setup_callbacks (void) __attribute__((constructor));
static void setup_callbacks (void)
{
	int id;

	//pspKernelSetKernelPC(); 
	//pspDebugInstallErrorHandler(0);
	pspDebugScreenInit();
	pspDebugScreenPrintf("starting\n");

	if ((id = sceKernelCreateThread("update_thread", update_thread, 0x11, 0xFA0, 0, 0)) >= 0)
		sceKernelStartThread(id, 0, 0);
}



static void back_to_kernel (void) __attribute__((destructor));
static void back_to_kernel (void)
{
	sceKernelExitGame();
}

