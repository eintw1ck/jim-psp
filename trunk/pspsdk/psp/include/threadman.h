#ifndef __THREADMAN_H__
#define __THREADMAN_H__

int sceKernelCreateSema(const char* name, int attr, int initVal, int maxVal, int option);
int sceKernelDeleteSema(int semaid);
int sceKernelSignalSema(int semaid, int signal);
int sceKernelWaitSema(int semaid, int signal, int unknown);
int sceKernelSleepThread(void);
int sceKernelCreateThread(const char* name, void *func, int initPriority, 
						  int stacksize, int attributes, int option);
int sceKernelStartThread(int thid, void *arg1, void *arg2);

int sceKernelCreateCallback(const char *name, void *func);
void sceKernelPollCallbacks(void);

#endif
