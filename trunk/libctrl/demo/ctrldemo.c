/* 68x34 480x272 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <libctrl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


PSP_MODULE_INFO("libctrl demo", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

#define printf pspDebugScreenPrintf


#define WORD_INTERVAL 7
#define MAX_X 417 // 480 - word_count*WORD_INTERVAL
#define MAX_Y 262 // 272 - 10

/* coordinate settings */
int x = 0;
int oldx = 0;
int y = 9;
int oldy = 9;
int dx = 1;
int dy = 1;
SceUID dx_mutex, dy_mutex;
int color = 0x11ffe6;

char autochange = 1;

int delay = 30000;

char pressed = 0;


/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
  int cbid;

  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);

  sceKernelSleepThreadCB();

  return 0;

}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
  int thid = 0;

  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if(thid >= 0) {
    sceKernelStartThread(thid, 0, 0);
  }

  return thid;
}

void print_word(int x, int y, int color, char const *const str)
{
  char *i;

  if ( !str ) return;

  i = (char*)str;

  while ( *i ) {
    pspDebugScreenPutChar(x, y, color, *i);

    x += WORD_INTERVAL;
    i++;
  }
}

int draw_thread(SceSize args, void *argp)
{
  while (1) {
    print_word(oldx, oldy, color, "      ");
    print_word(x, y, color, "Hello!");

    oldx = x;
    oldy = y;
    x += dx;
    y += dy;
    if ( ( x > MAX_X ) || ( x < 1 ) ) {
      sceKernelWaitSema(dx_mutex, 1, 0);
      dx = -dx;
      sceKernelSignalSema(dx_mutex, 1);
    }
    if ( ( y > MAX_Y ) || ( y < 1 ) ) {
      sceKernelWaitSema(dy_mutex, 1, 0);
      dy = -dy;
      sceKernelSignalSema(dy_mutex, 1);
    }
    x = oldx + dx;
    y = oldy + dy;
    
    if ( autochange ) color += 1000;
    if ( color > 0xFFFFFF ) color = 1;

    sceKernelDelayThread(delay);
  }

  return 0;
}

int main()
{
  SceUID ctrl_thid, draw_thid;
  ctrl_event_t *ctrl_event;


  pspDebugScreenInit();
  SetupCallbacks();


  pspDebugScreenSetXY(40,20);

  pspDebugScreenSetTextColor(0x11ffe6);


  /* Create mutexes */
  dx_mutex = sceKernelCreateSema("dx_mutex", 0, 1, 1, NULL);
  dy_mutex = sceKernelCreateSema("dy_mutex", 0, 1, 1, NULL);

  /* threads */
  ctrl_thid = sceKernelCreateThread("ctrl_thread", ctrl_thread, 0x10, 16384, 
			       0, NULL);
  if ( ctrl_thid < 0 ) {
    printf("Thread error");
    return 1;
  }
  sceKernelStartThread(ctrl_thid, 0, NULL);
  /* Time to safeguard against ctrl_thread() initialization isn't finished. */
  sceKernelDelayThread(100000);

  draw_thid = sceKernelCreateThread("draw_thread", draw_thread, 0x10, 16384, 
			       0, NULL);
  if ( draw_thid < 0 ) {
    printf("Thread error");
    return 1;
  }
  sceKernelStartThread(draw_thid, 0, NULL);

  /* Some settings */
  ctrl_set_key_mode(PSP_CTRL_UP_KEY, REPEAT);
  ctrl_set_key_repstart(PSP_CTRL_UP_KEY, 0);
  ctrl_set_key_mode(PSP_CTRL_DOWN_KEY, REPEAT);
  ctrl_set_key_repstart(PSP_CTRL_DOWN_KEY, 0);
  ctrl_set_key_mode(PSP_CTRL_LEFT_KEY, REPEAT);
  ctrl_set_key_repstart(PSP_CTRL_LEFT_KEY, 0);
  ctrl_set_key_mode(PSP_CTRL_RIGHT_KEY, REPEAT);
  ctrl_set_key_repstart(PSP_CTRL_RIGHT_KEY, 0);
  ctrl_set_key_mode(PSP_CTRL_LTRIGGER_KEY, REPEAT);
  ctrl_set_key_repstart(PSP_CTRL_LTRIGGER_KEY, 0);
  ctrl_set_key_mode(PSP_CTRL_RTRIGGER_KEY, REPEAT);
  ctrl_set_key_repstart(PSP_CTRL_RTRIGGER_KEY, 0);
  ctrl_set_jstick_coordstep(50, 50);
  ctrl_set_jstick_mode(REPEAT);


  ctrl_event = (ctrl_event_t*)malloc(sizeof(ctrl_event_t));

  while (1) {
    pspDebugScreenSetTextColor(0x663333);

    pspDebugScreenSetXY(1,1);
    printf("						  ");
    pspDebugScreenSetXY(1,1);
    printf("delay - %d, color - %x", delay, color);

    ctrl_pollevent(ctrl_event);

    if ( ctrl_event->event == PRESSED )
      switch (ctrl_event->key) {
      case PSP_CTRL_UP_KEY:
	sceKernelWaitSema(dy_mutex, 1, 0);
	if ( dy > -5 ) dy--;
	sceKernelSignalSema(dy_mutex, 1);
	break;
      case PSP_CTRL_DOWN_KEY:
	sceKernelWaitSema(dy_mutex, 1, 0);
	if ( dy < 5 ) dy++;
	sceKernelSignalSema(dy_mutex, 1);
	break;
      case PSP_CTRL_LEFT_KEY:
	sceKernelWaitSema(dx_mutex, 1, 0);
	if ( dx > -5 ) dx--;
	sceKernelSignalSema(dx_mutex, 1);
	break;
      case PSP_CTRL_RIGHT_KEY:
	sceKernelWaitSema(dx_mutex, 1, 0);
	if ( dx < 5 ) dx++;
	sceKernelSignalSema(dx_mutex, 1);
	break;
      case PSP_CTRL_LTRIGGER_KEY:
	if ( delay < 2000000 ) delay += 2000;
	break;
      case PSP_CTRL_RTRIGGER_KEY:
	if ( delay > 10000 ) delay -= 2000;
	break;
      default:
	break;
      }

    if ( ctrl_event->event == JOYSTICK ) {
      dy += ctrl_event->jstick_y;
      if ( dy <= -5 ) dy = -5;
      if ( dy >= 5 ) dy = 5;

      dx += ctrl_event->jstick_x;
      if ( dx <= -5 ) dx = -5;
      if ( dx >= 5 ) dx = 5;
    }

    sceDisplayWaitVblankStart();
  }

  sceKernelExitGame();
  return 0;
}
