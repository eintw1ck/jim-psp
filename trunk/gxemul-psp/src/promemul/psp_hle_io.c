
#include "psp_hle.h"

SYSCALL(0x2087,0x3251ea56,0x00000000,"sceIoPollAsync",HLE_unknown,4);
SYSCALL(0x2088,0xe23eec33,0x00000000,"sceIoWaitAsync",HLE_unknown,4);
SYSCALL(0x2089,0x35dbd746,0x00000000,"sceIoWaitAsyncCB",HLE_unknown,4);
SYSCALL(0x208a,0xcb05f8d6,0x00000000,"sceIoGetAsyncStat",HLE_unknown,4);
SYSCALL(0x208b,0xb293727f,0x00000000,"sceIoChangeAsyncPriority",HLE_unknown,4);
SYSCALL(0x208c,0xa12a0514,0x00000000,"sceIoSetAsyncCallback",HLE_unknown,4);
SYSCALL(0x208d,0x810c4bc3,0x00000000,"sceIoClose",HLE_sceIoClose,1);
SYSCALL(0x208e,0xff5940b6,0x00000000,"sceIoCloseAsync",HLE_unknown,4);
SYSCALL(0x208f,0x109f50bc,0x00000000,"sceIoOpen",HLE_sceIoOpen,3);
SYSCALL(0x2090,0x89aa9906,0x00000000,"sceIoOpenAsync",HLE_unknown,4);
SYSCALL(0x2091,0x6a638d83,0x00000000,"sceIoRead",HLE_sceIoRead,3);
SYSCALL(0x2092,0xa0b5a7c2,0x00000000,"sceIoReadAsync",HLE_unknown,4);
SYSCALL(0x2093,0x42ec03ac,0x00000000,"sceIoWrite",HLE_sceIoWrite,3);
SYSCALL(0x2094,0x0facab19,0x00000000,"sceIoWriteAsync",HLE_unknown,4);
SYSCALL(0x2095,0x27eb27b8,0x00000000,"sceIoLseek",HLE_unknown,4);
SYSCALL(0x2096,0x71b19e77,0x00000000,"sceIoLseekAsync",HLE_unknown,4);
SYSCALL(0x2097,0x68963324,0x00000000,"sceIoLseek32",HLE_unknown,4);
SYSCALL(0x2098,0x1b385d8f,0x00000000,"sceIoLseek32Async",HLE_unknown,4);
SYSCALL(0x2099,0x63632449,0x00000000,"sceIoIoctl",HLE_unknown,4);
SYSCALL(0x209a,0xe95a012b,0x00000000,"sceIoIoctlAsync",HLE_unknown,4);
SYSCALL(0x209b,0xb29ddf9c,0x00000000,"sceIoDopen",HLE_sceIoDopen,1);
SYSCALL(0x209c,0xe3eb004c,0x00000000,"sceIoDread",HLE_sceIoDread,2);
SYSCALL(0x209d,0xeb092469,0x00000000,"sceIoDclose",HLE_sceIoDclose,1);
SYSCALL(0x209e,0xf27a9c51,0x00000000,"sceIoRemove",HLE_unknown,4);
SYSCALL(0x209f,0x06a70004,0x00000000,"sceIoMkdir",HLE_unknown,4);
SYSCALL(0x20a0,0x1117c65f,0x00000000,"sceIoRmdir",HLE_unknown,4);
SYSCALL(0x20a1,0x55f4717d,0x00000000,"sceIoChdir",HLE_sceIoChdir,1);
SYSCALL(0x20a2,0xab96437f,0x00000000,"sceIoSync",HLE_unknown,4);
SYSCALL(0x20a3,0xace946e8,0x00000000,"sceIoGetstat",HLE_sceIoGetstat,2);
SYSCALL(0x20a4,0xb8a740f4,0x00000000,"sceIoChstat",HLE_unknown,4);
SYSCALL(0x20a5,0x779103a0,0x00000000,"sceIoRename",HLE_unknown,4);
SYSCALL(0x20a6,0x54f5fb11,0x00000000,"sceIoDevctl",HLE_unknown,4);
SYSCALL(0x20a7,0x08bd7374,0x00000000,"sceIoGetDevType",HLE_unknown,4);
SYSCALL(0x20a8,0xb2a628c1,0x00000000,"sceIoAssign",HLE_unknown,4);
SYSCALL(0x20a9,0x6d08a871,0x00000000,"sceIoUnassign",HLE_unknown,4);
SYSCALL(0x20aa,0xe8bc6571,0x00000000,"sceIoCancel",HLE_unknown,4);

