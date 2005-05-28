PSP_EBOOT = EBOOT.PBP
PSP_BIN = sdktest.elf
PSP_OBJS = main.o
PSP_LIBS = -ldebug
PSP_EBOOT_SFO = res/PARAM.SFO

all: release 

release : $(PSP_EBOOT)

clean:
	rm -f *.elf *.o *.a $(PSP_EBOOT)

include $(PSPSDK)/build/Makefile.pref
include $(PSPSDK)/build/Makefile.global

