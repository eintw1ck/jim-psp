#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <string.h>

// [[ Mikmod-specific
#include "mikmod.h"
// ]]


#define true 1
#define false 0

/* Define the module info section */
PSP_MODULE_INFO("MIKMODTEST", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

void dump_threadstatus(void);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

// [[ Mikmod-specific
extern int _mm_errno;
extern BOOL _mm_critical;
extern char *_mm_errmsg[];

void my_error_handler(void)
{
	printf("_mm_critical %d\n", _mm_critical);
	printf("_mm_errno %d\n", _mm_errno);
	printf("%s\n", _mm_errmsg[_mm_errno]);
	return;
}

extern UWORD md_mode;
extern UBYTE md_reverb;
extern UBYTE md_pansep;
// ]]

int main(void)
{
	SceCtrlData pad, lastpad;
	
// [[ Mikmod-specific
	int maxchan = 128;
	
	UNIMOD *mf = NULL; // for mod
	SAMPLE *sf = NULL; // for wav
	int voice = 0; 	   // for wav
	int pan = 127;
	int vol = 127;
	int freq = 22000;
// ]]
	BOOL playing = false;

	pspDebugScreenInit();
	SetupCallbacks();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(1);
	
// [[ Mikmod-specific
	_mm_RegisterErrorHandler(my_error_handler);
	MikMod_RegisterAllLoaders();
	MikMod_RegisterAllDrivers();
	md_mode = DMODE_16BITS|DMODE_STEREO|DMODE_SOFT_SNDFX|DMODE_SOFT_MUSIC; 
	md_reverb = 0;
	md_pansep = 128;
	MikMod_Init();
	MikMod_SetNumVoices(-1, 8);
	

	sf = WAV_LoadFN("ms0:/psp/game/mikmodtest/sound.wav");
	
// ]]
	printf("Starting.\n");
	Player_Start(mf);
	
	sceCtrlReadBufferPositive(&lastpad, 1);
	do {
		sceCtrlReadBufferPositive(&pad, 1);
		
		if(pad.Buttons != lastpad.Buttons) {
			if(pad.Buttons & PSP_CTRL_CROSS) {
				voice = MikMod_PlaySample(sf,0,0);
				Voice_SetPanning(voice, pan);
			}
			if(pad.Buttons & PSP_CTRL_SQUARE) {
				playing = !playing;
				playing?MikMod_EnableOutput():MikMod_DisableOutput();
			}
			
			if(pad.Buttons & PSP_CTRL_CIRCLE) {
				mf = MikMod_LoadSong("ms0:/psp/game/mikmodtest/MUSIC.XM", maxchan);
				Player_Start(mf);
				playing = true;
			}
			if(pad.Buttons & PSP_CTRL_TRIANGLE) {
				Player_Stop();
				MikMod_FreeSong(mf); // To stop the song for real, it needs
									 // to be freed. I know, weird...
				playing = false;
			}
			
			if(pad.Buttons & PSP_CTRL_SELECT)
				printf("Player is %s\n", Player_Active()?"On":"Off");
				
		}
		

		
		if(pad.Buttons & PSP_CTRL_LTRIGGER) {
			Voice_setPanning(voice, (pan<2)?pan:--pan);
			printf("pan is %d\n", pan);
		}
		if(pad.Buttons & PSP_CTRL_RTRIGGER) {
			Voice_setPanning(voice, (pan>254)?pan:++pan);
			printf("pan is %d\n", pan);
		}
			
		if(pad.Buttons & PSP_CTRL_UP) {
			Voice_setVolume(voice, (vol>254)?vol:++vol);
			printf("vol is %d\n", vol);
		}
		if(pad.Buttons & PSP_CTRL_DOWN) {
			Voice_setVolume(voice, (vol<2)?vol:--vol);
			printf("vol is %d\n", vol);
		}
			
		if(pad.Buttons & PSP_CTRL_LEFT) {
			Voice_setFrequency(voice, (freq<1001)?freq:(freq -=1000));
			printf("freq is %d\n", freq);
		}
		if(pad.Buttons & PSP_CTRL_RIGHT) {
			Voice_setFrequency(voice, (freq>44000)?freq:(freq +=1000));
			printf("freq is %d\n", freq);
		}

		

		sceDisplayWaitVblankStart();
		
	} while(!(pad.Buttons & PSP_CTRL_START));
	
	printf("Stopping.\n");
	Player_Stop();
	MikMod_FreeSong(mf);
	MikMod_Exit();

	sceKernelExitGame();
	return 0;
}
