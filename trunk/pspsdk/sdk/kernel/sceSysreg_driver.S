	.set noreorder

#include "pspimport.s"

#ifdef F_stub_sceSysreg_driver
	IMPORT_START	"sceSysreg_driver",0x00010000
#endif
#ifdef F_00000000_sceSysregInit
	IMPORT_FUNC	"sceSysreg_driver",0x9C863542,sceSysregInit
#endif
#ifdef F_00000001_sceSysregEnd
	IMPORT_FUNC	"sceSysreg_driver",0xF2DEAA14,sceSysregEnd
#endif
#ifdef F_00000002_sceSysreg_driver_E88B77ED
	IMPORT_FUNC	"sceSysreg_driver",0xE88B77ED,sceSysreg_driver_E88B77ED
#endif
#ifdef F_00000003_sceSysreg_driver_CD0F6715
	IMPORT_FUNC	"sceSysreg_driver",0xCD0F6715,sceSysreg_driver_CD0F6715
#endif
#ifdef F_00000004_sceSysreg_driver_844AF6BD
	IMPORT_FUNC	"sceSysreg_driver",0x844AF6BD,sceSysreg_driver_844AF6BD
#endif
#ifdef F_00000005_sceSysreg_driver_E2A5D1EE
	IMPORT_FUNC	"sceSysreg_driver",0xE2A5D1EE,sceSysreg_driver_E2A5D1EE
#endif
#ifdef F_00000006_sceSysreg_driver_4F46EEDE
	IMPORT_FUNC	"sceSysreg_driver",0x4F46EEDE,sceSysreg_driver_4F46EEDE
#endif
#ifdef F_00000007_sceSysreg_driver_8F4F4E96
	IMPORT_FUNC	"sceSysreg_driver",0x8F4F4E96,sceSysreg_driver_8F4F4E96
#endif
#ifdef F_00000008_sceSysregTopResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0xC29D614E,sceSysregTopResetEnable
#endif
#ifdef F_00000009_sceSysregScResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0xDC6139A4,sceSysregScResetEnable
#endif
#ifdef F_0000000A_sceSysregMeResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0xDE59DACB,sceSysregMeResetEnable
#endif
#ifdef F_0000000B_sceSysregMeResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0x2DB0EB28,sceSysregMeResetDisable
#endif
#ifdef F_0000000C_sceSysregAwResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0x26283A6F,sceSysregAwResetEnable
#endif
#ifdef F_0000000D_sceSysregAwResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0xA374195E,sceSysregAwResetDisable
#endif
#ifdef F_0000000E_sceSysregVmeResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0xD20581EA,sceSysregVmeResetEnable
#endif
#ifdef F_0000000F_sceSysregVmeResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0x7558064A,sceSysregVmeResetDisable
#endif
#ifdef F_00000010_sceSysregAvcResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0x9BB70D34,sceSysregAvcResetEnable
#endif
#ifdef F_00000011_sceSysregAvcResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0xFD6C562B,sceSysregAvcResetDisable
#endif
#ifdef F_00000012_sceSysregUsbResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0xCD4FB614,sceSysregUsbResetEnable
#endif
#ifdef F_00000013_sceSysregUsbResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0x69EECBE5,sceSysregUsbResetDisable
#endif
#ifdef F_00000014_sceSysregAtaResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0xF5B80837,sceSysregAtaResetEnable
#endif
#ifdef F_00000015_sceSysregAtaResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0x8075303F,sceSysregAtaResetDisable
#endif
#ifdef F_00000016_sceSysregMsifResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0x00C2628E,sceSysregMsifResetEnable
#endif
#ifdef F_00000017_sceSysregMsifResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0xEC4BF81F,sceSysregMsifResetDisable
#endif
#ifdef F_00000018_sceSysregKirkResetEnable
	IMPORT_FUNC	"sceSysreg_driver",0x8A7F9EB4,sceSysregKirkResetEnable
#endif
#ifdef F_00000019_sceSysregKirkResetDisable
	IMPORT_FUNC	"sceSysreg_driver",0xC32F2491,sceSysregKirkResetDisable
#endif
#ifdef F_0000001A_sceSysreg_driver_B21B6CBF
	IMPORT_FUNC	"sceSysreg_driver",0xB21B6CBF,sceSysreg_driver_B21B6CBF
