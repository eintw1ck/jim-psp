
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Python.h"

PSP_MODULE_INFO("Python", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

volatile int pspInterruptOccurred = 0;

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

int main(int argc, char *argv[])
{
    FILE *fp;

    SetupCallbacks();

#ifdef DEBUG
    pspDebugScreenInit();
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

    Py_Finalize();

    sceKernelExitGame();
    return 0;
}
