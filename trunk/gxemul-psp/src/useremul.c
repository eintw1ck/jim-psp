/*
 *  Copyright (C) 2004-2006  Anders Gavare.  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright  
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE   
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *
 *  $Id: useremul.c,v 1.70 2006/01/14 12:51:59 debug Exp $
 *
 *  Userland (syscall) emulation.
 *
 *  TODO:
 *
 *	environment passing for most emulation modes
 *
 *	implement more syscalls
 *
 *	32-bit vs 64-bit problems? MIPS n32, o32, n64?
 *
 *	Dynamic ELFs?
 *
 *	Try to prefix "/emul/mips/" or similar to all filenames,
 *		and only if that fails, try the given filename
 *
 *	Automagic errno translation?
 *
 *	Memory allocation? mmap etc.
 *
 *	File descriptor (0,1,2) assumptions?
 *
 *
 *  This module needs more cleanup.
 *  -------------------------------
 *
 *
 *  NOTE:  This module (useremul.c) is just a quick hack to see if
 *         userland emulation works at all.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <time.h>

#include "cpu.h"
#include "cpu_mips.h"
#include "emul.h"
#include "machine.h"
#include "memory.h"
#include "misc.h"

struct syscall_emul {
	char		*name;
	int		arch;
	char		*cpu_name;
	void		(*f)(struct cpu *, uint32_t);
	void		(*setup)(struct cpu *, int, char **);

	struct syscall_emul *next;
};

static struct syscall_emul *first_syscall_emul;

/*  Max length of strings passed using syscall parameters:  */
#define	MAXLEN		8192

void useremul__psp(struct cpu *cpu, uint32_t code);
void useremul__psp_setup(struct cpu *cpu, int argc, char **host_argv);
void useremul__psp_loadexecpayload_setup(struct cpu *cpu, int argc, char **host_argv);
void useremul__psp_iplbootstrap_setup(struct cpu *cpu, int argc, char **host_argv);

/*
 *  useremul_setup():
 *
 *  Set up an emulated environment suitable for running userland code. The
 *  program should already have been loaded into memory when this function
 *  is called.
 */
void useremul_setup(struct cpu *cpu, int argc, char **host_argv)
{
	struct syscall_emul *sep;

	sep = first_syscall_emul;

	while (sep != NULL) {
		if (strcasecmp(cpu->machine->userland_emul, sep->name) == 0) {
			sep->setup(cpu, argc, host_argv);
			return;
		}
		sep = sep->next;
	}

	fatal("useremul_setup(): internal error, unimplemented emulation?\n");
	exit(1);
}


/*
 *  get_userland_string():
 *
 *  This can be used to retrieve strings, for example filenames,
 *  from the emulated memory.
 *
 *  NOTE: This function returns a pointer to a malloced buffer. It is up to
 *        the caller to use free().
 */
unsigned char *get_userland_string(struct cpu *cpu, uint64_t baseaddr)
{
	unsigned char *charbuf;
	int i, len = 16384;

	charbuf = malloc(len);
	if (charbuf == NULL) {
		fprintf(stderr, "get_userland_string(): out of memory (trying"
		    " to allocate %i bytes)\n", len);
		exit(1);
	}

	/*  TODO: address validity check  */

	for (i=0; i<len; i++) {
		cpu->memory_rw(cpu, cpu->mem, baseaddr+i, charbuf+i,
		    1, MEM_READ, CACHE_DATA);
		if (charbuf[i] == '\0')
			break;
	}

	charbuf[MAXLEN-1] = 0;
	return charbuf;
}


/*
 *  get_userland_buf():
 *
 *  This can be used to retrieve buffers, for example inet_addr, from
 *  emulated memory.
 *
 *  NOTE: This function returns a pointer to a malloced buffer. It is up to
 *        the caller to use free().
 *
 *  TODO: combine this with get_userland_string() in some way
 */
unsigned char *get_userland_buf(struct cpu *cpu,	uint64_t baseaddr, uint64_t len)
{
	unsigned char *charbuf;
	size_t i;

	charbuf = malloc(len);
	if (charbuf == NULL) {
		fprintf(stderr, "get_userland_buf(): out of memory (trying"
		    " to allocate %lli bytes)\n", (long long)len);
		exit(1);
	}

	/*  TODO: address validity check  */
	for (i=0; i<len; i++) {
		cpu->memory_rw(cpu, cpu->mem, baseaddr+i, charbuf+i, 1,
		    MEM_READ, CACHE_DATA);
		/*  debug(" %02x", charbuf[i]);  */
	}
	/* debug("\n"); */

	return charbuf;
}


