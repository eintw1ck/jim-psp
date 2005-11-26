/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * gdb-userlib.c - GDB support functions for user mode.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id$
 */
#include <pspkernel.h>
#include <pspdebug.h>

#include <string.h>

static int sio_fd = -1;

/* GDB Debug putchar */
void putDebugChar(char ch)
{
	sceIoWrite(sio_fd, &ch, 1);
}

/* GDB Debug getchar */
char getDebugChar(void)
{
	char ch = 0;
	int count = 0;

	while(count <= 0)
	{
		count = sceIoRead(sio_fd, &ch, 1);
	}

	return ch;
}

int g_initialised = 0;

static int io_init(PspIoDrvArg *arg)
{
	return 0;
}

static int io_exit(PspIoDrvArg *arg)
{
	return 0;
}

static int io_open(PspIoDrvFileArg *arg, char *file, int mode, SceMode mask)
{
	return 0;
}

static int io_close(PspIoDrvFileArg *arg)
{
	return 0;
}

static int io_read(PspIoDrvFileArg *arg, char *data, int len)
{
	int ret = 0;
	int ch;

	while(ret < len)
	{
		ch = pspDebugSioGetchar();
		if(ch != -1)
		{
			data[ret++] = ch & 0xFF;
		}
		else
		{
			break;
		}
	}

	return ret;
}

static int io_write(PspIoDrvFileArg *arg, const char *data, int len)
{
	int ret = 0;

	while(ret < len)
	{
		pspDebugSioPutchar(data[ret++]);
	}

	return ret;
}

static int io_lseek(PspIoDrvFileArg *arg, u32 unk, long long ofs, int whence)
{
	return 0;
}

static int io_ioctl(PspIoDrvFileArg *arg, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen)
{
	return 0;
}

static int io_remove(PspIoDrvFileArg *arg, const char *name)
{
	return 0;
}

static int io_mkdir(PspIoDrvFileArg *arg, const char *name, SceMode mode)
{
	return 0;
}

static int io_rmdir(PspIoDrvFileArg *arg, const char *name)
{
	return 0;
}

static int io_dopen(PspIoDrvFileArg *arg, const char *dir)
{
	return 0;
}

static int io_dclose(PspIoDrvFileArg *arg)
{
	return 0;
}

static int io_dread(PspIoDrvFileArg *arg, SceIoDirent *dir)
{
	return 0;
}

static int io_getstat(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat)
{
	return 0;
}

static int io_chstat(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat, int bits)
{
	return 0;
}

static int io_rename(PspIoDrvFileArg *arg, const char *oldname, const char *newname)
{
	return 0;
}

static int io_chdir(PspIoDrvFileArg *arg, const char *dir)
{
	return 0;
}

static int io_mount(PspIoDrvFileArg *arg)
{
	return 0;
}

static int io_umount(PspIoDrvFileArg *arg)
{
	return 0;
}

void sceKernelDcacheWBinvAll(void);
void sceKernelIcacheClearAll(void);

static int io_devctl(PspIoDrvFileArg *arg,  unsigned int cmd, void *indata, int inlen, void *outdata, int outlen)
{
	pspKernelSetKernelPC();
	sceKernelDcacheWBinvAll();
	sceKernelIcacheClearAll();

	return 0;
}

static int io_unknown(PspIoDrvFileArg *arg)
{
	return 0;
}

static PspIoDrvFuncs sio_funcs = 
{
	io_init,
	io_exit,
	io_open,
	io_close,
	io_read,
	io_write,
	io_lseek,
	io_ioctl,
	io_remove,
	io_mkdir,
	io_rmdir,
	io_dopen,
	io_dclose,
	io_dread,
	io_getstat,
	io_chstat,
	io_rename,
	io_chdir,
	io_mount,
	io_umount,
	io_devctl,
	io_unknown,
};

static PspIoDrv sio_driver = 
{
	"sio", 0x10, 0x800, "SIO", &sio_funcs
};

int _gdbSupportLibReadByte(unsigned char *address, unsigned char *dest)
{
	u32 addr;

	addr = (u32) address;
	if((addr >= 0x08400000) && (addr < 0x0a000000))
	{
		*dest = *address;
		return 1;
	}

	/*
	else if((addr >= 0x88000000) && (addr < 0x8a000000))
	{
		*dest = *address;
		return 1;
	}
	*/

	return 0;
}

int _gdbSupportLibWriteByte(char val, unsigned char *dest)
{
	u32 addr;

	addr = (u32) dest;
	if((addr >= 0x08400000) && (addr < 0x0a000000))
	{
		*dest = val;
		return 1;
	}

	/*
	else if((addr >= 0x88000000) && (addr < 0x8a000000))
	{
		*dest = val;
		return 1;
	}
	*/

	return 0;
}

void _gdbSupportLibFlushCaches(void)
{
	sceIoDevctl("sio:", 0, NULL, 0, NULL, 0);
}

int _gdbSupportLibInit(void)
{
	int ret;

	if(!g_initialised)
	{
		(void) sceIoDelDrv("sio"); /* Ignore error */
		ret = sceIoAddDrv(&sio_driver);
		if(ret < 0)
		{
			return ret;
		}

		sio_fd = sceIoOpen("sio:", PSP_O_RDWR, 0);

		g_initialised = 1;
	}

	return 0;
}
