/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudio.h - Prototypes for the sceAudio library.
 *
 * Copyright (c) 2005 Adresd
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id$
 */
#ifndef PSPAUDIO_H
#define PSPAUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Audio User Audio Library */

/** @addtogroup Audio */

/*@{*/

/** The maximum output volume. */
#define PSP_AUDIO_VOLUME_MAX    0x8000

/** The maximum number of hardware channels. */
#define PSP_AUDIO_CHANNEL_MAX   8
/** Used to request the next available hardware channel. */
#define PSP_AUDIO_NEXT_CHANNEL  (-1)

enum PspAudioFormats {
    /** Channel is set to stereo output. */
    PSP_AUDIO_FORMAT_STEREO = 0,
    /** Channel is set to mono output. */
    PSP_AUDIO_FORMAT_MONO   = 0x10
};

/** The minimum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MIN    64
/** The maximum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MAX    65472
/** Make the given sample count a multiple of 64. */
#define PSP_AUDIO_SAMPLE_ALIGN(s) (((s) + 63) & ~63)
 
/**
  * Allocate and initialize a hardware output channel.
  *
  * @param channel - Use a value between 0 - 7 to reserve a specific channel.
  *                   Pass PSP_AUDIO_NEXT_CHANNEL to get the first available channel.
  * @param samplecount - The number of samples that can be output on the channel per
  *                      output call.  It must be a value between ::PSP_AUDIO_SAMPLE_MIN
  *                      and ::PSP_AUDIO_SAMPLE_MAX, and it must be aligned to 64 bytes
  *                      (use the ::PSP_AUDIO_SAMPLE_ALIGN macro to align it).
  * @param format - The output format to use for the channel.  One of ::PspAudioFormats.
  *
  * @returns The channel number on success, an error code if less than 0.
  */
int sceAudioChReserve(int channel, int samplecount, int format);

/**
  * Release a hardware output channel.
  *
  * @param channel - The channel to release.
  *
  * @returns 0 on success, an error if less than 0.
  */
int sceAudioChRelease(int channel);


int sceAudioOutput(int channel, int vol, void *buf);

/**
  * a
  *
  */
int sceAudioOutputBlocking(int channel, int vol, void *buf);

/**
  * a
  *
  */
int sceAudioOutputPanned(int channel, int leftvol, int rightvol, void *buffer);

/**
  * a
  *
  */
int sceAudioOutputPannedBlocking(int channel, int leftvol, int rightvol, void *buffer);

/**
  * a
  *
  */
int sceAudioGetChannelRestLen(int channel);

/**
  * a
  *
  */
int sceAudioSetChannelDataLen(int channel, int samplecount);

/**
  * a
  *
  */
int sceAudioChangeChannelConfig(int channel, int format);

/**
  * a
  *
  */
int sceAudioChangeChannelVolume(int channel, int leftvol, int rightvol);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPAUDIO_H */
