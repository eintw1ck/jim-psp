/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * threadutils.c - Thread manager extensions.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 *
 * $Id$
 */

#include <string.h>

#include "pspthreadman.h"
#include "pspsdk.h"

#define MAX_UIDS 256

/* TODO: Generalize this for all thread primatives that have names. */

int pspSdkReferThreadStatusByName(const char *name, SceUID *pUID, SceKernelThreadInfo *pInfo)
{
	int uid_count = 0;

	/* First determine the number of threads we have. */
	int res = sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, NULL, 0, &uid_count);
	if (res < 0) {
		return res;
	}
	if (uid_count == 0) {
		return -1;  /* XXX: Should we return a kernel errorcode here? */
	}

	/* Grab UIDs for all of the threads. */
	SceUID uid_buf[uid_count];
	res = sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, uid_buf, uid_count, NULL);
	if (res < 0) {
		return res;
	}

	int i;
	for (i = 0; i < uid_count; i++) {
		SceKernelThreadInfo thread_info;

		memset(&thread_info, 0, sizeof(SceKernelThreadInfo));
		thread_info.size = sizeof(SceKernelThreadInfo);

		res = sceKernelReferThreadStatus(uid_buf[i], &thread_info);
		if (res < 0) {
			/* If we got an error than we probably don't have enough privileges
			   to access the thread's info. */
			continue;
		}

		if (thread_info.name[0] != '\0' && strcmp(thread_info.name, name) == 0) {
			if (pUID != NULL) {
				*pUID = uid_buf[i];
			}
			if (pInfo != NULL) {
				memcpy(pInfo, &thread_info, sizeof(SceKernelThreadInfo));
			}

			/* Found it. */
			return 0;
		}
	}

	/* Unable to find the thread (or insufficient access to retrieve it's info). */
	return -1;  /* XXX: Should we return a kernel errorcode here? */
}
