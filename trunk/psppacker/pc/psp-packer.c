/*
 * PSPPacker
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPPacker root for details.
 *
 * psp-packer.c - PSPPacker PC side tool
 *
 * Copyright (c) 2006 TyRaNiD
 *
 * $HeadURL$
 * $Id$
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <zlib.h>
#include <stdlib.h>
#include "pspstub.h"
#include "../pspstub/psppacker.h"

#define TEMP_FILE "tmpPack"

int g_verbose = 0;

#define VPRINTF(fmt, ...) if(g_verbose) fprintf(stderr, fmt, ## __VA_ARGS__)

struct Config
{
	const char *input;
	const char *output;
	const char *stub;
	int depack;
};

int parse_args(int argc, char **argv, struct Config *cnf)
{
	int ret = 1;

	memset(cnf, 0, sizeof(*cnf));

	while(1)
	{
		int ch;

		ch = getopt(argc, argv, "vds:o:");
		if(ch == -1)
		{
			break;
		}

		switch(ch)
		{
			case 'v': g_verbose = 1;
					  break;
			case 's': cnf->stub = optarg;
					  break;
			case 'o': cnf->output = optarg;
					  break;
			case 'd': cnf->depack = 1;
					  break;
			default : ret = 0;
					  break;
		};

		if(ret == 0)
		{
			break;
		}
	}

	argc -= optind;
	argv += optind;

	if(argc >= 1)
	{
		cnf->input = argv[0];
		if(cnf->output == NULL)
		{
			cnf->output = cnf->input;
		}
		VPRINTF("Input %s - Output %s\n", cnf->input, cnf->output);
	}
	else
	{
		fprintf(stderr, "Error, not provided input argument\n");
		ret = 0;
	}

	return ret;
}

void print_help(void)
{
	fprintf(stderr, "PSPPacker v%d.%d (c) TyRaNiD 2k6\n", VER_MAJ, VER_MIN);
	fprintf(stderr, "Usage: packelf [options] input.elf\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-s stub        : Specify stub file\n");
	fprintf(stderr, "-o output.elf  : Output file name (default to input name)\n");
	fprintf(stderr, "-d             : Depack mode\n");
	fprintf(stderr, "-v             : Verbose mode\n");
}

void write_le_int(unsigned int val, void *data)
{
	unsigned char *p = data;

	p[0] = val & 0xFF;
	p[1] = (val >> 8) & 0xFF;
	p[2] = (val >> 16) & 0xFF;
	p[3] = (val >> 24) & 0xFF;
}

unsigned int read_le_int(void *data)
{
	unsigned char *p = data;

	return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

void *load_file(const char *name, unsigned int *size)
{
	struct stat st;
	void *pRet = NULL;
	FILE *fp;
	
	do
	{
		if(stat(name, &st) < 0)
		{
			fprintf(stderr, "Input file %s does not exist\n", name);
			break;
		}

		*size = st.st_size;
		pRet = malloc(st.st_size);
		if(pRet == NULL)
		{
			fprintf(stderr, "Could not allocate memory for file %s\n", name);
			break;
		}

		fp = fopen(name, "rb");
		if(fp == NULL)
		{
			fprintf(stderr, "Could not open %s\n", name);
			free(pRet);
			pRet = NULL;
			break;
		}

		fread(pRet, 1, *size, fp);
		fclose(fp);

		VPRINTF("Loading %s (%d bytes)\n", name, *size);
	}
	while(0);

	return pRet;
}

int output_elf(const struct Config *cnf)
{
	FILE *fp = NULL;
	gzFile gz = NULL;
	unsigned int data_size;
	unsigned int unpacked_size;
	void *data = NULL;
	void *stub = NULL;
	unsigned int stub_size;
	int ret = 1;
	struct PackHeader ph;

	do
	{
		data = load_file(cnf->input, &unpacked_size);
		if(data == NULL)
		{
			break;
		}

		gz = gzopen(TEMP_FILE, "wb9");
		if(gz == NULL)
		{
			fprintf(stderr, "Could not create temporary gzip file\n");
			break;
		}

		gzwrite(gz, data, unpacked_size);
		gzclose(gz);
		gz = NULL;
		free(data);
		data = NULL;

		data = load_file(TEMP_FILE, &data_size);
		unlink(TEMP_FILE);

		if(data == NULL)
		{
			break;
		}

		if(cnf->stub == NULL)
		{
			stub_size = size_pspstub;
			stub = malloc(stub_size);
			if(stub == NULL)
			{
				fprintf(stderr, "Could not allocate memory for stub\n");
				break;
			}
			memcpy(stub, pspstub, stub_size);
		}
		else
		{
			stub = load_file(cnf->stub, &stub_size);
			if(stub == NULL)
			{
				break;
			}
		}

		fp = fopen(cnf->output, "wb");
		if(fp == NULL)
		{
			fprintf(stderr, "Could not open output file %s\n", cnf->output);
			break;
		}

		memcpy(ph.magic, PACKER_MAGIC, 4);
		write_le_int(unpacked_size, &ph.unpacked_size);
		write_le_int(data_size, &ph.packed_size);

		/* Write stub, then compressed elf then pack header */
		fwrite(stub, 1, stub_size, fp);
		fwrite(data, 1, data_size, fp);
		fwrite(&ph, 1, sizeof(ph), fp);

		fclose(fp);
		fp = NULL;

		ret = 0;

		printf("Compressed file, unpacked %d, packed %d (%0.2f%%)\n",
				unpacked_size, (stub_size+data_size+sizeof(ph)),
				100.0f * (float)(stub_size+data_size+sizeof(ph)) / (float)unpacked_size);
	}
	while(0);

	if(fp != NULL)
	{
		fclose(fp);
	}

	if(data != NULL)
	{
		free(data);
	}

	if(stub != NULL)
	{
		free(stub);
	}

	return ret;
}

