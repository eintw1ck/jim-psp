/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * util.c - util functions for psplink
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
#include "psplink.h"
#include "util.h"

enum UsbStates 
{
	USB_NOSTART = 0,
	USB_ON      = 1,
	USB_OFF     = 2
};

/* Indicates whether the usb drivers have been loaded */
static enum UsbStates g_usbstate = USB_NOSTART;

/* Global functions which are setup to point to the correct function
   for the firmware */

extern struct GlobalContext g_context;
int (*g_QueryModuleInfo)(SceUID modid, SceKernelModuleInfo *info) = NULL;
int (*g_GetModuleIdList)(SceUID *readbuf, int readbufsize, int *idcount) = NULL;
extern int g_debuggermode;
extern void set_swbp(u32 addr);

int is_oct(char ch)
{
	if((ch >= '0') && (ch < '8'))
	{
		return 1;
	}

	return 0;
}

int oct_to_int(char ch)
{
	if((ch >= '0') && (ch < '8'))
	{
		return ch - '0';
	}

	return 0;
}

/* Check if character is a hexadecimal character */
int is_hex(char ch)
{
	ch = upcase(ch);

	if((ch >= '0') && (ch <= '9'))
		return 1;

	if((ch >= 'A') && (ch <= 'F'))
		return 1;

	return 0;
}

/* Convert a single hex digit to an int */
int hex_to_int(char ch)
{
	if((ch >= '0') && (ch <= '9'))
	{
		return ch - '0';
	}

	ch = upcase(ch);
	if((ch >= 'A') && (ch <= 'F'))
	{
		return ch - 'A' + 10;
	}

	return 0;
}


