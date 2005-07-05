/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */
      
#ifndef __pspgu_h__
#define __pspgu_h__

#include <psptypes.h>

/** @defgroup GU Graphics Utility Library
 *
 */

#if defined(__cplusplus)
extern "C" {
#endif

#define GU_PRIM_POINTS          (0)
#define GU_PRIM_LINES           (1)
#define GU_PRIM_LINESTRIPS      (2)
#define GU_PRIM_TRIANGLES       (3)
#define GU_PRIM_TRISTRIPS       (4)
#define GU_PRIM_TRIFANS         (5)
#define GU_PRIM_SPRITES         (6)

#define GU_STATE_ATE		(0) // Alpha Test
#define GU_STATE_ZTE		(1) // Depth Test
#define GU_STATE_SCISSOR	(2)
#define GU_STATE_UNKNOWN3	(3)
#define GU_STATE_ALPHA		(4) // Alpha Blend
#define GU_STATE_CULL		(5)
#define GU_STATE_UNKNOWN6	(6)
#define GU_STATE_UNKNOWN7	(7)
#define GU_STATE_UNKNOWN8	(8)
#define GU_STATE_TEXTURE	(9)
#define GU_STATE_LIGHTING	(10)
#define GU_STATE_LIGHT0		(11) // Light 0 Enable
#define GU_STATE_LIGHT1		(12) // Light 1 Enable
#define GU_STATE_LIGHT2		(13) // Light 2 Enable
#define GU_STATE_LIGHT3		(14) // Light 3 Enable
#define GU_STATE_UNKNOWN15	(15)
#define GU_STATE_UNKNOWN16	(16)
#define GU_STATE_UNKNOWN17	(17)
#define GU_STATE_UNKNOWN18	(18)
#define GU_STATE_UNKNOWN19	(19)
#define GU_STATE_PATCH_FACE	(20) // sceGuPatchFrontFace()
#define GU_STATE_UNKNOWN21	(21)

#define GU_DISPLAY_OFF		(0)
#define GU_DISPLAY_ON		(1)

#define GU_MATRIX_PROJECTION	(0)
#define GU_MATRIX_VIEW		(1)
#define GU_MATRIX_WORLD		(2)
#define GU_MATRIX_TEXTURE	(3) /* this is untested, only assumed */

/* TODO: should the GE_ defines move to pspge.h? It's not like they are exclusive to pspgu */

/* vertex type by Neovangelist */
#define GE_SETREG_VTYPE(tt, ct, nt, mt, wt, it, nw, vb, dm) \
        ((u32)(tt)      | ((u32)(ct) << 2)      | ((u32)(nt) << 5) | \
        ((u32)(mt) << 7)| ((u32)(wt) << 9)      | ((u32)(it) << 11) | \
        ((u32)(nw) <<14)| ((u32)(vb) << 18)     | ((u32)(dm) << 23))

#define GE_TT_NONE		0x00
#define GE_TT_8BIT		0x01
#define GE_TT_16BIT		0x02
#define GE_TT_32BITF		0x03

#define GE_CT_NONE		0x00
#define GE_CT_RES1		0x01
#define GE_CT_RES2		0x02
#define GE_CT_RES3		0x03
#define GE_CT_5650		0x04
#define GE_CT_5551		0x05
#define GE_CT_4444		0x06
#define GE_CT_8888		0x07

#define GE_NT_NONE		0x00
#define GE_NT_8BIT		0x01
#define GE_NT_16BIT		0x02
#define GE_NT_32BITF		0x03

#define GE_MT_RES		0x00
#define GE_MT_8BIT		0x01
#define GE_MT_16BIT		0x02
#define GE_MT_32BITF		0x03

#define GE_WT_NONE		0x00
#define GE_WT_8BIT		0x01
#define GE_WT_16BIT		0x02
#define GE_WT_32BITF		0x03

#define GE_IT_NONE		0x00
#define GE_IT_8BIT		0x01
#define GE_IT_16BIT		0x02
#define GE_IT_RES		0x03

#define GE_BM_3D		0x00
#define GE_BM_2D		0x01

#define GE_PSM_5650		(0)
#define GE_PSM_5551		(1)
#define GE_PSM_4444		(2)
#define GE_PSM_8888		(3)

#define GE_TPSM_5650		(0)
#define GE_TPSM_5551		(1)
#define GE_TPSM_4444		(2)
#define GE_TPSM_8888		(3)
#define GE_TPSM_T4		(4)
#define GE_TPSM_T8		(5)

#define GE_SHADE_FLAT		(0)
#define GE_SHADE_GOURAUD	(1)

#define GE_FILTER_POINT		(0)
#define GE_FILTER_LINEAR	(1)

#define GE_WRAP_REPEAT		(0)
#define GE_WRAP_CLAMP		(1)

#define GE_FACE_CW		(0)
#define GE_FACE_CCW		(1)

#define GE_TEST_NEVER		(0)
#define GE_TEST_ALWAYS		(1)
#define GE_TEST_FUNCTION2	(2) /* figure these out */
#define GE_TEST_FUNCTION3	(3)
#define GE_TEST_LESS		(4)
#define GE_TEST_LEQUAL		(5)
#define GE_TEST_GREATER		(6)
#define GE_TEST_GEQUAL		(7)

#define GE_CLEAR_COLOR		(1)
#define GE_CLEAR_DEPTH		(4)

#define GE_TFX_MODULATE		(0)
#define GE_TFX_REPLACE		(3)
#define GE_TFX_ADD		(4)

#define GE_TCC_RGB		(0)
#define GE_TCC_RGBA		(1)

#define GE_ALPHA_ADD		(0)
#define GE_ALPHA_SUBTRACT	(1)

#define GE_ALPHA_SRC_COLOR		(0)
#define GE_ALPHA_ONE_MINUS_SRC_COLOR	(1)
#define GE_ALPHA_SRC_ALPHA		(2)
#define GE_ALPHA_ONE_MINUS_SRC_ALPHA	(3)

#define GE_ALPHA_DST_COLOR		(0)
#define GE_ALPHA_ONE_MINUS_DST_COLOR	(1)

#define GE_ALPHA_FIX			(10)

/** @addtogroup GU */
/*@{*/

/**
  * Set depth buffer parameters
  *
  * @param zbp - VRAM pointer where the depthbuffer should start
  * @param zbw - The width of the depth-buffer (block-aligned)
  *
**/
void sceGuDepthBuffer(void* zbp, int zbw);

/**
  * Set display buffer parameters
  *
  * @par Example: Setup a standard 16-bit display buffer
  * @code
  * sceGuDispBuffer(480,272,(void*)512*272*2,512); // 480*272, skipping the draw buffer located at address 0
  * @endcode
  *
  * @param width - Width of the display buffer in pixels
  * @param height - Width of the display buffer in pixels
  * @param dispbp - VRAM pointer to where the display-buffer starts
  * @param dispbw - Display buffer width (block aligned)
  *
**/
void sceGuDispBuffer(int width, int height, void* dispbp, int dispbw);

/**
  * Set draw buffer parameters (and store in context for buffer-swap)
  *
  * @par Example: Setup a standard 16-bit draw buffer
  * @code
  * sceGuDispBuffer(GE_PSM_5551,(void*)0,512);
  * @endcode
  *
  * @param psm - Pixel format to use for rendering (and display)
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
void sceGuDrawBuffer(int psm, void* fbp, int fbw);

/**
  * Set draw buffer directly, not storing parameters in the context
  *
  * @param psm - Pixel format to use for rendering
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
void sceGuDrawBufferList(int psm, void* fbp, int fbw);

/**
  * Turn display on or off
  *
  * Available states are:
  *   - GE_DISPLAY_ON (1) - Turns display on
  *   - GE_DISPLAY_OFF (0) - Turns display off
  *
  * @param state - Turn display on or off
  * @returns State of the display prior to this call
**/
int sceGuDisplay(int state);

/**
  * Select which depth-test function to use
  *
  * Valid choices for the depth-test are:
  *   - GE_TEST_NEVER - No pixels pass the depth-test
  *   - GE_TEST_ALWAYS - All pixels pass the depth-test
  *   - GE_TEST_FUNCTION2 - Figure this one out
  *   - GE_TEST_FUNCTION3 - Figure this one out
  *   - GE_TEST_LESS - Pixels that are less in depth passes
  *   - GE_TEST_LEQUAL - Pixels that are less or equal in depth passes
  *   - GE_TEST_GREATER - Pixels that are greater in depth passes
  *   - GE_TEST_GEQUAL - Pixels that are greater or equal passes
  *
  * @param function - Depth test function to use
**/
void sceGuDepthFunc(int function);

/**
  * Depth write mask
  *
  * @param mask - Which bits to mask writes to?
**/
void sceGuDepthMask(unsigned int mask);

void sceGuDepthOffset(unsigned int offset);
void sceGuDepthRange(int near, int far);
void sceGuFog(float near, float far, unsigned int color);

/**
  * Initalize the GU system
  *
  * This function MUST be called as the first function, otherwise state is undetermined.
**/
void sceGuInit(void);

/**
  * Shutdown the GU system
  *
  * Called when GU is no longer needed
**/
void sceGuTerm(void);

void sceGuBreak(int a0);
void sceGuContinue(void);
void* sceGuSetCallback(int index, void (*callback)(int));
void sceGuSignal(int a0, int a1);

/**
  * Send raw float-command to the GE
  *
  * The argument is converted into a 24-bit float before transfer.
  *
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
void sceGuSendCommandf(int cmd, float argument);

/**
  * Send raw command to the GE
  *
  * Only the 24 lower bits of the command is passed along.
  *
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
void sceGuSendCommandi(int cmd, int argument);

/**
  * Allocate memory on the current display list for temporary storage
  *
  * @param size - How much memory allocate
  * @returns Memory-block ready for use
**/
void* sceGuGetMemory(int size);

/**
  * Start filling a new display-context
  *
  * Context 0 is the display context, contexts 1 and 2 are buffered and not directly rendered
  *
  * @param cid - Context ID (0,1,2)
  * @param list - Pointer to display-list (16 byte aligned)
**/
void sceGuStart(int cid, void* list);

/**
  * Finish current display list and possibly kick the display list
  *
  * If the current context is 0 (display context), the list is kicked. Otherwise the context
  * is popped back to the parent context and rendering commands may continue
  *
  * @returns Size of finished display list
**/
int sceGuFinish(void);

/**
  * Call previously generated display-list
  *
  * @param list - Display list to call
**/
void sceGuCallList(const void* list);

void sceGuCallMode(int mode);

/**
  * Check how large the current display-list is
  *
  * @returns The size of the current display list
**/
int sceGuCheckList(void);

void sceGuSendList(unsigned int mode, void* list, void* data);

/**
  * Swap display and draw buffer
**/
void* sceGuSwapBuffers(void);

/**
  * Wait until display list has finished executing
  *
  * @par Example: Wait for the currently executing display list
  * @code
  * sceGuSync(0,0);
  * @endcode
  *
  * @param mode - Unknown meaning, pass 0 for now
  * @param a1 - Unknown meaning, pass 0 for now
  * @returns Unknown at this time
**/
int sceGuSync(int mode, int a1);

/**
  * Draw array of vertices forming primitives
  *
  * Available primitive-types are:
  *   - GE_PRIM_POINTS - Single pixel points (1 vertex per primitive)
  *   - GE_PRIM_LINES - Single pixel lines (2 vertices per primitive)
  *   - GE_PRIM_LINESTRIPS - Single pixel line-strips (2 vertices for the first primitive, 1 for every following)
  *   - GE_PRIM_TRIANGLES - Filled triangles (3 vertices per primitive)
  *   - GE_PRIM_TRISTRIPS - Filled triangles-strips (3 vertices for the first primitive, 1 for every following)
  *   - GE_PRIM_TRIFANS - Filled triangle-fans (3 vertices for the first primitive, 1 for every following)
  *   - GE_PRIM_SPRITES - Filled blocks (2 vertices per primitive)
  *
  * The vertex-type decides how the vertices align and what kind of information they contain.
  * NOTE: Every vertex must align to 32 bits, which means that you HAVE to pad if it does not add up!
  *
  * @par Example: Render 400 triangles, with floating-point texture coordinates, and floating-point position, and no indices
  * @code
  * sceGuDrawArray(GU_PRIM_TRIANGLES,GE_SETREG_VTYPE(GE_TT_32BITF,0,0,GE_MT_32BITF,0,0,0,0,0),400,0,vertices);
  * @endcode
  *
  * @param prim - What kind of primitives to render
  * @param vtype - Vertex type to process (look at GU_SETREG_VTYPE)
  * @param count - How many vertices to process
  * @param indices - Optional pointer to an index-list
  * @param vertices - Optional pointer to an vertex-list
**/
void sceGuDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices);