#endif
#ifdef F_0000001B_sceSysreg_driver_BB3623DF
	IMPORT_FUNC	"sceSysreg_driver",0xBB3623DF,sceSysreg_driver_BB3623DF
#endif
#ifdef F_0000001C_sceSysreg_driver_53A6838B
	IMPORT_FUNC	"sceSysreg_driver",0x53A6838B,sceSysreg_driver_53A6838B
#endif
#ifdef F_0000001D_sceSysreg_driver_B4560C45
	IMPORT_FUNC	"sceSysreg_driver",0xB4560C45,sceSysreg_driver_B4560C45
#endif
#ifdef F_0000001E_sceSysreg_driver_DCA57573
	IMPORT_FUNC	"sceSysreg_driver",0xDCA57573,sceSysreg_driver_DCA57573
#endif
#ifdef F_0000001F_sceSysregMeBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x44F6CDA7,sceSysregMeBusClockEnable
#endif
#ifdef F_00000020_sceSysregMeBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0x158AD4FC,sceSysregMeBusClockDisable
#endif
#ifdef F_00000021_sceSysreg_driver_4D4CE2B8
	IMPORT_FUNC	"sceSysreg_driver",0x4D4CE2B8,sceSysreg_driver_4D4CE2B8
#endif
#ifdef F_00000022_sceSysreg_driver_789BD609
	IMPORT_FUNC	"sceSysreg_driver",0x789BD609,sceSysreg_driver_789BD609
#endif
#ifdef F_00000023_sceSysreg_driver_391CE1C0
	IMPORT_FUNC	"sceSysreg_driver",0x391CE1C0,sceSysreg_driver_391CE1C0
#endif
#ifdef F_00000024_sceSysreg_driver_82D35024
	IMPORT_FUNC	"sceSysreg_driver",0x82D35024,sceSysreg_driver_82D35024
#endif
#ifdef F_00000025_sceSysreg_driver_AF904657
	IMPORT_FUNC	"sceSysreg_driver",0xAF904657,sceSysreg_driver_AF904657
#endif
#ifdef F_00000026_sceSysreg_driver_438AECE9
	IMPORT_FUNC	"sceSysreg_driver",0x438AECE9,sceSysreg_driver_438AECE9
#endif
#ifdef F_00000027_sceSysregDmacplusBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x678AD3ED,sceSysregDmacplusBusClockEnable
#endif
#ifdef F_00000028_sceSysregDmacplusBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0x168C09B8,sceSysregDmacplusBusClockDisable
#endif
#ifdef F_00000029_sceSysregDmacBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x7E7EBC20,sceSysregDmacBusClockEnable
#endif
#ifdef F_0000002A_sceSysregDmacBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0xA265C719,sceSysregDmacBusClockDisable
#endif
#ifdef F_0000002B_sceSysregKirkBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x4F5AFBBE,sceSysregKirkBusClockEnable
#endif
#ifdef F_0000002C_sceSysregKirkBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0x845DD1A6,sceSysregKirkBusClockDisable
#endif
#ifdef F_0000002D_sceSysregAtaBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x16909002,sceSysregAtaBusClockEnable
#endif
#ifdef F_0000002E_sceSysregAtaBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0xB6C10DF0,sceSysregAtaBusClockDisable
#endif
#ifdef F_0000002F_sceSysregUsbBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x3E216017,sceSysregUsbBusClockEnable
#endif
#ifdef F_00000030_sceSysregUsbBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0xBFBABB63,sceSysregUsbBusClockDisable
#endif
#ifdef F_00000031_sceSysregMsifBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0x4716E71E,sceSysregMsifBusClockEnable
#endif
#ifdef F_00000032_sceSysregMsifBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0x826430C0,sceSysregMsifBusClockDisable
#endif
#ifdef F_00000033_sceSysreg_driver_7CC6CBFD
	IMPORT_FUNC	"sceSysreg_driver",0x7CC6CBFD,sceSysreg_driver_7CC6CBFD
#endif
#ifdef F_00000034_sceSysreg_driver_EE6B9411
	IMPORT_FUNC	"sceSysreg_driver",0xEE6B9411,sceSysreg_driver_EE6B9411
