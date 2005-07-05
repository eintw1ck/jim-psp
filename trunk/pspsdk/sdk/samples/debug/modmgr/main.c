/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate the module manager functions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
PSP_MODULE_INFO("PRXDecryptor", 0x1000, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(0);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

/* Exit callback */
int exit_callback(void)
{
	sceKernelExitGame();

	return 0;
}

/* Callback thread */
void CallbackThread(void *arg)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* ptr is a pointer to the file to decrypt, check is undocumented, look at decrypt_file to see how to use */
int (*sceKernelCheckExecFile)(void *ptr, void *check);

char g_data[0x400000] __attribute__((aligned(64)));
char g_decrypt_buf[0x400000] __attribute__((aligned(64)));

/* Decrypt a single PRX file */
int extract_file(const char* name, const char* dstname)
{
	int fd;
	int ret = 0;

	fd = sceIoOpen(name, PSP_O_RDONLY, 0777);
	if(fd >= 0)
	{
		int bytes_read;
		bytes_read = sceIoRead(fd, g_data, 4*1024*1024);
		sceIoClose(fd);
		if(bytes_read > 0)
		{
			u8 check[0x100];
			u32 size;
			char *output;

			memset(check, 0, sizeof(check));
			sceKernelCheckExecFile(g_data, check);
			/* Get size of data block */
			size = *(unsigned int *) (check+0x5C);

			/* Check if we managed to decrypt the file */
			if(*(unsigned short *)(check+0x5a) & 1)
			{
				/* Set decrypt buffer pointer */
				*(unsigned int*)(check+0x24) = (unsigned int) g_decrypt_buf;
				sceKernelCheckExecFile(g_data, check);
				output = g_decrypt_buf;
			}
			else
			{
				output = g_data;
			}

			if(size >= 0)
			{
				printf("Extracted file - size %d\n", size);
				fd = sceIoOpen(dstname, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
				if(fd >= 0)
				{
					sceIoWrite(fd, output, size);
					sceIoClose(fd);
					ret = 1;
				}
			}
			else
			{
				printf("Extract failed %s\n", name);
			}
		}
		else
		{
			printf("Couldn't read file\n");
		}
	}
	else
	{
		printf("Couldn't open file\n");
	}

	return ret;
}

SceIoDirent g_dir;
char g_infile[256];
char g_outfile[256];

void decrypt_files(const char *basedir, const char *destdir)
{
	int fd;

	printf("%s\n", basedir);
	fd = sceIoDopen(basedir);
	if(fd >= 0)
	{
		while(sceIoDread(fd, &g_dir) > 0)
		{
			if((g_dir.d_stat.st_attr & FIO_SO_IFDIR) == 0)
			{
				strcpy(g_infile, basedir);
				strcat(g_infile, g_dir.d_name);
				strcpy(g_outfile, destdir);
				strcat(g_outfile, g_dir.d_name);
				printf("Decrypting %s to %s\n", g_infile, g_outfile);
				extract_file(g_infile, g_outfile);
			}
		}

		sceIoClose(fd);
	}
}

/* Init our kernel hook, i.e. grab the pointer to sceKernelCheckExecFile */
/* This uses the module manager routines to grab a module and resolved an exported symbol */
/* This should hopefully be pretty portable, until Sony decide to change kernel structures :P */
int init_hooks(void)
{
	SceModuleInfo *mod;
	int ret = 0;

	/* Lookup the load core module by its name. this is the name as given in the module information */
	mod = pspDebugFindModule("sceLoaderCore");
	if(mod != NULL)
	{
		/* We have found the module we were looking for, lets grab the function by name */
		sceKernelCheckExecFile = pspDebugFindExportedFunctionByName(mod, "LoadCoreForKernel", "sceKernelCheckExecFile");
		/* Could also use the nid directly with, 
		   pspDebugFindExportedFunction(mod, "LoadCoreForKernel", 0x7BE1421C); */
		if(sceKernelCheckExecFile != NULL)
		{
			/* Woo, we have our kernel function */
			printf("sceKernelCheckExecFile %p\n", sceKernelCheckExecFile);
			ret = 1;
		}
		else
		{
			printf("Could not find sceKernelCheckExecFile in memory\n");
		}
	}
	else
	{
		printf("Could not find sceLoaderCore in memory\n");
	}

	return ret;
}

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

	if(init_hooks())
	{
		/* Decrypt kernel modules */
		sceIoMkdir("ms0:/kd", 0777);
		decrypt_files("flash0:/kd/", "ms0:/kd/");
		/* Decrypt VShell modules */
		sceIoMkdir("ms0:/vsh", 0777);
		decrypt_files("flash0:/vsh/module/", "ms0:/vsh/");
	}

	printf("Done\n");
	sceKernelExitDeleteThread(0);

	return 0;
}
