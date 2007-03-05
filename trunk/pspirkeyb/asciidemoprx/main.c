/*
    asciidemoprx: PSP IR Keyboard Library ascii demo application 
                    (http://pspirkeyb.podzone.net)
                  This is the same as the ascii demo but the driver get's loaded as PRX
    Copyright (C) 2007 Harald Fielker <harald.fielker@web.de>

    This program can be distributed under the terms of the GNU LGPL.
    See the file LICENSE.
*/

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspsdk.h>
#include <string.h>

#include <pspirkeybprx.h>
#include <pspirkeyb_rawkeys.h>

#define printf pspDebugScreenPrintf

const char * g_prx_module = "ms0:/seplugins/irkeyb.prx";

/* Define the module info section */
PSP_MODULE_INFO("asciidemo", PSP_MODULE_USER, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

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

SceUID load_module(const char *path, int flags, int type)
{
	SceKernelLMOption option;
	SceUID mpid;

	/* If the type is 0, then load the module in the kernel partition, otherwise load it
	   in the user partition. */
	if (type == 0) {
		mpid = 1;
	} else {
		mpid = 2;
	}

	memset(&option, 0, sizeof(option));
	option.size = sizeof(option);
	option.mpidtext = mpid;
	option.mpiddata = mpid;
	option.position = 0;
	option.access = 1;

	return sceKernelLoadModule(path, flags, type > 0 ? &option : NULL);
}

int main(int argc, char *argv[])
{
    SceCtrlData pad;
	SceUID modid = 0;
	SceModule *mod=NULL;
    u32 buttonsold = 0;
    int kernelmode = 0;       /* only 0 works for now - some keyboards need baud change */
    const char *config_file = NULL; /* this will force ms0:/seplugins/pspirkeyb.ini */ 

	SetupCallbacks();

    pspDebugScreenInit();
    printf("PSP Irda Keyboard test - ASCii input (PRX) \n");

	/* Start mymodule.prx and dump its information */
	printf("\nStart my module\n");
	modid = load_module(g_prx_module, 0, 0);
	printf("Module ID %08X\n", modid);
	mod = sceKernelFindModuleByUID(modid);
	printf("mod %p\n", mod);
	if(mod == NULL)
	{
        printf( "loading of module %s failed\n", g_prx_module );
        goto endprg;
    }
    
    if( pspIrKeybInitPrx( config_file, kernelmode ) != 0 )
    {
        printf( "error: can't inialize the keyboard\n" );
        printf( "       check keyboard type/map in ms0:/seplugins/pspirkeyb.ini\n" );
    }
    else
    {
        unsigned char termchar = 'X';
        unsigned char buffer[255];
        int i, length=0;

        printf("\npress %c on keyboard or any PSP button to exit\n", termchar );

        /* setup output method to ASCii */
        pspIrKeybOutputModePrx( PSP_IRKBD_OUTPUT_MODE_ASCII );

        while(1) {
            length = 0;
            /* non blocking read */
            if( pspIrKeybReadinputPrx(buffer, &length) >= 0 )
            {
                for( i=0; i < length; i++ )
                    printf( "%c", buffer[i] ); 
                if( length == 1 && buffer[0] == termchar )
                    break;
            } 
            else 
            {
                // tick(); /* non  blocking */

                sceCtrlReadBufferPositive(&pad, 1);
                if (pad.Buttons != buttonsold)
                    break;
            }
        }

        /* bye keyboard */
        pspIrKeybFinishPrx();
    }

endprg:
    printf( "\n bye... (PRESS psp button to quit)\n" );

    buttonsold = 0;
    while (1) {
        sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons != buttonsold) {
            /* Exit */
            sceKernelExitGame();
        }
    }

	return 0;
}
