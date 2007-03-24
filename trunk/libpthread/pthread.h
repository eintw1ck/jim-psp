/*
	pthread library for the PSP
	Copyright (C) 2006  Rafael Cabezas a.k.a. Raf

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef PTHREAD_H
	#define PTHREAD_H
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	typedef void (*thread_function)(void *);
	
	#define PTHREAD_SCOPE_SYSTEM  10 /* Kernel */
	#define PTHREAD_SCOPE_PROCESS 20 /* User */
	#define PTHREAD_SCOPE_PROCESS_VFPU 30 /* VFPU App */
	#define SCHED_OTHER			  0
	#define PTHREAD_STACK_MIN	  8*1024    /* 8KB   */
	#define PTHREAD_STACK_DEFAULT 128*1024  /* 128KB */

	/** Revise: */
	typedef int pthread_t;

	typedef struct 
	{
		int scope;
		int priority;
		int stack_size;
	} pthread_attr_t;

	struct sched_param
	{
		int sched_priority;
		int sched_policy;
	};

	/* Create a thread */
	int pthread_create(pthread_t *thread_id, const pthread_attr_t *attributes, thread_function tf, void *arguments);
	
	/* pthreads terminate when they return, or if they call: */
	int pthread_exit(void *status);
	

	int pthread_attr_init(pthread_attr_t *attr);
	int pthread_attr_setstacksize(pthread_attr_t *attr, size_t size);
	int pthread_attr_setscope(pthread_attr_t *attr, int scope);
	int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param);

	///int pthread_join(pthread_t thread, void **status_ptr);
	
	/* get thread id from within thread */
	///pthread_t pthread_self();
	
	/* to compare thread ids */
	///int pthread_equal(pthread_t t1, pthread_t t2);
	
	/** Mutexes */
	///int pthread_mutex_init, unlock, trylock, destroy
	
	#ifdef __cplusplus
	}
	#endif

#endif
