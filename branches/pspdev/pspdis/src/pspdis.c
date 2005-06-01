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
# File:         pspdis.c
# Description:  Disassembler for PSP Allegrex binaries.
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pspdis.h"
#include "pspelf.h"
#include "../libopcodes/dis-asm.h"
#include "libopcodes_helper.h"
#include "util.h"

int main(int argc, char *argv[]) {
	FILE *in;
	elfHeader *header = NULL;
	sectionHeader *sHeaders = NULL;
	u8 *elfData;
	u8 elfType[32];
	u8 *sectionStringTable = NULL;
	u8 *elfStringTable = NULL;
	u8 *libStub = NULL;
	u8 *libStubBtm = NULL;
	u8 *sceResident = NULL;
	u8 *text = NULL;
	u32 textSize = 0;
	u32 *sceNid = NULL;
	u32 i;
	size_t elfDataSize = 0;
	SceModuleInfo *moduleInfo = NULL;
	disassemble_info dinfo;
	
	printf("pspDis v%0.1f\n\n", PSPDISVER);
	if (argc != 2) {
		printf("Usage: %s <elf file>\n", argv[0]);
		return 1;
	}
	
	in = fopen(argv[1], "rb");
	if (!in) {
		printf("Could not open file '%s'.\n", argv[1]);
		return 1;
	}
	//read file
	fseek(in, 0, SEEK_END);
	elfDataSize = ftell(in);
	elfData = (u8*)malloc(elfDataSize);
	fseek(in, 0, SEEK_SET);
	if(fread(elfData, 1, elfDataSize, in) != elfDataSize) {
		printf("Error reading %d bytes.\n", elfDataSize);
		free(elfData);
		fclose(in);
		return 1;
	}
	
	//read header
	header = (elfHeader*)elfData;
	
	//get section headers
	if (header->numSectionHeaderEntries != 0) {
		sHeaders = (sectionHeader*)&elfData[header->sectionHeaderOffset];
	}
	
	//determine elf type
	if (memcmp(header->ident, "~PSP", 4) == 0)
		sprintf(elfType, "an Encrypted PRX");
	else if (memcmp(header->ident, "\x7F\x45\x4c\x46", 4) == 0)
		if (header->elfType == PSPelfTypeELF)
			sprintf(elfType, "an ELF Executable");
		else if(header->elfType == PSPelfTypePRX)
			sprintf(elfType, "a PRX Library");
		else
			sprintf(elfType, "an unrecognized ELF type 0x%02X", header->elfType);
	else {
		printf("File is not a valid PSP ELF (%s)\n", header->ident);
		fclose(in);
		free(elfData);
		return 1;
	}
	printf("File is %s with %d sections\n", elfType, header->numSectionHeaderEntries);
	
	//find string tables
	for (i = 0; i < header->numSectionHeaderEntries; i++)
		if (sHeaders[i].type == stringTable) {
			dprintf("Found string table @ index %d with size %d @0x%08X.\n", i, sHeaders[i].size,sHeaders[i].offset );
			//check to see if this is .strtab or .shstrtab
			if (sHeaders[i].nameIndex <= sHeaders[i].size) {
				//dprintf("%d <= %d\n", sHeaders[i].nameIndex,sHeaders[i].size);
				sectionStringTable = &elfData[sHeaders[i].offset];
				//if our name is not .shstrtab then we're .strtab
				if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".shstrtab") != 0) {
					//dprintf("we're not shstrtab (%s)\n", &sectionStringTable[sHeaders[i].nameIndex]);
					elfStringTable = sectionStringTable;
					sectionStringTable = NULL;
				}
			} else {
				elfStringTable = &elfData[sHeaders[i].offset];
			}
		}

	//determine name of executable
	for (i = 0; i < header->numSectionHeaderEntries; i++) {
		if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".rodata.sceModuleInfo") == 0) {
			moduleInfo = (SceModuleInfo*)&elfData[sHeaders[i].offset];
			printf("Module name: %s\n", moduleInfo->name);
		}
	}
	
	//enumerate section headers
	for (i = 0; i < header->numSectionHeaderEntries; i++) {
		dprintf("Section %d: '%s' (%d bytes)\n", i, &sectionStringTable[sHeaders[i].nameIndex], sHeaders[i].size);
		if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".lib.stub") == 0) {
			libStub = &elfData[sHeaders[i].offset];
		} else if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".lib.stub.btm") == 0) {
			libStubBtm = &elfData[sHeaders[i].offset];
		} else if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".rodata.sceResident") == 0) {
			sceResident = &elfData[sHeaders[i].offset];
		} else if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".rodata.sceNid") == 0) {
			sceNid = (u32*)&elfData[sHeaders[i].offset];
		} else if (strcmp(&sectionStringTable[sHeaders[i].nameIndex], ".text") == 0) {
			text = &elfData[sHeaders[i].offset];
			textSize = sHeaders[i].size;
		}
	}
	
	//print out imports
	printf("Found %d imports:\n", (int)(libStubBtm-libStub)/sizeof(SceLibStubEntry));
	u8 *stubPos = libStub;
	SceLibStubEntry* stubEntry;
	if (stubPos) {
		while (stubPos < libStubBtm) {
			stubEntry = (SceLibStubEntry*)stubPos;
			printf("\t%s\n", &text[stubEntry->moduleNameSymbol]);//, stubEntry->moduleNameSymbol );
			for(i = 0; i < stubEntry->numFuncs; i++) {
				printf("\t\t0x%08X\n", *(long*)&text[stubEntry->nidData+4*i]);
			}
			printf("\n");
			stubPos += sizeof(SceLibStubEntry);
		}
	}
	
	//do disassembly
	printf("Disassembly:\n");

	//setup disasm struct
	init_disassemble_info(&dinfo, stdout, (fprintf_ftype)fprintf);
	dinfo.flavour = bfd_target_elf_flavour;
	dinfo.arch = bfd_mach_mips_allegrex;
	dinfo.mach = bfd_mach_mips_allegrex;
	
	dinfo.read_memory_func = libopcodes_read_mem;
	dinfo.print_address_func = libopcodes_print_addr;
	//don't need these functions yet.
	/*
	dinfo.memory_error_func = libopcodes_mem_error;
	dinfo.symbol_at_address_func = libopcodes_symbol_at_addr;
	dinfo.symbol_is_valid = libopcodes_symbol_is_valid;
	*/
	int bytecount = 0;
	while (bytecount < textSize) {
		printf("\n0x%08X: ", bytecount);
		dinfo.insn_info_valid = 0;
		bytecount += print_insn_little_mips((bfd_vma)(u32)&text[bytecount], &dinfo);
		if (dinfo.insn_info_valid != 0) {
			
		}
//		printf("\ndisasm ate %d bytes\n", );
	}
	free(elfData);
	fclose(in);
}
