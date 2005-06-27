PSPSDK=$(shell psp-config --pspsdk-path)
PSP_EBOOT = EBOOT.PBP
PSP_BIN = sdktest.elf
PSP_OBJS = main.o
PSP_LIBS = -lpspdebug
#PSP_EBOOT_SFO = res/PARAM.SFO
PSP_EBOOT_TITLE = SDK Test v1.0

all: release 

release : $(PSP_EBOOT)

clean:
	rm -f *.elf *.o *.a $(PSP_EBOOT) $(PSP_EBOOT_SFO)

include ../../build/Makefile.global

