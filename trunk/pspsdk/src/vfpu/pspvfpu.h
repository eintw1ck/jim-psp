/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspvfpu.h - Prototypes for the VFPU library
 *
 * Copyright (c) 2005 Jeremy Fitzhardinge <jeremy@goop.org>
 *
 * $Id: pspwlan.h 1663 2006-01-08 23:35:29Z tyranid $
 */
#ifndef __PSPVFPU_H__
#define __PSPVFPU_H__


#ifdef __cplusplus
//extern "C" {
#endif

struct pspvfpu_context;

#define VMAT0	(1<<0)
#define VMAT1	(1<<1)
#define VMAT2	(1<<2)
#define VMAT3	(1<<3)
#define VMAT4	(1<<4)
#define VMAT5	(1<<5)
#define VMAT6	(1<<6)
#define VMAT7	(1<<7)

/**
   Prepare to use the VFPU.  This set's the calling thread's VFPU
   attribute, and returns a pointer to some VFPU state storage.

   @param matrixset A bitfield of matrices the caller wants to start
   using.  This may be updated later on.
   @return A vfpu context
 */
struct pspvfpu_context *pspvfpu_initcontext(unsigned matrixset);

/**
   Delete a VFPU context.  This frees the resources used by the VFPU
   context.

   @param context The VFPU context to be deleted.
 */
void pspvfpu_deletecontext(struct pspvfpu_context *context);

/**
   Resume use of the VFPU.  This restores the parts of the VFPU state
   the caller wants restored (if necessary).  If the caller was the
   previous user of the context, then this call is effectively a
   no-op.

   @param vfpucontext The VFPU context the caller wants to restore.
   @param matrixset The set of matrices the caller wants to use.  This
   need not match the original matrixset when the context was created.
 */
void pspvfpu_usecontext(struct pspvfpu_context *context, unsigned matrixset);

#ifdef __cplusplus
//}
#endif

#endif	/* __PSPVFPU_H__ */
