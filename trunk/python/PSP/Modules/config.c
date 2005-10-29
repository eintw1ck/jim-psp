
/**
 * @file config.c
 */

/**********************************************************************

  Created: 02 Oct 2005

**********************************************************************/
// $Id$

#include "Python.h"

extern void PyMarshal_Init(void);
extern void initimp(void);
extern void initgc(void);
extern void initswi(void);

extern void inittime(void);
extern void initmath(void);
extern void initstruct(void);
extern void initbinascii(void);
extern void init_random(void);
extern void init_sre(void);
extern void initcStringIO(void);
extern void initerrno(void);
extern void initthread(void);
extern void initcollections(void);

extern void init_psp(void);
extern void initpspos(void);
extern void initgu(void);

struct _inittab _PyImport_Inittab[] = {
	{"marshal", PyMarshal_Init},
	{"imp", initimp},

	{"__main__", NULL},
	{"__builtin__", NULL},

	{"sys", NULL},
	{"exceptions", NULL},

	{"gc", initgc},

        {"time", inittime},
        {"math", initmath},
        {"struct", initstruct},
        {"binascii", initbinascii},
        {"_random", init_random},
        {"_sre", init_sre},
        {"cStringIO", initcStringIO},
        {"errno", initerrno},
        {"thread", initthread},
        {"collections", initcollections},

        {"_psp", init_psp},
        {"pspos", initpspos},

        {"gu", initgu},

	{0, 0}
};

#ifdef _GNUC
static const char* _rcsid_config __attribute__((unused)) = "$Id$";
#endif
