/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_resolver.h - PSP networking libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 *
 * Portions based on PspPet's wifi_03 sample code.
 * 
 * $Id$
 */

#ifndef PSPNET_RESOLVER_H
#define PSPNET_RESOLVER_H

#ifdef __cplusplus
extern "C" {
#endif

int sceNetResolverInit(void);

int sceNetResolverTerm(void);

#ifdef __cplusplus
}
#endif

#endif /* PSPNET_RESOLVER_H */
