#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Audio Audio Library */

/** @addtogroup Audio */

/*@{*/

/**
  * a
  *
  */
void sceAudioOutputBlocking();

/**
  * a
  *
  */
void sceAudioOutputPanned();

/**
  * a
  *
  */
long sceAudioOutputPannedBlocking(int handle, int vol1, int vol2, void *buffer);

/**
  * a
  *
  */
//init buffer? returns handle, minus if error
long sceAudioChReserve(int id, int samplecount, int unknown);

/**
  * a
  *
  */
//free buffer?
void sceAudioChRelease(int handle);

/**
  * a
  *
  */
void sceAudioGetChannelRestLen();

/**
  * a
  *
  */
int sceAudioSetChannelDataLen(int a, int b);

/**
  * a
  *
  */
void sceAudioChangeChannelConfig();

/**
  * a
  *
  */
void sceAudioChangeChannelVolume();

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