void sceGuBeginObject(int type, int a1, void* indices, void* vertices);
void sceGuEndObject(void);

/**
  * Enable or disable GE state
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to change
  * @param status - Wether to enable or disable the state
**/
void sceGuSetStatus(int state, int status);

/**
  * Get if state is currently enabled or disabled
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to query about
  * @returns Wether state is enabled or not
**/
int sceGuGetStatus(int state);

/**
  * Set the status on all 22 available states
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param status - Bit-mask (0-21) containing the status of all 22 states
**/
void sceGuSetAllStatus(int status);

/**
  * Query status on all 22 available states
  *
  * Look at sceGuEnable() for a list of states
  *
  * @returns Status of all 22 states as a bitmask (0-21)
**/
int sceGuGetAllStatus(void);

/**
  * Enable GE state
  *
  * The currently available states are:
  *   - GE_STATE_ATE - Alpha testing
  *   - GE_STATE_ZTE - Depth testing
  *   - GE_STATE_SCISSOR - Display custom scissoring
  *   - GU_STATE_ALPHA - Alpha blending
  *   - GU_STATE_CULL - Primitive culling
  *   - GU_STATE_TEXTURE - Texture mapping
  *   - GU_STATE_LIGHTING - Hardware lighting enable
  *   - GU_STATE_LIGHT0 - Light 0 enable
  *   - GU_STATE_LIGHT1 - Light 1 enable
  *   - GU_STATE_LIGHT2 - Light 2 enable
  *   - GU_STATE_LIGHT3 - Light 3 enable
  *
  * @param state - Which state to enable
**/
void sceGuEnable(int state);

