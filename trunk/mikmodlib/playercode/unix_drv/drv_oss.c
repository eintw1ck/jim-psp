/*

Name:
DRV_VOX.C

Description:
Mikmod driver for output on linux and FreeBSD Open Sound System (OSS)
(/dev/dsp) 

Portability:  VoxWare/SS/OSS land. Linux, FreeBSD (NetBSD & SCO?)

New fragment configuration code done by Rao:
============================================

You can use the environment variables 'MM_FRAGSIZE' and 'MM_NUMFRAGS' to 
override the default size & number of audio buffer fragments. If you 
experience crackles & pops, try experimenting with these values.

Read experimental.txt within the VoxWare package for information on these 
options. They are _VERY_ important with relation to sound popping and smooth
playback.                                                        

In general, the slower your system, the higher these values need to be. 

MM_NUMFRAGS is within the range 2 to 255 (decimal)

MM_FRAGSIZE is is within the range 7 to 17 (dec). The requested fragment size 
will be 2^MM_FRAGSIZE

- This driver DOES work with MikMod 3.0
- modifed to use an ioctl() to figure out how much data to do with 
	each write, keeps us from blocking extensivly 

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef __FreeBSD__
#include <machine/soundcard.h>
#else
#include <sys/soundcard.h>
#endif /* __FreeBSD__ */
#include <sys/ioctl.h>
#include <sys/wait.h>
#include "mikmod.h"
#include "mmio.h"

#define DEFAULT_FRAGSIZE 17
#define DEFAULT_NUMFRAGS 4

static int sndfd;
static int fragmentsize;
static char* audiobuffer;


static BOOL OSS_IsThere(void)
{
	return (access("/dev/dsp",W_OK)==0);
}


static BOOL OSS_Init(void)
{
	char *env;
	int play_precision,play_stereo,play_rate;
	int fragsize,numfrags;
	
	if((sndfd=open("/dev/dsp",O_WRONLY))<0){
		return 1;
	}

	fragsize=(env=getenv("MM_FRAGSIZE")) ? atoi(env) : DEFAULT_FRAGSIZE;
	numfrags=(env=getenv("MM_NUMFRAGS")) ? atoi(env) : DEFAULT_NUMFRAGS;
		
	if(fragsize<7 || fragsize>17)  fragsize=DEFAULT_FRAGSIZE;
	if(numfrags<2 || numfrags>255) numfrags=DEFAULT_NUMFRAGS;

	fragmentsize=(numfrags<<16) | fragsize;
	
#ifndef __FreeBSD__   
	if(ioctl(sndfd, SNDCTL_DSP_SETFRAGMENT, &fragmentsize)<0){
		close(sndfd);
		return 1;
	}
#endif /* __FreeBSD__ */

	play_precision = (md_mode & DMODE_16BITS) ? 16 : 8;
	play_stereo= (md_mode & DMODE_STEREO) ? 1 : 0;
	play_rate=md_mixfreq;

	if(ioctl(sndfd, SNDCTL_DSP_SAMPLESIZE, &play_precision) == -1 || 
	   ioctl(sndfd, SNDCTL_DSP_STEREO, &play_stereo) == -1 ||
	   ioctl(sndfd, SNDCTL_DSP_SPEED, &play_rate) == -1){
		close(sndfd);
		return 1;
	}

	ioctl(sndfd, SNDCTL_DSP_GETBLKSIZE, &fragmentsize);

/*	Lose this for now - it will confuse ncurses etc...
	printf("Fragment size is %ld\n",fragmentsize); */

	if(VC_Init()){
		close(sndfd);
		return 1;
	}

	audiobuffer = (char*) _mm_malloc(fragmentsize * sizeof(char) * 2);
	
	if(audiobuffer==NULL){
		VC_Exit();
		close(sndfd);
		return 1;
	}
	
	return 0;
}


static void OSS_Exit(void)
{
	free(audiobuffer);
	VC_Exit();
	close(sndfd);
}


static void OSS_Update(void)
{
	audio_buf_info buffinf;
	ioctl(sndfd, SNDCTL_DSP_GETOSPACE, &buffinf);
	VC_WriteBytes(audiobuffer,buffinf.fragments*buffinf.fragsize);
	write(sndfd,audiobuffer,buffinf.fragments*buffinf.fragsize);
}

BOOL OSS_Reset(void)
{
	ioctl(sndfd, SNDCTL_DSP_RESET);
	VC_Exit();
	return VC_Init();
}


MDRIVER drv_oss =
{
	NULL,
	"Open Sound System (OSS)",
	"Open Sound System (OSS) Driver v1.3 - by Rao & MikMak (with a little hacking from Pete)",
	0,255,
	OSS_IsThere,
	VC_SampleLoad,
	VC_SampleUnload,
	VC_SampleSpace,
	VC_SampleLength,
	OSS_Init,
	OSS_Exit,
	OSS_Reset,
	VC_SetNumVoices,
	VC_PlayStart,
	VC_PlayStop,
	OSS_Update,
	VC_VoiceSetVolume,
	VC_VoiceSetFrequency,
	VC_VoiceSetPanning,
	VC_VoicePlay,
	VC_VoiceStop,
	VC_VoiceStopped,
	VC_VoiceReleaseSustain,
	VC_VoiceGetPosition,
	VC_VoiceRealVolume
};
