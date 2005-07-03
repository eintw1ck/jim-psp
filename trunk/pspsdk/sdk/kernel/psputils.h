/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputils.h - Prototypes for the sceUtils library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 * $Id$
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Utils Utils Library */

/** @addtogroup Utils */

/*@{*/

#include <sys/time.h>

/**
  * Get the time in seconds since the epoc (1st Jan 1970)
  *
  */
time_t sceKernelLibcTime(time_t *t);

/** 
  * Get the processor clock used since the start of the process
  */
clock_t sceKernelLibcClock(void);

/** 
  * Get the current time of time and time zone information
  */
int sceKernelLibcGettimeofday(struct timeval *tp, struct timezone *tzp);

/** 
  * Write back the data cache to memory
  */
void sceKernelDcacheWritebackAll(void);

/** Structure for holding a mersenne twister context */
typedef struct _Mt19937Context
{
	/** The context, from looking at utils.prx it seems that this structure is something 
	  like u32, u32[624] but made 1024 for security :P */
	u32 context[1024];
} Mt19937Context;

/** 
  * Function to initialise a mersenne twister context.
  *
  * @param ctx - Pointer to a context
  * @param seed - A seed for the random function.
  *
  * @par Example:
  * @code
  * Mt19927Context ctx;
  * sceKernelUtilsMt19937Init(&ctx, time(NULL));
  * u23 rand_val = sceKernelUtilsMt19937UInt(&ctx);
  * @endcode
  *
  * @return < 0 on error.
  */
int sceKernelUtilsMt19937Init(Mt19937Context *ctx, u32 seed);

/**
  * Function to return a new psuedo random number.
  *
  * @param ctx - Pointer to a pre-initialised context.
  * @return A pseudo random number (between 0 and MAX_INT).
  */
u32 sceKernelUtilsMt19937UInt(Mt19937Context *ctx);

typedef struct _Md5Context
{
	u8 context[96];
} Md5Context;

/**
  * Function to perform an MD5 digest of a data block.
  *
  * @param data - Pointer to a data block to make a digest of.
  * @param size - Size of the data block.
  * @param digest - Pointer to a 16byte buffer to store the resulting digest
  *
  * @return < 0 on error.
  */
int sceKernelUtilsMd5Digest(u8 *data, u32 size, u8 *digest);

/**
  * Function to initialise a MD5 digest context
  *
  * @param ctx - A context block to initialise
  *
  * @return < 0 on error.
  * @par Example:
  * @code
  * Md5Context ctx;
  * u8 digest[16];
  * sceKernelUtilsMd5BlockInit(&ctx);
  * sceKernelUtilsMd5BlockUpdate(&ctx, (u8*) "Hello", 5);
  * sceKernelUtilsMd5BlockResult(&ctx, digest);
  * @endcode
  */
int sceKernelUtilsMd5BlockInit(Md5Context *ctx);

/**
  * Function to update the MD5 digest with a block of data.
  *
  * @param ctx - A filled in context block.
  * @param data - The data block to hash.
  * @param size - The size of the data to hash
  *
  * @return < 0 on error.
  */
int sceKernelUtilsMd5BlockUpdate(Md5Context *ctx, u8 *data, u32 size);

/**
  * Function to get the digest result of the MD5 hash.
  *
  * @param ctx - A filled in context block.
  * @param digest - A 16 byte array to hold the digest.
  *
  * @return < 0 on error.
  */
int sceKernelUtilsMd5BlockResult(Md5Context *ctx, u8 *digest);

/** Type to hold a sha1 context */
typedef struct _Sha1Context
{
	/* The context, I am pretty sure this is not the correct size */
	u8 ctx[128];
} Sha1Context;

/**
  * Function to SHA1 hash a data block.
  * 
  * @param data - The data to hash.
  * @param size - The size of the data.
  * @param digest - Pointer to a 20 byte array for storing the digest
  *
  * @return < 0 on error.
  */
int sceKernelUtilsSha1Digest(u8 *data, u32 size, u8 *digest);

/**
  * Function to initialise a context for SHA1 hashing.
  *
  * @param ctx - Pointer to a context.
  *
  * @return < 0 on error.
  *
  * @par Example:
  * @code
  * Sha1Context ctx;
  * u8 digest[20];
  * sceKernelUtilsSha1BlockInit(&ctx);
  * sceKernelUtilsSha1BlockUpdate(&ctx, (u8*) "Hello", 5);
  * sceKernelUtilsSha1BlockResult(&ctx, digest);
  * @endcode
  */
int sceKernelUtilsSha1BlockInit(Sha1Context *ctx);

/**
  * Function to update the current hash.
  *
  * @param ctx - Pointer to a prefilled context.
  * @param data - The data block to hash.
  * @param size - The size of the data block
  *
  * @return < 0 on error.
  */
int sceKernelUtilsSha1BlockUpdate(Sha1Context *ctx, u8 *data, u32 size);

/**
  * Function to get the result of the SHA1 hash.
  * 
  * @param ctx - Pointer to a prefilled context.
  * @param digest - A pointer to a 20 byte array to contain the digest.
  *
  * @return < 0 on error.
  */
int sceKernelUtilsSha1BlockResult(Sha1Context *ctx, u8 *digest);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
