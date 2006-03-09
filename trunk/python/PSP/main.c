
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspsdk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef WITH_PSP2D
#include <pspgu.h>
#endif

#include "Python.h"

PSP_MODULE_INFO("Python", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

volatile int pspInterruptOccurred = 0;

#if defined(DEBUG_THREAD) || defined(DEBUG_IMPORT)
#define DEBUG
#endif

static char* save_argv0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
    pspInterruptOccurred = 1;

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

    thid = sceKernelCreateThread("update_thread", CallbackThread,
                                 0x11, 0xFA0, 0, 0);
    if(thid >= 0)
    {
       sceKernelStartThread(thid, 0, 0);
    }

    return thid;
}

int main_thread(SceSize args, void *argp)
{
    FILE *fp;
    int argc = 1;
    char *argv[] = {save_argv0};

#ifdef WITH_PSP2D
    sceGuInit();
#endif

    Py_Initialize();

    PySys_SetPath("ms0:/python");
    PySys_SetArgv(argc, argv);

    fp = fopen("script.py", "r");
    if (fp)
    {
       PyRun_SimpleFile(fp, "script.py");
       fclose(fp);
    }
    else
    {
#ifndef DEBUG
       pspDebugScreenInit();
#endif

       pspDebugScreenPrintf("Error - could not open script.py\n");
    }

#ifdef DEBUG
    sceKernelDelayThreadCB(1e7);
#endif

    Py_Finalize();

#ifdef WITH_PSP2D
    sceGuTerm();
#endif

    sceKernelExitGame();

    return 0;
}

int main(int argc, char *argv[])
{
    SceUID thid;

    save_argv0 = strdup(argv[0]);

    SetupCallbacks();

#ifdef DEBUG
    pspDebugScreenInit();
#endif

    if(pspSdkLoadInetModules() < 0)
       return 1;

    thid = sceKernelCreateThread("python_thread", main_thread, 0x18, 0x10000,
                                 PSP_THREAD_ATTR_USER|PSP_THREAD_ATTR_VFPU, NULL);
    sceKernelStartThread(thid, 0, NULL);

    sceKernelExitDeleteThread(0);

    return 0;
}
