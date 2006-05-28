/*
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright  
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE   
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */

//#define PSP_UART_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "device.h"
#include "machine.h"
#include "memory.h"
#include "misc.h"

struct psp_uart_data {
	unsigned char	*name;
	uint64_t	vaddr;
	uint64_t	length;

	unsigned char	*data;
	unsigned char	*dataold;

	uint32_t	fifoin;
	uint32_t	fifoout;
	uint32_t	status;

	uint32_t	div1;
	uint32_t	div2;
	uint32_t	baud;	// pseudo register

	uint32_t	control;
};

#define	PSP_UART_TICK_SHIFT		5

void dev_psp_uart_tick(struct cpu *cpu, void *extra)
{
	struct psp_uart_data *d = extra;

#ifdef PSP_UART_DEBUG
	debug("dev_psp_uart_tick\n");
#endif
	if(d->status&(1<<5)) // transmit buffer full
	{
		debug("[%s OUT:%02x]\n",d->name,d->fifoout);
		d->status&=~(1<<5);
	}
}

DEVICE_ACCESS(psp_uart)
{
	int i;
	struct psp_uart_data *d = extra;
	if (writeflag==MEM_READ) {
		debug("[R %s: Reg 0x%02x:",d->name,(int)relative_addr);
		memcpy(data,d->data+(int)relative_addr,len);
	} 
	else 
	{
		debug("[W %s: Reg 0x%02x:",d->name,(int)relative_addr);
		memcpy(d->dataold+(int)relative_addr,d->data+(int)relative_addr,len);
		memcpy(d->data+(int)relative_addr,data,len);
	}
	if(len==4)
	{
		uint32_t n,o;
		n=(data[3]<<24)+(data[2]<<16)+(data[1]<<8)+(data[0]<<0);
		o=(d->dataold[3+(int)relative_addr]<<24)+(d->dataold[2+(int)relative_addr]<<16)+(d->dataold[1+(int)relative_addr]<<8)+(d->dataold[0+(int)relative_addr]<<0);
//		debug(" [old:%08x]",o);
		switch(relative_addr)
		{
			case 0x00:
				debug(" FIFO    ");
				if (writeflag==MEM_READ) 
				{
					// read from fifo
					debug(" 0x%08x",d->fifoin);
				} 
				else 
				{
					// write to fifo
					d->status|=(1<<5);
					d->fifoout=(data[3]<<24)+(data[2]<<16)+(data[1]<<8)+(data[0]<<0);
					debug(" 0x%08x",d->fifoout);
				}
				break;
			case 0x04:
			case 0x08:
			case 0x0c:
			case 0x10:
			case 0x14:
				debug(" UNK_%02x  ",relative_addr);
				debug(" 0x%08x",n);
				break;
			case 0x18:
				debug(" STATUS  ");
				debug(" 0x%08x",d->status);
				if (writeflag==MEM_READ) 
				{
					// read from STATUS
					data[3]=(d->status>>24)&0xff;
					data[2]=(d->status>>16)&0xff;
					data[1]=(d->status>> 8)&0xff;
					data[0]=(d->status>> 0)&0xff;
				} 
				else 
				{
					// write to STATUS
					d->status=(data[3]<<24)+(data[2]<<16)+(data[1]<<8)+(data[0]<<0);
				}
				break;
			case 0x1c:
			case 0x20:
				debug(" UNK_%02x  ",relative_addr);
				debug(" 0x%08x",n);
				break;
			case 0x24:
				debug(" DIV1    ");
				debug(" 0x%08x",n);
				if (writeflag==MEM_READ) 
				{
					// read from DIV1
					debug(" %08x",(d->div1));
				} 
				else 
				{
					// write to DIV1
					d->div1=(data[3]<<24)+(data[2]<<16)+(data[1]<<8)+(data[0]<<0);
				}
				break;
			case 0x28:
				debug(" DIV2    ");
				debug(" 0x%08x",n);
				if (writeflag==MEM_READ) 
				{
					// read from DIV2
					debug(" %08x",(d->div2));
				} 
				else 
				{
					// write to DIV2
					d->div2=(data[3]<<24)+(data[2]<<16)+(data[1]<<8)+(data[0]<<0);
				}
				break;
			case 0x2c:
				debug(" CONTROL ");
				if (writeflag==MEM_READ) 
				{
					// read from DIV2
					debug(" 0x%08x",(d->control));
				} 
				else 
				{
					// write to DIV2
					d->control=(data[3]<<24)+(data[2]<<16)+(data[1]<<8)+(data[0]<<0);
					debug(" 0x%08x",(d->control));
					if(d->control&(1<<6))
					{
					if(d->control&(1<<5))
					{
					d->baud=96000000/((d->div1<<6)|(d->div2));
					debug(" set baud:%d",(d->baud));
					}
					}
				}
				break;
			case 0x30:
			case 0x34:
			case 0x38:
			case 0x3c:
			case 0x40:
			case 0x44:
			case 0x48:
			case 0x4c:
				debug(" UNK_%02x  ",relative_addr);
				debug(" 0x%08x",n);
				break;
		}
		if (writeflag==MEM_WRITE) {
			if((~o)&(n))
			{
				debug(" set:0x%08x",(~o)&(n));
			}
			if((o)&(~n))
			{
				debug(" unset:0x%08x",(o)&(~n));
			}
		}


		debug("]\n");
	}
	else
	{
		for (i=0; i<len; i++)
			debug(" %02x", data[i]);
		debug(" (len=%i) ]\n", len);
	}
	return 1;
}


void dev_psp_uart_init(struct machine *machine, uint64_t baseaddr, uint64_t length,char *name)
{
	struct psp_uart_data *d;

	d = malloc(sizeof(struct psp_uart_data));
	if (d == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	memset(d, 0, sizeof(struct psp_uart_data));
	d->data= malloc(length);
	if (d->data == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	memset(d->data, 0x00, length);
	//d->data[0x18]=(1<<5)|(1<<4); // recieve buffer empty, transmit buffer full
	d->dataold= malloc(length);
	if (d->dataold == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	memset(d->dataold, 0x00, length);
	d->name= malloc(strlen(name)+1);
	if (d->name == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	strcpy(d->name,name);
	d->vaddr= baseaddr;
	d->length= length;

	memory_device_register(machine->memory, name, d->vaddr,
	    d->length, dev_psp_uart_access, d, DM_DEFAULT, d->data);

	machine_add_tickfunction(machine, dev_psp_uart_tick, d, PSP_UART_TICK_SHIFT);

	return 1;
}

