/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * testsuite.c - Regression testharness.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#include <stdio.h>
#include "testsuite.h"

void init_testsuite(test_suite *p)
{
	p->ntests = 0;
	p->tests = NULL;
}

int add_test(test_suite *p, const char *name, testfunc_t func, void *arg)
{
	p->tests = (test_t *)realloc(p->tests, (p->ntests + 1) * sizeof(test_t));
	p->tests[p->ntests].name = name;
	p->tests[p->ntests].func = func;
	p->tests[p->ntests].arg = arg;
	p->ntests++;
	return p->ntests;
}

int run_testsuite(test_suite *p)
{
	int i, successful;

	printf("Running %d tests\n", p->ntests);
	successful = 0;
	for (i=0; i<p->ntests; i++)
	{
		const char *error;

		printf("Test %d: %s ", i + 1, p->tests[i].name);
		error = p->tests[i].func(p->tests[i].arg);
		if (error != NULL)
		{
			printf("[%s]", error);
		}
		else
		{
			successful++;
		}

		printf("\n");
	}

	printf("\nTotal failures: %d\n", p->ntests - successful);

	return successful;
}
