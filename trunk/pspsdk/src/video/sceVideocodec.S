	.set noreorder

#include "pspimport.s"

#ifdef F_sceVideocodec_0000
	IMPORT_START	"sceVideocodec",0x40090000
#endif
#ifdef F_sceVideocodec_0001
	IMPORT_FUNC	"sceVideocodec",0x2D31F5B1,sceVideocodecGetEDRAM
#endif
#ifdef F_sceVideocodec_0002
	IMPORT_FUNC	"sceVideocodec",0x4F160BF4,sceVideocodecReleaseEDRAM
#endif
#ifdef F_sceVideocodec_0003
	IMPORT_FUNC	"sceVideocodec",0xC01EC829,sceVideocodecOpen
#endif
#ifdef F_sceVideocodec_0004
	IMPORT_FUNC	"sceVideocodec",0x17099F0A,sceVideocodecInit
#endif
#ifdef F_sceVideocodec_0005
	IMPORT_FUNC	"sceVideocodec",0xDBA273FA,sceVideocodecDecode
#endif
#ifdef F_sceVideocodec_0006
	IMPORT_FUNC	"sceVideocodec",0xA2F0564E,sceVideocodecStop
#endif
#ifdef F_sceVideocodec_0007
	IMPORT_FUNC	"sceVideocodec",0x307E6E1C,sceVideocodecDelete
#endif
#ifdef F_sceVideocodec_0008
	IMPORT_FUNC	"sceVideocodec",0x745A7B7A,sceVideocodecSetMemory
#endif
#ifdef F_sceVideocodec_0009
	IMPORT_FUNC	"sceVideocodec",0x2F385E7F,sceVideocodecScanHeader
#endif
#ifdef F_sceVideocodec_0010
	IMPORT_FUNC	"sceVideocodec",0x26927D19,sceVideocodecGetVersion
#endif
#ifdef F_sceVideocodec_0011
	IMPORT_FUNC	"sceVideocodec",0x893B32B1,sceVideocodec_893B32B1
#endif
#ifdef F_sceVideocodec_0012
	IMPORT_FUNC	"sceVideocodec",0x627B7D42,sceVideocodec_627B7D42
#endif
#ifdef F_sceVideocodec_0013
	IMPORT_FUNC	"sceVideocodec",0x17CF7D2C,sceVideocodec_17CF7D2C
#endif
