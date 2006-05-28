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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "device.h"
#include "machine.h"
#include "memory.h"
#include "misc.h"

struct unimplemented_data {
	unsigned char	*data;
	unsigned char	*dataold;
	unsigned char	*name;
	uint64_t	vaddr;
	uint64_t	length;
};

DEVICE_ACCESS(unimplemented)
{
	int i;
	struct unimplemented_data *d = extra;
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
		debug("0x%08x",n);
//		debug(" [old:%08x]",o);
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


void dev_unimplemented_init(struct machine *machine, uint64_t baseaddr, uint64_t length,char *name)
{
	struct unimplemented_data *d;

	d = malloc(sizeof(struct unimplemented_data));
	if (d == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	memset(d, 0, sizeof(struct unimplemented_data));
	d->data= malloc(length);
	if (d->data == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	memset(d->data, 0x00, length);
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
/*
	memory_device_register(devinit->machine->memory,
	    devinit->name, devinit->addr, devinit->len,
	    dev_unimplemented_access, d, DM_DEFAULT, NULL);
*/
	memory_device_register(machine->memory, name, d->vaddr,
	    d->length, dev_unimplemented_access, d, DM_DEFAULT, d->data);

	return 1;
}

