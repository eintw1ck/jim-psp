#ifndef __TYPES_H__
#define __TYPES_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#include "_stdint.h"
#else
#include <sys/types.h>
#define uint8_t u_int8_t
#define uint16_t u_int16_t
#define uint32_t u_int32_t
#define uint64_t u_int64_t
#endif

/* Re-define some system types */
typedef uint8_t 	u8;
typedef uint16_t 	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;
typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;
typedef int64_t		s64;

inline u32 lw_le(const u8 *ptr)
{
	u32 val;

	val = ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);

	return val;
}

inline u16 lh_le(const u8 *ptr)
{
	u16 val;

	val = ptr[0] | (ptr[1] << 8);

	return val;
}

inline u32 lw_be(const u8 *ptr)
{
	u32 val;

	val = (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];

	return val;
}

inline u16 lh_be(const u8 *ptr)
{
	u16 val;

	val = (ptr[0] << 16) | ptr[1];

	return val;
}

/* Should be different for different architectures */
/* Should read X as a little endian word and return the native word */
#define LW_LE(x) (lw_le((u8*) &(x)))
#define LW_BE(x) (lw_be((u8*) &(x)))
#define LH_LE(x) (lh_le((u8*) &(x)))
#define LH_BE(x) (lh_be((u8*) &(x)))
#define LW(x) (LW_LE(x))
#define LH(x) (LH_LE(x))

inline void sw_le(u8 *ptr, u32 val)
{
	ptr[0] = (u8) (val & 0xFF);
	ptr[1] = (u8) ((val >> 8) & 0xFF);
	ptr[2] = (u8) ((val >> 16) & 0xFF);
	ptr[3] = (u8) ((val >> 24) & 0xFF);
}

inline void sh_le(u8 *ptr, u16 val)
{
	ptr[0] = (u8) (val & 0xFF);
	ptr[1] = (u8) ((val >> 8) & 0xFF);
}

inline void sw_be(u8 *ptr, u32 val)
{
	ptr[0] = (u8) ((val >> 24) & 0xFF);
	ptr[1] = (u8) ((val >> 16) & 0xFF);
	ptr[2] = (u8) ((val >> 8) & 0xFF);
	ptr[3] = (u8) (val & 0xFF);
}

inline void sh_be(u8 *ptr, u16 val)
{
	ptr[0] = (u8) ((val >> 8) & 0xFF);
	ptr[1] = (u8) (val & 0xFF);
}

/* Should be different for different architectures */
/* Should read X as a little endian word and return the native word */
#define SW_LE(x, v) (sw_le((u8*) &(x), (v)))
#define SW_BE(x, v) (sw_be((u8*) &(x), (v)))
#define SH_LE(x, v) (sh_le((u8*) &(x), (v)))
#define SH_BE(x, v) (sh_be((u8*) &(x), (v)))
#define SW(x, v) (SW_LE(x, v))
#define SH(x, v) (SH_LE(x, v))


/* Do a safe alloc which should work on vc6 or latest gcc etc */
/* If alloc fails will always return NULL */
#define SAFE_ALLOC(p, t) try { (p) = new t; } catch(...) { (p) = NULL; }

#ifndef MAXPATH
#define MAXPATH 256
#endif

#endif
