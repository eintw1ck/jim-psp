
#include "psp_hle.h"
/*
MEMHOOk(0x00000000,"_start",HLE_nohook,2);
MEMHOOk(0x00000000,"main",HLE_nohook,2);
MEMHOOk(0x00000000,"_init",HLE_nohook,0);
MEMHOOk(0x00000000,"_fini",HLE_nohook,0);
MEMHOOk(0x00000000,"_exit",HLE_nohook,1);
MEMHOOk(0x00000000,"_Exit",HLE_nohook,1);
MEMHOOk(0x00000000,"atexit",HLE_nohook,1);
MEMHOOk(0x00000000,"exit",HLE_nohook,1);
MEMHOOk(0x00000000,"isdigit",HLE_nohook,1);
MEMHOOk(0x00000000,"malloc",HLE_nohook,1);
MEMHOOk(0x00000000,"free",HLE_nohook,1);
MEMHOOk(0x00000000,"strdup",HLE_nohook,1);
MEMHOOk(0x00000000,"strcmp",HLE_nohook,2);
MEMHOOk(0x00000000,"strncpy",HLE_nohook,3);
MEMHOOk(0x00000000,"strlcpy",HLE_nohook,3);
MEMHOOk(0x00000000,"strlcat",HLE_nohook,3);
MEMHOOk(0x00000000,"strncmp",HLE_nohook,3);
MEMHOOk(0x00000000,"memcmp",HLE_nohook,3);
MEMHOOk(0x00000000,"bzero",HLE_nohook,2);
MEMHOOk(0x00000000,"bcopy",HLE_nohook,3);
MEMHOOk(0x00000000,"__psp_path_absolute",HLE_nohook,3);
MEMHOOk(0x00000000,"__psp_libc_init",HLE_nohook,2);
MEMHOOk(0x00000000,"__psp_init_cwd",HLE_nohook,0);
MEMHOOk(0x00000000,"__psp_free_heap",HLE_nohook,0);
MEMHOOk(0x00000000,"pspDebugScreenInit",HLE_nohook,0);
MEMHOOk(0x00000000,"pspDebugScreenPrintData",HLE_nohook,2);
MEMHOOk(0x00000000,"pspDebugScreenPutChar",HLE_nohook,4);
*/

MEMHOOK(0x00000000,"chdir",HLE_chdir,1);
MEMHOOK(0x00000000,"getcwd",HLE_getcwd,2);

MEMHOOK(0x00000000,"strchr",HLE_strchr,2);
MEMHOOK(0x00000000,"strrchr",HLE_strrchr,2);
MEMHOOK(0x00000000,"strcpy",HLE_strcpy,2);
MEMHOOK(0x00000000,"strlen",HLE_strlen,1);
MEMHOOK(0x00000000,"memcpy",HLE_memcpy,3);
MEMHOOK(0x00000000,"memset",HLE_memset,3);
 
MEMHOOK(0x00000000,"kprintf",HLE_kprintf,8);
MEMHOOK(0x00000000,"sprintf",HLE_sprintf,8);
MEMHOOK(0x00000000,"vsnprintf",HLE_vsnprintf,8);
MEMHOOK(0x00000000,"vsprintf",HLE_vsprintf,8);

MEMHOOK(0x00000000,"sceKernelCheckExecFile",HLE_sceKernelCheckExecFile,4);
MEMHOOK(0x00000000,"sceKernelProbeExecuteableObject",HLE_nohook,4);
MEMHOOK(0x00000000,"CheckPspCompress",HLE_nohook,4);

MEMHOOK(0x00000000,"exception_and_uart4_stuff_88c04104",HLE_nohook,4);


void HLE_strlen(int32_t arg0)
{
uint32_t len=0;
char thischar;

	debug("HLE_strlen(%08x) ",arg0);
	hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	while(thischar!=0)
	{
		len++;arg0++;
//		debug("d:%02x\n",thischar);
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	}
	HLE_RETURN_INT(len);
}

