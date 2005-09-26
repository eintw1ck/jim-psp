/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psp-fixup-imports.c - Simple program to fixup an ELF's imports
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id$
 */

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "types.h"
#include "elftypes.h"
#include "prxtypes.h"

#define PRX_LIBSTUB_SECT  ".lib.stub"
#define PRX_STUBTEXT_SECT ".sceStub.text"
#define PRX_NID_SECT      ".rodata.sceNid"

static const char *g_outfile;
static const char *g_infile;
static unsigned char *g_elfdata = NULL;
static unsigned int  g_elfsize;
static struct ElfHeader g_elfhead = {0};
static struct ElfSection *g_elfsections = NULL;
static struct ElfSection *g_modinfo = NULL;
static struct ElfSection *g_libstub = NULL;
static struct ElfSection *g_stubtext = NULL;
static struct ElfSection *g_nid = NULL;

/* Specifies that the current usage is to the print the pspsdk path */
static int g_verbose = 0;

static struct option arg_opts[] = 
{
	{"output", required_argument, NULL, 'o'},
	{"verbose", no_argument, NULL, 'v'},
	{ NULL, 0, NULL, 0 }
};

/* Process the arguments */
int process_args(int argc, char **argv)
{
	int ch;

	g_outfile = NULL;
	g_infile = NULL;

	ch = getopt_long(argc, argv, "vo:", arg_opts, NULL);
	while(ch != -1)
	{
		switch(ch)
		{
			case 'v' : g_verbose = 1;
					   break;
			case 'o' : g_outfile = optarg;
					   break;
			default  : break;
		};

		ch = getopt_long(argc, argv, "vo:", arg_opts, NULL);
	}

	argc -= optind;
	argv += optind;

	if(argc < 1)
	{
		return 0;
	}

	g_infile = argv[0];

	if(g_outfile == NULL)
	{
		g_outfile = argv[0];
	}

	if(g_verbose)
	{
		fprintf(stderr, "Loading %s, outputting to %s\n", g_infile, g_outfile);
	}

	return 1;
}

void print_help(void)
{
	fprintf(stderr, "Usage: psp-fixup-imports [-v] [-o outfile.elf] infile.elf\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-o, --output outfile    : Output to a different file\n");
	fprintf(stderr, "-v, --verbose           : Verbose output\n");
}

unsigned char *load_file(const char *file, unsigned int *size)
{
	FILE *fp;
	unsigned char *data = NULL;

	do
	{
		fp = fopen(file, "rb");
		if(fp != NULL)
		{
			(void) fseek(fp, 0, SEEK_END);
			*size = ftell(fp);
			rewind(fp);

			if(*size < sizeof(Elf32_Ehdr))
			{
				fprintf(stderr, "Error, invalid file size\n");
				break;
			}

			data = (unsigned char *) malloc(*size);
			if(data == NULL)
			{
				fprintf(stderr, "Error, could not allocate memory for ELF\n");
				break;
			}

			(void) fread(data, 1, *size, fp);
			fclose(fp);
		}
		else
		{
			fprintf(stderr, "Error, could not find file %s\n", file);
		}
	}
	while(0);

	return data;
}

/* Validate the ELF header */
int validate_header(unsigned char *data)
{
	Elf32_Ehdr *head;
	int ret = 0;

	head = (Elf32_Ehdr*) data;

	do
	{
		/* Read in the header structure */
		g_elfhead.iMagic = LW(head->e_magic);
		g_elfhead.iClass = head->e_class;
		g_elfhead.iData = head->e_data;
		g_elfhead.iIdver = head->e_idver;
		g_elfhead.iType = LH(head->e_type);
		g_elfhead.iMachine = LH(head->e_machine);
		g_elfhead.iVersion = LW(head->e_version);
		g_elfhead.iEntry = LW(head->e_entry);
		g_elfhead.iPhoff = LW(head->e_phoff);
		g_elfhead.iShoff = LW(head->e_shoff);
		g_elfhead.iFlags = LW(head->e_flags);
		g_elfhead.iEhsize = LH(head->e_ehsize);
		g_elfhead.iPhentsize = LH(head->e_phentsize);
		g_elfhead.iPhnum = LH(head->e_phnum);
		g_elfhead.iShentsize = LH(head->e_shentsize);
		g_elfhead.iShnum = LH(head->e_shnum);
		g_elfhead.iShstrndx = LH(head->e_shstrndx);

		if(g_verbose)
		{
			fprintf(stderr, "Magic %08X, Class %02X, Data %02X, Idver %02X\n", g_elfhead.iMagic,
					g_elfhead.iClass, g_elfhead.iData, g_elfhead.iIdver);
			fprintf(stderr, "Type %04X, Machine %04X, Version %08X, Entry %08X\n", g_elfhead.iType,
					g_elfhead.iMachine, g_elfhead.iVersion, g_elfhead.iEntry);
			fprintf(stderr, "Phoff %08X, Shoff %08X, Flags %08X, Ehsize %08X\n", g_elfhead.iPhoff,
					g_elfhead.iShoff, g_elfhead.iFlags, g_elfhead.iEhsize);
			fprintf(stderr, "Phentsize %04X, Phnum %04X\n", g_elfhead.iPhentsize, g_elfhead.iPhnum);
			fprintf(stderr, "Shentsize %04X, Shnum %08X, Shstrndx %04X\n", g_elfhead.iShentsize,
					g_elfhead.iShnum, g_elfhead.iShstrndx);
		}

		if(g_elfhead.iMagic != ELF_MAGIC)
		{
			fprintf(stderr, "Error, invalid magic in the header\n");
			break;
		}

		if((g_elfhead.iType != ELF_EXEC_TYPE) && (g_elfhead.iType != ELF_PRX_TYPE))
		{
			fprintf(stderr, "Error, not EXEC type elf\n");
			break;
		}

		if(g_elfhead.iMachine != ELF_MACHINE_MIPS)
		{
			fprintf(stderr, "Error, not MIPS type ELF\n");
			break;
		}

		if(g_elfhead.iShnum < g_elfhead.iShstrndx)
		{
			fprintf(stderr, "Error, number of headers is less than section string index\n");
			break;
		}

		ret = 1;
	}
	while(0);

	return ret;
}

