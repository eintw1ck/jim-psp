/*
 *  libctrl - A wrapper for the pspctrl lib
 *  Version 1.0.1
 *  Copyright (C) 2009 Lego_12239 aka Oleg Nemanov
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <time.h>
#include <stdlib.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psprtc.h>
#include "libctrl.h"


#define printf pspDebugScreenPrintf


#define CTRL_KEY_COUNT 10

static ctrl_key_t ctrl_key[CTRL_KEY_COUNT];
static ctrl_jstick_t ctrl_jstick;

/* For an efficient memory allocation time usage this variable is global.*/
static pspTime ctrl_key_time;

static int ctrl_events_queue_len = 16;
static ctrl_event_t *ctrl_events_queue;
/* Pointers to the last event and the first event in the events queue. */
static ctrl_event_t *ctrl_events_queue_le, *ctrl_events_queue_fe;
static SceUID ctrl_key_event_mutex;


/*
 * Lock a mutex.
 * Return 0 if error or 1 otherwise.
 */
inline static int lock_mutex(SceUID mutex)
{
  if ( sceKernelWaitSema(mutex, 1, 0) < 0 )
    return 0;
  else
    return 1;
}

/*
 * Unlock a mutex.
 * Return 0 if error or 1 otherwise.
 */
inline static int unlock_mutex(SceUID mutex)
{
  if ( sceKernelSignalSema(mutex, 1) < 0 )
    return 0;
  else
    return 1;
}

/*
 * Create the events queue. 
 * Return 0 if error or 1 otherwise.
 */
static int create_events_queue(void)
{
  int i;


  ctrl_events_queue = (ctrl_event_t*)malloc(ctrl_events_queue_len * 
					   sizeof(ctrl_event_t));
  if ( !ctrl_events_queue )
    return 0;

  ctrl_events_queue_fe = ctrl_events_queue_le = ctrl_events_queue;

  for(i = 0; i < ctrl_events_queue_len; i++) {
    ctrl_events_queue[i].event = EMPTY;
  }

  return 1;
}

/*
 * Change an events queue length.
 * All events existing in the queue are deleted.
 * A smaller events queue give a smaller latency.
 * Return 0 if an error has occured during the create_events_queue()
 * call (Not enough memory for a queue) or the lock_mutex() call or
 * unlock_mutex().
 */
int ctrl_set_eq_len(size_t len)
{
  int ret;


  if ( ! lock_mutex(ctrl_key_event_mutex) ) return 0;

  /* Delete old events queue. */
  free(ctrl_events_queue);

  /* Create new events queue. */
  /* Cann't create a zero-length queue. */
  if ( ! len ) len++;
  ctrl_events_queue_len = len;
  ret = create_events_queue();

  if ( ! unlock_mutex(ctrl_key_event_mutex) ) return 0;

  return ret;
}

/*
 * Clear an all events.
 * Return 0 if a mutex error occured or 1 otherwise.
 */
int ctrl_clear_events(void)
{
  int i;

  if ( ! lock_mutex(ctrl_key_event_mutex) ) return 0;

  for(i = 0; i < ctrl_events_queue_len; i++) {
    ctrl_events_queue[i].event = EMPTY;
  }

  ctrl_events_queue_fe = ctrl_events_queue_le = ctrl_events_queue;

  if ( ! unlock_mutex(ctrl_key_event_mutex) ) return 0;

  return 1;
}

/*
 * Set key mode.
 */
void ctrl_set_key_mode(ctrl_key_code_t key_code, ctrl_mode_t mode)
{
  if (( key_code < 0 ) || ( key_code > CTRL_KEY_CODE_MAX )) return;

  ctrl_key[key_code].mode = mode;
}

/*
 * Get a key mode.
 */
ctrl_mode_t ctrl_get_key_mode(ctrl_key_code_t key_code)
{
  if (( key_code < 0 ) || ( key_code > CTRL_KEY_CODE_MAX )) return -1;

  return ctrl_key[key_code].mode;
}

/*
 * Set key repeat start time.
 * rep_start_time is a time in seconds since key is pressed when
 * repeating start.
 */
void ctrl_set_key_repstart(ctrl_key_code_t key_code, 
			 unsigned int rep_start_time)
{
  if (( key_code < 0 ) || ( key_code > CTRL_KEY_CODE_MAX )) return;

  ctrl_key[key_code].repeat_start = rep_start_time;
}

/*
 * Set key repeat interval.
 * rep_interval is a time interval in deciseconds beetwen PRESSED events 
 * while key is pressed.
 */
