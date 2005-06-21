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
 * @param a
 * @param b
 * @param c
 */
void sceDisplaySetMode(long a, long b, long c);
/**
 * Display set framebuf
 *
 * @par Example1:
 * @code
 * @endcode
 *
 * @param topaddr*
 * @param linesize*
 * @param pixelsize*
 * @param d
 */
void sceDisplaySetFrameBuf(char *topaddr, long linesize, long pixelsize, long
	d);

#ifdef __cplusplus
}
#endif

#endif
