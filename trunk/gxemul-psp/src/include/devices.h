#ifndef	DEVICES_H
#define	DEVICES_H

/*
 *  Copyright (C) 2003-2005  Anders Gavare.  All rights reserved.
 *
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
 *
 *
 *  $Id: devices.h,v 1.207 2006/02/18 17:55:25 debug Exp $
 *
 *  Memory mapped devices.
 *
 *  TODO: Separate into lots of smaller files? That might speed up a compile,
 *        but I'm not sure that it's a price worth paying.
 */

#include <sys/types.h>
#include <inttypes.h>

struct cpu;
struct machine;
struct memory;
struct pci_data;

/* #ifdef WITH_X11
#include <X11/Xlib.h>
#endif */

/*  dev_cons.c:  */
#define	DEV_CONS_ADDRESS		0x0000000010000000
#define	DEV_CONS_LENGTH			0x0000000000000020
#define	    DEV_CONS_PUTGETCHAR		    0x0000
#define	    DEV_CONS_HALT		    0x0010
struct cons_data {
	int	console_handle;
	int	irq_nr;
	int	in_use;
};
/*  dev_disk.c:  */
#define	DEV_DISK_ADDRESS		0x13000000

/*  dev_ether.c:  */
#define	DEV_ETHER_ADDRESS		0x14000000
#define	DEV_ETHER_LENGTH		0x8000

/*  dev_fb.c:  */
#define	DEV_FB_ADDRESS		0x12000000	/*  Default for testmips  */
#define	DEV_FB_LENGTH		0x3c0000	/*  3c0000 to not colide with */
						/*  turbochannel rom,         */
						/*  otherwise size = 4MB      */
/*  Type:  */
#define	VFB_GENERIC		0
#define	VFB_HPC			1
#define	VFB_DEC_VFB01		2
#define	VFB_DEC_VFB02		3
#define	VFB_DEC_MAXINE		4
#define	VFB_PLAYSTATION2	5
#define	VFB_PSP			6
/*  Extra flags:  */
#define	VFB_REVERSE_START	0x10000
struct vfb_data {
	int		vfb_type;

	int		vfb_scaledown;

	int		xsize;
	int		ysize;
	int		bit_depth;
	int		color32k;	/*  hack for 16-bit HPCmips  */
	int		psp_15bit;	/*  plastation portable hack  */

	unsigned char	color_plane_mask;

	int		bytes_per_line;		/*  cached  */

	int		visible_xsize;
	int		visible_ysize;

	size_t		framebuffer_size;
	int		x11_xsize, x11_ysize;

	int		update_x1, update_y1, update_x2, update_y2;

	/*  RGB palette for <= 8 bit modes:  (r,g,b bytes for each)  */
	unsigned char	rgb_palette[256 * 3];

	void (*redraw_func)(struct vfb_data *, int, int);

	/*  These should always be in sync:  */
	unsigned char	*framebuffer;
	struct fb_window *fb_window;
};
#define	VFB_MFB_BT455			0x100000
#define	VFB_MFB_BT431			0x180000
#define	VFB_MFB_VRAM			0x200000
#define	VFB_CFB_BT459			0x200000
void set_grayscale_palette(struct vfb_data *d, int ncolors);
void dev_fb_resize(struct vfb_data *d, int new_xsize, int new_ysize);
void dev_fb_setcursor(struct vfb_data *d, int cursor_x, int cursor_y, int on, 
        int cursor_xsize, int cursor_ysize);
void framebuffer_blockcopyfill(struct vfb_data *d, int fillflag, int fill_r,
	int fill_g, int fill_b, int x1, int y1, int x2, int y2,
	int from_x, int from_y);
void dev_fb_tick(struct cpu *, void *);
int dev_fb_access(struct cpu *cpu, struct memory *mem, uint64_t relative_addr,
	unsigned char *data, size_t len, int writeflag, void *);
struct vfb_data *dev_fb_init(struct machine *machine, struct memory *mem,
	uint64_t baseaddr, int vfb_type, int visible_xsize, int visible_ysize,
	int xsize, int ysize, int bit_depth, char *name);

/*  dev_ram.c:  */
#define	DEV_RAM_RAM				0
#define	DEV_RAM_MIRROR				1
#define	DEV_RAM_MIGHT_POINT_TO_DEVICES		0x10
int dev_ram_access(struct cpu *cpu, struct memory *mem, uint64_t relative_addr,
	unsigned char *data, size_t len, int writeflag, void *);
void dev_ram_init(struct machine *machine, uint64_t baseaddr, uint64_t length,
	int mode, uint64_t otheraddr);

/* dev_psp_uart.c */
void dev_psp_uart_init(struct machine *machine, uint64_t baseaddr, uint64_t length,char *name);


#endif	/*  DEVICES_H  */