#endif
#ifdef F_00000035_sceSysregEmcsmBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0xF97D9D73,sceSysregEmcsmBusClockEnable
#endif
#ifdef F_00000036_sceSysregEmcsmBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0x2D0F7755,sceSysregEmcsmBusClockDisable
#endif
#ifdef F_00000037_sceSysreg_driver_63B9EB65
	IMPORT_FUNC	"sceSysreg_driver",0x63B9EB65,sceSysreg_driver_63B9EB65
#endif
#ifdef F_00000038_sceSysreg_driver_E1AA9788
	IMPORT_FUNC	"sceSysreg_driver",0xE1AA9788,sceSysreg_driver_E1AA9788
#endif
#ifdef F_00000039_sceSysregAudioBusClockEnable
	IMPORT_FUNC	"sceSysreg_driver",0xAA63C8BD,sceSysregAudioBusClockEnable
#endif
#ifdef F_0000003A_sceSysregAudioBusClockDisable
	IMPORT_FUNC	"sceSysreg_driver",0x054AC8C6,sceSysregAudioBusClockDisable
#endif
#ifdef F_0000003B_sceSysreg_driver_6B01D71B
	IMPORT_FUNC	"sceSysreg_driver",0x6B01D71B,sceSysreg_driver_6B01D71B
#endif
#ifdef F_0000003C_sceSysreg_driver_FC186A83
	IMPORT_FUNC	"sceSysreg_driver",0xFC186A83,sceSysreg_driver_FC186A83
#endif
#ifdef F_0000003D_sceSysreg_driver_7234EA80
	IMPORT_FUNC	"sceSysreg_driver",0x7234EA80,sceSysreg_driver_7234EA80
#endif
#ifdef F_0000003E_sceSysreg_driver_38EC3281
	IMPORT_FUNC	"sceSysreg_driver",0x38EC3281,sceSysreg_driver_38EC3281
#endif
#ifdef F_0000003F_sceSysreg_driver_31154490
	IMPORT_FUNC	"sceSysreg_driver",0x31154490,sceSysreg_driver_31154490
#endif
#ifdef F_00000040_sceSysreg_driver_8E2D835D
	IMPORT_FUNC	"sceSysreg_driver",0x8E2D835D,sceSysreg_driver_8E2D835D
#endif
#ifdef F_00000041_sceSysreg_driver_8835D1E1
	IMPORT_FUNC	"sceSysreg_driver",0x8835D1E1,sceSysreg_driver_8835D1E1
#endif
#ifdef F_00000042_sceSysreg_driver_8B90B8B5
	IMPORT_FUNC	"sceSysreg_driver",0x8B90B8B5,sceSysreg_driver_8B90B8B5
#endif
#ifdef F_00000043_sceSysreg_driver_7725CA08
	IMPORT_FUNC	"sceSysreg_driver",0x7725CA08,sceSysreg_driver_7725CA08
#endif
#ifdef F_00000044_sceSysreg_driver_A3E4154C
	IMPORT_FUNC	"sceSysreg_driver",0xA3E4154C,sceSysreg_driver_A3E4154C
#endif
#ifdef F_00000045_sceSysreg_driver_E8533DCA
	IMPORT_FUNC	"sceSysreg_driver",0xE8533DCA,sceSysreg_driver_E8533DCA
#endif
#ifdef F_00000046_sceSysreg_driver_F6D83AD0
	IMPORT_FUNC	"sceSysreg_driver",0xF6D83AD0,sceSysreg_driver_F6D83AD0
#endif
#ifdef F_00000047_sceSysreg_driver_A9CD1C1F
	IMPORT_FUNC	"sceSysreg_driver",0xA9CD1C1F,sceSysreg_driver_A9CD1C1F
#endif
#ifdef F_00000048_sceSysreg_driver_2F216F38
	IMPORT_FUNC	"sceSysreg_driver",0x2F216F38,sceSysreg_driver_2F216F38
#endif
#ifdef F_00000049_sceSysreg_driver_A24C242A
	IMPORT_FUNC	"sceSysreg_driver",0xA24C242A,sceSysreg_driver_A24C242A
#endif
#ifdef F_0000004A_sceSysreg_driver_E89243BE
	IMPORT_FUNC	"sceSysreg_driver",0xE89243BE,sceSysreg_driver_E89243BE
#endif
#ifdef F_0000004B_sceSysreg_driver_7DCA8302
	IMPORT_FUNC	"sceSysreg_driver",0x7DCA8302,sceSysreg_driver_7DCA8302