void ctrl_set_key_repinterval(ctrl_key_code_t key_code,
			    unsigned int rep_interval)
{
  if (( key_code < 0 ) || ( key_code > CTRL_KEY_CODE_MAX )) return;

  ctrl_key[key_code].repeat_interval = rep_interval;
}

/*
 * Set joystick axes zero ranges.
 * If an axis changes within this range, it interpretes like the zero value.
 */
void ctrl_set_jstick_zerorange(unsigned char x_zero_range,
			      unsigned char y_zero_range)
{
  ctrl_jstick.axis_x.zero_range = x_zero_range;
  ctrl_jstick.axis_y.zero_range = y_zero_range;
}

/*
 * Get values of axes zero ranges.
 */
void ctrl_get_jstick_zerorange(unsigned char *x_zero_range,
			      unsigned char *y_zero_range)
{
  *x_zero_range = ctrl_jstick.axis_x.zero_range;
  *y_zero_range = ctrl_jstick.axis_y.zero_range;
}

/*
 * Set joystick axes coordinates step.
 * For example, if x_coord_step is 1, than x axis can be from -128 to 127;
 * if x_coord_step is 10, than x axis can be from -12 to 12.
 */
void ctrl_set_jstick_coordstep(unsigned char x_coord_step,
			      unsigned char y_coord_step)
{
  if ( !x_coord_step ) x_coord_step++;
  if ( !y_coord_step ) y_coord_step++;

  ctrl_jstick.axis_x.coord_step = x_coord_step;
  ctrl_jstick.axis_y.coord_step = y_coord_step;
}

/*
 * Get joystick axes coordinates step.
 */
void ctrl_get_jstick_coordstep(unsigned char *x_coord_step,
			      unsigned char *y_coord_step)
{
  *x_coord_step = ctrl_jstick.axis_x.coord_step;
  *y_coord_step = ctrl_jstick.axis_y.coord_step;
}

/*
 * Return a count of coordinates taking into account a current coord_step.
 */
void ctrl_get_jstick_coordcount(unsigned char *x_count, unsigned char *y_count)
{
  *x_count = 128 / ctrl_jstick.axis_x.coord_step;
  *y_count = 128 / ctrl_jstick.axis_y.coord_step;
}

/*
 * Set joystick mode.
 */
void ctrl_set_jstick_mode(ctrl_mode_t mode)
{
  ctrl_jstick.mode = mode;
}

/*
 * Set joystick repeat interval.
 * rep_interval is a time interval in deciseconds beetwen JOYSTICK events 
 * while key is pressed.
 */
void ctrl_set_jstick_repinterval(unsigned int rep_interval)
{
  ctrl_jstick.repeat_interval = rep_interval;
}

/*
 * Push an event into the queue.
 * Return 0 if a mutex error occured or 1 otherwise.
 */
static int ctrl_events_queue_pushe(ctrl_event_type_t event, unsigned int key,
				   char axis_x, char axis_y)
{
  ctrl_event_t *tmp = ctrl_events_queue_le;


  if ( ! lock_mutex(ctrl_key_event_mutex) ) return 0;

  if ( ctrl_events_queue_le->event != EMPTY ) {
    if ( tmp == &ctrl_events_queue[ctrl_events_queue_len - 1] )
      tmp = ctrl_events_queue;
    else
      tmp = ctrl_events_queue_le + 1;

    if ( tmp == ctrl_events_queue_fe ) {
      if ( ! unlock_mutex(ctrl_key_event_mutex) ) return 0;
      return 1;
    }
    ctrl_events_queue_le = tmp;
  }

  ctrl_events_queue_le->event = event;
  ctrl_events_queue_le->key = key;
  ctrl_events_queue_le->jstick_x = axis_x;
  ctrl_events_queue_le->jstick_y = axis_y;

  if ( ! unlock_mutex(ctrl_key_event_mutex) ) return 0;

  return 1;
}

/*
 * Return 1 if some event is poped.
 * Return 0 if there is no event to pop.
 * Return -1 if a mutex error occured.
 */
static int ctrl_events_queue_pope(ctrl_event_t *const event)
{
  if ( ! lock_mutex(ctrl_key_event_mutex) ) return -1;

  if ( ctrl_events_queue_fe->event == EMPTY ) {
    event->event = EMPTY;
    if ( ! unlock_mutex(ctrl_key_event_mutex) ) return -1;
    return 0;
  }

  event->event = ctrl_events_queue_fe->event;
  event->key = ctrl_events_queue_fe->key;
  event->jstick_x = ctrl_events_queue_fe->jstick_x;
  event->jstick_y = ctrl_events_queue_fe->jstick_y;
  ctrl_events_queue_fe->event = EMPTY;

  if ( ctrl_events_queue_fe == ctrl_events_queue_le ) {
    if ( ! unlock_mutex(ctrl_key_event_mutex) ) return -1;
    return 1;
  }
  
  if ( ctrl_events_queue_fe == &ctrl_events_queue[ctrl_events_queue_len - 1] )
    ctrl_events_queue_fe = ctrl_events_queue;
  else
    ctrl_events_queue_fe++;

  if ( ! unlock_mutex(ctrl_key_event_mutex) ) return -1;
  return 1;
}

