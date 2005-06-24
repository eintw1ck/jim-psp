#ifndef __AUDIOLIB_H__
#define __AUDIOLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define AUDIO_CHANNELS 4
#define AUDIO_SAMPLES 1024
#define MAXVOLUME 0x8000

typedef struct {
  int threadhandle;
  int handle;
  int volumeleft;
  int volumeright;
  void (*callback)(void *buf, unsigned long reqn);
} audio_channelinfo;

typedef int (*AudioThreadfunc_t)(int args, void *argp);

void AudioSetVolume(int channel, int left, int right);
void AudioChannelThreadCallback(int channel, void *buf, unsigned long reqn);
void AudioSetChannelCallback(int channel, void *callback);
int AudioOutBlocking(unsigned long channel,unsigned long vol1,unsigned long vol2,void *buf);
int AudioInit();
void AudioEndPre();
void AudioEnd();

#ifdef __cplusplus
}
#endif

#endif
