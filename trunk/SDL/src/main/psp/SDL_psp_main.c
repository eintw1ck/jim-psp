/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2004 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

/*  
    PSP port contributed by:
    Marcus R. Brown <mrbrown@ocgnet.org>
    Jim Paris <jim@jtan.com>
    Matthew H <matthewh@webone.com.au>
*/

#include "SDL_main.h"
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <pspthreadman.h>
#include <stdlib.h>
#include <stdio.h>

#define STDOUT_FILE	"stdout.txt"
#define STDERR_FILE	"stderr.txt"

/* If application's main() is redefined as SDL_main, and libSDLmain is
   linked, then this file will create the standard exit callback,
   define the PSP_* macros, add an exception handler, nullify device 
   checks and exit back to the browser when the program is finished. */

extern int SDL_main(int argc, char *argv[]);

static void cleanup_output(void);

PSP_MODULE_INFO("SDL App", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int sdl_psp_exit_callback(int arg1, int arg2, void *common)
{
	cleanup_output();
	sceKernelExitGame();
	return 0;
}

int sdl_psp_callback_thread(SceSize args, void *argp)
{
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", 
				       sdl_psp_exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

int sdl_psp_setup_callbacks(void)
{
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", 
				     sdl_psp_callback_thread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
		sceKernelStartThread(thid, 0, 0);
	return thid;
}

void sdl_psp_exception_handler(PspDebugRegBlock *regs)
{
	pspDebugScreenInit();

	pspDebugScreenSetBackColor(0x00FF0000);
	pspDebugScreenSetTextColor(0xFFFFFFFF);
	pspDebugScreenClear();

	pspDebugScreenPrintf("I regret to inform you your psp has just crashed\n\n");
	pspDebugScreenPrintf("Exception Details:\n");
	pspDebugDumpException(regs);
	pspDebugScreenPrintf("\nThe offending routine may be identified with:\n\n"
		"\tpsp-addr2line -e target.elf -f -C 0x%x 0x%x 0x%x\n",
		regs->epc, regs->badvaddr, regs->r[31]);
}

/* If this flag is set to 1, the _init() function was called and all
   global/static constructors have been called. */
static int init_was_called = 0;

__attribute__ ((constructor))
void loaderInit()
{
	int kmode_is_available = (sceKernelDevkitVersion() < 0x02000010);

	if (kmode_is_available) {
		pspKernelSetKernelPC();
		pspSdkInstallNoDeviceCheckPatch();
		pspDebugInstallErrorHandler(sdl_psp_exception_handler);
	}

	init_was_called = 1;
}

/* Remove the output files if there was no output written */
static void cleanup_output(void)
{
#ifndef NO_STDIO_REDIRECT
	FILE *file;
	int empty;
#endif

	/* Flush the output in case anything is queued */
	fclose(stdout);
	fclose(stderr);

#ifndef NO_STDIO_REDIRECT
	/* See if the files have any output in them */
	file = fopen(STDOUT_FILE, "rb");
	if ( file ) {
		empty = (fgetc(file) == EOF) ? 1 : 0;
		fclose(file);
		if ( empty ) {
			remove(STDOUT_FILE);
		}
	}
	file = fopen(STDERR_FILE, "rb");
	if ( file ) {
		empty = (fgetc(file) == EOF) ? 1 : 0;
		fclose(file);
		if ( empty ) {
			remove(STDERR_FILE);
		}
	}
#endif
}

extern void _init(void);

int main(int argc, char *argv[])
{
	/* Fanjita's EBOOT loader can be configured to skip the call to _init().
	   Since we need _init() for C++, we check to see if _init() has been
	   called.  If it hasn't we call it manually, after determining whether or
	   not we can access the kernel. */
	if (!init_was_called) {
		_init();
	}
	
	pspDebugScreenInit();
	sdl_psp_setup_callbacks();

#ifndef NO_STDIO_REDIRECT
	/* Redirect standard output and standard error. */
	/* TODO: Error checking. */
	freopen(STDOUT_FILE, "w", stdout);
	freopen(STDERR_FILE, "w", stderr);
	setvbuf(stdout, NULL, _IOLBF, BUFSIZ);	/* Line buffered */
	setbuf(stderr, NULL);					/* No buffering */
#endif /* NO_STDIO_REDIRECT */

	atexit(cleanup_output);

	(void)SDL_main(argc, argv);

	cleanup_output();
	sceKernelDelayThread(2500000);
	sceKernelExitGame();
	return 0;
}