/* Load sections into ram */
int load_sections(unsigned char *data)
{
	int ret = 0;
	int found_rel = 0;
	unsigned int load_addr = 0xFFFFFFFF;

	if(g_elfhead.iShnum > 0)
	{
		do
		{
			Elf32_Shdr *sect;
			int i;

			g_elfsections = (struct ElfSection *) malloc(sizeof(struct ElfSection) * g_elfhead.iShnum);
			if(g_elfsections == NULL)
			{
				fprintf(stderr, "Error, could not allocate memory for sections\n");
				break;
			}

			memset(g_elfsections, 0, sizeof(struct ElfSection) * g_elfhead.iShnum);

			for(i = 0; i < g_elfhead.iShnum; i++)
			{
				sect = (Elf32_Shdr *) (g_elfdata + g_elfhead.iShoff + (i * g_elfhead.iShentsize));

				g_elfsections[i].iName = LW(sect->sh_name);
				g_elfsections[i].iType = LW(sect->sh_type);
				g_elfsections[i].iAddr = LW(sect->sh_addr);
				g_elfsections[i].iFlags = LW(sect->sh_flags);
				g_elfsections[i].iOffset = LW(sect->sh_offset);
				g_elfsections[i].iSize = LW(sect->sh_size);
				g_elfsections[i].iLink = LW(sect->sh_link);
				g_elfsections[i].iInfo = LW(sect->sh_info);
				g_elfsections[i].iAddralign = LW(sect->sh_addralign);
				g_elfsections[i].iEntsize = LW(sect->sh_entsize);
				g_elfsections[i].iIndex = i;

				if(g_elfsections[i].iOffset != 0)
				{
					g_elfsections[i].pData = g_elfdata + g_elfsections[i].iOffset;
				}

				if(g_elfsections[i].iFlags & SHF_ALLOC)
				{
					g_elfsections[i].blOutput = 1;
					if(g_elfsections[i].iAddr < load_addr)
					{
						load_addr = g_elfsections[i].iAddr;
					}
				}

				if(((g_elfsections[i].iType == SHT_REL) || (g_elfsections[i].iType == SHT_PRXRELOC)) 
						&& (g_elfsections[g_elfsections[i].iInfo].iFlags & SHF_ALLOC))
				{
					g_elfsections[i].pRef = &g_elfsections[g_elfsections[i].iInfo];
					found_rel = 1;
				}
			}

			/* Okay so we have loaded all the sections, lets fix up the names */
			for(i = 0; i < g_elfhead.iShnum; i++)
			{
				strcpy(g_elfsections[i].szName, g_elfsections[g_elfhead.iShstrndx].pData + g_elfsections[i].iName);
				if(strcmp(g_elfsections[i].szName, PSP_MODULE_INFO_NAME) == 0)
				{
					g_modinfo = &g_elfsections[i];
				}
				else if(strcmp(g_elfsections[i].szName, PRX_LIBSTUB_SECT) == 0)
				{
					g_libstub = &g_elfsections[i];
				}
				else if(strcmp(g_elfsections[i].szName, PRX_STUBTEXT_SECT) == 0)
				{
					g_stubtext = &g_elfsections[i];
				}
				else if(strcmp(g_elfsections[i].szName, PRX_NID_SECT) == 0)
				{
					g_nid = &g_elfsections[i];
				}
			}

			if(g_verbose)
			{
				for(i = 0; i < g_elfhead.iShnum; i++)
				{
					fprintf(stderr, "\nSection %d: %s\n", i, g_elfsections[i].szName);
					fprintf(stderr, "Name %08X, Type %08X, Flags %08X, Addr %08X\n", 
							g_elfsections[i].iName, g_elfsections[i].iType,
							g_elfsections[i].iFlags, g_elfsections[i].iAddr);
					fprintf(stderr, "Offset %08X, Size %08X, Link %08X, Info %08X\n", 
							g_elfsections[i].iOffset, g_elfsections[i].iSize,
							g_elfsections[i].iLink, g_elfsections[i].iInfo);
					fprintf(stderr, "Addralign %08X, Entsize %08X pData %p\n", 
							g_elfsections[i].iAddralign, g_elfsections[i].iEntsize,
							g_elfsections[i].pData);
				}

				fprintf(stderr, "ELF Load Base address %08X\n", load_addr);
			}

			if(g_modinfo == NULL)
			{
				fprintf(stderr, "Error, no sceModuleInfo section found\n");
				break;
			}

			if(g_libstub == NULL)
			{
				fprintf(stderr, "Error, no .lib.stub section found\n");
				break;
			}

			if(g_stubtext == NULL)
			{
				fprintf(stderr, "Error, no stub text section found\n");
				break;
			}

			if(g_nid == NULL)
			{
				fprintf(stderr, "Error, no nid section found\n");
				break;
			}

			ret = 1;
		}
		while(0);
	}
	else
	{
		fprintf(stderr, "Error, no sections in the ELF\n");
	}

	return ret;
}

