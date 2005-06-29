#ifndef __gu_h__
#define __gu_h__

#if defined(__cplusplus)
extern "C" {
#endif

#define GU_STATE_ATE            (0) // Alpha Test
#define GU_STATE_DEPTH_TEST     (1) // Depth Test
#define GU_STATE_SCISSOR        (2)
#define GU_STATE_UNKNOWN3       (3)
#define GU_STATE_BLEND          (4) // Alpha Blend
#define GU_STATE_UNKNOWN5       (5)
#define GU_STATE_UNKNOWN6       (6)
#define GU_STATE_UNKNOWN7       (7)
#define GU_STATE_UNKNOWN8       (8)
#define GU_STATE_UNKNOWN9       (9)
#define GU_STATE_UNKNOWN10      (10)
#define GU_STATE_LIGHT0         (11) // Light 0 Enable
#define GU_STATE_LIGHT1         (12) // Light 1 Enable
#define GU_STATE_LIGHT2         (13) // Light 2 Enable
#define GU_STATE_LIGHT3         (14) // Light 3 Enable
#define GU_STATE_UNKNOWN15      (15)
#define GU_STATE_UNKNOWN16      (16)
#define GU_STATE_UNKNOWN17      (17)
#define GU_STATE_UNKNOWN18      (18)
#define GU_STATE_UNKNOWN19      (19)
#define GU_STATE_PATCH_FACE     (20) // sceGuPatchFrontFace()
#define GU_STATE_UNKNOWN21      (21)

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