/**
  * Disable GE state
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to disable
**/
void sceGuDisable(int state);

/* lights */
void sceGuLight(int index, int a1, int a2, const ScePspFVector3* position);
void sceGuLightAtt(int index, float f12, float f13, float f14);
void sceGuLightColor(int light, int type, unsigned int color);
void sceGuLightMode(int mode);
void sceGuLightSpot(int index, const ScePspFVector3* direction, float f12, float f13);

/**
  * Clear current drawbuffer
  *
  * Available clear-flags are:
  *   - GE_CLEAR_COLOR - Clears the color-buffer
  *   - GE_CLEAR_DEPTH - Clears the depth-buffer
  *
  * @param flags - Which part of the buffer to clear
**/
void sceGuClear(int flags);

/**
  * Set the current clear-color
  *
  * @param color - Color to clear with
**/
void sceGuClearColor(unsigned int color);

/**
  * Set the current clear-depth
  *
  * @param depth - Set which depth to clear with (0x0000-0xffff)
**/
void sceGuClearDepth(unsigned int depth);

void sceGuClearStencil(unsigned int stencil);
void sceGuPixelMask(unsigned int mask);

/**
  * Set current primitive color
  *
  * @param color - Which color to use (overriden by vertex-colors)
**/
void sceGuColor(unsigned int color);