#endif
#ifdef F_0000004C_sceSysreg_driver_45225F8F
	IMPORT_FUNC	"sceSysreg_driver",0x45225F8F,sceSysreg_driver_45225F8F
#endif
#ifdef F_0000004D_sceSysreg_driver_D74D3AB6
	IMPORT_FUNC	"sceSysreg_driver",0xD74D3AB6,sceSysreg_driver_D74D3AB6
#endif
#ifdef F_0000004E_sceSysreg_driver_AD7C4ACB
	IMPORT_FUNC	"sceSysreg_driver",0xAD7C4ACB,sceSysreg_driver_AD7C4ACB
#endif
#ifdef F_0000004F_sceSysreg_driver_DC68A93F
	IMPORT_FUNC	"sceSysreg_driver",0xDC68A93F,sceSysreg_driver_DC68A93F
#endif
#ifdef F_00000050_sceSysreg_driver_94B0323C
	IMPORT_FUNC	"sceSysreg_driver",0x94B0323C,sceSysreg_driver_94B0323C
#endif
#ifdef F_00000051_sceSysreg_driver_6417CDD6
	IMPORT_FUNC	"sceSysreg_driver",0x6417CDD6,sceSysreg_driver_6417CDD6
#endif
#ifdef F_00000052_sceSysreg_driver_20388C9E
	IMPORT_FUNC	"sceSysreg_driver",0x20388C9E,sceSysreg_driver_20388C9E
#endif
#ifdef F_00000053_sceSysreg_driver_E3AECFFA
	IMPORT_FUNC	"sceSysreg_driver",0xE3AECFFA,sceSysreg_driver_E3AECFFA
#endif
#ifdef F_00000054_sceSysreg_driver_3BBD0C0C
	IMPORT_FUNC	"sceSysreg_driver",0x3BBD0C0C,sceSysreg_driver_3BBD0C0C
#endif
#ifdef F_00000055_sceSysreg_driver_C1DA05D2
	IMPORT_FUNC	"sceSysreg_driver",0xC1DA05D2,sceSysreg_driver_C1DA05D2
#endif
#ifdef F_00000056_sceSysreg_driver_DE170397
	IMPORT_FUNC	"sceSysreg_driver",0xDE170397,sceSysreg_driver_DE170397
#endif
#ifdef F_00000057_sceSysreg_driver_1969E840
	IMPORT_FUNC	"sceSysreg_driver",0x1969E840,sceSysreg_driver_1969E840
#endif
#ifdef F_00000058_sceSysreg_driver_1D382514
	IMPORT_FUNC	"sceSysreg_driver",0x1D382514,sceSysreg_driver_1D382514
#endif
#ifdef F_00000059_sceSysreg_driver_833E6FB1
	IMPORT_FUNC	"sceSysreg_driver",0x833E6FB1,sceSysreg_driver_833E6FB1
#endif
#ifdef F_0000005A_sceSysreg_driver_03340297
	IMPORT_FUNC	"sceSysreg_driver",0x03340297,sceSysreg_driver_03340297
#endif
#ifdef F_0000005B_sceSysreg_driver_9100B4E5
	IMPORT_FUNC	"sceSysreg_driver",0x9100B4E5,sceSysreg_driver_9100B4E5
#endif
#ifdef F_0000005C_sceSysreg_driver_0A83FC7B
	IMPORT_FUNC	"sceSysreg_driver",0x0A83FC7B,sceSysreg_driver_0A83FC7B
#endif
#ifdef F_0000005D_sceSysreg_driver_D6628A48
	IMPORT_FUNC	"sceSysreg_driver",0xD6628A48,sceSysreg_driver_D6628A48
#endif
#ifdef F_0000005E_sceSysreg_driver_1E18EA43
	IMPORT_FUNC	"sceSysreg_driver",0x1E18EA43,sceSysreg_driver_1E18EA43
