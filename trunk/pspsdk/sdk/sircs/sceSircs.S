	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceSircs
	IMPORT_START	"sceSircs",0x40010000
#endif
#ifdef F_00000000_sceSircsSend
	IMPORT_FUNC	"sceSircs",0x71EEF62D,sceSircsSend
#endif
