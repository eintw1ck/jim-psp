	.set noreorder

#include "pspimport.s"

#ifdef F_sceAudio_0000
	IMPORT_START	"sceAudio",0x40010000
#endif
#ifdef F_sceAudio_0001
	IMPORT_FUNC	"sceAudio",0x8C1009B2,sceAudioOutput
#endif
#ifdef F_sceAudio_0002
	IMPORT_FUNC	"sceAudio",0x136CAF51,sceAudioOutputBlocking
#endif
#ifdef F_sceAudio_0003
	IMPORT_FUNC	"sceAudio",0xE2D56B2D,sceAudioOutputPanned
#endif
#ifdef F_sceAudio_0004
	IMPORT_FUNC	"sceAudio",0x13F592BC,sceAudioOutputPannedBlocking
#endif
#ifdef F_sceAudio_0005
	IMPORT_FUNC	"sceAudio",0x5EC81C55,sceAudioChReserve
#endif
#ifdef F_sceAudio_0006
	IMPORT_FUNC	"sceAudio",0x41EFADE7,sceAudioOneshotOutput
#endif
#ifdef F_sceAudio_0007
	IMPORT_FUNC	"sceAudio",0x6FC46853,sceAudioChRelease
#endif
#ifdef F_sceAudio_0008
	IMPORT_FUNC	"sceAudio",0xE9D97901,sceAudioGetChannelRestLen
#endif
#ifdef F_sceAudio_0009
	IMPORT_FUNC	"sceAudio",0xCB2E439E,sceAudioSetChannelDataLen
#endif
#ifdef F_sceAudio_0010
	IMPORT_FUNC	"sceAudio",0x95FD0C2D,sceAudioChangeChannelConfig
#endif
#ifdef F_sceAudio_0011
	IMPORT_FUNC	"sceAudio",0xB7E1D8E7,sceAudioChangeChannelVolume
#endif
#ifdef F_sceAudio_0012
	IMPORT_FUNC	"sceAudio",0x38553111,sceAudio_38553111
#endif
#ifdef F_sceAudio_0013
	IMPORT_FUNC	"sceAudio",0x5C37C0AE,sceAudio_5C37C0AE
#endif
#ifdef F_sceAudio_0014
	IMPORT_FUNC	"sceAudio",0xE0727056,sceAudio_E0727056
#endif
#ifdef F_sceAudio_0015
	IMPORT_FUNC	"sceAudio",0x086E5895,sceAudioInputBlocking
#endif
#ifdef F_sceAudio_0016
	IMPORT_FUNC	"sceAudio",0x6D4BEC68,sceAudioInput
#endif
#ifdef F_sceAudio_0017
	IMPORT_FUNC	"sceAudio",0xA708C6A6,sceAudioGetInputLength
#endif
#ifdef F_sceAudio_0018
	IMPORT_FUNC	"sceAudio",0x87B2E651,sceAudioWaitInputEnd
#endif
#ifdef F_sceAudio_0019
	IMPORT_FUNC	"sceAudio",0x7DE61688,sceAudioInputInit
#endif
