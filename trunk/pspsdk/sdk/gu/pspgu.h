#ifndef __gu_h__
#define __gu_h__

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
#define GU_STATE_BLEND		(4) // Alpha Blend
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

#define GE_SHADE_FLAT		(0)
#define GE_SHADE_GOURAUD	(1)

#define GE_FILTER_POINT		(0)
#define GE_FILTER_LINEAR	(1)

#define GE_WRAP_REPEAT		(0)
#define GE_WRAP_CLAMP		(1)

#define GE_FACE_CW		(0)
#define GE_FACE_CCW		(1)

#define GE_ZTST_NEVER		(0)
#define GE_ZTST_ALWAYS		(1)
#define GE_ZTST_FUNCTION2	(2) /* figure these out */
#define GE_ZTST_FUNCTION3	(3)
#define GE_ZTST_LESS		(4)
#define GE_ZTST_LEQUAL		(5)
#define GE_ZTST_GREATER		(6)
#define GE_ZTST_GEQUAL		(7)

#define GE_CLEAR_COLOR		(1)
#define GE_CLEAR_DEPTH		(4)

#define GE_TFX_MODULATE		(0)
#define GE_TFX_REPLACE		(3)
#define GE_TFX_ADD		(4)

/* screen buffers */
void sceGuDepthBuffer(void* depth_buffer, int depth_width);
void sceGuDispBuffer(int width, int height, void* disp_buffer, int frame_width);
void sceGuDrawBuffer(int pixel_size, void* frame_buffer, int frame_width);
void sceGuDrawBufferList(int pixel_size, void* frame_buffer, int frame_width);
int sceGuDisplay(int on);

/* depth buffering */
void sceGuDepthFunc(int a0);
void sceGuDepthMask(unsigned int mask);
void sceGuDepthOffset(unsigned int offset);
void sceGuDepthRange(int near, int far);
void sceGuFog(float near, float far, unsigned int color);

/* system */
void sceGuInit(void);
void sceGuTerm(void);
void sceGuBreak(int a0);
void sceGuContinue(void);
void* sceGuSetCallback(int index, void (*callback)(int));
void sceGuSignal(int a0, int a1);
void sceGuSendCommandf(int cmd, float argument);
void sceGuSendCommandi(int cmd, int argument);

/* execution */
void* sceGuGetMemory(int size);
void sceGuStart(int cid, void* list);
int sceGuFinish(void);
void sceGuCallList(const void* list);
void sceGuCallMode(int mode);
int sceGuCheckList(void);
void sceGuSendList(unsigned int mode, void* list, void* data);
void* sceGuSwapBuffers(void);
int sceGuSync(int mode, int a1);

/* rendering */
void sceGuDrawArray(int primitive_type, int vertex_type, int count, void* indices, void* vertices);
void sceGuBeginObject(int type, int a1, void* indices, void* vertices);
void sceGuEndObject(void);

/* states */
void sceGuSetStatus(int index, int status);
int sceGuGetStatus(int state);
void sceGuSetAllStatus(int status);
int sceGuGetAllStatus(void);
void sceGuEnable(int state);
void sceGuDisable(int state);

/* lights */
void sceGuLight(int index, int a1, int a2, const float* position);
void sceGuLightAtt(int index, float f12, float f13, float f14);
void sceGuLightColor(int light, int type, unsigned int color);
void sceGuLightMode(int mode);
void sceGuLightSpot(int index, float* direction, float f12, float f13);

/* clearing */
void sceGuClear(int flags);
void sceGuClearColor(unsigned int color);
void sceGuClearDepth(unsigned int depth);
void sceGuClearStencil(unsigned int stencil);
void sceGuPixelMask(unsigned int mask);

/* appearance */
void sceGuColor(unsigned int color);
void sceGuColorFunc(int a0, unsigned int color, int a2);
void sceGuColorMaterial(int a0);
void sceGuAlphaFunc(int a0, int a1, int a2);
void sceGuAmbient(unsigned int color);
void sceGuAmbientColor(unsigned int color);
void sceGuBlendFunc(int a0, int a1, int a2, unsigned int a3, unsigned int t0);
void sceGuMaterial(int mode, int color);
void sceGuModelColor(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void sceGuStencilFunc(unsigned int a0, unsigned int a1, unsigned int a2);
void sceGuStencilOp(unsigned int a0, unsigned int a1, unsigned int a2);
void sceGuSpecular(float power);
void sceGuFrontFace(unsigned int a0);
void sceGuLogicalOp(int a0);
void sceGuSetDither(int* matrix);
void sceGuShadeModel(int mode);

/* textures */
void sceGuCopyImage(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int t0, unsigned int t1, void* ptr1, unsigned int t3, unsigned int stack0, unsigned int stack1, void* ptr2);
void sceGuTexEnvColor(unsigned int color);
void sceGuTexFilter(unsigned int a0, unsigned int a1);
void sceGuTexFlush(void);
void sceGuTexFunc(unsigned int a0, unsigned int a1);
void sceGuTexImage(int mipmap, int width, int height, int tbw, const void* tbp);
void sceGuTexLevelMode(unsigned int a0, float f12);
void sceGuTexMapMode(unsigned int a0, unsigned int a1, unsigned int a2);
void sceGuTexMode(int a0, int a1, int a2, int a3);
void sceGuTexOffset(float u, float v);
void sceGuTexProjMapMode(unsigned int mode);
void sceGuTexScale(float u, float v);
void sceGuTexSlope(float slope);
void sceGuTexSync();
void sceGuTexWrap(int u, int v);
void sceGuClutLoad(unsigned int a0, const void* cbp);
void sceGuClutMode(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);

/* view */
void sceGuOffset(unsigned int x, unsigned int y);
void sceGuScissor(int x, int y, int w, int h);
void sceGuViewport(int a0, int a1, int a2, int a3);

/* patches */
void sceGuDrawBezier(int vertex_type, int a1, int a2, void* indices, void* vertices);
void sceGuPatchDivide(unsigned int a0, unsigned int a1);
void sceGuPatchFrontFace(unsigned int a0);
void sceGuPatchPrim(unsigned int a0);

/* transform & skinning */
void sceGuSetMatrix(int type, float* matrix);
void sceGuBoneMatrix(unsigned int index, const float* matrix);
void sceGuMorphWeight(int index,float weight);

/* sprites */
void sceGuSpriteMode(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);

/* debugging */
void sceGuDebugFlush(void);


#if defined(__cplusplus)
};
#endif

#endif