int depack_elf(struct Config *cnf)
{
	void *data = NULL;
	unsigned int data_size;
	unsigned int packed_size;
	unsigned int unpacked_size;
	struct PackHeader ph;
	int ret = 1;
	FILE *fp = NULL;
	gzFile gz;

	do
	{
		data = load_file(cnf->input, &data_size);
		if(data == NULL)
		{
			break;
		}

		if(data_size < sizeof(ph))
		{
			fprintf(stderr, "File not big enough for a packed elf\n");
			break;
		}

		memcpy(&ph, data + (data_size - sizeof(ph)), sizeof(ph));
		if(memcmp(ph.magic, PACKER_MAGIC, 4) != 0)
		{
			fprintf(stderr, "Invalid packer magic\n");
			break;
		}

		packed_size = read_le_int(&ph.packed_size);
		unpacked_size = read_le_int(&ph.unpacked_size);

		VPRINTF("Packed %d - Unpacked %d\n", ph.packed_size, ph.unpacked_size);

		fp = fopen(TEMP_FILE, "wb");
		if(fp == NULL)
		{
			fprintf(stderr, "Could not open temporary file %s\n", TEMP_FILE);
			break;
		}

		fwrite(data + (data_size - packed_size - sizeof(ph)), 1, packed_size, fp);
		fclose(fp);

		free(data);
		data = malloc(unpacked_size);
		if(data == NULL)
		{
			fprintf(stderr, "Could not allocate unpacked memory\n");
			break;
		}

		gz = gzopen(TEMP_FILE, "rb");
		if(gz == NULL)
		{
			fprintf(stderr, "Could not open temporary file for reading\n");
			break;
		}

		if(gzread(gz, data, unpacked_size) != unpacked_size)
		{
			fprintf(stderr, "Could not unpack data\n");
			break;
		}
		gzclose(gz);
		gz = NULL;

		fp = fopen(cnf->output, "wb");
		if(fp == NULL)
		{
			fprintf(stderr, "Could not open output file %s\n", cnf->output);
			break;
		}

		fwrite(data, 1, unpacked_size, fp);
		fclose(fp);
		fp = NULL;

		printf("Written %d bytes\n", unpacked_size);

		ret = 0;
	}
	while(0);

	unlink(TEMP_FILE);

	if(fp != NULL)
	{
		fclose(fp);
	}

	if(gz != NULL)
	{
		gzclose(gz);
	}

	if(data != NULL)
	{
		free(data);
	}

	return ret;
}

int main(int argc, char **argv)
{
	struct Config cnf;
	int ret = 0;

	if(parse_args(argc, argv, &cnf))
	{
		if(cnf.depack)
		{
			ret = depack_elf(&cnf);
		}
		else
		{
			ret = output_elf(&cnf);
		}
	}
	else
	{
		print_help();
		ret = 1;
	}

	return ret;
}