void sceGuColorFunc(int a0, unsigned int color, int a2);
void sceGuColorMaterial(int a0);
void sceGuAlphaFunc(int a0, int a1, int a2);
void sceGuAmbient(unsigned int color);
void sceGuAmbientColor(unsigned int color);

/**
  * Set the blending-mode
  *
  * Available blending-operations are:
  *   - GE_ALPHA_ADD - Additive blend
  *   - GE_ALPHA_SUB - Subtractive blend
  *
  * Available blending-functions are:
  *   - GE_ALPHA_SRC_COLOR
  *   - GE_ALPHA_ONE_MINUS_SRC_COLOR
  *   - GE_ALPHA_SRC_ALPHA
  *   - GE_ALPHA_ONE_MINUS_SRC_ALPHA
  *   - GE_ALPHA_DST_COLOR
  *   - GE_ALPHA_ONE_MINUS_DST_COLOR
  *   - GE_ALPHA_FIX
  *
  * @param op - Blending Operation
  * @param src - Blending function for source operand
  * @param dest - Blending function for dest operand
  * @param srcfix - Fix value for GL_ALPHA_FIX (source operand)
  * @param destfix - Fix value for GL_ALPHA_FIX (dest operand)
**/
void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix);

void sceGuMaterial(int mode, int color);
void sceGuModelColor(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void sceGuStencilFunc(unsigned int a0, unsigned int a1, unsigned int a2);
void sceGuStencilOp(unsigned int a0, unsigned int a1, unsigned int a2);
void sceGuSpecular(float power);

/**
  * Set the current face-order (for culling)
  *
  * This only has effect when culling is enabled (GE_STATE_CULL)
  *
  * Culling order can be:
  *   - GE_FACE_CW - Clockwise primitives are not culled
  *   - GE_FACE_CCW - Counter-clockwise are not culled
  *
  * @param order - Which order to use
**/
void sceGuFrontFace(int order);

void sceGuLogicalOp(int a0);
void sceGuSetDither(const ScePspIMatrix4* matrix);

/**
  * Set how primitives are shaded
  *
  * The available shading-methods are:
  *   - GE_SHADE_FLAT - Primitives are flatshaded, the last vertex-color takes effet
  *   - GE_SHADE_GOURAUD - Primtives are gouraud-shaded, all vertex-colors take effect
  *
  * @param mode - Which mode to use
**/
void sceGuShadeModel(int mode);

/* textures */
void sceGuCopyImage(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int t0, unsigned int t1, void* ptr1, unsigned int t3, unsigned int stack0, unsigned int stack1, void* ptr2);
void sceGuTexEnvColor(unsigned int color);

/**
  * Set how the texture is filtered
  *
  * Available filters are:
  *   - GE_FILTER_POINT - Texture is point-filtered
  *   - GE_FILTER_LINEAR - Texture is bilinear-filtered
  *
  * @param a0 - Filter to use (when magnifying? mag?)
  * @param a1 - Filter to use (when minimizing? min?)
**/
void sceGuTexFilter(unsigned int a0, unsigned int a1);

/**
  * Flush texture page-cache
  *
  * Do this if you have copied/rendered into an area currently in the texture-cache
  *
**/
void sceGuTexFlush(void);

/**
  * Set how textures are applied
  *
  * Available apply-modes are: (TFX)
  *   - GE_TFX_MODULATE - The texture is multiplied with the current diffuse fragment
  *   - GE_TFX_REPLACE - The texture replaces the fragment
  *   - GE_TFX_ADD - The texture is added on-top of the diffuse fragment
  *   
  * Available component-modes are: (TCC)
  *   - GE_TCC_RGB - The texture alpha does not have any effect
  *   - GE_TCC_RGBA - The texture alpha is taken into account
  *
  * @param tfx - Which apply-mode to use
  * @param tcc - Which component-mode to use
**/
void sceGuTexFunc(int tfx, int tcc);

/**
  * Set current texturemap
  *
  * The texture may reside in main RAM, but the GE can only read from RAM with 50MB/s,
  * instead as from VRAM with 500MB/s (at almost optimal conditions)
  *
  * @param mipmap - Mipmap level
  * @param width - Width of texture (must be a power of 2)
  * @param height - Height of texture (must be a power of 2)
  * @param tbw - Texture Buffer Width (block-aligned)
  * @param tbp - Texture buffer pointer (16 byte aligned)
**/
void sceGuTexImage(int mipmap, int width, int height, int tbw, const void* tbp);
void sceGuTexLevelMode(unsigned int a0, float f12);
void sceGuTexMapMode(unsigned int a0, unsigned int a1, unsigned int a2);

/**
  * Set texture-mode parameters
  *
  * Available texture-formats are:
  *   - GE_TPSM_5650 - Hicolor, 16-bit
  *   - GE_TPSM_5551 - Hicolor, 16-bit
  *   - GE_TPSM_4444 - Hicolor, 16-bit
  *   - GE_TPSM_8888 - Truecolor, 32-bit
  *   - GE_TPSM_T4 - Indexed, 4-bit (2 pixels per byte)
  *   - GE_TPSM_T8 - Indexed, 8-bit
  *
  * @param tpsm - Which texture format to use
  * @param a1 - Unknown, set to 0
  * @param a2 - Unknown, set to 0
  * @param swizzle - Set to 1 to swizzle texture-reads
**/
void sceGuTexMode(int tpsm, int a1, int a2, int swizzle);
void sceGuTexOffset(float u, float v);
void sceGuTexProjMapMode(unsigned int mode);
void sceGuTexScale(float u, float v);
void sceGuTexSlope(float slope);
void sceGuTexSync();

/**
  * Set if the texture should repeat or clamp
  *
  * Available modes are:
  *   - GE_WRAP_CLAMP - Texture clamps at the border
  *   - GE_WRAP_REPEAT - The texture repeats after crossing the border
  *
  * @param u - Wrap-mode for the U direction
  * @param v - Wrap-mode for the V direction
**/
void sceGuTexWrap(int u, int v);

/**
  * Upload CLUT (Color Lookup Table)
  *
  * @param num_blocks - How many blocks of 8 entries to upload (32*8 is 256 colors)
  * @param cbp - Pointer to palette (16 byte aligned)
**/
void sceGuClutLoad(int num_blocks, const void* cbp);

/**
  * Set current CLUT mode
  *
  * Available pixel formats for palettes are:
  *   - GE_TPSM_5650
  *   - GE_TPSM_5551
  *   - GE_TPSM_4444
  *   - GE_TPSM_8888
  *
  * @param cpsm - Which pixel format to use for the palette
  * @param a1 - Unknown, set to 0
  * @param a2 - Unknown, set to 0
  * @param a3 - Unknown, set to 0
**/
void sceGuClutMode(unsigned int cpsm, unsigned int a1, unsigned int a2, unsigned int a3);

/**
  * Set virtual coordinate offset
  *
  * The PSP has a virtual coordinate-space of 4096x4096, this controls where rendering is performed
  * 
  * @par Example: Center the virtual coordinate range
  * @code
  * sceGuOffset(2048-(480/2),2048-(480/2));
  * @endcode
  *
  * @param x - Offset (0-4095)
  * @param y - Offset (0-4095)
**/
void sceGuOffset(unsigned int x, unsigned int y);

/**
  * Set what to scissor within the current viewport
  *
  * Note that scissoring is only performed if the custom scissoring is enabled (GU_STATE_SCISSOR)
  *
  * @param x - Left of scissor region
  * @param y - Top of scissor region
  * @param w - Width of scissor region
  * @param h - Height of scissor region
**/
void sceGuScissor(int x, int y, int w, int h);

/**
  * Set current viewport
  *
  * @par Example: Setup a viewport of size (480,272) with origo at (2048,2048)
  * @code
  * sceGuViewport(2048,2048,480,272);
  * @endcode
  *
  * @param cx - Center for horizontal viewport
  * @param cy - Center for vertical viewport
  * @param width - Width of viewport
  * @param height - Height of viewport
**/
void sceGuViewport(int cx, int cy, int width, int height);

/* patches */
void sceGuDrawBezier(int vertex_type, int a1, int a2, void* indices, void* vertices);
void sceGuPatchDivide(unsigned int a0, unsigned int a1);
void sceGuPatchFrontFace(unsigned int a0);
void sceGuPatchPrim(unsigned int a0);

/**
  * Set transform matrices
  *
  * Available matrices are:
  *   - GE_MATRIX_PROJECTION - View->Projection matrix, 4x4
  *   - GE_MATRIX_VIEW - World->View matrix, 3*4
  *   - GE_MATRIX_WORLD - Object->World matrix, 3*4
  *   - GE_MATRIX_TEXTURE - Untested, only assumed, 3*4
  *
  * @param type - Which matrix-type to set
  * @param matrix - Matrix to load
**/
void sceGuSetMatrix(int type, const ScePspFMatrix4* matrix);

void sceGuBoneMatrix(unsigned int index, const ScePspFMatrix4* matrix);
void sceGuMorphWeight(int index, float weight);

/* sprites */
void sceGuSpriteMode(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);

/* debugging */
void sceGuDebugFlush(void);

/*@}*/

#if defined(__cplusplus)
};
#endif

#endif
