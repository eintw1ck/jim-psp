
/* PSP threading */

#include <pspkernel.h>

static void PyThread__init_thread(void)
{
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

    if (!initialized)
       PyThread_init_thread();

    thid = sceKernelCreateThread("Python thread", my_thread_cb, 0x18, 0x10000, 0, 0);
    if (thid < 0)
       return -1;

    tprm.id = thid;
    tprm.func = func;
    tprm.arg = arg;

    if (sceKernelStartThread(thid, sizeof(tprm), &tprm) < 0)
    {
       sceKernelDeleteThread(thid);
       return -1;
    }

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

    id = sceKernelCreateSema("Python lock", 0, 1, 1, 0);
    return (PyThread_type_lock)id;
}

void PyThread_free_lock(PyThread_type_lock id)
{
    sceKernelDeleteSema((int)id);
}

int PyThread_acquire_lock(PyThread_type_lock id, int waitflag)
{
    // XXX TODO: non-blocking mode. Is it even possible ?
    if (sceKernelWaitSemaCB((int)id, 1, 0) < 0)
       return -1;

    return 0;
}

void PyThread_release_lock(PyThread_type_lock id)
{
    sceKernelSignalSema((int)id, 1);
}
