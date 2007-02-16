/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * main.c - PSPLINK USB Remote Joystick Driver
 *
 * Copyright (c) 2006 James F <tyranid@gmail.com>
 *
 * $HeadURL$
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspkdebug.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <psppower.h>
#include <pspdisplay.h>
#include <pspdisplay_kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usbasync.h>
#include <apihook.h>
//#include "minilzo.h"
#include "remotejoy.h"

PSP_MODULE_INFO("RemoteJoy", PSP_MODULE_KERNEL, 1, 1);

//#define ENABLE_TIMING 

#ifdef BUILD_PLUGIN
#define HOSTFSDRIVER_NAME "USBHostFSDriver"
#define HOSTFSDRIVER_PID  (0x1C9)
#include <pspusb.h>
#endif

SceCtrlData g_currjoy;
struct AsyncEndpoint g_endp;
SceUID g_scrthid = -1;
SceUID g_scrsema = -1;
SceUID g_screvent = -1;
char  *g_scrptr = NULL;
int   g_enabled = 0;

int scePowerVolatileMemLock(int, char**, int*);
unsigned int psplinkSetK1(unsigned int k1);

#define ASYNC_JOY ASYNC_USER
#define ABS(x) ((x) < 0 ? -x : x)

int map_axis(int real, int new)
{
	int val1, val2;

	val1 = ((int) real) - 127;
	val2 = ((int) new) - 127;

	if(ABS(val1) > ABS(val2))
	{
		return real;
	}
	else
	{
		return new;
	}
}

void add_values(SceCtrlData *pad_data, int count, int neg)
{
	int i;
	int intc;

	intc = pspSdkDisableInterrupts();
	for(i = 0; i < count; i++)
	{
		if(neg)
		{
			pad_data[i].Buttons &= ~g_currjoy.Buttons;
		}
		else
		{
			pad_data[i].Buttons |= g_currjoy.Buttons;
		}

		pad_data[i].Lx = map_axis(pad_data[i].Lx, g_currjoy.Lx);
		pad_data[i].Ly = map_axis(pad_data[i].Ly, g_currjoy.Ly);
	}
	pspSdkEnableInterrupts(intc);
}

int read_buffer_positive(SceCtrlData *pad_data, int count)
{
	int ret;

	ret = sceCtrlReadBufferPositive(pad_data, count);
	if(ret <= 0)
	{
		return ret;
	}

	add_values(pad_data, ret, 0);

	return ret;
}

int peek_buffer_positive(SceCtrlData *pad_data, int count)
{
	int ret;

	ret = sceCtrlPeekBufferPositive(pad_data, count);
	if(ret <= 0)
	{
		return ret;
	}

	add_values(pad_data, ret, 0);

	return ret;
}

int read_buffer_negative(SceCtrlData *pad_data, int count)
{
	int ret;

	ret = sceCtrlReadBufferNegative(pad_data, count);
	if(ret <= 0)
	{
		return ret;
	}

	add_values(pad_data, ret, 1);

	return ret;
}

int peek_buffer_negative(SceCtrlData *pad_data, int count)
{
	int ret;

	ret = sceCtrlPeekBufferNegative(pad_data, count);
	if(ret <= 0)
	{
		return ret;
	}

	add_values(pad_data, ret, 1);

	return ret;
}

void copy16to16(void *in, void *out);
void copy32to16(void *in, void *out);

int copy_32bpp_raw(void *topaddr)
{
	unsigned int *u;
	unsigned int *frame_addr;
	int y;

	u = (unsigned int*) (g_scrptr + sizeof(struct JoyScrHeader));
	frame_addr = topaddr;
	for(y = 0; y < 272; y++)
	{
		memcpy(u, frame_addr, 480*4);
		u += 480;
		frame_addr += 512;
	}

	return 480*272*4;
}

