#include "psp_hle.h"

SYSCALL(0x212c,0x0e20f177,0x00000000,"sceDisplaySetMode",HLE_sceDisplaySetMode,3);
SYSCALL(0x212d,0xdea197d4,0x00000000,"sceDisplayGetMode",HLE_unknown,4);
SYSCALL(0x212e,0xdba6c4c4,0x00000000,"sceDisplayGetFramePerSec",HLE_unknown,4);
SYSCALL(0x212f,0x7ed59bc4,0x00000000,"sceDisplaySetHoldMode",HLE_unknown,4);
SYSCALL(0x2130,0xa544c486,0x00000000,"sceDisplaySetResumeMode",HLE_unknown,4);
SYSCALL(0x2131,0x289d82fe,0x00000000,"sceDisplaySetFrameBuf",HLE_sceDisplaySetFrameBuf,4);
SYSCALL(0x2132,0xeeda2e54,0x00000000,"sceDisplayGetFrameBuf",HLE_unknown,4);
SYSCALL(0x2133,0xb4f378fa,0x00000000,"sceDisplayIsForeground",HLE_unknown,4);
SYSCALL(0x2134,0x31c4baa8,0x00000000,"sceDisplayGetBrightness",HLE_unknown,4);
SYSCALL(0x2135,0x9c6eaad7,0x00000000,"sceDisplayGetVcount",HLE_unknown,4);
SYSCALL(0x2136,0x4d4e10ec,0x00000000,"sceDisplayIsVblank",HLE_unknown,4);
SYSCALL(0x2137,0x36cdfade,0x00000000,"sceDisplayWaitVblank",HLE_unknown,4);
SYSCALL(0x2138,0x8eb9ec49,0x00000000,"sceDisplayWaitVblankCB",HLE_unknown,4);
SYSCALL(0x2139,0x984c27e7,0x00000000,"sceDisplayWaitVblankStart",HLE_sceDisplayWaitVblankStart,0);
SYSCALL(0x213a,0x46f186c3,0x00000000,"sceDisplayWaitVblankStartCB",HLE_unknown,4);
SYSCALL(0x213b,0x773dd3a3,0x00000000,"sceDisplayGetCurrentHcount",HLE_unknown,4);
SYSCALL(0x213c,0x210eab3a,0x00000000,"sceDisplayGetAccumulatedHcount",HLE_unknown,4);

/** Framebuffer pixel formats. */
enum PspDisplayPixelFormats {
	/** 16-bit RGB 5:6:5. */
	PSP_DISPLAY_PIXEL_FORMAT_565 = 0,
	/** 16-bit RGBA 5:5:5:1. */
	PSP_DISPLAY_PIXEL_FORMAT_5551,
	/* 16-bit RGBA 4:4:4:4. */
	PSP_DISPLAY_PIXEL_FORMAT_4444,
	/* 32-bit RGBA 8:8:8:8. */
	PSP_DISPLAY_PIXEL_FORMAT_8888
};

enum PspDisplaySetBufSync {
	/** Buffer change effective immediately */
	PSP_DISPLAY_SETBUF_IMMEDIATE = 0, 
	/** Buffer change effective next frame */
	PSP_DISPLAY_SETBUF_NEXTFRAME = 1
};

#include <devices.h>
extern struct vfb_data *HLE_dev_fb;

void HLE_sceDisplaySetMode(int mode, int width, int height)
{
	debug("HLE_sceDisplaySetMode(mode:%08x width:%d height:%d) ",mode,width,height);
	HLE_RETURN_INT(0);
}
//void sceDisplaySetFrameBuf(void *topaddr, int bufferwidth, int pixelformat, int sync);
void HLE_sceDisplaySetFrameBuf(int32_t arg0,int32_t arg1,int32_t arg2,int32_t arg3)
{
	debug("HLE_sceDisplaySetFrameBuf(topaddr:%08x bufferwidth:%08x pixelformat:%08x sync:%08x) ",arg0,arg1,arg2,arg3);
	if(arg2==PSP_DISPLAY_PIXEL_FORMAT_8888)
	{
		HLE_dev_fb->bit_depth = 32;
		HLE_dev_fb->bytes_per_line = HLE_dev_fb->xsize * HLE_dev_fb->bit_depth / 8;
	}
	else
	{
		HLE_dev_fb->bit_depth = 16;
		HLE_dev_fb->bytes_per_line = HLE_dev_fb->xsize * HLE_dev_fb->bit_depth / 8;
	}
	HLE_RETURN_INT(0);
}
 
void HLE_sceDisplayWaitVblankStart(void)
{
	debug("HLE_sceDisplayWaitVblankStart() ");
	HLE_RETURN_INT(0);
}
