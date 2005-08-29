	.set noreorder

#include "pspimport.s"

#ifdef F_stub_UtilsForKernel
	IMPORT_START	"UtilsForKernel",0x00090000
#endif
#ifdef F_00000000_sceUtilsKernelDcacheWBinvRange
	IMPORT_FUNC	"UtilsForKernel",0x80FE032E,sceUtilsKernelDcacheWBinvRange
#endif
#ifdef F_00000001_sceKernelUtilsMd5Digest
	IMPORT_FUNC	"UtilsForKernel",0xC8186A58,sceKernelUtilsMd5Digest
#endif
#ifdef F_00000002_sceKernelUtilsMd5BlockInit
	IMPORT_FUNC	"UtilsForKernel",0x9E5C5086,sceKernelUtilsMd5BlockInit
#endif
#ifdef F_00000003_sceKernelUtilsMd5BlockUpdate
	IMPORT_FUNC	"UtilsForKernel",0x61E1E525,sceKernelUtilsMd5BlockUpdate
#endif
#ifdef F_00000004_sceKernelUtilsMd5BlockResult
	IMPORT_FUNC	"UtilsForKernel",0xB8D24E78,sceKernelUtilsMd5BlockResult
#endif
#ifdef F_00000005_sceKernelUtilsSha1Digest
	IMPORT_FUNC	"UtilsForKernel",0x840259F1,sceKernelUtilsSha1Digest
#endif
#ifdef F_00000006_sceKernelUtilsSha1BlockInit
	IMPORT_FUNC	"UtilsForKernel",0xF8FCD5BA,sceKernelUtilsSha1BlockInit
#endif
#ifdef F_00000007_sceKernelUtilsSha1BlockUpdate
	IMPORT_FUNC	"UtilsForKernel",0x346F6DA8,sceKernelUtilsSha1BlockUpdate
#endif
#ifdef F_00000008_sceKernelUtilsSha1BlockResult
	IMPORT_FUNC	"UtilsForKernel",0x585F1C09,sceKernelUtilsSha1BlockResult
#endif
#ifdef F_00000009_sceKernelUtilsMt19937Init
	IMPORT_FUNC	"UtilsForKernel",0xE860E75E,sceKernelUtilsMt19937Init
#endif
#ifdef F_0000000A_sceKernelUtilsMt19937UInt
	IMPORT_FUNC	"UtilsForKernel",0x06FB8A63,sceKernelUtilsMt19937UInt
#endif
#ifdef F_0000000B_sceKernelSetGPIMask
	IMPORT_FUNC	"UtilsForKernel",0x193D4036,sceKernelSetGPIMask
#endif
#ifdef F_0000000C_sceKernelSetGPOMask
	IMPORT_FUNC	"UtilsForKernel",0x95035FEF,sceKernelSetGPOMask
#endif
#ifdef F_0000000D_sceKernelGetGPI
	IMPORT_FUNC	"UtilsForKernel",0x37FB5C42,sceKernelGetGPI
#endif
#ifdef F_0000000E_sceKernelSetGPO
	IMPORT_FUNC	"UtilsForKernel",0x6AD345D7,sceKernelSetGPO
#endif
#ifdef F_0000000F_sceKernelRegisterLibcRtcFunc
	IMPORT_FUNC	"UtilsForKernel",0x7B7ED3FD,sceKernelRegisterLibcRtcFunc
#endif
#ifdef F_00000010_sceKernelReleaseLibcRtcFunc
	IMPORT_FUNC	"UtilsForKernel",0x6151A7C3,sceKernelReleaseLibcRtcFunc
#endif
#ifdef F_00000011_sceKernelLibcClock
	IMPORT_FUNC	"UtilsForKernel",0x91E4F6A7,sceKernelLibcClock
#endif
#ifdef F_00000012_sceKernelLibcTime
	IMPORT_FUNC	"UtilsForKernel",0x27CC57F0,sceKernelLibcTime
