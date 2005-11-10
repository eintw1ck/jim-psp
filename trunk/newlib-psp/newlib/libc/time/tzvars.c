/* Moved these variables from tzset_r.c to avoid including all of _tzset_r()
   and the functions it uses. -- MRB (PSPDEV LOCAL) */

#include <sys/time.h>
#include "local.h"

/* default to GMT */
char *_tzname[2] = {"GMT" "GMT"};
int _daylight = 0;
time_t _timezone = (time_t)0;

int __tzyear = 0;

int __tznorth = 1;

__tzrule_type __tzrule[2] = { {'J', 0, 0, 0, 0, (time_t)0, 0 }, 
			      {'J', 0, 0, 0, 0, (time_t)0, 0 } };