#endif
#ifdef F_0000005F_sceSysregEmcsmIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x9DD1F821,sceSysregEmcsmIoEnable
#endif
#ifdef F_00000060_sceSysregEmcsmIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x1C4C4C7A,sceSysregEmcsmIoDisable
#endif
#ifdef F_00000061_sceSysregUsbIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0xBC68D9B6,sceSysregUsbIoEnable
#endif
#ifdef F_00000062_sceSysregUsbIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0xA3C8E075,sceSysregUsbIoDisable
#endif
#ifdef F_00000063_sceSysregAtaIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x79338EA3,sceSysregAtaIoEnable
#endif
#ifdef F_00000064_sceSysregAtaIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0xCADB92AA,sceSysregAtaIoDisable
#endif
#ifdef F_00000065_sceSysregMsifIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0xD74F1D48,sceSysregMsifIoEnable
#endif
#ifdef F_00000066_sceSysregMsifIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x18172C6A,sceSysregMsifIoDisable
#endif
#ifdef F_00000067_sceSysregLcdcIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x63B1AADF,sceSysregLcdcIoEnable
#endif
#ifdef F_00000068_sceSysregLcdcIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0xF74F14E9,sceSysregLcdcIoDisable
#endif
#ifdef F_00000069_sceSysregAudioIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0xBB26CF1F,sceSysregAudioIoEnable
#endif
#ifdef F_0000006A_sceSysregAudioIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x8E2FB536,sceSysregAudioIoDisable
#endif
#ifdef F_0000006B_sceSysregIicIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x0436B60F,sceSysregIicIoEnable
#endif
#ifdef F_0000006C_sceSysregIicIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x58F47EFD,sceSysregIicIoDisable
#endif
#ifdef F_0000006D_sceSysregSircsIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x4C49A8BC,sceSysregSircsIoEnable
#endif
#ifdef F_0000006E_sceSysregSircsIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x26FA0928,sceSysregSircsIoDisable
#endif
#ifdef F_0000006F_sceSysreg_driver_F844DDF3
	IMPORT_FUNC	"sceSysreg_driver",0xF844DDF3,sceSysreg_driver_F844DDF3
#endif
#ifdef F_00000070_sceSysreg_driver_29A119A1
	IMPORT_FUNC	"sceSysreg_driver",0x29A119A1,sceSysreg_driver_29A119A1
#endif
#ifdef F_00000071_sceSysregKeyIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x77DED992,sceSysregKeyIoEnable
#endif
#ifdef F_00000072_sceSysregKeyIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x6879790B,sceSysregKeyIoDisable
#endif
#ifdef F_00000073_sceSysregPwmIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x7A5D2D15,sceSysregPwmIoEnable
#endif
#ifdef F_00000074_sceSysregPwmIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x25B0AC52,sceSysregPwmIoDisable
#endif
#ifdef F_00000075_sceSysregUartIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x7FD7A631,sceSysregUartIoEnable
#endif
#ifdef F_00000076_sceSysregUartIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0xBB823481,sceSysregUartIoDisable
#endif
#ifdef F_00000077_sceSysregSpiIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0x8C5C53DE,sceSysregSpiIoEnable
#endif
#ifdef F_00000078_sceSysregSpiIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0xA16E55F4,sceSysregSpiIoDisable
#endif
#ifdef F_00000079_sceSysregGpioIoEnable
	IMPORT_FUNC	"sceSysreg_driver",0xB627582E,sceSysregGpioIoEnable
#endif
#ifdef F_0000007A_sceSysregGpioIoDisable
	IMPORT_FUNC	"sceSysreg_driver",0x1E9C3607,sceSysregGpioIoDisable
#endif
#ifdef F_0000007B_sceSysreg_driver_55B18B84
	IMPORT_FUNC	"sceSysreg_driver",0x55B18B84,sceSysreg_driver_55B18B84
#endif
#ifdef F_0000007C_sceSysreg_driver_2112E686
	IMPORT_FUNC	"sceSysreg_driver",0x2112E686,sceSysreg_driver_2112E686
#endif
#ifdef F_0000007D_sceSysreg_driver_7B9E9A53
	IMPORT_FUNC	"sceSysreg_driver",0x7B9E9A53,sceSysreg_driver_7B9E9A53
#endif
#ifdef F_0000007E_sceSysreg_driver_7BDF0556
	IMPORT_FUNC	"sceSysreg_driver",0x7BDF0556,sceSysreg_driver_7BDF0556
#endif
#ifdef F_0000007F_sceSysreg_driver_8D0FED1E
	IMPORT_FUNC	"sceSysreg_driver",0x8D0FED1E,sceSysreg_driver_8D0FED1E