SYSCALL(0x20ab,0x3054d478,0x00000000,"sceKernelStdioRead",HLE_unknown,4);
SYSCALL(0x20ac,0x0cbb0571,0x00000000,"sceKernelStdioLseek",HLE_unknown,4);
SYSCALL(0x20ad,0xa46785c9,0x00000000,"sceKernelStdioSendChar",HLE_unknown,4);
SYSCALL(0x20ae,0xa3b931db,0x00000000,"sceKernelStdioWrite",HLE_unknown,4);
SYSCALL(0x20af,0x9d061c19,0x00000000,"sceKernelStdioClose",HLE_unknown,4);
SYSCALL(0x20b0,0x924aba61,0x00000000,"sceKernelStdioOpen",HLE_unknown,4);
SYSCALL(0x20b1,0x172d316e,0x00000000,"sceKernelStdin",HLE_sceKernelStdin,0);
SYSCALL(0x20b2,0xa6bab2e9,0x00000000,"sceKernelStdout",HLE_sceKernelStdout,0);
SYSCALL(0x20b3,0xf78ba90a,0x00000000,"sceKernelStderr",HLE_sceKernelStderr,0);
 
// IoFileMgrForKernel
SYSCALL(0x2201,0x3c54e908, 0x00000000,"sceIoReopen",HLE_unknown,4);
SYSCALL(0x2202,0x8e982a74, 0x00000000,"sceIoAddDrv",HLE_unknown,4);
SYSCALL(0x2203,0xc7f35804, 0x00000000,"sceIoDelDrv",HLE_unknown,4);

// StdioForKernel
SYSCALL(0x2204,0x98220f3e, 0x00000000,"sceKernelStdoutReopen",HLE_unknown,4);
SYSCALL(0x2205,0xfb5380c5, 0x00000000,"sceKernelStderrReopen",HLE_unknown,4);

// KDebugForKernel
SYSCALL(0x21f8,0xe146606d, 0x00000000,"sceKernelRegisterDebugPutchar",HLE_unknown,4);
SYSCALL(0x21f9,0x84f370bc, 0x00000000,"Kprintf",HLE_Kprintf,9);
SYSCALL(0x21fa,0xd636b827, 0x00000000,"sceKernelRemoveByDebugSection",HLE_unknown,4);
SYSCALL(0x2215,0x7CEB2C09, 0x00000000,"sceKernelRegisterKprintfHandler",HLE_sceKernelRegisterKprintfHandler,2);

typedef struct
{
	char *name;
	FILE *local_fd;
} PSP_File;
PSP_File pspfiles[10];
int        numfiles=3;	// 0,1,2 are stdin,out,err

/**
	IoFileMgrForKernel
*/
void HLE_sceIoOpen(int32_t arg0,int32_t arg1,int32_t arg2)
{
char *name;
	name=get_userland_string(hle_cpu, arg0);
	debug("HLE_sceIoOpen(Name:%s Mode:%08x Perm:%08x) ",name,arg1,arg2);
	pspfiles[numfiles].name=name;
	numfiles++;
	HLE_RETURN_INT(numfiles-1);
}
void HLE_sceIoClose(int32_t arg0)
{
	debug("HLE_sceIoClose(fd: %08x - Name:%s) ",arg0,pspfiles[arg0].name);
	free(pspfiles[arg0].name);
	HLE_RETURN_INT(0);
}
void HLE_sceIoRead(int32_t arg0,int32_t arg1,int32_t arg2)
{
	debug("HLE_sceIoRead(fd:%08x buf:%08x len:%08x) ",arg0,arg1,arg2);
	HLE_RETURN_INT(0);
}
void HLE_sceIoWrite(int32_t arg0,int32_t arg1,int32_t arg2)
{
	debug("HLE_sceIoWrite(fd:%08x buf:%08x len:%08x) ",arg0,arg1,arg2);
	if((arg0==1)|(arg0==2)) // stdout/stderr
	{
		char *b;
		int i;
		b=get_userland_buf(hle_cpu,arg1,arg2);
		for(i=0;i<arg2;i++)
		{
			debug("'%c' ",b[i]);
		}
		free(b);
	}
	HLE_RETURN_INT(arg2);
}

