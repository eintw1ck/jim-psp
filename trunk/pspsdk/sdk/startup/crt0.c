/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * crt0.c - Startup code.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id$
 */

#include <pspkerneltypes.h>
#include <pspmoduleinfo.h>
#include <pspthreadman.h>
#include <stdlib.h>
#include <string.h>

/* The maximum number of arguments that can be passed to main(). */
#define ARG_MAX 20

/* Default thread parameters for the main program thread. */
#define DEFAULT_THREAD_PRIORITY 32
#define DEFAULT_THREAD_ATTRIBUTE THREAD_ATTR_USER
#define DEFAULT_THREAD_STACK_KB_SIZE 256

/* If these variables are defined by the program, then they override the
   defaults given above. */
extern int sce_newlib_nocreate_thread_in_start __attribute__((weak));
extern unsigned int sce_newlib_priority __attribute__((weak));
extern unsigned int sce_newlib_attribute __attribute__((weak));
extern unsigned int sce_newlib_stack_kb_size __attribute__((weak));

/* This is declared weak in case someone compiles an empty program.  That
   program won't work on the PSP, but it could be useful for testing the
   toolchain. */
extern SceModuleInfo module_info __attribute__((weak));

extern void _init(void);
extern void _fini(void);

extern int main(int argc, char *argv[]);

/**
 * Main program thread
 *
 * Initializes runtime parameters and calls the program's main().
 *
 * @param args - Size (in bytes) of the argp parameter.
 * @param argp - Pointer to program arguments.  Each argument is a NUL-terminated string.
 */
void _main(SceSize args, void *argp)
{
	char *argv[ARG_MAX], *ap = (char *) argp;
	int argc = 0;

	/* Turn our thread arguments into main()'s argc and argv[]. */
	if (args > 0) {
		do {
			argv[argc++] = ap;
			ap += strlen(ap) + 1;
		} while ((argc < ARG_MAX) && (((char *) argp - ap) < args));
	}

	/* Make sure _fini() is called when the program ends, and call _init() to
	   initialize global constructors. */
	atexit((void *) _fini);
	_init();

	/* Call main(). */
	int res = main(argc, argv);

	/* Return control to the operating system. */
	exit(res);
}

/**
 * Startup thread
 *
 * Creates the main program thread based on variables defined by the program.
 *
 * @param args - Size (in bytes) of arguments passed to the program by the kernel.
 * @param argp - Pointer to arguments passed by the kernel.
 */
int _start(SceSize args, void *argp)
{
	if (&sce_newlib_nocreate_thread_in_start != NULL) {
		/* The program does not want main() to be run in a seperate thread. */
		_main(args, argp);
		return 1;
	}

	int priority = DEFAULT_THREAD_PRIORITY;
	unsigned int attribute = DEFAULT_THREAD_ATTRIBUTE;
	unsigned int stackSize = DEFAULT_THREAD_STACK_KB_SIZE * 1024;

	if (&sce_newlib_priority != NULL) {
		priority = sce_newlib_priority;
	}
	if (&sce_newlib_attribute != NULL) {
		attribute = sce_newlib_attribute;
	}
	if (&sce_newlib_stack_kb_size != NULL) {
		stackSize = sce_newlib_stack_kb_size * 1024;
	}

	SceUID thid;
	thid = sceKernelCreateThread("user_main", (void *) _main, priority, stackSize, attribute, 0);
	sceKernelStartThread(thid, args, argp);

	return 0;
}

/* The entry table provides pointers to the executable's _start() and
   module_info structure. */
static const unsigned int __entrytable[4] __attribute__((section(".rodata.sceResident"))) = {
	0xD632ACDB, 0xF01D73A7, (unsigned int) &_start, (unsigned int) &module_info
};

/* Create the empty library entry used to describe the program's _start() and
   module_info. */
static const struct _library_entry {
	const char *	name;
	unsigned short	version;
	unsigned short	attribute;
	unsigned char	entLen;
	unsigned char	varCount;
	unsigned short	funcCount;
	void *			entrytable;
} _library_entry __attribute__((section(".lib.ent"), used)) = {
	NULL, 0, 0x8, 4, 1, 1, &__entrytable
};
