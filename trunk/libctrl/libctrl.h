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

#ifndef __LIBCTRL_H_
#define __LIBCTRL_H_


#define CTRL_KEY_CODE_MAX 9

/* Key to array index mappings. */
typedef enum ctrl_key_code_t {
  PSP_CTRL_UP_KEY = 0,
  PSP_CTRL_RIGHT_KEY = 1,
  PSP_CTRL_DOWN_KEY = 2,
  PSP_CTRL_LEFT_KEY = 3,
  PSP_CTRL_LTRIGGER_KEY = 4,
  PSP_CTRL_RTRIGGER_KEY = 5,
  PSP_CTRL_TRIANGLE_KEY = 6,
  PSP_CTRL_CIRCLE_KEY = 7,
  PSP_CTRL_CROSS_KEY = 8,
  PSP_CTRL_SQUARE_KEY = CTRL_KEY_CODE_MAX
} ctrl_key_code_t;

typedef enum ctrl_event_type_t {
    EMPTY,
    PRESSED,
    RELEASED,
    JOYSTICK
} ctrl_event_type_t;

typedef struct ctrl_event_t {
  /* Key codes. Like a PSP_CTRL_UP_KEY. */
  ctrl_key_code_t key;
  char jstick_x;
  char jstick_y;
  ctrl_event_type_t event;
} ctrl_event_t;

typedef enum ctrl_mode_t {
  NO_REPEAT,
  REPEAT
} ctrl_mode_t;

typedef struct ctrl_key_t {
  /* PSP button codes. Like a PSP_CTRL_UP. */
  unsigned int button;
  /* Last press time. Must be 0 when initialized.*/
  time_t press_time;
  /* Last repeat time in deciseconds since press_time. */
  unsigned int last_repeat;
  /* Repeat start time in seconds since press_time. Default: 1.*/
  unsigned int repeat_start;
  /* Repeat interval in deciseconds. Default: 4. */
  unsigned int repeat_interval;
  /* Repeat or no repeat. */
  ctrl_mode_t mode;
  SceUID mutex;
} ctrl_key_t;

typedef struct ctrl_jstick_axis_t {
  /* Axis value. */
  char coord;
  /* Zero range value. Default: 40.*/
  unsigned char zero_range;
  /* Axis values step. Default: 10.*/
  unsigned char coord_step;
} ctrl_jstick_axis_t;

typedef struct ctrl_jstick_t {
  /* Axes. */
  ctrl_jstick_axis_t axis_x;
  ctrl_jstick_axis_t axis_y;
  /* Last change time. Must be 0 when initialized.*/
  time_t changed_time;
  /* Last repeat time in deciseconds since press_time. */
  unsigned int last_repeat;
  /* Repeat interval in deciseconds. Default: 4. */
  unsigned int repeat_interval;
  /* Repeat or no repeat. */
  ctrl_mode_t mode;
} ctrl_jstick_t;


/*
 * Change an events queue length by a queue recreating.
 * All events existing in the queue and queue by itself are deleted.
 * A smaller events queue give a smaller latency.
 * Return 0 if an error has occured (May be not enough memory for 
 * a new queue or a mutex error occured). By default the queue len is 16.
 */
int ctrl_set_eq_len(size_t len);

/*
 * Clear an all events.
 * Return 0 if a mutex error occured or 1 otherwise.
 */
int ctrl_clear_events(void);

/*
 * Set key mode
 */
void ctrl_set_key_mode(ctrl_key_code_t key_code, ctrl_mode_t mode);

/*
 * Get a key mode.
 */
ctrl_mode_t ctrl_get_key_mode(ctrl_key_code_t key_code);

/*
 * Set key repeat start time.
 * rep_start_time is a time in seconds since key is pressed when
 * repeating start.
 */
void ctrl_set_key_repstart(ctrl_key_code_t key_code, 
			 unsigned int rep_start_time);

/*
 * Set key repeat interval.
 * rep_interval is a time interval in deciseconds beetwen PRESSED events 
 * until key is pressed.
 */
void ctrl_set_key_repinterval(ctrl_key_code_t key_code,
			    unsigned int rep_interval);

/*
 * Set a joystick axis zero range.
 * If an axis changes within this range, it interpretes like the zero value.
 */
void ctrl_set_jstick_zerorange(unsigned char x_zero_range,
			      unsigned char y_zero_range);

/*
 * Get values of axes zero ranges.
 */
void ctrl_get_jstick_zerorange(unsigned char *x_zero_range,
			      unsigned char *y_zero_range);

/*
 * Set joystick axes values step.
 * For example, if x_coord_step is 1, than x axis can be from -128 to 127;
 * if x_coord_step is 10, than x axis can be from -12 to 12.
 */
void ctrl_set_jstick_coordstep(unsigned char x_coord_step,
			      unsigned char y_coord_step);

/*
 * Return a count of coordinates taking into account a current coord_step.
 */
void ctrl_get_jstick_coordcount(unsigned char *x_count,
			       unsigned char *y_count);

/*
 * Set joystick mode.
 */
void ctrl_set_jstick_mode(ctrl_mode_t mode);

/*
 * Set joystick repeat interval.
 * rep_interval is a time interval in deciseconds beetwen JOYSTICK events 
 * while key is pressed.
 */
void ctrl_set_jstick_repinterval(unsigned int rep_interval);

/*
 * Nonblocking function.
 * It check if any button is pressed.
 * If any button is pressed return 1 and fill the key structure with 
 * apropriate values or return 0 otherwise.
 * Return -1 if a mutex error occured.
 */
inline int ctrl_pollevent(ctrl_event_t *key);

/*
 * Blocking function.
 * It wait button event and fill with values the key structure
 * after a key is pressed and return.
 * User must free it by himself.
 * Return -1 if a mutex error occured.
 */
int ctrl_waitevent(ctrl_event_t *key);

int ctrl_thread(SceSize args, void *argp);

/*
 * Init a ctrl thread. Must be called before calling any of the ctrl 
 * functions.
 * Return an error code or 0 if evething is ok. 
 * ctrl thread id is returned through *thid. If an error occured 
 * *thid is undefined.
 */
int init_ctrl_thread(SceUID *thid);


#endif /* __LIBCTRL_H__ */
