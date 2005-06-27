/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * runner.c - Testsuite runner
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#include <stdio.h>
#include "testsuite.h"

#ifdef _EE
#include <sifrpc.h>
#endif

extern int libc_add_tests(test_suite *p);

int main(int argc, char *argv[])
{
	test_suite suite;

	#ifdef _EE
	SifInitRpc(0); 
	#endif

	/* initialize test suite */
	init_testsuite(&suite);

	/* add all tests to this suite */
	libc_add_tests(&suite);

	/* run all tests */
	run_testsuite(&suite);

	return 0;
}
