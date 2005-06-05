/*                          ____  _     
#         ____  _________  / __ \(_)____
#        / __ \/ ___/ __ \/ / / / / ___/
#       / /_/ (__  ) /_/ / /_/ / (__  ) 
#      / .___/____/ .___/_____/_/____/  
#     /_/        /_/
#     
# Copyright 2005, pspdev - http://www.pspdev.org
# Author:       John Kelley
# Date:         June 1 2005
# File:         pspelf.h
# Description:  Elf parsing code based on TIS's ELF_Format.pdf with
#               added PSP specific stuff. PSP specific structures
#               written by vvuk.
#
*/
#ifndef _PSPELF_H_
#define _PSPELF_H_

#include "util.h"

#define PSPelfTypeELF 0x0002
#define PSPelfTypePRX 0xFFA0

#define identLen 16
#define objTypeProcessorSpecific 0xFF00

typedef enum {
	NoMachine,
	M32,
	SPARC,
	in386,
	m68k,
	m88k,
	i860,
	MIPS
} procType;

typedef enum {
	None,
	Relocatable,
	Executable,
	Shared,
	Core
} objType;
	
typedef struct {
	u8	ident[identLen];
	u16	elfType;
	u16	processorType;
	u32	version;
	u32	startAddr;
	u32	programHeaderOffset;
	u32	sectionHeaderOffset;
	u32	flags;
	u16	elfHeaderSize;
	u16	programHeaderEntrySize;
	u16	numProgramHeaderEntries;
	u16	sectionHeaderSize;
	u16	numSectionHeaderEntries;
	u16	sectionHeaderStringTableIndex;
} elfHeader;

typedef struct {
	u32	nameIndex;
	u32	type;
	u32	flags;
	u32	address;
	u32	offset;
	u32	size;
	u32	link;
	u32	info;
	u32	addressAlign;
	u32	entrySize;
} sectionHeader;

typedef enum {
	inactive,
	program,
	symbolTable,
	stringTable,
	relocationAddends,
	hashTable,
	dynamic,
	note,
	empty,
	relocation,
	library, //reserved
	dynamicSymbolTable
} sectionType;

typedef struct {
	u32	nameIndex;
	u32	value;
	u32	size;
	u8	info;
	u8	other;
	u16	sectionHeaderIndex;
} symbolTableEntry;


typedef struct {
    // 0, 0, 1, 1 ?
    unsigned char c1, c2, c3, c4;
    // 28 bytes of module name, packed with 0's.
    // (might be less with 0 longs after)
    char name[28];
    unsigned long ptr1;         /* ptr to somewhere after executable */
    unsigned long libent;       /* ptr to .lib.ent section */
    unsigned long libentend;    /* ptr to end of .lib.ent section */
    unsigned long libstub;      /* ptr to .lib.stub section */
    unsigned long libstubend;   /* ptr to end of .lib.stub section */
} __attribute__((packed)) SceModuleInfo;

// this struct seems to appear as the data in
// the .lib.ent section, and is referenced by
// the module info
typedef struct {
    const char *libname;	/* Library name. */
    unsigned int flags;		/* Flags. */
    unsigned char ent_len;	/* Number of DWORDs in this entry. The size of the entry is ent_len * 4. */
    unsigned char var_ent_count; /* Number of variable entries following function entries. */
    unsigned short func_ent_count; /* Number of function entries. */
    // addr of start of .rodata.sceResident, which has 4
    // longs (and one 0 long) before module name strings start,
    // which includes things like a ptr to _start
    unsigned long sceResidentAddr;
} SceLibEntData;

// this struct is pointed to by SceLibEntData, and appears at the
// start of .rodata.sceResident.  Each entry in .rodata.sceResident
// has a null long in between it, with the module strings (used in
// LibStubEntry) being padded to 4-byte alignment, and always
// including a terminating 0.

typedef struct {
    unsigned long l1; // unknown 0xd632acdb
    unsigned long l2; // unknown 0xf01d73a7
    unsigned long startAddress; // address of _start
    unsigned long moduleInfoAddr; // address of sceModuleInfo struct
} SceResidentData;
    

typedef struct {
    // pointer to module name (will be in .rodata.sceResident section)
    unsigned long moduleNameSymbol;
    // mod version
    unsigned short version;
    unsigned short attr;
    unsigned char structsz; // 0x5
    unsigned char numVars;
    // number of symbols
    unsigned short numFuncs;
    // each symbol has an associated nid; nidData is a pointer
    // (in .rodata.sceNid section) to an array of longs, one
    // for each function, which identifies the function whose
    // address is to be inserted.
    //
    // The hash is the first 4 bytes of a SHA-1 hash of the function
    // name.  (Represented as a little-endian long, so the order 
    // of the bytes is reversed.)
    unsigned long nidData;
    // the function to be relocated
    unsigned long firstSymAddr;
} __attribute__((packed)) SceLibStubEntry;

#endif
