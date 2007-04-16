#include <stdio.h>
#include <pspkernel.h>
#include <pspkerneltypes.h>
#include "pthread.h"

typedef struct
{
	thread_function tf;
	void *arguments;
} __pthread_lib_user_thread_and_args;

int _pthread_lib_thread_handler(SceSize args, void *argp);

/* Create a thread */
int pthread_create(pthread_t *thread_id, const pthread_attr_t *attributes, thread_function tf, void *arguments)
{
	__pthread_lib_user_thread_and_args tdata;
	int thid;
	static int ctr = 0;
	char strName[32];
	int  initPriority;
	int  stackSize;
	SceUInt attr;
	SceKernelThreadOptParam *option = NULL;
	pthread_attr_t pthread_attr;
	
	if (attributes == NULL) 
	{
		pthread_attr_init(&pthread_attr);
		attributes = &pthread_attr;
	}

	initPriority = attributes->priority;
	stackSize = attributes->stack_size;
	switch(attributes->scope)
	{
		case PTHREAD_SCOPE_SYSTEM:
			attr = 0;
			break;
		case PTHREAD_SCOPE_PROCESS_VFPU:
			attr = PSP_THREAD_ATTR_VFPU;
			break;
		case PTHREAD_SCOPE_PROCESS:
		default:
			attr = PSP_THREAD_ATTR_USER;
			break;
	}

	tdata.tf = tf;
	tdata.arguments = arguments;
	ctr++;

	sprintf(strName, "pthread%d", ctr);

	thid = sceKernelCreateThread(strName, _pthread_lib_thread_handler, initPriority, stackSize, attr, option);

	if (thid >= 0)
	{
		sceKernelStartThread(thid, sizeof(__pthread_lib_user_thread_and_args), &tdata);
	}

	return 0;
}

/* pthreads terminate when they return, or if they call: */
int pthread_exit(void *status)
{
	sceKernelExitDeleteThread(0);
	return 0;
}

int _pthread_lib_thread_handler(SceSize args, void *argp)
{	
	__pthread_lib_user_thread_and_args *ptdata = (__pthread_lib_user_thread_and_args *)argp;
	int iRet = 0;
	
	/** Call user thread */
	(ptdata->tf)(ptdata->arguments);

	pthread_exit(NULL);

	return iRet;
}

int pthread_attr_init(pthread_attr_t *attr)
{
	/** Default to usermode */
	attr->scope      = PTHREAD_SCOPE_PROCESS; 
	/** Default to parent's priority */
	attr->priority   = sceKernelGetThreadCurrentPriority(); 
	attr->stack_size = PTHREAD_STACK_DEFAULT; 
	return 0;
}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t size) 
{
	attr->stack_size = size;
	return 0;
}

int pthread_attr_setscope(pthread_attr_t *attr, int scope) 
{
	attr->scope = scope;
	return 0;
}

int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param) 
{
	attr->priority = param->sched_priority;
	return 0;
}

int sched_yield(void)
{
	sceKernelDelayThread(0);
	return 0;
}
