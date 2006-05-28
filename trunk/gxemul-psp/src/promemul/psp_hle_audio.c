
#include "psp_hle.h"

SYSCALL(0x2119,0x8c1009b2,0x00000000,"sceAudioOutput",HLE_unknown,4);
SYSCALL(0x211a,0x136caf51,0x00000000,"sceAudioOutputBlocking",HLE_unknown,4);
SYSCALL(0x211b,0xe2d56b2d,0x00000000,"sceAudioOutputPanned",HLE_unknown,4);
SYSCALL(0x211c,0x13f592bc,0x00000000,"sceAudioOutputPannedBlocking",HLE_unknown,4);
SYSCALL(0x211d,0x5ec81c55,0x00000000,"sceAudioChReserve",HLE_sceAudioChReserve,3);
SYSCALL(0x211e,0x41efade7,0x00000000,"sceAudioOneshotOutput",HLE_unknown,4);
SYSCALL(0x211f,0x6fc46853,0x00000000,"sceAudioChRelease",HLE_sceAudioChRelease,1);
SYSCALL(0x2120,0xe9d97901,0x00000000,"sceAudioGetChannelRestLen",HLE_unknown,4);
SYSCALL(0x2121,0xcb2e439e,0x00000000,"sceAudioSetChannelDataLen",HLE_unknown,4);
SYSCALL(0x2122,0x95fd0c2d,0x00000000,"sceAudioChangeChannelConfig",HLE_unknown,4);
SYSCALL(0x2123,0xb7e1d8e7,0x00000000,"sceAudioChangeChannelVolume",HLE_unknown,4);
SYSCALL(0x2124,0x38553111,0x00000000,"sceAudio_38553111",HLE_unknown,4);
SYSCALL(0x2125,0x5c37c0ae,0x00000000,"sceAudio_5C37C0AE",HLE_unknown,4);
SYSCALL(0x2126,0xe0727056,0x00000000,"sceAudio_E0727056",HLE_unknown,4);
SYSCALL(0x2127,0x086e5895,0x00000000,"sceAudioInputBlocking",HLE_unknown,4);
SYSCALL(0x2128,0x6d4bec68,0x00000000,"sceAudioInput",HLE_unknown,4);
SYSCALL(0x2129,0xa708c6a6,0x00000000,"sceAudioGetInputLength",HLE_sceAudioGetInputLength,1);
SYSCALL(0x212a,0x87b2e651,0x00000000,"sceAudioWaitInputEnd",HLE_unknown,4);
SYSCALL(0x212b,0x7de61688,0x00000000,"sceAudioInputInit",HLE_unknown,4);
 
//int sceAudioChReserve(int channel, int samplecount, int format);
void HLE_sceAudioChReserve(int32_t arg0,int32_t arg1,int32_t arg2)
{
	debug("HLE_sceAudioChReserve(channel:%08x samplecount:%08x format:%08x) ",arg0,arg1,arg2);
	HLE_RETURN_INT(0);
}

//int sceAudioChRelease(int channel);
void HLE_sceAudioChRelease(int32_t arg0)
{
	debug("HLE_sceAudioChRelease(channel:%08x) ",arg0);
	HLE_RETURN_INT(0);
}



void HLE_sceAudioGetInputLength(int32_t arg0)
{
	debug("HLE_sceAudioGetInputLength(channel:%08x) ",arg0);
	HLE_RETURN_INT(4);
}
