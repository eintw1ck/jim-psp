/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmoduleinfo.h - Definitions for the .rodata.sceModuleInfo ELF section.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef PSPMODULEINFO_H
#define PSPMODULEINFO_H

/* Note: Some of the structures and definitions in this file were extrapolated from
   symbolic debugging information found in the Japanese version of Puzzle Bobble. */

/* Module info structure.  Used to declare a module (library or executable).  This structure
   is required in all PSP executables. */
typedef struct _scemoduleinfo {
	unsigned short		modattribute;
	unsigned char		modversion[2];
	char			modname[27];
	char			terminal;
	void *			gp_value;
	void *			ent_top;
	void *			ent_end;
	void *			stub_top;
	void *			stub_end;
} _sceModuleInfo;

typedef const _sceModuleInfo SceModuleInfo;

extern char _gp[];

#ifdef __cplusplus

/* Declare a module.  This must be specified in the source of a library or executable. */
#define PSP_MODULE_INFO(name, attributes, major_version, minor_version) \
	asm (                                                           \
	"    .set push\n"                                               \
	"    .section .lib.ent.top, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_ent_top:\n"                                              \
	"    .section .lib.ent.btm, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"__lib_ent_bottom:\n"                                           \
	"    .word 0\n"                                                 \
	"    .section .lib.stub.top, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_stub_top:\n"                                             \
	"    .section .lib.stub.btm, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"__lib_stub_bottom:\n"                                          \
	"    .word 0\n"                                                 \
	"    .set pop\n"                                                \
	);                                                              \
	extern char __lib_ent_top[], __lib_ent_bottom[];                \
	extern char __lib_stub_top[], __lib_stub_bottom[];              \
	extern SceModuleInfo module_info                                \
		__attribute__((section(".rodata.sceModuleInfo"),        	\
			       aligned(16), unused)) = {                		\
	  attributes, { minor_version, major_version }, #name, 0, _gp,  \
	  __lib_ent_top, __lib_ent_bottom,                              \
	  __lib_stub_top, __lib_stub_bottom                             \
	}
#else
/* Declare a module.  This must be specified in the source of a library or executable. */
#define PSP_MODULE_INFO(name, attributes, major_version, minor_version) \
	asm (                                                           \
	"    .set push\n"                                               \
	"    .section .lib.ent.top, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_ent_top:\n"                                              \
	"    .section .lib.ent.btm, \"a\", @progbits\n"                 \
	"    .align 2\n"                                                \
	"__lib_ent_bottom:\n"                                           \
	"    .word 0\n"                                                 \
	"    .section .lib.stub.top, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"    .word 0\n"                                                 \
	"__lib_stub_top:\n"                                             \
	"    .section .lib.stub.btm, \"a\", @progbits\n"                \
	"    .align 2\n"                                                \
	"__lib_stub_bottom:\n"                                          \
	"    .word 0\n"                                                 \
	"    .set pop\n"                                                \
	);                                                              \
	extern char __lib_ent_top[], __lib_ent_bottom[];                \
	extern char __lib_stub_top[], __lib_stub_bottom[];              \
	SceModuleInfo module_info                                       \
		__attribute__((section(".rodata.sceModuleInfo"),        	\
			       aligned(16), unused)) = {                		\
	  attributes, { minor_version, major_version }, #name, 0, _gp,  \
	  __lib_ent_top, __lib_ent_bottom,                              \
	  __lib_stub_top, __lib_stub_bottom                             \
	}
#endif

/* Define the main thread's attributes */
#define PSP_MAIN_THREAD_ATTR(attr) u32 _main_thread_attr = (attr)

#endif /* PSPMODULEINFO_H */