/* Load an ELF file */
int load_elf(const char *elf)
{
	int ret = 0;

	do
	{
		g_elfdata = load_file(elf, &g_elfsize);
		if(g_elfdata == NULL)
		{
			break;
		}

		if(!validate_header(g_elfdata))
		{
			break;
		}

		if(!load_sections(g_elfdata))
		{
			break;
		}

		ret = 1;
	}
	while(0);

	return ret;
}

/* Free allocated memory */
void free_data(void)
{
	if(g_elfdata != NULL)
	{
		free(g_elfdata);
		g_elfdata = NULL;
	}

	if(g_elfsections != NULL)
	{
		free(g_elfsections);
		g_elfsections = NULL;
	}
}

#define MIPS_JR_31 0x03e00008
#define MIPS_NOP   0x0

void fixup_imports(void)
{
	unsigned int *pText;
	unsigned int *pNid;
	int count;

	/* First let's check the sizes are correct */
	if(g_stubtext->iSize != (g_nid->iSize * 2))
	{
		fprintf(stderr, "Error, size of text section and nid section do not match\n");
		return;
	}

	count = g_nid->iSize / 4;
	pText = (unsigned int *) g_stubtext->pData;
	pNid = (unsigned int *) g_nid->pData;

	if(g_verbose)
	{
		fprintf(stderr, "Import count %d\n", count);
	}

	while(count > 0)
	{
		unsigned int stub_addr;
		unsigned int stub_nid;
		unsigned int sect_nid;

		stub_addr = LW(pText[0]);
		stub_nid  = LW(pText[1]);
		sect_nid  = LW(pNid[0]);

		/* Check if this is an original format NID */
		if((stub_addr != MIPS_JR_31) || (stub_nid != MIPS_NOP))
		{
			struct PspModuleImport *pImport;
			u16    func_count;

			if(g_verbose)
			{
				fprintf(stderr, "Found import to fixup. pStub %08X, Nid %08X, NidInSect %08X\n", stub_addr, stub_nid, sect_nid);
			}

			if(stub_nid != sect_nid)
			{
				fprintf(stderr, "Error, unmatched NIDs\n");
				break;
			}

			if((stub_addr < g_libstub->iAddr) || (stub_addr > (g_libstub->iAddr + g_libstub->iSize)) || (stub_addr & 3))
			{
				fprintf(stderr, "Error, invalid stub address\n");
				break;
			}

			pImport = (struct PspModuleImport *) (g_libstub->pData + (stub_addr - g_libstub->iAddr));
			if(g_verbose)
			{
				fprintf(stderr, "Import Stub %p, %08X, %08X, %02X, %02X, %04X, %08X, %08X\n", pImport, 
						LW(pImport->name), LW(pImport->flags), pImport->entry_size, pImport->var_count, 
						LH(pImport->func_count), LW(pImport->nids), LW(pImport->funcs));
			}

			func_count = LH(pImport->func_count);

			if(func_count == 0)
			{
				/* Setup the stub */
				SW(&pImport->nids, ((unsigned char *) pNid - g_nid->pData) + g_nid->iAddr);
				SW(&pImport->funcs, ((unsigned char *) pText - g_stubtext->pData) + g_stubtext->iAddr);
			}

			func_count++;
			SH(&pImport->func_count, func_count);
			SW(&pText[0], MIPS_JR_31);
			SW(&pText[1], MIPS_NOP);
		}

		pText += 2;
		pNid++;
		count--;
	}

	/* Should indicate no error occurred */
	if(count == 0)
	{
		FILE *fp;

		fp = fopen(g_outfile, "wb");
		if(fp != NULL)
		{
			(void) fwrite(g_elfdata, 1, g_elfsize, fp);
			fclose(fp);
		}
		else
		{
			fprintf(stderr, "Error, couldn't open %s for writing\n", g_outfile);
		}
	}
}

int main(int argc, char **argv)
{
	if(process_args(argc, argv))
	{
		if(load_elf(g_infile))
		{
			fixup_imports();
			free_data();
		}
	}
	else
	{
		print_help();
	}

	return 0;
}