/*
 *  useremul_syscall():
 *
 *  Handle userland syscalls.  This function is called whenever a userland
 *  process runs a 'syscall' instruction.  The code argument is the code
 *  embedded into the syscall instruction, if any.  (This 'code' value is not
 *  necessarily used by specific emulations.)
 */
void useremul_syscall(struct cpu *cpu, uint32_t code)
{
	if (cpu->useremul_syscall == NULL) {
		fatal("useremul_syscall(): cpu->useremul_syscall == NULL\n");
	} else
		cpu->useremul_syscall(cpu, code);
}

/*
 *  useremul_name_to_useremul():
 *
 *  Example:
 *     Input:  name = "netbsd/pmax"
 *     Output: sets *arch = ARCH_MIPS, *machine_name = "NetBSD/pmax",
 *             and *cpu_name = "R3000".
 */
void useremul_name_to_useremul(struct cpu *cpu, char *name, int *arch,
	char **machine_name, char **cpu_name)
{ 
	struct syscall_emul *sep;

	sep = first_syscall_emul;

	while (sep != NULL) {
		if (strcasecmp(name, sep->name) == 0) {
			if (cpu_family_ptr_by_number(sep->arch) == NULL) {
				printf("\nSupport for the CPU family needed"
				    " for '%s' userland emulation was not"
				    " enabled at configuration time.\n",
				    sep->name);
				exit(1);
			}

			if (cpu != NULL)
				cpu->useremul_syscall = sep->f;

			if (arch != NULL)
				*arch = sep->arch;

			if (machine_name != NULL) {
				*machine_name = strdup(sep->name);
				if (*machine_name == NULL) {
					printf("out of memory\n");
					exit(1);
				}
			}

			if (cpu_name != NULL) {
				*cpu_name = strdup(sep->cpu_name);
				if (*cpu_name == NULL) {
					printf("out of memory\n");
					exit(1);
				}
			}
			return;
		}

		sep = sep->next;
	}

	fatal("Unknown userland emulation '%s'\n", name);
	exit(1);
}


/*
 *  add_useremul():
 *
 *  For internal use, from useremul_init() only. Adds an emulation mode.
 */
static void add_useremul(char *name, int arch, char *cpu_name,
	void (*f)(struct cpu *, uint32_t),
	void (*setup)(struct cpu *, int, char **))
{
	struct syscall_emul *sep;

	sep = malloc(sizeof(struct syscall_emul));
	if (sep == NULL) {
		printf("add_useremul(): out of memory\n");
		exit(1);
	}
	memset(sep, 0, sizeof(sep));

	sep->name     = name;
	sep->arch     = arch;
	sep->cpu_name = cpu_name;
	sep->f        = f;
	sep->setup    = setup;

	sep->next = first_syscall_emul;
	first_syscall_emul = sep;
}


/*
 *  useremul_list_emuls():
 *
 *  List all available userland emulation modes.  (Actually, only those which
 *  have CPU support enabled.)
 */
void useremul_list_emuls(void)
{
	struct syscall_emul *sep;
	int iadd = DEBUG_INDENTATION * 2;

	sep = first_syscall_emul;

	if (sep == NULL)
		return;

	debug("The following userland-only (syscall) emulation modes are"
	    " available:\n\n");
	debug_indentation(iadd);

	while (sep != NULL) {
		if (cpu_family_ptr_by_number(sep->arch) != NULL) {
			debug("%s (default CPU \"%s\")\n",
			    sep->name, sep->cpu_name);
		}

		sep = sep->next;
	}

	debug_indentation(-iadd);
	debug("\n(Most of these modes are bogus.)\n\n");
}


/*
 *  useremul_init():
 *
 *  This function should be called before any other useremul_*() function
 *  is used.
 */
void useremul_init(void)
{
	/*  Note: These are in reverse alphabetic order:  */
	add_useremul("psp", ARCH_MIPS, "Allegrex", useremul__psp, useremul__psp_setup);
	add_useremul("psp-loadexec-payload", ARCH_MIPS, "Allegrex", useremul__psp, useremul__psp_loadexecpayload_setup);
	add_useremul("psp-ipl-bootstrap", ARCH_MIPS, "Allegrex", useremul__psp, useremul__psp_iplbootstrap_setup);
}

