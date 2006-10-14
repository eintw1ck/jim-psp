/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * config.c - PSPLINK kernel module configuration loader.
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 * Copyright (c) 2005 Julian T <lovely@crm114.net>
 *
 * $HeadURL$
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <pspumd.h>
#include <psputilsforkernel.h>
#include <pspsysmem_kernel.h>
#include <usbhostfs.h>
#include "memoryUID.h"
#include "psplink.h"
#include "psplinkcnf.h"
#include "parse_args.h"
#include "util.h"
#include "sio.h"
#include "shell.h"
#include "disasm.h"
#include "config.h"

struct psplink_config
{
	const char *name;
	int   isnum;
	void (*handler)(struct ConfigContext *ctx, const char *szVal, unsigned int iVal);
};

static void config_baud(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	int valid = 0;

	switch(iVal)
	{
		case 4800:
		case 9600:
		case 19200:
		case 38400:
		case 57600:
		case 115200: valid = 1;
					 break;
		default: break;
	};

	if(valid)
	{
		Kprintf("Setting baud to %d\n", iVal);
		ctx->baudrate = iVal;
	}
	else
	{
		Kprintf("Invalid baud rate %d\n", iVal);
		/* Set a default */
		ctx->baudrate = DEFAULT_BAUDRATE;

	}
}

static void config_modload(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	(void) load_start_module(szVal, 0, NULL);
}

static void config_pluser(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	ctx->enableuser = iVal;
}

static void config_prompt(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	strncpy(ctx->cliprompt, szVal, sizeof(ctx->cliprompt)-1);
	ctx->cliprompt[sizeof(ctx->cliprompt)-1] = 0;
}

static void config_startsh(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	strncpy(ctx->startsh, szVal, sizeof(ctx->startsh)-1);
	ctx->startsh[sizeof(ctx->startsh)-1] = 0;
}

static void config_path(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	strncpy(ctx->path, szVal, sizeof(ctx->path)-1);
	ctx->path[sizeof(ctx->path)-1] = 0;
}

static void config_resetonexit(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	ctx->resetonexit = iVal;
}

static void config_disopt(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	disasmSetOpts(szVal, 1);
}

static void config_kprintf(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	ctx->kprintf = iVal;
}

static void config_pid(struct ConfigContext *ctx, const char *szVal, unsigned int iVal)
{
	ctx->pid = iVal;
}

struct psplink_config config_names[] = {
	{ "baud", 1, config_baud },
	{ "modload", 0, config_modload },
	{ "pluser", 1, config_pluser },
	{ "prompt", 0, config_prompt },
	{ "resetonexit", 1, config_resetonexit },
	{ "pid", 1, config_pid },
	{ "startsh", 0, config_startsh },
	{ "path", 0, config_path },
	{ "disopt", 0, config_disopt },
	{ "kprintf", 1, config_kprintf },
	{ NULL, 0, NULL }
};

void configLoad(const char *bootpath, struct ConfigContext *ctx)
{
	char cnf_path[256];
	struct ConfigFile cnf;

	memset(ctx, 0, sizeof(*ctx));
	strcpy(cnf_path, bootpath);
	strcat(cnf_path, "psplink.ini");
	Kprintf("Config Path %s\n", cnf_path);
	if(psplinkConfigOpen(cnf_path, &cnf))
	{
		const char *name;
		const char *val;

		while((val = psplinkConfigReadNext(&cnf, &name)))
		{
			int config;

			config = 0;
			while(config_names[config].name)
			{
				if(strcmp(config_names[config].name, name) == 0)
				{
					unsigned int iVal = 0;
					if(config_names[config].isnum)
					{
						char *endp;

						iVal = strtoul(val, &endp, 0);
						if(*endp != 0)
						{
							Kprintf("Error, line %d value should be a number\n", cnf.line); 
							break;
						}
					}

					config_names[config].handler(ctx, val, iVal);
				}
				config++;
			}

			/* Ignore anything we don't care about */
		}

		psplinkConfigClose(&cnf);
	}
}

void configPrint(const char *bootpath)
{
	char cnf_path[256];
	struct ConfigFile cnf;

	strcpy(cnf_path, bootpath);
	strcat(cnf_path, "psplink.ini");
	Kprintf("Config Path %s\n", cnf_path);
	if(psplinkConfigOpen(cnf_path, &cnf))
	{
		const char *name;
		const char *val;

		while((val = psplinkConfigReadNext(&cnf, &name)))
		{
			Kprintf("%s=%s\n", name, val);
		}

		psplinkConfigClose(&cnf);
	}
}

void configChange(const char *bootpath, const char *newname, const char *newval, int mode)
{
	char cnf_path[256];
	char new_path[256];
	int found = 0;
	struct ConfigFile cnf;
	int fd = -1;

	if((mode != CONFIG_MODE_ADD) && (mode != CONFIG_MODE_DEL))
	{
		return;
	}

	strcpy(cnf_path, bootpath);
	strcat(cnf_path, "psplink.ini");
	Kprintf("Config Path %s\n", cnf_path);

	strcpy(new_path, bootpath);
	strcat(new_path, "psplink.ini.tmp");
	fd = sceIoOpen(new_path, PSP_O_WRONLY | PSP_O_TRUNC | PSP_O_CREAT, 0777);
	if(fd >= 0)
	{
		if(psplinkConfigOpen(cnf_path, &cnf))
		{
			const char *name;
			const char *val;

			while((val = psplinkConfigReadNext(&cnf, &name)))
			{
				if(strcmp(name, newname) == 0)
				{
					if(mode == CONFIG_MODE_ADD)
					{
						fdprintf(fd, "%s=\"%s\"\n", newname, newval);
						found = 1;
					}
				}
				else
				{
					fdprintf(fd, "%s=\"%s\"\n", name, val);
				}
			}

			if((mode == CONFIG_MODE_ADD) && (!found))
			{
				fdprintf(fd, "%s=\"%s\"\n", newname, newval);
			}

			sceIoClose(fd);
			fd = -1;
			psplinkConfigClose(&cnf);

			if(sceIoRemove(cnf_path) < 0)
			{
				SHELL_PRINT("Error deleting original configuration\n");
			}
			else
			{
				if(sceIoRename(new_path, cnf_path) < 0)
				{
					SHELL_PRINT("Error renaming configuration\n");
				}
			}
		}
		else
		{
			SHELL_PRINT("Couldn't open temporary config file %s\n", new_path);
		}

		if(fd >= 0)
		{
			sceIoClose(fd);
			sceIoRemove(new_path);
		}
	}
}
