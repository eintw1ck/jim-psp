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
#include "nidDb.h"

int main(int argc, char *argv[]) {
	FILE *in;
	elfHeader *header = NULL;
	sectionHeader *sHeaders = NULL;
	u8 *elfData;
	char elfType[32];
	u8 *sectionStringTable = NULL;
	u8 *libStub = NULL;
	u8 *libStubBtm = NULL;
	u8 *sceResident = NULL;
	u8 *text = NULL;
	u32 textSize = 0;
	sectionHeader * textSection = NULL;
	u32 *sceNid = NULL;
	u32 i;
	size_t elfDataSize = 0;
	SceModuleInfo *moduleInfo = NULL;
	disassemble_info dinfo;
	xref_type xrefs;
	nidDb nids;
	
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
	
	//Load XML NID List
	nids.loadFromXml("../libdoc/psplibdoc.xml");
	//get section header string table (.shstrtab)
	sectionStringTable = &elfData[sHeaders[header->sectionHeaderStringTableIndex].offset];
	
	//determine module name
	for (i = 0; i < header->numSectionHeaderEntries; i++) {
		if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], ".rodata.sceModuleInfo") == 0) {
			moduleInfo = (SceModuleInfo*)&elfData[sHeaders[i].offset];
			printf("Module name: %s\n", moduleInfo->name);
		}
	}
	
	//enumerate section headers
	for (i = 0; i < header->numSectionHeaderEntries; i++) {
		dprintf("Section %u: '%s' (%u bytes)\n", (unsigned int)i, &sectionStringTable[sHeaders[i].nameIndex], (unsigned int)sHeaders[i].size);
		if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], ".lib.stub") == 0) {
			libStub = &elfData[sHeaders[i].offset];
		} else if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], ".lib.stub.btm") == 0) {
			libStubBtm = &elfData[sHeaders[i].offset];
		} else if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], ".rodata.sceResident") == 0) {
			sceResident = &elfData[sHeaders[i].offset];
		} else if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], ".rodata.sceNid") == 0) {
			sceNid = (u32*)&elfData[sHeaders[i].offset];
		} else if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], ".text") == 0) {
			text = &elfData[sHeaders[i].offset];
			textSize = sHeaders[i].size;
			textSection = &sHeaders[i];
		} else if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], "sdgsdg") == 0) {
		} else if (strcmp((const char *)&sectionStringTable[sHeaders[i].nameIndex], "dsfgsd") == 0) {
		}
	}
	
	//print out imports
	printf("Found %d imports:\n", (int)(libStubBtm-libStub)/sizeof(SceLibStubEntry));
	u8 *stubPos = libStub;
	SceLibStubEntry* stubEntry;
	if (stubPos) {
		while (stubPos < libStubBtm) {
			char *libName;
			stubEntry = (SceLibStubEntry*)stubPos;
			libName = (char *)&text[stubEntry->moduleNameSymbol];
			printf("\t%s\n", libName);
			for(i = 0; i < stubEntry->numFuncs; i++) {
				printf("\t\t0x%08X %s (%s)\n", *(unsigned int*)&text[stubEntry->nidData+4*i], nids.resolveNid(libName, *(u32*)&text[stubEntry->nidData+4*i]), nids.getNidType(libName, *(u32*)&text[stubEntry->nidData+4*i]) == nidType_Function ? "Function" : "Variable");
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
	dinfo.arch = (bfd_architecture) bfd_mach_mips_allegrex;
	dinfo.mach = bfd_mach_mips_allegrex;
	disassemble_init_for_target(&dinfo);
	
	printf("data in buffer at 0x%08X, section vma is 0x%08X, length is %u\n", (unsigned int)text, (unsigned int)textSection->address, (unsigned int)textSize);
	dinfo.buffer = text;
	dinfo.buffer_vma = textSection->address;
	dinfo.buffer_length = textSize;

	dinfo.print_address_func = libopcodes_print_addr;
	/*
	//don't need these functions yet.
	dinfo.symbol_at_address_func = libopcodes_symbol_at_addr;
	dinfo.symbol_is_valid = libopcodes_symbol_is_valid;
	*/
	u32 bytecount = 0;
	while (bytecount < textSize) {
		int increment = 0;
		printf("\n0x%08X: ", (unsigned int)bytecount);
		dinfo.insn_info_valid = 0;
		increment += print_insn_little_mips((bfd_vma)bytecount, &dinfo);
		if (dinfo.insn_info_valid != 0) {
			if (dinfo.insn_type == dis_branch ||
			    dinfo.insn_type == dis_condbranch ||
			    dinfo.insn_type == dis_jsr ||
			    dinfo.insn_type == dis_condjsr) {
			    	//fixme: msotly special cased atm
			    	//ignore xrefs to 0x00000000 unless they're straight to 0 or a relative jump to 0 (todo)
			    	int instr = *(u32*)&text[bytecount];
			    	if(dinfo.target != 0 || dinfo.target == 0 && (instr & 0x00FFFFFF) == 0) {
					xrefs[dinfo.target].push_back(bytecount);
				}
			}
		}
		bytecount += increment;
	}
	
	//print xrefs
	printf("\n\nxref report\n");
	for (xref_type::iterator it = xrefs.begin(); it != xrefs.end(); ++it) {
		printf("%u xrefs for addr 0x%08X\n", (unsigned int)(*it).second.size(), (unsigned int)(*it).first);
		for(size_t i = 0; i < (*it).second.size(); i++)
			printf("\t0x%08X\n", (unsigned int)(*it).second[i]);
	}
	free(elfData);
	fclose(in);
}
