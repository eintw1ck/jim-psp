	.set noreorder

#include "pspimport.s"

#ifdef F_stub_UtilsForUser
	IMPORT_START	"UtilsForUser",0x40010000
#endif
#ifdef F_00000000_sceKernelDcacheInvalidateRange
	IMPORT_FUNC	"UtilsForUser",0xBFA98062,sceKernelDcacheInvalidateRange
#endif
#ifdef F_00000001_sceKernelUtilsMd5Digest
	IMPORT_FUNC	"UtilsForUser",0xC8186A58,sceKernelUtilsMd5Digest
#endif
#ifdef F_00000002_sceKernelUtilsMd5BlockInit
	IMPORT_FUNC	"UtilsForUser",0x9E5C5086,sceKernelUtilsMd5BlockInit
#endif
#ifdef F_00000003_sceKernelUtilsMd5BlockUpdate
	IMPORT_FUNC	"UtilsForUser",0x61E1E525,sceKernelUtilsMd5BlockUpdate
#endif
#ifdef F_00000004_sceKernelUtilsMd5BlockResult
	IMPORT_FUNC	"UtilsForUser",0xB8D24E78,sceKernelUtilsMd5BlockResult
#endif
#ifdef F_00000005_sceKernelUtilsSha1Digest
	IMPORT_FUNC	"UtilsForUser",0x840259F1,sceKernelUtilsSha1Digest
#endif
#ifdef F_00000006_sceKernelUtilsSha1BlockInit
	IMPORT_FUNC	"UtilsForUser",0xF8FCD5BA,sceKernelUtilsSha1BlockInit
#endif
#ifdef F_00000007_sceKernelUtilsSha1BlockUpdate
	IMPORT_FUNC	"UtilsForUser",0x346F6DA8,sceKernelUtilsSha1BlockUpdate
#endif
#ifdef F_00000008_sceKernelUtilsSha1BlockResult
	IMPORT_FUNC	"UtilsForUser",0x585F1C09,sceKernelUtilsSha1BlockResult
#endif
#ifdef F_00000009_sceKernelUtilsMt19937Init
	IMPORT_FUNC	"UtilsForUser",0xE860E75E,sceKernelUtilsMt19937Init
#endif
#ifdef F_0000000A_sceKernelUtilsMt19937UInt
	IMPORT_FUNC	"UtilsForUser",0x06FB8A63,sceKernelUtilsMt19937UInt
#endif
#ifdef F_0000000B_sceKernelGetGPI
	IMPORT_FUNC	"UtilsForUser",0x37FB5C42,sceKernelGetGPI
#endif
#ifdef F_0000000C_sceKernelSetGPO
	IMPORT_FUNC	"UtilsForUser",0x6AD345D7,sceKernelSetGPO
#endif
#ifdef F_0000000D_sceKernelLibcClock
	IMPORT_FUNC	"UtilsForUser",0x91E4F6A7,sceKernelLibcClock
#endif
#ifdef F_0000000E_sceKernelLibcTime
	IMPORT_FUNC	"UtilsForUser",0x27CC57F0,sceKernelLibcTime
#endif
#ifdef F_0000000F_sceKernelLibcGettimeofday
	IMPORT_FUNC	"UtilsForUser",0x71EC4271,sceKernelLibcGettimeofday
#endif
#ifdef F_00000010_sceKernelDcacheWritebackAll
	IMPORT_FUNC	"UtilsForUser",0x79D1C3FA,sceKernelDcacheWritebackAll
#endif
#ifdef F_00000011_sceKernelDcacheWritebackInvalidateAll
	IMPORT_FUNC	"UtilsForUser",0xB435DEC5,sceKernelDcacheWritebackInvalidateAll
#endif
#ifdef F_00000012_sceKernelDcacheWritebackRange
	IMPORT_FUNC	"UtilsForUser",0x3EE30821,sceKernelDcacheWritebackRange
#endif
#ifdef F_00000013_sceKernelDcacheWritebackInvalidateRange
	IMPORT_FUNC	"UtilsForUser",0x34B9FA9E,sceKernelDcacheWritebackInvalidateRange
#endif
#ifdef F_00000014_sceKernelDcacheProbe
	IMPORT_FUNC	"UtilsForUser",0x80001C4C,sceKernelDcacheProbe
#endif
#ifdef F_00000015_sceKernelDcacheReadTag
	IMPORT_FUNC	"UtilsForUser",0x16641D70,sceKernelDcacheReadTag
#endif
#ifdef F_00000016_sceKernelIcacheProbe
	IMPORT_FUNC	"UtilsForUser",0x4FD31C9D,sceKernelIcacheProbe
#endif
#ifdef F_00000017_sceKernelIcacheReadTag
	IMPORT_FUNC	"UtilsForUser",0xFB05FAD0,sceKernelIcacheReadTag
#endif
