
libdir = @PSPSDK_LIBDIR@

CC = @PSP_CC@
CCAS = $(CC)
AR = @PSP_AR@
RANLIB = @PSP_RANLIB@

INCLUDES = -I$(top_srcdir)/sdk/base -I$(top_srcdir)/sdk/user
CFLAGS = @PSPSDK_CFLAGS@
CCASFLAGS = $(CFLAGS) $(INCLUDES)

AUDIO_OBJS = stub_sceAudio.o 00000000_sceAudioOutput.o 00000001_sceAudioOutputBlocking.o 00000002_sceAudioOutputPanned.o \
			 00000003_sceAudioOutputPannedBlocking.o 00000004_sceAudioChReserve.o 00000005_sceAudioOneshotOutput.o \
			 00000006_sceAudioChRelease.o 00000007_sceAudioGetChannelRestLen.o 00000008_sceAudioSetChannelDataLen.o \
			 00000009_sceAudioChangeChannelConfig.o 0000000A_sceAudioChangeChannelVolume.o 0000000B_sceAudio_38553111.o \
			 0000000C_sceAudio_5C37C0AE.o 0000000D_sceAudio_E0727056.o 0000000E_sceAudioInputBlocking.o \
			 0000000F_sceAudioInput.o 00000010_sceAudioGetInputLength.o 00000011_sceAudioWaitInputEnd.o 00000012_sceAudioInputInit.o 

libpspaudioincludedir = @PSPSDK_INCLUDEDIR@
libpspaudioinclude_HEADERS = pspaudio.h

libpspaudiolibincludedir = @PSPSDK_INCLUDEDIR@
libpspaudiolibinclude_HEADERS = pspaudiolib.h

lib_LIBRARIES = libpspaudio.a libpspaudiolib.a

libpspaudio_a_SOURCES = sceAudio.S
libpspaudio_a_LIBADD = $(AUDIO_OBJS)

libpspaudiolib_a_SOURCES = pspaudiolib.c

$(AUDIO_OBJS): sceAudio.S
	$(COMPILE) -DF_$* $< -c -o $@