int is_aspace(int ch)
{
	if((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r'))
	{
		return 1;
	}

	return 0;
}

/* Normalise the path, remove . and .. directories, will ignore anything at the end with no dir slash */
static int normalize_path(char *path)
{
	char *last_dir = NULL;
	char *curr_pos;
	int ret = 1;

	/* Can't start with an absolute path */
	if(*path == '/')
	{
		ret = 0;
	}
	else
	{
		curr_pos = strchr(path, '/');
		while(curr_pos != NULL)
		{
			if(last_dir != NULL)
			{
				if(strncmp(last_dir, "/.", curr_pos - last_dir) == 0)
				{
					strcpy(last_dir, curr_pos);
					curr_pos = last_dir;
				}
				else if(strncmp(last_dir, "/..", curr_pos - last_dir) == 0)
				{
					char *last_pos;
					/* Find the last directory slash from last_dir */
					last_pos = last_dir - 1;
					while(last_pos > path)
					{
						if(*last_pos == '/')
						{
							break;
						}
						last_pos--;
					}

					if(last_pos > path)
					{
						last_dir = last_pos;
					}

					strcpy(last_dir, curr_pos);
					curr_pos = last_dir;
				}
				else
				{
					/* Ignore */
				}
			}

			last_dir = curr_pos;
			curr_pos = strchr(curr_pos + 1, '/');
		}
	}

	return ret;
}

int handlepath(char *currentdir, char *relative, char *path, int type, int valid)
{
	int len, fd;

	/* Strip whitespace and append a final slash */
	path[0] = 0;
	if(strchr(relative, ':') == NULL)
	{
		if(relative[0] == '/')
		{
			int currdir_pos = 0;
			int path_pos = 0;
			while(currentdir[currdir_pos] != 0)
			{
				path[path_pos] = currentdir[currdir_pos];
				if(currentdir[currdir_pos] == ':')
				{
					path[path_pos + 1] = 0;
					break;
				}
				currdir_pos++;
				path_pos++;
			}
		}
		else
		{
			/* relative directory */
			strcpy(path, currentdir);
		}
	}

	strcat(path, relative);
	len = strlen(path);
	while((len > 0) && (is_aspace(path[len-1])))
	{
		path[len-1] = 0;
		len--;
	}

	/* Very unsafe, but still */
	if(type == TYPE_DIR && path[len-1] != '/') {
		path[len] = '/';
		path[len+1] = 0;
	} else if(type == TYPE_FILE && path[len] == '/') {
		path[len] = 0;
	}

	if(normalize_path(path) == 0)
		return 0;

	if(valid) {
		if(type == TYPE_DIR) {
			if((fd = sceIoDopen(path)) < 0) {
				/* Invalid Directory */
				return 0;
			} else {
				sceIoDclose(fd);
			}
		} else if(type == TYPE_FILE) {
			if((fd = sceIoOpen(path, PSP_O_RDONLY, 0777)) < 0) {
				/* Invalid File */
				return 0;
			} else {
				sceIoClose(fd);
			}
		} else {
			printf("unable to validate ether type\n");
			return 0;
		}
	}

	return 1;
}

/* Make the character upper case */
char upcase(char ch)
{
	if((ch >= 'a') && (ch <= 'z'))
	{
		ch ^= (1 << 5);
	}

	return ch;
}

int build_bootargs(char *args, const char *bootfile, const char *execfile, int argc, char **argv)
{
	int loc = 0;
	int i;

	strcpy(args, bootfile);
	loc += strlen(bootfile) + 1;
	if(execfile != NULL)
	{
		strcpy(&args[loc], execfile);
		loc += strlen(execfile) + 1;
		for(i = 0; i < argc; i++)
		{
			strcpy(&args[loc], argv[i]);
			loc += strlen(argv[i]) + 1;
		}
	}

	return loc;
}

int build_args(char *args, const char *execfile, int argc, char **argv)
{
	int loc = 0;
	int i;

	strcpy(args, execfile);
	loc += strlen(execfile) + 1;
	for(i = 0; i < argc; i++)
	{
		strcpy(&args[loc], argv[i]);
		loc += strlen(argv[i]) + 1;
	}

	return loc;
}

int load_start_module(const char *name, int argc, char **argv)
{
	SceUID modid;
	int status;
	char args[1024];
	int len;

	modid = sceKernelLoadModule(name, 0, NULL);
	if(modid >= 0)
	{
		len = build_args(args, name, argc, argv);
		modid = sceKernelStartModule(modid, len, (void *) args, &status, NULL);
		Kprintf("lsm: name '%s' ret %08X\n",name, modid);
	}
	else
	{
		Kprintf("lsm: Error loading module %s %08X\n", name, modid);
	}

	return modid;
}

int load_start_module_debug(const char *name)
{
	SceUID modid;
	int status;

	modid = sceKernelLoadModule(name, 0, NULL);
	if(modid >= 0)
	{
		SceKernelModuleInfo info;
		int ret;

		ret = g_QueryModuleInfo(modid, &info);
		if(ret >= 0)
		{
			//u32 result;

			g_debuggermode = 1;
			stop_usb();
			pspDebugGdbStubInit();

			set_swbp(info.entry_addr);
			sceKernelDcacheWritebackAll();
			sceKernelIcacheInvalidateAll();
			Kprintf("lsmd: using name '%s'\n",name);
			modid = sceKernelStartModule(modid, strlen(name) + 1, (void *)name, &status, NULL);

			//sceKernelWaitEventFlag(g_eventflag, EVENT_RESUMESH, 0x100, &result, NULL);
		}
	}

	return modid;
}

void map_firmwarerev(void)
{
	/* Special case for version 1 firmware */
    if((sceKernelDevkitVersion() & 0xFFFF0000) == 0x01000000)
	{
		g_QueryModuleInfo = pspSdkQueryModuleInfoV1;
		g_GetModuleIdList = pspSdkGetModuleIdList;
	}
	else
	{
		g_QueryModuleInfo = sceKernelQueryModuleInfo;
		g_GetModuleIdList = sceKernelGetModuleIdList;
	}
}

int init_usb(void)
{
	int retVal;

	do
	{
		if(g_usbstate == USB_ON)
		{
			retVal = 0;
			break;
		}

		if(g_usbstate == USB_NOSTART)
		{
			load_start_module("flash0:/kd/semawm.prx", 0, NULL);
			load_start_module("flash0:/kd/usbstor.prx", 0, NULL);
			load_start_module("flash0:/kd/usbstormgr.prx", 0, NULL);
			load_start_module("flash0:/kd/usbstorms.prx", 0, NULL);
			load_start_module("flash0:/kd/usbstorboot.prx", 0, NULL);
		}

		retVal = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
		if (retVal != 0) {
			Kprintf("Error starting USB Bus driver (0x%08X)\n", retVal);
			break;
		}
		retVal = sceUsbStart(PSP_USBSTOR_DRIVERNAME, 0, 0);
		if (retVal != 0) {
			Kprintf("Error starting USB Mass Storage driver (0x%08X)\n",
			   retVal);
			break;
		}
		retVal = sceUsbstorBootSetCapacity(0x800000);
		if (retVal != 0) {
			Kprintf
			("Error setting capacity with USB Mass Storage driver (0x%08X)\n",
			 retVal);
			break;
		}

		retVal = sceUsbActivate(0x1c8);

		if(retVal == 0)
		{
			g_usbstate = USB_ON;
		}
	}
	while(0);

	return retVal;
}

int stop_usb(void)
{
	int retVal;

	if(g_usbstate != USB_ON)
	{
		return 0;
	}

	retVal = sceUsbDeactivate();
	if (retVal != 0) {
	    Kprintf("Error calling sceUsbDeactivate (0x%08X)\n", retVal);
    }

    retVal = sceUsbStop(PSP_USBSTOR_DRIVERNAME, 0, 0);
    if (retVal != 0) {
		Kprintf("Error stopping USB Mass Storage driver (0x%08X)\n",
	       retVal);
	}

    retVal = sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
    if (retVal != 0) {
		Kprintf("Error stopping USB BUS driver (0x%08X)\n", retVal);
	}

	g_usbstate = USB_OFF;

	return 0;
}

void save_execargs(int argc, char **argv)
{
	int i;
	int loc = 0;

	for(i = 0; i < (argc < MAX_ARGS ? argc : MAX_ARGS-1); i++)
	{
		strcpy(&g_context.execargs[loc], argv[i]);
		g_context.execargv[i] = &g_context.execargs[loc];
		loc += strlen(argv[i]) + 1;
	}

	argv[i] = NULL;
	g_context.execargc = argc;
}

int openfile(const char *filename, PspFile *pFile)
{
	int iRet = 0;

	do
	{
		if(pFile == NULL)
		{
			Kprintf("Error, invalid file\n");
			break;
		}

		memset(pFile, 0, sizeof(PspFile));

		pFile->fd = sceIoOpen(filename, PSP_O_RDONLY, 0777);
		if(pFile->fd < 0)
		{
			Kprintf("Error, cannot open file %s\n", filename);
			break;
		}

		iRet = 1;
	}
	while(0);

	return iRet;
}

int closefile(PspFile *pFile)
{
	int iRet = 0;
	do
	{
		if(pFile == NULL)
		{
			Kprintf("Error, invalid configuration structure\n");
			break;
		}

		if(pFile->fd < 0)
		{
			Kprintf("Error, invalid file descriptor\n");
			break;
		}

		sceIoClose(pFile->fd);
		iRet = 1;
	}
	while(0);

	return iRet;
}

/* Seems the kernel's fdgetc is broken :/ */
int fdgetc(PspFile *pFile)
{
	int ch = -1;

	if(pFile->read_size == 0)
	{
		int size;
		size = sceIoRead(pFile->fd, pFile->read_buf, MAX_BUFFER);
		if(size > 0)
		{
			pFile->read_size = size;
			pFile->read_pos = 0;
		}
		else
		{
			pFile->read_size = 0;
			pFile->read_pos = 0;
		}
	}

	if(pFile->read_pos < pFile->read_size)
	{
		ch = pFile->read_buf[pFile->read_pos++];
	}

	return ch;
}

/* As the kernel's fdgetc is broke so is fdgets */
int fdgets(PspFile *pFile, char *buf, int max)
{
	int pos = 0;

	while(pos < (max-1))
	{
		int ch;

		ch = fdgetc(pFile);

		/* EOF */
		if(ch == -1)
		{
			break;
		}

		buf[pos++] = (char) ch;

		if(ch == '\n')
		{
			break;
		}
	}

	buf[pos] = 0;

	return pos;
}

void strip_whitesp(char *s)
{
	int start;
	int end;

	end = strlen(s);
	while(end > 0)
	{
		if(is_aspace(s[end-1]))
		{
			s[end-1] = 0;
		}
		else
		{
			break;
		}
	}

	start = 0;
	while(s[start])
	{
		if(is_aspace(s[start]))
		{
			start++;
		}
		else
		{
			break;
		}
	}

	if(start > 0)
	{
		int pos = 0;
		while(s[start])
		{
			s[pos++] = s[start++];
		}
		s[pos] = 0;
	}
}

int strtoint(const char *str, u32 *i)
{
	char *endp;
	u32 val;

	val = strtoul(str, &endp, 0);
	if(*endp != 0)
	{
		return 0;
	}
	*i = val;

	return 1;
}

int memcmp_mask(void *data1, void *data2, void *mask, int len)
{
	unsigned char *m, *d1, *d2;
	int i;

	m = mask;
	d1 = data1;
	d2 = data2;

	if(m == NULL)
	{
		return memcmp(data1, data2, len);
	}

	for(i = 0; i < len; i++)
	{
		if((d1[i] & m[i]) != d2[i])
		{
			return (d1[i] & m[i]) - d2[i];
		}
	}

	return 0;
}

void* memmem_mask(void *data, void *mask, int len, void *search, int slen)
{
	int i;

	if((data == NULL) || (len < 0) || (search == NULL) || (slen < 0))
	{
		return NULL;
	}

	for(i = 0; i < (len - slen + 1); i++)
	{
		if(memcmp_mask(data, search, mask, slen) == 0)
		{
			return data;
		}
		data++;
	}

	return NULL;
}