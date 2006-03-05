
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
extern void initmd5(void);
extern void init_socket(void);
extern void initselect(void);
extern void initpspos(void);

#ifdef WITH_PSP
extern void init_psp(void);
#endif

#ifdef WITH_GU
extern void initgu(void);
#endif

#ifdef WITH_PSP2D
extern void initpsp2d(void);
extern void initpspsnd(void);
#endif

extern void initpspnet(void);

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
        {"md5", initmd5 },
        {"_socket", init_socket},
        {"select", initselect},

        {"pspos", initpspos},

#ifdef WITH_PSP
        {"_psp", init_psp},
#endif

#ifdef WITH_GU
        {"gu", initgu},
#endif

#ifdef WITH_PSP2D
        {"psp2d", initpsp2d},
        {"pspsnd", initpspsnd},
#endif

        {"pspnet", initpspnet},

	{0, 0}
};

#ifdef _GNUC
static const char* _rcsid_config __attribute__((unused)) = "$Id$";
#endif
