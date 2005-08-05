/*

Name:
drv_stdout.C

Output data to stdout

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include "mikmod.h"
#include "mmio.h"

#define DEFAULT_FRAGSIZE 17
#define DEFAULT_NUMFRAGS 4

static int sndfd;
static int fragmentsize;
static char* audiobuffer;


static BOOL stdout_IsThere(void)
{
	return 1;
}


static BOOL stdout_Init(void)
{
	char *env;
	int play_precision,play_stereo,play_rate;
	int fragsize,numfrags;
	
	if(VC_Init()){
		return 1;
	}

	audiobuffer = (char*) _mm_malloc(0xFFFF);
	
	if(audiobuffer==NULL){
		VC_Exit();
		return 1;
	}
	
	return 0;
}


static void stdout_Exit(void)
{
	free(audiobuffer);
	VC_Exit();
	close(sndfd);
}


static void stdout_Update(void)
{
	VC_WriteBytes(audiobuffer, 0xFFFF);
	write(1, audiobuffer, 0xFFFF);
}

BOOL stdout_Reset(void)
{
	VC_Exit();
	return VC_Init();
}


MDRIVER drv_stdout =
{
	NULL,
	"stdout",
	"Standard output Driver v1.0 - by Pete",
	0,255,
	stdout_IsThere,
	VC_SampleLoad,
	VC_SampleUnload,
	VC_SampleSpace,
	VC_SampleLength,
	stdout_Init,
	stdout_Exit,
	stdout_Reset,
	VC_SetNumVoices,
	VC_PlayStart,
	VC_PlayStop,
	stdout_Update,
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