#endif
#ifdef F_00000080_sceSysreg_driver_A46E9CA8
	IMPORT_FUNC	"sceSysreg_driver",0xA46E9CA8,sceSysreg_driver_A46E9CA8
#endif
#ifdef F_00000081_sceSysreg_driver_633595F2
	IMPORT_FUNC	"sceSysreg_driver",0x633595F2,sceSysreg_driver_633595F2
#endif
#ifdef F_00000082_sceSysregUsbQueryIntr
	IMPORT_FUNC	"sceSysreg_driver",0x32471457,sceSysregUsbQueryIntr
#endif
#ifdef F_00000083_sceSysregUsbAcquireIntr
	IMPORT_FUNC	"sceSysreg_driver",0x692F31FF,sceSysregUsbAcquireIntr
#endif
#ifdef F_00000084_sceSysreg_driver_D43E98F6
	IMPORT_FUNC	"sceSysreg_driver",0xD43E98F6,sceSysreg_driver_D43E98F6
#endif
#ifdef F_00000085_sceSysreg_driver_BF91FBDA
	IMPORT_FUNC	"sceSysreg_driver",0xBF91FBDA,sceSysreg_driver_BF91FBDA
#endif
#ifdef F_00000086_sceSysreg_driver_36A75390
	IMPORT_FUNC	"sceSysreg_driver",0x36A75390,sceSysreg_driver_36A75390
#endif
#ifdef F_00000087_sceSysregIntrInit
	IMPORT_FUNC	"sceSysreg_driver",0x25673620,sceSysregIntrInit
#endif
#ifdef F_00000088_sceSysregIntrEnd
	IMPORT_FUNC	"sceSysreg_driver",0x4EE8E2C8,sceSysregIntrEnd
#endif
#ifdef F_00000089_sceSysregInterruptToOther
	IMPORT_FUNC	"sceSysreg_driver",0x61BFF85F,sceSysregInterruptToOther
#endif
#ifdef F_0000008A_sceSysregSemaTryLock
	IMPORT_FUNC	"sceSysreg_driver",0x9FC87ED4,sceSysregSemaTryLock
#endif
#ifdef F_0000008B_sceSysregSemaUnlock
	IMPORT_FUNC	"sceSysreg_driver",0x8BE2D520,sceSysregSemaUnlock
#endif
#ifdef F_0000008C_sceSysregEnableIntr
	IMPORT_FUNC	"sceSysreg_driver",0x083F56E2,sceSysregEnableIntr
#endif
#ifdef F_0000008D_sceSysregDisableIntr
	IMPORT_FUNC	"sceSysreg_driver",0x7C5B543C,sceSysregDisableIntr
#endif
#ifdef F_0000008E_sceSysregRequestIntr
	IMPORT_FUNC	"sceSysreg_driver",0x3EA188AD,sceSysregRequestIntr
#endif
#ifdef F_0000008F_sceSysreg_driver_5664F8B5
	IMPORT_FUNC	"sceSysreg_driver",0x5664F8B5,sceSysreg_driver_5664F8B5
#endif
#ifdef F_00000090_sceSysreg_driver_44704E1D
	IMPORT_FUNC	"sceSysreg_driver",0x44704E1D,sceSysreg_driver_44704E1D
#endif
#ifdef F_00000091_sceSysreg_driver_584AD989
	IMPORT_FUNC	"sceSysreg_driver",0x584AD989,sceSysreg_driver_584AD989
#endif
#ifdef F_00000092_sceSysreg_driver_377F035F
	IMPORT_FUNC	"sceSysreg_driver",0x377F035F,sceSysreg_driver_377F035F
#endif
#ifdef F_00000093_sceSysreg_driver_AB3185FD
	IMPORT_FUNC	"sceSysreg_driver",0xAB3185FD,sceSysreg_driver_AB3185FD
#endif
#ifdef F_00000094_sceSysreg_driver_0EA487FA
	IMPORT_FUNC	"sceSysreg_driver",0x0EA487FA,sceSysreg_driver_0EA487FA
#endif
#ifdef F_00000095_sceSysreg_driver_136E8F5A
	IMPORT_FUNC	"sceSysreg_driver",0x136E8F5A,sceSysreg_driver_136E8F5A
#endif
#ifdef F_00000096_sceSysreg_driver_F4811E00
	IMPORT_FUNC	"sceSysreg_driver",0xF4811E00,sceSysreg_driver_F4811E00
#endif
