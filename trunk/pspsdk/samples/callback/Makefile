PSP_OUTPUT=EBOOT.PBP
PSP_PATCHEDBIN=sdktestp.bin
PSP_BIN=sdktest.bin
PSP_OBJS=main.o
PSP_MAP=sdktest.map
PSP_CFLAGS=-Wall -march=r4000 -g -G0 -mgp32 -mlong32 -I. -I$(PSPSDK)/include

all: $(PSP_OUTPUT)

clean: 
	rm -f $(PSP_OBJS) $(PSP_MAP) $(PSP_BIN) $(PSP_PATCHEDBIN) $(PSP_OUTPUT)

$(PSP_OUTPUT) : $(PSP_PATCHEDBIN)
	./elf2pbp.exe $(PSP_PATCHEDBIN) "SDK Test"
	cp	EBOOT.PBP /cygdrive/f/PSP/GAME/test

$(PSP_PATCHEDBIN) :	$(PSP_OBJS)
	ee-ld -O0 -G0 $(PSPSDK)/startup/crt0.o $(PSP_OBJS) -L$(PSPSDK)/lib -lkernel -M -Ttext 8900000 -q -o $(PSP_BIN) > $(PSP_MAP)
	$(PSPSDK)/bin/outpatch $(PSP_BIN) $(PSP_PATCHEDBIN)

%.o : %.c
	ee-gcc $(PSP_CFLAGS) -c $< -o $@

%.o : %.s
	ee-gcc $(PSP_CFLAGS) -c -xassembler -O -o $@ $<
