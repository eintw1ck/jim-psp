
/* PSP threading */

#include <pspkernel.h>

#ifdef DEBUG
#include <pspdebug.h>
#endif

static void PyThread__init_thread(void)
{
#ifdef DEBUG
    pspDebugScreenPrintf("Screen initialized (threading debug).\n");
#endif
}

typedef struct
{
      int id;
      void (*func)(void*);
      void *arg;
} PSP_THREAD_ST;

static int my_thread_cb(SceSize args, void *argp)
{
    (*(((PSP_THREAD_ST*)argp)->func))(((PSP_THREAD_ST*)argp)->arg);

    return 0;
}

long PyThread_start_new_thread(void (*func)(void*), void *arg)
{
    int thid;
    PSP_THREAD_ST tprm;

#ifdef DEBUG
    pspDebugScreenPrintf("Starting new thread\n");
#endif

    if (!initialized)
       PyThread_init_thread();

    thid = sceKernelCreateThread("Python thread", my_thread_cb, 0x18, 0x10000, 0, 0);
    if (thid < 0)
    {
#ifdef DEBUG
       pspDebugScreenPrintf("Thread creation failed\n");
#endif
       return -1;
    }

#ifdef DEBUG
    pspDebugScreenPrintf("Thread created.\n");
#endif

    tprm.id = thid;
    tprm.func = func;
    tprm.arg = arg;

    if (sceKernelStartThread(thid, sizeof(tprm), &tprm) < 0)
    {
#ifdef DEBUG
       pspDebugScreenPrintf("Could not start thread\n");
#endif

       sceKernelDeleteThread(thid);
       return -1;
    }

#ifdef DEBUG
    pspDebugScreenPrintf("Thread started.\n");
#endif

    return 0;
}

long PyThread_get_thread_ident(void)
{
    if (!initialized)
       PyThread_init_thread();

    return (long)sceKernelGetThreadId();
}

void PyThread_exit_thread(void)
{
    sceKernelExitThread(0);
}

void PyThread__exit_thread(void)
{
    sceKernelExitThread(0);
}

PyThread_type_lock PyThread_allocate_lock(void)
{
    int id;

#ifdef DEBUG
    pspDebugScreenPrintf("Creating semaphore.\n");
#endif

    id = sceKernelCreateSema("Python lock", 0, 1, 1, 0);

#ifdef DEBUG
    pspDebugScreenPrintf("Semaphore created: %d.\n", id);
#endif

    return (PyThread_type_lock)id;
}

void PyThread_free_lock(PyThread_type_lock id)
{
#ifdef DEBUG
    pspDebugScreenPrintf("Destroying semaphore %d.\n", (int)id);
#endif

    sceKernelDeleteSema((int)id);
}

int PyThread_acquire_lock(PyThread_type_lock id, int waitflag)
{
    SceUInt timeout, *ptimeout;

    if (!waitflag)
    {
       timeout = 1;
       ptimeout = &timeout;
    }
    else
    {
       ptimeout = NULL;
    }

#ifdef DEBUG
    pspDebugScreenPrintf("Acquiring semaphore %d from thread %ld (%d).\n", (int)id, PyThread_get_thread_ident(), waitflag);
#endif

    if (sceKernelWaitSemaCB((int)id, 1, ptimeout) < 0)
    {

#ifdef DEBUG
    pspDebugScreenPrintf("Error acquiring semaphore %d.\n", (int)id);
#endif

       return 0;
    }

#ifdef DEBUG
    pspDebugScreenPrintf("Semaphore %d acquired.\n", (int)id);
#endif

    return 1;
}

void PyThread_release_lock(PyThread_type_lock id)
{
#ifdef DEBUG
    pspDebugScreenPrintf("Releasing semaphore %d in thread %ld.\n", (int)id, PyThread_get_thread_ident());
#endif

    sceKernelSignalSema((int)id, 1);

#ifdef DEBUG
    pspDebugScreenPrintf("Semaphore %d released.\n", (int)id);
#endif
}
