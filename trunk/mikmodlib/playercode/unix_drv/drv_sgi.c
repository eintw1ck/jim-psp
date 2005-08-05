/*

Name:
DRV_SGI.C, version 0.4, 24/11/1997
Copyright 1996,1997 by Stephan Kanthak, kanthak@i6.informatik.rwth-aachen.de

History:
Version 0.1 - first working, released version
Version 0.2 - updated to use new driver API
Version 0.3 - new sampling rates, larger values for MM_..., bugfixes
Version 0.4 - re-integration into mikmod-3.0.1

Description:
Mikmod driver for output on SGI audio system (needs libaudio from the
dmedia package).

Portability:
SGI only. Mainly based on voxware driver.

Fragment configuration:
=======================

You can use the environment variables 'MM_SGI_FRAGSIZE' and
'MM_SGI_BUFSIZE' to override the default size of the audio buffer. If you
experience crackles & pops, try experimenting with these values.

Please read README.SGI first before contacting the author because there are
some things to know about the specials of the SGI audio driver.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dmedia/audio.h>
#include "mikmod.h"
#include "mmio.h"


#define DEFAULT_SGI_FRAGSIZE  20000
#define DEFAULT_SGI_BUFSIZE   40000


static ALconfig sgi_config;
static ALport sgi_port;
static int sample_factor;
static int sgi_fragsize;
static int sgi_bufsize;
static SBYTE *audiobuffer;


static BOOL SGI_IsThere(void)
{
	long params[] = { AL_OUTPUT_RATE, 0 };

	ALqueryparams(AL_DEFAULT_DEVICE, params, 2);
	if (params[1] != 0) return 1;
	else return 0;
}

static BOOL SGI_Init(void)
{
	char *env;
	int play_rate;
	int fragsize,numfrags;
	long chpars[] = { AL_OUTPUT_RATE, AL_RATE_22050 };

	switch(md_mixfreq) {
	case 8000:
		chpars[1] = AL_RATE_8000;
		break;
	case 11025:
		chpars[1] = AL_RATE_11025;
		break;
	case 16000:
		chpars[1] = AL_RATE_16000;
		break;
	case 22050:
		chpars[1] = AL_RATE_22050;
		break;
	case 32000:
		chpars[1] = AL_RATE_32000;
		break;
	case 44100:
		chpars[1] = AL_RATE_44100;
		break;
	case 48000:
		chpars[1] = AL_RATE_48000;
		break;
	default:
		printf("mixing rate not supported.\n");
		return 1;
		break;
	}
	ALsetparams(AL_DEFAULT_DEVICE, chpars, 2);

	if ((sgi_config = ALnewconfig()) == 0) {
		printf("cannot configure sound device.\n");
		return 1;
	}
	
	if (md_mode & DMODE_16BITS) {
		if (ALsetwidth(sgi_config, AL_SAMPLE_16) < 0) {
			printf("samplesize of 16 bits not supported.\n");
			return 1;
		}
		sample_factor = 2;
	} else {
		if (ALsetwidth(sgi_config, AL_SAMPLE_8) < 0) {
			printf("samplesize of 8 bits not supported.\n");
			return 1;
		}
		sample_factor = 1;
	}

	if (md_mode & DMODE_STEREO) {
		if (ALsetchannels(sgi_config, AL_STEREO) < 0) {
			printf("stereo mode not supported.\n");
			return 1;
		}
	} else{
		if (ALsetchannels(sgi_config, AL_MONO) < 0) {
			printf("mono mode not supported.\n");
			return 1;
		}
	}

	if(VC_Init()){
		return 1;
	}

	sgi_fragsize=(env=getenv("MM_SGI_FRAGSIZE")) ? atol(env) : DEFAULT_SGI_BUFSIZE;
	sgi_bufsize=(env=getenv("MM_SGI_BUFSIZE")) ? atol(env) : DEFAULT_SGI_BUFSIZE;

	ALsetqueuesize(sgi_config, sgi_bufsize);
	if ((sgi_port = ALopenport("MikMod", "w", sgi_config)) == 0) {
		printf("cannot open SGI audio port.\n");
		return 1;
	}

	audiobuffer = (SBYTE *)_mm_malloc(sgi_fragsize * sizeof(char));

	if(audiobuffer==NULL){
		VC_Exit();
		return 1;
	}
	
	return 0;
}


static void SGI_Exit(void)
{
	free(audiobuffer);
	VC_Exit();
}


BOOL SGI_Reset(void)
{
        SGI_Exit();
        return SGI_Init();
}


static void SGI_Update(void)
{
	VC_WriteBytes(audiobuffer, sgi_fragsize);
	ALwritesamps(sgi_port,audiobuffer, sgi_fragsize/sample_factor);
}


MDRIVER drv_sgi={
	NULL,
	"SGI Audio System",
	"SGI Audio System Driver v0.4 - by Stephan Kanthak",
	0,255,
	SGI_IsThere,
	VC_SampleLoad,
	VC_SampleUnload,
	VC_SampleSpace,
	VC_SampleLength,
	SGI_Init,
	SGI_Exit,
	SGI_Reset,
        VC_SetNumVoices,
        VC_PlayStart,
        VC_PlayStop,
	SGI_Update,
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