/*
 * Nonblocking function.
 * It check if any button is pressed.
 * If any button is pressed return 1 and fill the key structure with 
 * apropriate values or return 0 otherwise.
 * Return -1 if a mutex error occured.
 */
inline int ctrl_pollevent(ctrl_event_t *const event)
{
  return ctrl_events_queue_pope(event);
}

/*
 * Blocking function.
 * It wait button event and return a pointer to ctrl_key_t structure,
 * after a key is pressed.
 * Return -1 if a mutex error occured.
 */
int ctrl_waitevent(ctrl_event_t *const event)
{
  int caught;

  do {
    caught = ctrl_events_queue_pope(event);
    sceDisplayWaitVblankStart();
  } while (!caught);

  return caught;
}

/*
 * Return 1 if pressed, 2 if released, 0 otherwise.
 * Return -1 if a mutex error occured.
 */
static int process_but(unsigned int key_code, unsigned int is_pressed)
{
  ctrl_key_t * key = &ctrl_key[key_code];
  time_t t;
  unsigned int decisec;

  if ( ( !is_pressed ) && ( !key->press_time ) ) return 0;

  if ( is_pressed ) {
    if ( !key->press_time ) {
      key->press_time = time(NULL);
      key->last_repeat = 0;

      if ( ! ctrl_events_queue_pushe(PRESSED, key_code, 0, 0) ) return -1;

      return 1;
    } else {
      t = time(NULL);
      sceRtcGetCurrentClockLocalTime(&ctrl_key_time);
      decisec = (t - key->press_time)*10 + 
       ctrl_key_time.microseconds/100000;

      if ( ( key->mode == REPEAT ) &&
	  ( t - key->press_time >= key->repeat_start ) &&
	  ( decisec - key->last_repeat >= key->repeat_interval) ) {
       if ( ! ctrl_events_queue_pushe(PRESSED, key_code, 0, 0) ) return -1;
       key->last_repeat = decisec;
      }

      return 0;
    }
  } else {
    key->press_time = 0;
  }


  if ( ! ctrl_events_queue_pushe(RELEASED, key_code, 0, 0) ) return -1;

  return 2;
}

/*
 * Return 1 if everything is ok.
 * Return 0 if a mutex error occured.
 */
static int process_jstick(unsigned char Lx, unsigned char Ly)
{
  char x, y;
  /* x and y zero half range. */
  char x_zhr = ctrl_jstick.axis_x.zero_range / 2;
  char y_zhr = ctrl_jstick.axis_y.zero_range / 2;
  time_t t;
  unsigned int decisec_delta;


  /* Process the x axis. */
  x = Lx - 128;
  /* 
   * If Lx isn't in the zero range, calculate x.
   * Otherwise, set x to zero.
   */
  if ( x < -x_zhr )
    x = (x + x_zhr) / ctrl_jstick.axis_x.coord_step - 1;
  else if ( x > x_zhr )
    x = (x - x_zhr) / ctrl_jstick.axis_x.coord_step + 1;
  else
    x = 0;

  /* Process the y axis. */
  y = Ly - 128;
  /* 
   * If Ly isn't in the zero range, calculate y.
   * Otherwise, set y to zero.
   */
  if ( y < -y_zhr )
    y = (y + y_zhr) / ctrl_jstick.axis_y.coord_step - 1;
  else if ( y > y_zhr )
    y = (y - y_zhr) / ctrl_jstick.axis_y.coord_step + 1;
  else
    y = 0;


  /* Make a decision. */
  /* If nothing has been changed - exit. */
  if (( x == ctrl_jstick.axis_x.coord ) && ( y == ctrl_jstick.axis_y.coord )) {
    if ( ctrl_jstick.mode == REPEAT ) {
      t = time(NULL);
      sceRtcGetCurrentClockLocalTime(&ctrl_key_time);
      decisec_delta = (t - ctrl_jstick.changed_time)*10 + 
       ctrl_key_time.microseconds/100000 - ctrl_jstick.last_repeat;

      if ( decisec_delta < ctrl_jstick.repeat_interval )
       return 1;

      ctrl_jstick.last_repeat += decisec_delta;
    } else
      return 1;
  } else
    if ( ctrl_jstick.mode == REPEAT ) {
      ctrl_jstick.changed_time = time(NULL);
      ctrl_jstick.last_repeat = 0;
    }


  /* Else - place event in the events queue. */
  if ( ! ctrl_events_queue_pushe(JOYSTICK, 0, x, y) ) return 0;

  ctrl_jstick.axis_x.coord = x;
  ctrl_jstick.axis_y.coord = y;

  return 1;
}

