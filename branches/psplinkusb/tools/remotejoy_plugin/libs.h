/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * libs.h - Module library code for psplink
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/psplink/libs.h $
 * $Id: libs.h 2106 2006-12-18 18:55:53Z tyranid $
 */
#ifndef __LIBS_H__
#define __LIBS_H__

int libsPrintEntries(SceUID uid);
int libsPrintImports(SceUID uid);
u32 libsFindExportByName(SceUID uid, const char *library, const char *name);
u32 libsFindExportByNid(SceUID uid, const char *library, u32 nid);
void* libsFindExportAddrByName(SceUID uid, const char *library, const char *name);
void* libsFindExportAddrByNid(SceUID uid, const char *library, u32 nid);
int libsPatchFunction(SceUID uid, const char *library, u32 nid, u16 retval);
u32 libsNameToNid(const char *name);
u32 libsFindImportAddrByName(SceUID uid, const char *library, const char *name);
u32 libsFindImportAddrByNid(SceUID uid, const char *library, u32 nid);

#endif
