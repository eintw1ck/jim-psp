/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Sample to demonstrate how to use the message dialog utility
 *
 * Copyright (c) 2005 Marcus Comstedt <marcus@mc.pp.se>
 *
 * $Id$
 */
#include <pspkernel.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pspmoduleinfo.h>
#include <psputility.h>
#include <pspgu.h>
#include <pspgum.h>

/* Define the module info section */
PSP_MODULE_INFO("MsgDialog Sample", 0, 1, 0);


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
    if (thid >= 0)
	sceKernelStartThread(thid, 0, 0);
    return thid;
}


/* Graphics stuff, based on cube sample */

static unsigned int __attribute__((aligned(16))) list[262144];

struct Vertex
{
    float u, v;
    unsigned int color;
    float x,y,z;
};

struct Vertex __attribute__((aligned(16))) vertices[12*3] =
{
    {0, 0, 0xff7f0000,-1,-1, 1}, // 0
    {1, 0, 0xff7f0000,-1, 1, 1}, // 4
    {1, 1, 0xff7f0000, 1, 1, 1}, // 5
    
    {0, 0, 0xff7f0000,-1,-1, 1}, // 0
    {1, 1, 0xff7f0000, 1, 1, 1}, // 5
    {0, 1, 0xff7f0000, 1,-1, 1}, // 1
    
    {0, 0, 0xff7f0000,-1,-1,-1}, // 3
    {1, 0, 0xff7f0000, 1,-1,-1}, // 2
    {1, 1, 0xff7f0000, 1, 1,-1}, // 6
    
    {0, 0, 0xff7f0000,-1,-1,-1}, // 3
    {1, 1, 0xff7f0000, 1, 1,-1}, // 6
    {0, 1, 0xff7f0000,-1, 1,-1}, // 7
    
    {0, 0, 0xff007f00, 1,-1,-1}, // 0
    {1, 0, 0xff007f00, 1,-1, 1}, // 3
    {1, 1, 0xff007f00, 1, 1, 1}, // 7
    
    {0, 0, 0xff007f00, 1,-1,-1}, // 0
    {1, 1, 0xff007f00, 1, 1, 1}, // 7
    {0, 1, 0xff007f00, 1, 1,-1}, // 4
    
    {0, 0, 0xff007f00,-1,-1,-1}, // 0
    {1, 0, 0xff007f00,-1, 1,-1}, // 3
    {1, 1, 0xff007f00,-1, 1, 1}, // 7
    
    {0, 0, 0xff007f00,-1,-1,-1}, // 0
    {1, 1, 0xff007f00,-1, 1, 1}, // 7
    {0, 1, 0xff007f00,-1,-1, 1}, // 4
    
    {0, 0, 0xff00007f,-1, 1,-1}, // 0
    {1, 0, 0xff00007f, 1, 1,-1}, // 1
    {1, 1, 0xff00007f, 1, 1, 1}, // 2
    
    {0, 0, 0xff00007f,-1, 1,-1}, // 0
    {1, 1, 0xff00007f, 1, 1, 1}, // 2
    {0, 1, 0xff00007f,-1, 1, 1}, // 3
    
    {0, 0, 0xff00007f,-1,-1,-1}, // 4
    {1, 0, 0xff00007f,-1,-1, 1}, // 7
    {1, 1, 0xff00007f, 1,-1, 1}, // 6
    
    {0, 0, 0xff00007f,-1,-1,-1}, // 4
    {1, 1, 0xff00007f, 1,-1, 1}, // 6
    {0, 1, 0xff00007f, 1,-1,-1}, // 5
};

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

static void SetupGu()
{
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
    sceGuFinish();
    sceGuSync(0,0);
    
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

static void DrawStuff(void)
{
    static int val = 0;

    sceGuStart(GU_DIRECT,list);

    // clear screen
    
    sceGuClearColor(0xff554433);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
    
    // setup matrices for cube
    
    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);
    
    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();
    
    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
    {
	ScePspFVector3 pos = { 0, 0, -2.5f };
	ScePspFVector3 rot = { val * 0.79f * (M_PI/180.0f), val * 0.98f * (M_PI/180.0f), val * 1.32f * (M_PI/180.0f) };
	sceGumRotateXYZ(&rot);
	sceGumTranslate(&pos);
    }
    
    // draw cube
    
    sceGuAmbientColor(0xffffffff);
    sceGumDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,12*3,0,vertices);
    
    sceGuFinish();
    sceGuSync(0,0);

    val ++;
}


/* Utility dialog functions */

static void ConfigureDialog(SceUtilityMsgDialogParams *dialog, size_t dialog_size)
{
    memset(dialog, 0, dialog_size);

    dialog->size = dialog_size;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,
				&dialog->language); // Prompt language
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,
				&dialog->buttonSwap); // X/O button swap

    dialog->unknown[0] = 0x11;	// ???
    dialog->unknown[1] = 0x13;
    dialog->unknown[2] = 0x12;
    dialog->unknown[3] = 0x10;
}

static void ShowErrorDialog(const unsigned int error)
{
    SceUtilityMsgDialogParams dialog;

    ConfigureDialog(&dialog, sizeof(dialog));
    dialog.unknown[10] = 0;
    dialog.unknown[11] = error;

    sceUtilityMsgDialogInitStart(&dialog);

    for(;;) {

	DrawStuff();
	
	switch(sceUtilityMsgDialogGetStatus()) {
	    
	case 2:
	    sceUtilityMsgDialogUpdate(2);
	    break;
	    
	case 3:
	    sceUtilityMsgDialogShutdownStart();
	    break;
	    
	case 0:
	    return;
	    
	}

	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
    }
}

static void ShowMessageDialog(const char *message)
{
    SceUtilityMsgDialogParams dialog;

    ConfigureDialog(&dialog, sizeof(dialog));
    dialog.unknown[10] = 1;
    strcpy(dialog.message, message);

    sceUtilityMsgDialogInitStart(&dialog);

    for(;;) {

	DrawStuff();
	
	switch(sceUtilityMsgDialogGetStatus()) {
	    
	case 2:
	    sceUtilityMsgDialogUpdate(2);
	    break;
	    
	case 3:
	    sceUtilityMsgDialogShutdownStart();
	    break;
	    
	case 0:
	    return;
	    
	}

	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
    }
}

/* main routine */
int main(int argc, char *argv[])
{
    SetupCallbacks();
    SetupGu();

    ShowMessageDialog("This is a utility message dialog.\n"
		      "After you acknowledge it, this program will\n"
		      "show an error message dialog.");

    ShowErrorDialog(0x80020001);

    ShowMessageDialog("This is a utility message dialog.\n"
		      "After you acknowledge it, this program will\n"
		      "automatically exit to the shell.");

    sceKernelExitGame();
    return 0;
}