//int sceIoGetstat(const char *file, SceIoStat *stat);
void HLE_sceIoGetstat(int32_t arg0,int32_t arg1)
{
char *name;
	name=get_userland_string(hle_cpu, arg0);
	debug("HLE_sceIoGetstat(Name:%s stat:%08x) ",name,arg1);
	HLE_RETURN_INT(0);
}

// SceUID sceIoDopen(const char *dirname);
void HLE_sceIoDopen(int32_t arg0)
{
char *name;
	name=get_userland_string(hle_cpu, arg0);
	debug("HLE_sceIoDopen(Name:%s) ",name);
	HLE_RETURN_INT(1);
}
void HLE_sceIoDclose(int32_t arg0)
{
	debug("HLE_sceIoDclose(fd:%08x) ",arg0);
	HLE_RETURN_INT(0);
}
//int sceIoDread(SceUID fd, SceIoDirent *dir);
void HLE_sceIoDread(int32_t arg0,int32_t arg1)
{
	debug("HLE_sceIoDread(fd:%08x dirent:%08x) ",arg0,arg1);
	HLE_RETURN_INT(0);
}

void HLE_sceIoChdir(int32_t arg0)
{
char *name;
	name=get_userland_string(hle_cpu, arg0);
	debug("HLE_sceIoChdir(Name:%s) ",name);
	HLE_RETURN_INT(0);
}

/**
	kernel stdio
*/

void HLE_sceKernelStdin(void)
{
	debug("HLE_sceKernelStdin() ");
	HLE_RETURN_INT(0);
}
void HLE_sceKernelStdout(void)
{
	debug("HLE_sceKernelStdout() ");
	HLE_RETURN_INT(1);
}
void HLE_sceKernelStderr(void)
{
	debug("HLE_sceKernelStderr() ");
	HLE_RETURN_INT(2);
}

/**
	KDebugForKernel
*/
uint32_t HLE_KprintfHandler=0;

void HLE_sceKernelRegisterKprintfHandler(int32_t arg0,int32_t arg1)
{
	debug("HLE_sceKernelRegisterKprintfHandler(func:%08x args:%08x) ",arg0,arg1);
	HLE_KprintfHandler=arg0;
	HLE_RETURN_INT(0);
}


void HLE_Kprintf(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3,int32_t arg4,int32_t arg5,int32_t arg6,int32_t arg7,int32_t arg8)
{
char *format;
	format=get_userland_string(hle_cpu, arg0);
	debug("HLE_Kprintf(arg0:%s arg1:%08x arg2:%08x arg3:%08x arg4:%08x arg5:%08x arg6:%08x arg7:%08x arg8:%08x) ",format,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);

	if(HLE_KprintfHandler==0)
	{
		HLE_RETURN_INT(0);
	}
	else
	{
		uint32_t args=0x08ff0000; // hack!
		store_32bit_word(hle_cpu, args+(0*4)+(0*4), arg1);
		store_32bit_word(hle_cpu, args+(0*4)+(1*4), arg2);
		store_32bit_word(hle_cpu, args+(0*4)+(2*4), arg3);
		HLE_RETURN_CALL3ARGS(HLE_KprintfHandler,NULL,arg0,args);
	}
}

/*
	stdlib
*/
/*
	chdir to path
	ret: 0:ok -1:error
*/
char _cwd[0x400];
void HLE_chdir(int32_t arg0)
{
char *path;
	path=get_userland_string(hle_cpu, arg0);
	debug("HLE_chdir(path:%08x \"%s\") ",arg0,path);
	strcpy(_cwd,path);
	HLE_RETURN_INT(0);	
}
void HLE_getcwd(int32_t arg0,int32_t arg1)
{
int32_t dest=arg0;
char *c;
char *path;
	path=get_userland_string(hle_cpu, arg0);
	debug("HLE_getcwd(arg0:%08x arg1:%08x) ",arg0,path);
	c=_cwd;
	while(arg1)
	{
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, c,1, MEM_WRITE, CACHE_DATA);	
		arg1--;arg0++;c++;
		if(*c==0)break;
	}
		hle_cpu->memory_rw(hle_cpu, hle_cpu->mem, arg0, c,1, MEM_WRITE, CACHE_DATA);	
	HLE_RETURN_PTR(dest);	
}


