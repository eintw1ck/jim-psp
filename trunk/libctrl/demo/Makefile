TARGET = ctrldemo.c
OBJS = ctrldemo.o

PSPSDK = $(PSPDEV)/psp/sdk
CFLAGS = -O2 -G0 -Wall
LIBS = -lctrl -lpsprtc
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION = 500

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = libctrl demo

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

install:
	mount /media/usbflash 
	mkdir -p /media/usbflash/psp/game5xx/ctrldemo || true
	cp EBOOT.PBP /media/usbflash/psp/game5xx/ctrldemo
	umount /media/usbflash
