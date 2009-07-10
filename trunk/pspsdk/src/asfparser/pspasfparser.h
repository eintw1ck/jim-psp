/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspasfparser.h - Prototypes for the sceAsfParser library.
 * usage: see
 * http://code.google.com/p/xreader/source/browse/branches/trunk-alpha-me/src/wmaplayer.c
 * for detail
 *
 * Copyright (c) 2009 hrimfaxi <outmatch@gmail.com>
 * Copyright (c) 2009 cooleyes <eyes.cooleyes@gmail.com>
 *
 */
#ifndef __SCELIBASFPARSER_H__
#define __SCELIBASFPARSER_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Asf Frame structure */
typedef struct SceAsfFrame
{
	ScePVoid pData;			// frame data buffer, alloc by yourself
	SceUInt32 iFrameMs;		// current frame ms
	SceUInt32 iUnk1;
	SceUInt32 iUnk2;		// 0~7
	SceUInt32 iUnk3;		// maybe frame data size
	SceUInt32 iUnk4;		// first frame is 1, other is 0
	SceUInt32 iUnk5;		// 128 256 512 1024 2048
	SceUInt32 iUnk6;		// 128 256 512 1024 2048
	SceUChar8 u8Unknown[32];	// unknown
} SceAsfFrame;

/** Asf Parser structure */
typedef struct _SceAsfParser
{
	SceUInt32 iUnk0;
	SceUInt32 iUnk1;
	SceUInt32 iUnk2;
	SceUInt32 iUnk3;
	SceUInt32 iUnk4;
	SceUInt32 iUnk5;
	SceUInt32 iUnk6;
	SceUInt32 iUnk7;
	SceUInt32 iNeedMem;		//8
	ScePVoid pNeedMemBuffer;	//9
//  SceUInt32 iUnk10_3626[3616]; // 10 - 3626
	SceUInt32 iUnk10_20[10];	// 10 - 20 
	SceUInt64 iDuration;	// 20 - 22
	SceUInt32 iUnk22_3626[3604];	// 22 - 3626
	SceAsfFrame sFrame;		//3626 - 3345
	SceUInt32 iUnk3345_3643[298];	//3345 - 3643
	SceUInt32 iUnk3644;
	SceUInt32 iUnk3644_4095[451];
} SceAsfParser;

/** Asf read callback */
typedef SceInt64(*SceAsfParserReadCB) (void *user_data, void *buf,
									   SceSize size);

/** Asf seek callback */
typedef SceInt64(*SceAsfParserSeekCB) (void *user_data, void *buf,
									   SceOff offset, int whence);

/**
* Check the memory of an asf parser
*
* @param parser - pointer to a SceAsfParser struct
*
* @return < 0 if error else if (parser->iNeedMem > 0x8000) also error.
*/
int sceAsfCheckNeedMem(SceAsfParser * parser);

/**
* Initialize asf parser
*
* @param parser - pointer to a SceAsfParser struct
* @param user_data - user pointer for read/seek callback
* @param read_cb - read callback
* @param seek_cb - seek callback
*
* @return < 0 if error else success.
*/
int sceAsfInitParser(SceAsfParser * parser, ScePVoid user_data,
					 SceAsfParserReadCB read_cb,
					 SceAsfParserSeekCB seek_cb);

/**
* Get frame in asf stream
*
* @param parser - pointer to a SceAsfParser struct
* @param unknown - unknown, set to 1
* @param frame - pointer to a SceAsfFrame struct
*
* @return < 0 if error else success.
*/
int sceAsfGetFrameData(SceAsfParser * parser, int unknown,
					   SceAsfFrame * frame);

/**
* Seek in asf stream
*
* @param parser - pointer to a SceAsfParser struct
* @param unknown - unknown, set to 1
* @param ms - will contain value of seek ms
*
* @return < 0 if error else success.
*/
int sceAsfSeekTime(SceAsfParser * parser, int unknown, SceUInt32 * ms);

/**
* Get WMA Tag frame's offset and size
*
* @param asf pointer to a SceAsfParser struct
* @param ptr unknown, pass NULL
* @param start pointer to frame offset
* @param size pointer to frame size
* @param flag can be one of: \n
* 0x00000001: get asf file header information \n
* 0x00004000: get standard tag information \n
* 0x00008000: get extra tag infomration \n
* 0x00040000: unknown \n
* 0x00080000: unknown
* @note use after sceAsfInitParser completed
*/
int sceAsfParser_685E0DA7(SceAsfParser * asf, void *ptr, int flag,
						  void *arg4, SceUInt64 * start, SceUInt64 * size);

/**
* Get ASF stream header frame's offset and size
*
* @param asf pointer to a SceAsfParser struct
* @param unk unknown, pass NULL
* @param start pointer to frame offset
* @param size pointer to frame size
* @note use after sceAsfInitParser completed
*/
int sceAsfParser_C6D98C54(SceAsfParser * asf, void *unk, SceUInt64 * start,
						  SceUInt64 * size);

#ifdef __cplusplus
}
#endif

#endif
