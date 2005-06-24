#ifndef __AUDIOLIB_H__
#define __AUDIOLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PSP_NUM_AUDIO_CHANNELS 4
#define PSP_AUDIO_SAMPLE_SIZE 1024
#define PSP_VOLUME_MAX 0x8000

typedef struct {
  int threadhandle;
  int handle;
  int volumeleft;
  int volumeright;
  void (*callback)(void *buf, unsigned int reqn);
} psp_audio_channelinfo;

typedef int (* pspAudioThreadfunc_t)(int args, void *argp);

int  pspAudioInit();
void pspAudioEndPre();
void pspAudioEnd();

void pspAudioSetVolume(int channel, int left, int right);
void pspAudioChannelThreadCallback(int channel, void *buf, unsigned int reqn);
void pspAudioSetChannelCallback(int channel, void *callback);
int  pspAudioOutBlocking(unsigned int channel, unsigned int vol1, unsigned int vol2, void *buf);

#ifdef __cplusplus
}
#endif

#endif
