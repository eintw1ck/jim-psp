// Audiolib for PSP
// built on top of sceAudio, but to provide multiple thread usage and callbacks
//
// adresd 2005

#include <kernel.h>
#include <debug.h>
#include <stdlib.h>
#include <string.h>
#include <threadman.h>
#include <audio.h>

#include "audiolib.h"

int audio_ready=0;
short audio_sndbuf[AUDIO_CHANNELS][2][AUDIO_SAMPLES][2];

audio_channelinfo AudioStatus[AUDIO_CHANNELS];

volatile int audio_terminate=0;

void AudioSetVolume(int channel, int left, int right)
{
  AudioStatus[channel].volumeright = right;
  AudioStatus[channel].volumeleft  = left;
}

void AudioChannelThreadCallback(int channel, void *buf, unsigned long reqn)
{
	void (*callback)(void *buf, unsigned long reqn);
	callback=AudioStatus[channel].callback;
}


void AudioSetChannelCallback(int channel, void *callback)
{
	AudioStatus[channel].callback=callback;
}

int AudioOutBlocking(unsigned long channel,unsigned long vol1,unsigned long vol2,void *buf)
{
	if (!audio_ready) return -1;
	if (channel>=AUDIO_CHANNELS) return -1;
	if (vol1>MAXVOLUME) vol1=MAXVOLUME;
	if (vol2>MAXVOLUME) vol2=MAXVOLUME;
	return sceAudioOutputPannedBlocking(AudioStatus[channel].handle,vol1,vol2,buf);
}

static int AudioChannelThread(int args, void *argp)
{
	volatile int bufidx=0;
	int channel=*(int *)argp;
	
	while (audio_terminate==0) {
		void *bufptr=&audio_sndbuf[channel][bufidx];
		void (*callback)(void *buf, unsigned long reqn);
		callback=AudioStatus[channel].callback;
		if (callback) {
			callback(bufptr,AUDIO_SAMPLES);
		} else {
			unsigned long *ptr=bufptr;
			int i;
			for (i=0; i<AUDIO_SAMPLES; ++i) *(ptr++)=0;
		}
		AudioOutBlocking(channel,AudioStatus[channel].volumeleft,AudioStatus[channel].volumeright,bufptr);
		bufidx=(bufidx?0:1);
	}
	sceKernelExitThread(0);
	return 0;
}



/******************************************************************************/



int AudioInit()
{
	int i,ret;
	int failed=0;
	char str[32];

	audio_terminate=0;
	audio_ready=0;

	for (i=0; i<AUDIO_CHANNELS; i++) {
    AudioStatus[i].handle = -1;
    AudioStatus[i].threadhandle = -1;
    AudioStatus[i].volumeright = MAXVOLUME;
    AudioStatus[i].volumeleft  = MAXVOLUME;
    AudioStatus[i].callback = 0;
	}
	for (i=0; i<AUDIO_CHANNELS; i++) {
		if ((AudioStatus[i].handle = sceAudioChReserve(-1,AUDIO_SAMPLES,0))<0) 
      failed=1;
	}
	if (failed) {
		for (i=0; i<AUDIO_CHANNELS; i++) {
			if (AudioStatus[i].handle != -1) 
        sceAudioChRelease(AudioStatus[i].handle);
			AudioStatus[i].handle = -1;
		}
		return -1;
	}
	audio_ready = 1;
	strcpy(str,"audiot0");
	for (i=0; i<AUDIO_CHANNELS; i++) {
		str[6]='0'+i;
		AudioStatus[i].threadhandle = sceKernelCreateThread(str,(AudioThreadfunc_t)&AudioChannelThread,0x12,0x10000,0,NULL);
		if (AudioStatus[i].threadhandle < 0) {
			AudioStatus[i].threadhandle = -1;
			failed=1;
			break;
		}
		ret=sceKernelStartThread(AudioStatus[i].threadhandle,sizeof(i),&i);
		if (ret!=0) {
			failed=1;
			break;
		}
	}
	if (failed) {
		audio_terminate=1;
		for (i=0; i<AUDIO_CHANNELS; i++) {
			if (AudioStatus[i].threadhandle != -1) {
				//sceKernelWaitThreadEnd(AudioStatus[i].threadhandle,NULL);
				sceKernelDeleteThread(AudioStatus[i].threadhandle);
			}
			AudioStatus[i].threadhandle = -1;
		}
		audio_ready=0;
		return -1;
	}
	return 0;
}


void AudioEndPre()
{
	audio_ready=0;
	audio_terminate=1;
}


void AudioEnd()
{
	int i;
	audio_ready=0;
	audio_terminate=1;

	for (i=0; i<AUDIO_CHANNELS; i++) {
		if (AudioStatus[i].threadhandle != -1) {
			//sceKernelWaitThreadEnd(AudioStatus[i].threadhandle,NULL);
			sceKernelDeleteThread(AudioStatus[i].threadhandle);
		}
		AudioStatus[i].threadhandle = -1;
	}

	for (i=0; i<AUDIO_CHANNELS; i++) {
		if (AudioStatus[i].handle != -1) {
			sceAudioChRelease(AudioStatus[i].handle);
			AudioStatus[i].handle = -1;
		}
	}
}


