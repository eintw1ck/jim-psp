	.set noreorder

#include "pspimport.s"

#ifdef F_psplink_driver_0000
	IMPORT_START "psplink_driver",0x00090000
#endif
#ifdef F_psplink_driver_0001
	IMPORT_FUNC  "psplink_driver",0x670C6041,psplinkPresent
#endif
#ifdef F_psplink_driver_0002
	IMPORT_FUNC  "psplink_driver",0x811971CE,psplinkHandleException
#endif
#ifdef F_psplink_driver_0003
	IMPORT_FUNC  "psplink_driver",0xB03642D9,psplinkExitShell
#endif
#ifdef F_psplink_driver_0004
	IMPORT_FUNC  "psplink_driver",0x8F31ACE7,psplinkReferModule
#endif
#ifdef F_psplink_driver_0005
	IMPORT_FUNC  "psplink_driver",0x94804B42,psplinkRegisterExceptions
#endif
#ifdef F_psplink_driver_0006
	IMPORT_FUNC  "psplink_driver",0xB3277521,psplinkFindUserThreadContext
#endif
#ifdef F_psplink_driver_0007
	IMPORT_FUNC  "psplink_driver",0x754F9BB8,psplinkReferModuleByName
#endif
#ifdef F_psplink_driver_0008
	IMPORT_FUNC  "psplink_driver",0x4A45386D,psplinkReset
#endif
#ifdef F_psplink_driver_0009
	IMPORT_FUNC  "psplink_driver",0xCBA8647D,apiHookByName
#endif
#ifdef F_psplink_driver_0010
	IMPORT_FUNC  "psplink_driver",0x4ED59445,apiHookByNid
#endif
#ifdef F_psplink_driver_0011
	IMPORT_FUNC  "psplink_driver",0xEFB166B7,debugEnableHW
#endif
#ifdef F_psplink_driver_0012
	IMPORT_FUNC  "psplink_driver",0xDD3E47DE,debugDisableHW
#endif
#ifdef F_psplink_driver_0013
	IMPORT_FUNC  "psplink_driver",0xEF83FB58,debugHWEnabled
#endif
#ifdef F_psplink_driver_0014
	IMPORT_FUNC  "psplink_driver",0xD0A22864,debugGetEnv
#endif
#ifdef F_psplink_driver_0015
	IMPORT_FUNC  "psplink_driver",0x4EC6E035,debugSetEnv
#endif
