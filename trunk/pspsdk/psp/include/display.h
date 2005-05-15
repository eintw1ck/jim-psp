#ifndef __DISPLAY_H__
#define __DISPLAY_H__

void sceDisplayWaitVblankStart();
void sceDisplaySetMode(long,long,long);
void sceDisplaySetFrameBuf(char *topaddr,long linesize,long pixelsize,long);

#endif
