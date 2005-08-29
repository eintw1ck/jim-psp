	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceAudio
	IMPORT_START	"sceAudio",0x40010000
#endif
#ifdef F_00000000_sceAudioOutput
	IMPORT_FUNC	"sceAudio",0x8C1009B2,sceAudioOutput
#endif
#ifdef F_00000001_sceAudioOutputBlocking
	IMPORT_FUNC	"sceAudio",0x136CAF51,sceAudioOutputBlocking
#endif
#ifdef F_00000002_sceAudioOutputPanned
	IMPORT_FUNC	"sceAudio",0xE2D56B2D,sceAudioOutputPanned
#endif
#ifdef F_00000003_sceAudioOutputPannedBlocking
	IMPORT_FUNC	"sceAudio",0x13F592BC,sceAudioOutputPannedBlocking
#endif
#ifdef F_00000004_sceAudioChReserve
	IMPORT_FUNC	"sceAudio",0x5EC81C55,sceAudioChReserve
#endif
#ifdef F_00000005_sceAudioOneshotOutput
	IMPORT_FUNC	"sceAudio",0x41EFADE7,sceAudioOneshotOutput
#endif
#ifdef F_00000006_sceAudioChRelease
	IMPORT_FUNC	"sceAudio",0x6FC46853,sceAudioChRelease
#endif
#ifdef F_00000007_sceAudioGetChannelRestLen
	IMPORT_FUNC	"sceAudio",0xE9D97901,sceAudioGetChannelRestLen
#endif
#ifdef F_00000008_sceAudioSetChannelDataLen
	IMPORT_FUNC	"sceAudio",0xCB2E439E,sceAudioSetChannelDataLen
#endif
#ifdef F_00000009_sceAudioChangeChannelConfig
	IMPORT_FUNC	"sceAudio",0x95FD0C2D,sceAudioChangeChannelConfig
#endif
#ifdef F_0000000A_sceAudioChangeChannelVolume
	IMPORT_FUNC	"sceAudio",0xB7E1D8E7,sceAudioChangeChannelVolume
#endif
#ifdef F_0000000B_sceAudio_38553111
	IMPORT_FUNC	"sceAudio",0x38553111,sceAudio_38553111
#endif
#ifdef F_0000000C_sceAudio_5C37C0AE
	IMPORT_FUNC	"sceAudio",0x5C37C0AE,sceAudio_5C37C0AE
#endif
#ifdef F_0000000D_sceAudio_E0727056
	IMPORT_FUNC	"sceAudio",0xE0727056,sceAudio_E0727056
#endif
#ifdef F_0000000E_sceAudioInputBlocking
	IMPORT_FUNC	"sceAudio",0x086E5895,sceAudioInputBlocking
#endif
#ifdef F_0000000F_sceAudioInput
	IMPORT_FUNC	"sceAudio",0x6D4BEC68,sceAudioInput
#endif
#ifdef F_00000010_sceAudioGetInputLength
	IMPORT_FUNC	"sceAudio",0xA708C6A6,sceAudioGetInputLength
#endif
#ifdef F_00000011_sceAudioWaitInputEnd
	IMPORT_FUNC	"sceAudio",0x87B2E651,sceAudioWaitInputEnd
#endif
#ifdef F_00000012_sceAudioInputInit
	IMPORT_FUNC	"sceAudio",0x7DE61688,sceAudioInputInit
#endif