void HLE_strcpy(int32_t arg0,int32_t arg1)
{
uint32_t dest;
char thischar;
	dest=arg0;
	debug("HLE_strcpy(%08x,%08x) ",arg0,arg1);
	hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	while(thischar!=0)
	{
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg1, &thischar,1, MEM_WRITE, CACHE_DATA);	
		arg0++;arg1++;
//		debug("d:%02x\n",thischar);
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	}
	HLE_RETURN_INT(dest);
}
// returns pointer to first occurance of arg1 in arg0
void HLE_strchr(int32_t arg0,int32_t arg1)
{
uint32_t res=NULL;
char thischar;
	debug("HLE_strchr(%08x,'%c') ",arg0,arg1);
	hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	while(thischar!=0)
	{
//		debug("d:%02x\n",thischar);
		if(thischar==arg1)
		{
			res=arg0;
			break;
		}
		arg0++;
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	}
	HLE_RETURN_PTR(res);
}
// returns pointer to last occurance of arg1 in arg0
void HLE_strrchr(int32_t arg0,int32_t arg1)
{
uint32_t res=NULL;
char thischar;
	debug("HLE_strchr(%08x,'%c') ",arg0,arg1);
	hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	while(thischar!=0)
	{
//		debug("d:%02x\n",thischar);
		if(thischar==arg1)
		{
			res=arg0;
		}
		arg0++;
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_READ, CACHE_DATA);	
	}
	HLE_RETURN_PTR(res);
}

void HLE_memset(int32_t arg0,int32_t arg1,int32_t arg2)
{
uint32_t dest;
char thischar;
	dest=arg0;
	thischar=arg1;
	debug("HLE_memset(%08x,%08x,%08x) ",arg0,arg1,arg2);
	while(arg2>0)
	{
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_WRITE, CACHE_DATA);	
		arg2--;
//		debug("d:%02x\n",thischar);
	}
	HLE_RETURN_INT(dest);
}

void HLE_memcpy(int32_t arg0,int32_t arg1,int32_t arg2)
{
uint32_t dest;
char thischar;
	dest=arg0;
	debug("HLE_memcpy(%08x,%08x,%08x) ",arg0,arg1,arg2);
	while(arg2>0)
	{
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg1, &thischar,1, MEM_READ, CACHE_DATA);	
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, &thischar,1, MEM_WRITE, CACHE_DATA);	
		arg2--;arg1++;arg0++;
//		debug("d:%02x\n",thischar);
	}
	HLE_RETURN_INT(dest);
}

/*
	printf style functions

*/

uint32_t _outp_console(uint32_t p,uint32_t c)
{
	if(c==0) return;
	fprintf(stdout,"%c",c);
}
uint32_t _outp_pspstr(uint32_t p,uint32_t c)
{
char thischar;
	thischar=c;
	hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, p, &thischar,1, MEM_WRITE, CACHE_DATA);	
}

uint32_t _getc_pspmem(uint32_t p)
{
char thischar;
int c;
//	fprintf(stdout,"<p:%08x>",p);
	hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, p, &thischar,1, MEM_READ, CACHE_DATA);	
	c=thischar;
	return c;
}

uint32_t _getarg_pspmem(uint32_t *arg)
{
uint32_t n;
	// first 8 args come from registers
	if((*arg)<8)
	{
		n=hle_cpu->cd.mips.gpr[(*arg)+4];
	}
	else
	{
		// next args are on the stack
		n=load_32bit_word(hle_cpu, hle_cpu->cd.mips.gpr[MIPS_GPR_SP] + ((*arg)-8));
	}
	*arg++;
	return n;
}

uint32_t _getvargs_pspmem(uint32_t *arg)
{
uint32_t n;
	n=load_32bit_word(hle_cpu, *arg);
//	debug("word:%08x @ %08x\n",n,*arg);
	*arg+=4;
	return n;
}