int copy_32bpp_vfpu(void *topaddr)
{
	struct JoyScrHeader *head = (struct JoyScrHeader*) (0x40000000 | (u32) g_scrptr);

	sceKernelDcacheWritebackInvalidateRange(g_scrptr, sizeof(struct JoyScrHeader));
	copy32to16(topaddr, (g_scrptr + sizeof(struct JoyScrHeader)));

	head->mode = 0;
	return 480*272*2;
}

/*

	char *wrkmem = (char*) 0x08700000;
	int res;
	lzo_uint out_len;
	
	res = lzo1x_1_compress(topaddr, 512*272*4, (unsigned char*) (g_scrptr + sizeof(struct JoyScrHeader)), &out_len, wrkmem);
	if(res != LZO_E_OK)
	{
		printf("Error compressing %d\n", res);
		return 0;
	}

	return out_len;
*/

int copy_16bpp_raw(void *topaddr)
{
	unsigned short *u;
	unsigned short *frame_addr;
	int y;

	u = (unsigned short*) (g_scrptr + sizeof(struct JoyScrHeader));
	frame_addr = topaddr;
	for(y = 0; y < 272; y++)
	{
		memcpy(u, frame_addr, 480*2);
		u += 480;
		frame_addr += 512;
	}

	return 480*272*2;
}

int copy_16bpp_vfpu(void *topaddr)
{
	sceKernelDcacheWritebackInvalidateRange(g_scrptr, sizeof(struct JoyScrHeader));
	copy16to16(topaddr, g_scrptr + sizeof(struct JoyScrHeader));

	return 480*272*2;
}

	/*
	char *wrkmem = (char*) 0x08700000;
	int res;
	lzo_uint out_len;
	
	res = lzo1x_1_compress(topaddr, 512*272*2, (unsigned char*) (g_scrptr + sizeof(struct JoyScrHeader)), &out_len, wrkmem);
	if(res != LZO_E_OK)
	{
		printf("Error compressing %d\n", res);
		return 0;
	}

	return out_len;
	*/

int (*copy_32bpp)(void *topaddr) = copy_32bpp_vfpu;
int (*copy_16bpp)(void *topaddr) = copy_16bpp_vfpu;

void set_frame_buf(void *topaddr, int bufferwidth, int pixelformat, int sync)
{
	unsigned int k1;

	k1 = psplinkSetK1(0);
	if((topaddr) && (sceKernelPollSema(g_scrsema, 1) == 0))
	{
		/* We dont wait for this to complete, probably stupid ;) */
		sceKernelSetEventFlag(g_screvent, 1);
	}

	sceDisplaySetFrameBuf(topaddr, bufferwidth, pixelformat, sync);
	psplinkSetK1(k1);
}

inline int build_frame(void)
{
	struct JoyScrHeader *head;
	void *topaddr;
	int bufferwidth;
	int pixelformat;
	int sync;
	
	sceDisplayGetFrameBuf(&topaddr, &bufferwidth, &pixelformat, &sync);
	if(topaddr)
	{
		head = (struct JoyScrHeader*) g_scrptr;
		head->magic = JOY_MAGIC;
		head->mode = pixelformat;

		switch(pixelformat)
		{
			case 3: head->size = copy_32bpp(topaddr);
					break;
			case 0:
			case 1:
			case 2: head->size = copy_16bpp(topaddr);
					break;
			default: head->size = 0; 
					break;
		};

		if(head->size > 0)
		{
			return 1;
		}
	}

	return 0;
}