/*
 * Return 1 if everything is ok.
 * Return 0 if error.
 */
static int init_events_queue(void)
{
  ctrl_key_event_mutex = sceKernelCreateSema("event_mutex", 0, 1, 1, NULL);

  return create_events_queue();
}

static void init_keys_array(void)
{
  int i;


  for(i = 0; i < CTRL_KEY_COUNT; i++) {
    ctrl_key[i].repeat_start = 1;
    ctrl_key[i].repeat_interval = 4;
  }

  ctrl_key[PSP_CTRL_UP_KEY].button       = PSP_CTRL_UP;
  ctrl_key[PSP_CTRL_RIGHT_KEY].button    = PSP_CTRL_RIGHT;
  ctrl_key[PSP_CTRL_DOWN_KEY].button     = PSP_CTRL_DOWN;
  ctrl_key[PSP_CTRL_LEFT_KEY].button     = PSP_CTRL_LEFT;
  ctrl_key[PSP_CTRL_LTRIGGER_KEY].button = PSP_CTRL_LTRIGGER;
  ctrl_key[PSP_CTRL_RTRIGGER_KEY].button = PSP_CTRL_RTRIGGER;
  ctrl_key[PSP_CTRL_TRIANGLE_KEY].button = PSP_CTRL_TRIANGLE;
  ctrl_key[PSP_CTRL_CIRCLE_KEY].button   = PSP_CTRL_CIRCLE;
  ctrl_key[PSP_CTRL_CROSS_KEY].button    = PSP_CTRL_CROSS;
  ctrl_key[PSP_CTRL_SQUARE_KEY].button   = PSP_CTRL_SQUARE;
}

static void init_jstick(void)
{
  sceCtrlSetSamplingMode(1);

  ctrl_jstick.axis_x.coord = 0;
  ctrl_jstick.axis_x.zero_range = 40;
  ctrl_jstick.axis_x.coord_step = 10;
  ctrl_jstick.axis_y.coord = 0;
  ctrl_jstick.axis_y.zero_range = 40;
  ctrl_jstick.axis_y.coord_step = 10;
  ctrl_jstick.mode = NO_REPEAT;
  ctrl_jstick.changed_time = 0;
  ctrl_jstick.last_repeat = 0;
  ctrl_jstick.repeat_interval = 4;
}

int ctrl_thread(SceSize args, void *argp)
{
  SceCtrlData *pad;
  int i;
  
  if ( !(pad = (SceCtrlData*)malloc(sizeof(SceCtrlData))) )
    sceKernelExitThread(1);

  /* Initialize the events queue. */
  init_events_queue();

  /* Initialize the ctrl_key array. */
  init_keys_array();

  /* Initialize the joystick related things. */
  init_jstick();

  /* Do a work. */
  while (1) {
    sceDisplayWaitVblankStart();

    sceCtrlReadBufferPositive(pad, 1);

    for(i = 0; i < CTRL_KEY_COUNT; i++) {
      process_but(i, pad->Buttons & ctrl_key[i].button);
    }
    process_jstick(pad->Lx, pad->Ly);
  }

  free(pad);

  return 0;
}

/*
 * Init a ctrl thread. Must be called before calling any of the ctrl 
 * functions.
 * Return an error code or 0 if evething is ok. 
 * ctrl thread id is returned through *thid. If an error occured 
 * *thid is undefined.
 */
int init_ctrl_thread(SceUID *thid)
{
  SceUID ctrl_thid;


  ctrl_thid = sceKernelCreateThread("ctrl_thread", ctrl_thread, 0x10, 16384,
				 0, NULL);
  if ( ctrl_thid < 0 )
    return ctrl_thid;

  sceKernelStartThread(ctrl_thid, 0, NULL);
  /* Give ctrl_thread() a time to initialize needed variables. */
  sceKernelDelayThread(10000);

  /* If ctrl_thread() do sceKernelExitThread() return the error code 1. */
  if ( sceKernelGetThreadExitStatus(ctrl_thid) != 0x800201a4 )
    return 1;

  *thid = ctrl_thid;

  return 0;
}
