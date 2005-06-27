/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * sbrk.c - kernel sbrk function, primary function to malloc - reserved
 *
 * Copyright (c) 2001 Gustavo Scotti <gustavo@scotti.com>
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * $Id$
 */
#include <pspkernel.h>

/* Let's do a quick bodge :P */

/* Define a heap size of 16 megs */
#define HEAP_SIZE	(16*1024*1024)

extern void _end;

void *EndOfHeap(void)
{
	return ((u8 *) &_end) + HEAP_SIZE;
}

void *ps2_sbrk(size_t increment)
{
	static void * _heap_ptr = &_end;
	void *mp, *ret = (void *)-1;

	if (increment == 0)
		return _heap_ptr;

	/* If the area we want to allocated is past the end of our heap, we have a problem. */
	mp = _heap_ptr + increment;
	if (mp <= EndOfHeap()) {
		ret = _heap_ptr;
		_heap_ptr = mp;
	}

	return ret;
}
