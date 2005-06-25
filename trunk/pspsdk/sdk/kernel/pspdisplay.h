#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Wait for vertical blank
 *
 * @par Example1:
 * @code
 * @endcode
 *
 */
void sceDisplayWaitVblankStart();
/**
 * Set display mode
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param unk1 - unknown always 0?
 * @param width - width of screen in pixels
 * @param height - height of screen in pixels
 */
void sceDisplaySetMode(long unk1, long width, long height);
/**
 * Display set framebuf
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param topaddr* - address of start of framebuffer
 * @param bufferwidth* - buffer width (must be power of 2)
 * @param pixelformat* - one of the following: 0 - BGRA 5551, 3 - ABGR 8888
 * @param unk1 - unknown, always 1? (vblank sync?)
 */
void sceDisplaySetFrameBuf(char *topaddr, long bufferwidth, long pixelformat, long
	unk1);

#ifdef __cplusplus
}
#endif

#endif
