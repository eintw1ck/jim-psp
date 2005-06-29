TARGET = cube
OBJS = cube.o

INCDIR = ../../include
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = ../../src
LDFLAGS =
LIBS= -lgu

PSP_DIR_NAME=CUBE
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = SceGu Cube

include $(PSPSDK)/lib/build.mak

kxploit:
	rm -rf "$(PSP_DIR_NAME)" "$(PSP_DIR_NAME)%" .psp
	mkdir .psp
	pwd
	(cd .psp;unpack-pbp ../EBOOT.PBP;mkdir "$(PSP_DIR_NAME)";mv UNKNOWN.PSP "$(PSP_DIR_NAME)/EBOOT.PBP";mkdir "$(PSP_DIR_NAME)%";touch UNKNOWN.PSP;pack-pbp "$(PSP_DIR_NAME)%/EBOOT.PBP" PARAM.SFO ICON0.PNG ICON1.PMF UKNOWN.PNG PIC1.PNG SND0.AT3 UNKNOWN.PSP UNKNOWN.PSAR;mv $(PSP_DIR_NAME)* ..)
	rm -rf .psp