int screen_thread(SceSize args, void *argp)
{
	SceModule *pMod;
	struct JoyScrHeader *head;
	int size;

	/* Should actually hook the memory correctly :/ */

	/* Enable free memory */
	_sw(0xFFFFFFFF, 0xBC00000C);
	g_scrptr = (char*) (0x08800000-(512*1024));

	g_scrsema = sceKernelCreateSema("ScreenSema", 0, 1, 1, NULL);
	if(g_scrsema < 0)
	{
		printf("Could not create sema 0x%08X\n", g_scrsema);
		sceKernelExitDeleteThread(0);
	}

	pMod = sceKernelFindModuleByName("sceDisplay_Service");
	if(pMod == NULL)
	{
		printf("Could not get display module\n");
		sceKernelExitDeleteThread(0);
	}

	if(apiHookByName(pMod->modid, "sceDisplay", "sceDisplaySetFrameBuf", set_frame_buf) == 0)
	{
		printf("Could not hook set frame buf function\n");
		sceKernelExitDeleteThread(0);
	}

	/* Display current frame */

	if(build_frame())
	{
		head = (struct JoyScrHeader*) g_scrptr;
		size = head->size;

		usbWriteBulkData(ASYNC_JOY, g_scrptr, sizeof(struct JoyScrHeader) + size);
	}

	while(1)
	{
		int ret;
		unsigned int status;

		ret = sceKernelWaitEventFlag(g_screvent, 3, PSP_EVENT_WAITOR | PSP_EVENT_WAITCLEAR, &status, NULL);
		if(ret < 0)
		{
			sceKernelExitDeleteThread(0);
		}

		if(status & 1)
		{
#ifdef ENABLE_TIMING
			unsigned int start, end;
			static long long avg = 0;
			static int count = 0;

			asm __volatile__  ( "mfc0  %0, $9\n" : "=r"(start) );
#endif
			if(build_frame())
			{
				head = (struct JoyScrHeader*) g_scrptr;
				size = head->size;

				usbWriteBulkData(ASYNC_JOY, g_scrptr, sizeof(struct JoyScrHeader) + size);
#ifdef ENABLE_TIMING
				asm __volatile__  ( "mfc0  %0, $9\n" : "=r"(end) );
				count++;
				avg += (end-start);
				printf("Time: 0x%08X avg:0x%08X\n", end-start, (unsigned int) avg/count);
#endif
			}
			sceKernelSignalSema(g_scrsema, 1);
		}

		if(status & 2)
		{
			sceKernelSleepThread();
		}
	}

	return 0;
}

void do_screen_cmd(unsigned int value)
{
	if(value & SCREEN_CMD_ACTIVE)
	{
		/* Create a thread */
		if(g_scrthid < 0)
		{
			g_screvent = sceKernelCreateEventFlag("ScreenEvent", 0, 0, NULL);
			if(g_screvent < 0)
			{
				printf("Could not create event 0x%08X\n", g_screvent);
				return;
			}

			g_scrthid = sceKernelCreateThread("ScreenThread", screen_thread, 16, 0x800, PSP_THREAD_ATTR_VFPU, NULL);
			if(g_scrthid >= 0)
			{
				sceKernelStartThread(g_scrthid, 0, NULL);
			}
			g_enabled = 1;
		}
		else
		{
			if(!g_enabled)
			{
				sceKernelWakeupThread(g_scrthid);
				g_enabled = 1;
			}
		}
	}
	else
	{
		/* Disable the screen display */
		/* Stop the thread at the next available opportunity */
		if(g_scrthid >= 0)
		{
			if(g_enabled)
			{
				sceKernelSetEventFlag(g_screvent, 2);
				g_enabled = 0;
			}
		}
	}
}

void send_screen_probe(void)
{
	struct JoyScrHeader head;

	head.magic = JOY_MAGIC;
	head.mode = -1;
	head.size = 0;
	head.pad = 0;

	usbAsyncWrite(ASYNC_JOY, &head, sizeof(head));
}

