/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * sio.c - Some basic SIO (remote port) functions.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: kprintf.c 664 2005-07-16 08:23:18Z tyranid $
 */

#include <pspkernel.h>
#include <pspdebug.h>

/* Define some important parameters */
#define PSP_UART4_FIFO 0xBE500000
#define PSP_UART4_STAT 0xBE500018
#define PSP_UART_TXFULL  0x20
#define PSP_UART_RXEMPTY 0x10

/* Some function prototypes we will need */
int sceHprmEnd(void);
int sceSysregUartIoEnable(int uart);
int sceSyscon_driver_44439604(int power);
extern u32 sceKernelRemoveByDebugSection;

void pspDebugSioPutchar(int ch)
{
	while(_lw(PSP_UART4_STAT) & PSP_UART_TXFULL);
	_sw(ch, PSP_UART4_FIFO);
}

int pspDebugSioGetchar(void)
{
	if(_lw(PSP_UART4_STAT) & PSP_UART_RXEMPTY)
	{
		return -1;
	}

	return _lw(PSP_UART4_FIFO);
}

void pspDebugSioPuts(const char *str)
{
	while(*str)
	{
		pspDebugSioPutchar(*str);
		str++;
	}

	pspDebugSioPutchar('\r');
	pspDebugSioPutchar('\n');
}

int pspDebugSioPutData(const char *data, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		pspDebugSioPutchar(data[i]);
	}

	return len;
}

void pspDebugSioInit(void)
{
	/* Shut down the remote driver */
	sceHprmEnd();
	/* Enable UART 4 */
	sceSysregUartIoEnable(4);
	/* Enable remote control power */
	sceSyscon_driver_44439604(1);
	/* Delay thread for a but */
	sceKernelDelayThread(2000000);
}

static u32 *get_debug_register(void)
{
	u32 *pData;
	u32 ptr;

	pData = (u32 *) (0x80000000 | ((sceKernelRemoveByDebugSection & 0x03FFFFFF) << 2));
	ptr = ((pData[0] & 0xFFFF) << 16) + (short) (pData[2] & 0xFFFF);

	return (u32 *) ptr;
}

void pspDebugEnablePutchar(void)
{
	u32 *pData;

	pData = get_debug_register();
	*pData |= 0x1000;
}

static void PutCharDebug(unsigned short *data, unsigned int type)
{
	if((type & 0xFF00) == 0)
	{
		if(type == '\n')
		{
			pspDebugSioPutchar('\r');
		}

		pspDebugSioPutchar(type);
	}
}

void pspDebugSioInstallKprintf(void)
{
	pspDebugEnablePutchar();
	sceKernelRegisterDebugPutchar(PutCharDebug);
}