int32_t hle_printf(int maxlen,uint32_t (*_sputter)(),uint32_t _parg,uint32_t (*_sgetter)(),uint32_t _sarg,uint32_t (*_arggetter)(),uint32_t _aarg)
{
uint32_t c,a;
uint32_t aarg;
int32_t len=0;

	aarg=_aarg;

	while(maxlen>len)
	{
		c=_sgetter(_sarg);_sarg++;
		switch(c)
		{
			case 0:
				_sputter(_parg,0);_parg++;
				return(len);
			break;

			case '%':
			{
				int informat=1;
				while(informat)
				{
					c=_sgetter(_sarg);_sarg++;
					switch(c)
					{
						case 0:
							_sputter(_parg,0);_parg++;
							return(len);
						break;
						case '%':
							_sputter(_parg,'%');_parg++;len++;
							informat=0;
						break;
	
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case '.':
						case '-':
						break;
	
						case 'c':
							a=_arggetter(&aarg);
							_sputter(_parg,a);_parg++;len++;
							informat=0;
						break;
						case 's':
							a=_arggetter(&aarg);
							while(c=_sgetter(a))
							{
								a++;
								_sputter(_parg,c);_parg++;len++;
							}
							informat=0;
						break;
						case 'd':
						{
							char temp[32];int i,l;
							a=_arggetter(&aarg);
							sprintf(temp,"%d",a);
							l=strlen(temp);len+=l;
							for(i=0;i<l;i++) 
							{
								_sputter(_parg,temp[i]);_parg++;
							}
							informat=0;
						}
						break;
						case 'p':
						case 'x':
						case 'X':
						{
							char temp[32];int i,l;
							a=_arggetter(&aarg);
							sprintf(temp,"%x",a);
							l=strlen(temp);len+=l;
							for(i=0;i<l;i++) 
							{
								_sputter(_parg,temp[i]);_parg++;
							}
							informat=0;
						}
						break;
						default:
							informat=0;
						break;
					}
				}
			}
			break;

			default:
				_sputter(_parg,c);_parg++;len++;
			break;
		}
	}

	return(len);
}

void HLE_kprintf(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
char *name;
int32_t len=0;

	name=get_userland_string(hle_cpu, arg0);
	debug("kprintf(\"%s\" %08x %08x %08x) ",name,arg1,arg2,arg3);
	free(name);
////	debug("kprintf(%08x %08x %08x %08x) ",arg0,arg1,arg2,arg3);
//	fprintf(stdout,name,arg1,arg2,arg3);

	len=hle_printf(-1,_outp_console,0,_getc_pspmem,arg0,_getarg_pspmem,1);
//	return -1;
	HLE_RETURN_INT(len);
}

void HLE_vsprintf(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3,int32_t arg4,int32_t arg5)
{
char *format;
int32_t len=0;

	format=get_userland_string(hle_cpu, arg1);
	debug("vsprintf(%08x \"%s\" %08x %08x %08x) ",arg0,format,arg1,arg2,arg3);
	free(format);
//	debug("kprintf(%08x %08x %08x %08x) ",arg0,arg1,arg2,arg3);
//	fprintf(stdout,name,arg1,arg2,arg3);

	len=hle_printf(0xffff,_outp_pspstr,arg0,_getc_pspmem,arg1,_getvargs_pspmem,arg2);

//	format=get_userland_string(hle_cpu, arg0);
//	debug(":\"%s\" ",format);
//	free(format);
//	return -1;
	HLE_RETURN_INT(len);
}

void HLE_vsnprintf(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3,int32_t arg4,int32_t arg5)
{
char *format;
int32_t len=0;

	format=get_userland_string(hle_cpu, arg2);
	debug("vsnprintf(%08x %08x \"%s\" %08x %08x %08x) ",arg0,arg1,format,arg3,arg4,arg5);
	free(format);
//	debug("kprintf(%08x %08x %08x %08x) ",arg0,arg1,arg2,arg3);
//	fprintf(stdout,name,arg1,arg2,arg3);

	len=hle_printf(arg1,_outp_pspstr,arg0,_getc_pspmem,arg2,_getvargs_pspmem,arg3);

//	format=get_userland_string(hle_cpu, arg0);
//	debug(":\"%s\" ",format);
//	free(format);
//	return -1;
	HLE_RETURN_INT(len);
}

void HLE_sprintf(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3,int32_t arg4,int32_t arg5)
{
char *format;
int32_t len=0;

	format=get_userland_string(hle_cpu, arg1);
	debug("HLE_sprintf(%08x \"%s\" %08x %08x %08x) ",arg0,format,arg1,arg2,arg3);
	free(format);
//	debug("kprintf(%08x %08x %08x %08x) ",arg0,arg1,arg2,arg3);
//	fprintf(stdout,name,arg1,arg2,arg3);

	len=hle_printf(0xffff,_outp_pspstr,arg0,_getc_pspmem,arg1,_getarg_pspmem,2);

//	format=get_userland_string(hle_cpu, arg0);
//	debug(":\"%s\" ",format);
//	free(format);
//	return -1;
	HLE_RETURN_INT(len);
}


void HLE_sceKernelCheckExecFile(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
	debug("HLE_sceKernelCheckExecFile(%08x %08x %08x %08x) ",arg0,arg1,arg2,arg3);
	HLE_RETURN_INT(0x00000001);
}