#endif
#ifdef F_00000013_sceKernelLibcGettimeofday
	IMPORT_FUNC	"UtilsForKernel",0x71EC4271,sceKernelLibcGettimeofday
#endif
#ifdef F_00000014_sceKernelDcacheWritebackAll
	IMPORT_FUNC	"UtilsForKernel",0x79D1C3FA,sceKernelDcacheWritebackAll
#endif
#ifdef F_00000015_sceKernelDcacheWritebackInvalidateAll
	IMPORT_FUNC	"UtilsForKernel",0xB435DEC5,sceKernelDcacheWritebackInvalidateAll
#endif
#ifdef F_00000016_sceKernelDcacheInvalidateAll
	IMPORT_FUNC	"UtilsForKernel",0x864A9D72,sceKernelDcacheInvalidateAll
#endif
#ifdef F_00000017_sceKernelDcacheWritebackRange
	IMPORT_FUNC	"UtilsForKernel",0x3EE30821,sceKernelDcacheWritebackRange
#endif
#ifdef F_00000018_sceKernelDcacheWritebackInvalidateRange
	IMPORT_FUNC	"UtilsForKernel",0x34B9FA9E,sceKernelDcacheWritebackInvalidateRange
#endif
#ifdef F_00000019_sceKernelDcacheInvalidateRange
	IMPORT_FUNC	"UtilsForKernel",0xBFA98062,sceKernelDcacheInvalidateRange
#endif
#ifdef F_0000001A_sceKernelDcacheProbe
	IMPORT_FUNC	"UtilsForKernel",0x80001C4C,sceKernelDcacheProbe
#endif
#ifdef F_0000001B_sceKernelDcacheReadTag
	IMPORT_FUNC	"UtilsForKernel",0x16641D70,sceKernelDcacheReadTag
#endif
#ifdef F_0000001C_sceKernelIcacheInvalidateAll
	IMPORT_FUNC	"UtilsForKernel",0x920F104A,sceKernelIcacheInvalidateAll
#endif
#ifdef F_0000001D_sceKernelIcacheInvalidateRange
	IMPORT_FUNC	"UtilsForKernel",0xC2DF770E,sceKernelIcacheInvalidateRange
#endif
#ifdef F_0000001E_sceKernelIcacheProbe
	IMPORT_FUNC	"UtilsForKernel",0x4FD31C9D,sceKernelIcacheProbe
#endif
#ifdef F_0000001F_sceKernelIcacheReadTag
	IMPORT_FUNC	"UtilsForKernel",0xFB05FAD0,sceKernelIcacheReadTag
#endif
#ifdef F_00000020_sceKernelGzipDecompress
	IMPORT_FUNC	"UtilsForKernel",0x78934841,sceKernelGzipDecompress
#endif
#ifdef F_00000021_sceKernelGzipIsValid
	IMPORT_FUNC	"UtilsForKernel",0xE0CE3E29,sceKernelGzipIsValid
#endif
#ifdef F_00000022_sceKernelGzipGetInfo
	IMPORT_FUNC	"UtilsForKernel",0xB0E9C31F,sceKernelGzipGetInfo
#endif
#ifdef F_00000023_sceKernelGzipGetName
	IMPORT_FUNC	"UtilsForKernel",0xE0E6BA96,sceKernelGzipGetName
#endif
#ifdef F_00000024_sceKernelGzipGetComment
	IMPORT_FUNC	"UtilsForKernel",0x8C1FBE04,sceKernelGzipGetComment
#endif
#ifdef F_00000025_sceKernelGzipGetCompressedData
	IMPORT_FUNC	"UtilsForKernel",0x23FFC828,sceKernelGzipGetCompressedData
#endif
#ifdef F_00000026_sceKernelDeflateDecompress
	IMPORT_FUNC	"UtilsForKernel",0xE8DB3CE6,sceKernelDeflateDecompress
#endif