int main_thread(SceSize args, void *argp)
{
	SceModule *pMod;
	struct JoyEvent joyevent;
	int intc;

#ifdef BUILD_PLUGIN
	int retVal = 0;

	retVal = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
	if (retVal != 0) {
		Kprintf("Error starting USB Bus driver (0x%08X)\n", retVal);
		return 0;
	}
	retVal = sceUsbStart(HOSTFSDRIVER_NAME, 0, 0);
	if (retVal != 0) {
		Kprintf("Error starting USB Host driver (0x%08X)\n",
		   retVal);
		return 0;
	}

	retVal = sceUsbActivate(HOSTFSDRIVER_PID);
#endif

	pMod = sceKernelFindModuleByName("sceController_Service");
	if(pMod == NULL)
	{
		printf("Could not get controller module\n");
		sceKernelExitDeleteThread(0);
	}

	if(apiHookByName(pMod->modid, "sceCtrl", "sceCtrlReadBufferPositive", read_buffer_positive) == 0)
	{
		printf("Could not hook controller function\n");
		sceKernelExitDeleteThread(0);
	}

	if(apiHookByName(pMod->modid, "sceCtrl", "sceCtrlPeekBufferPositive", peek_buffer_positive) == 0)
	{
		printf("Could not hook controller function\n");
		sceKernelExitDeleteThread(0);
	}

	if(apiHookByName(pMod->modid, "sceCtrl", "sceCtrlReadBufferNegative", read_buffer_negative) == 0)
	{
		printf("Could not hook controller function\n");
		sceKernelExitDeleteThread(0);
	}

	if(apiHookByName(pMod->modid, "sceCtrl", "sceCtrlPeekBufferNegative", peek_buffer_negative) == 0)
	{
		printf("Could not hook controller function\n");
		sceKernelExitDeleteThread(0);
	}

#ifdef BUILD_PLUGIN
	sceKernelDelayThread(1000000);
#endif
	pMod = sceKernelFindModuleByName("sceVshBridge_Driver");

	/* Ignore if we dont find vshbridge */
	if(pMod)
	{
		if(apiHookByName(pMod->modid, "sceVshBridge","vshCtrlReadBufferPositive", read_buffer_positive) == 0)
		{
			printf("Could not hook controller function\n");
		}
	}

	if(usbAsyncRegister(ASYNC_JOY, &g_endp) < 0)
	{
		printf("Could not register remotejoy provider\n");
		sceKernelExitDeleteThread(0);
	}

	usbWaitForConnect();

	/* Send a probe packet for screen display */
	send_screen_probe();

	while(1)
	{
		int len;
		len = usbAsyncRead(ASYNC_JOY, (void*) &joyevent, sizeof(joyevent));

		if((len != sizeof(joyevent)) || (joyevent.magic != JOY_MAGIC))
		{
			if(len < 0)
			{
				/* Delay thread, necessary to ensure that the kernel can reboot :) */
				sceKernelDelayThread(250000);
			}
			else
			{
				printf("Invalid read size %d\n", len);
				usbAsyncFlush(ASYNC_JOY);
			}
			continue;
		}

		intc = pspSdkDisableInterrupts();
		switch(joyevent.type)
		{
			case TYPE_BUTTON_UP: g_currjoy.Buttons &= ~joyevent.value;
								 break;
			case TYPE_BUTTON_DOWN: g_currjoy.Buttons |= joyevent.value;
								 break;  
			case TYPE_ANALOG_Y: g_currjoy.Ly = joyevent.value;
								break;
			case TYPE_ANALOG_X: g_currjoy.Lx = joyevent.value;
								break;
			default: break;
		};
		pspSdkEnableInterrupts(intc);

		/* We do screen stuff outside the disabled interrupts */
		if(joyevent.type == TYPE_SCREEN_CMD)
		{
			do_screen_cmd(joyevent.value);
		}
		scePowerTick(0);
	}

	return 0;
}

/* Entry point */
int module_start(SceSize args, void *argp)
{
	int thid;

	memset(&g_currjoy, 0, sizeof(g_currjoy));
	g_currjoy.Lx = 0x80;
	g_currjoy.Ly = 0x80;
	/* Create a high priority thread */
	thid = sceKernelCreateThread("RemoteJoy", main_thread, 15, 0x800, 0, NULL);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, args, argp);
	}
	return 0;
}

/* Module stop entry */
int module_stop(SceSize args, void *argp)
{
	return 0;
}
