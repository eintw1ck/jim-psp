#include "config.h"
#include "aalib.h"

#include <pspgu.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <Font.c>


#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */


struct Vertex
{
	        float u,v;
	        float x,y,z;
};



static unsigned int __attribute__((aligned(16))) list[262144*2];

void init_driver_gu() {

        sceGuInit();
        sceGuStart(GU_DIRECT,list);
        sceGuDrawBuffer(GU_PSM_5551,(void*)0,BUF_WIDTH);
        sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,(void*)FRAME_SIZE,BUF_WIDTH);
        sceGuDepthBuffer((void*)(FRAME_SIZE*2),BUF_WIDTH);
        sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
        sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
        sceGuDepthRange(0xc350,0x2710);
        sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
        sceGuEnable(GU_SCISSOR_TEST);

        sceGuColorFunc(GU_NOTEQUAL,0,0xffff);
        sceGuEnable(GU_COLOR_TEST);

        sceGuFrontFace(GU_CW);

        sceGuFinish();
        sceGuSync(0,0);
        sceDisplayWaitVblankStart();
        sceGuDisplay(GU_TRUE);



}

void draw_char(char car,int x, int y)
{
        int i=0,n=0,u,v;
        char c;


        sceGuStart(GU_DIRECT,list);
                sceGuEnable(GU_TEXTURE_2D);
                sceGuTexMode(GU_PSM_5551,0,0,0);
                sceGuTexImage(0,512,512,512,FontData); // width, height, buffer width, tbp
                sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGB);
                sceGuTexFilter(GU_NEAREST,GU_NEAREST);
                sceGuTexWrap(GU_CLAMP,GU_CLAMP);

                sceGuAmbientColor(0xffffffff);

                struct Vertex* vertices = sceGuGetMemory( 200 * sizeof(struct Vertex));

                //while(1){
                ///if ((c=car) != '\0') {
			c=car;

                        v = (c-32)/16;
                        u = (c-32)%16;

                        vertices[n].u = u*16;
                        vertices[n].v = v*16;
                        vertices[n].x = x;
                        vertices[n].y = y;

                        vertices[n+1].u = u*16 +16;
                        vertices[n+1].v = v*16 +16;
                        vertices[n+1].x = x+6;
                        vertices[n+1].y = y+6;

                        n+=2;
                        x+=1;
                        i++;
                //}
                //else break;
                //}

                sceGuDrawArray(GU_SPRITES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_2D,n,0,vertices);
                sceGuFinish();
                sceGuSync(0,0);

}


static int gu_init(struct aa_hardware_params *p, void *none, struct aa_hardware_params *dest, void **n)
{
    static struct aa_hardware_params def={NULL, AA_NORMAL_MASK | AA_EXTENDED};
    *dest=def;

    
    //init gu
    init_driver_gu();
     
    
    //pspDebugScreenInit();
    //pspDebugScreenClear();
    //sceDisplayWaitVblankStart();
    return 1;
}
static void gu_uninit(aa_context * c)
{
}
static void gu_getsize(aa_context * c, int *width, int *height)
{
}

static void gu_flush(aa_context * c)
{
    int x, y;
    for (y = 0; y < aa_scrheight(c); y++) {
	for (x = 0; x < aa_scrwidth(c)-2; x++) {
	    draw_char(c->textbuffer[x + y * aa_scrwidth(c)],x*6, y*6);
	    //pspDebugScreenPrintf("%c",c->textbuffer[x + y * aa_scrwidth(c)]);
	}

	//draw_char("\n",x,y);
	//pspDebugScreenPrintf(" \n");
    }
    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
		    
    //pspDebugScreenPrintf(" \n");
    //pspDebugScreenClear();
    //sceDisplayWaitVblankStart();
}
static void gu_gotoxy(aa_context * c, int x, int y)
{
}
struct aa_driver gu_d =
{
    "gu", "Gu diver pour psp",
    gu_init,
    gu_uninit,
    gu_getsize,
    NULL,
    NULL,
    gu_gotoxy,
    gu_flush,
    NULL
};
