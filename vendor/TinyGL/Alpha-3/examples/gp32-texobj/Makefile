CC = arm-thumb-elf-gcc
AS = arm-thumb-elf-as
LD = arm-thumb-elf-gcc
OBJCOPY = arm-thumb-elf-objcopy

.SFILES	=	crt0.s

.CFILES	=	gpstart.c texobj.c sdl.c

.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)

CFLAGS	=	-I../../include -Iinclude-gp32 -I.  \
		-mtune=arm920 -march=armv4t -marm -mno-thumb-interwork \
		-msoft-float -ffast-math -nostdlib -fno-common -ffreestanding \
		-fno-builtin -fno-exceptions -mstructure-size-boundary=8 \
		-O3 -fomit-frame-pointer -fstrict-aliasing -Wall \
		-DGP32

#		-DUSE_FIXED_POINT -DGP32

LDFLAGS	=	-T$(LDSCRIPT) user_init.o -nostartfiles \
			-lgpos -lgpsound -lgpmem -lgpgraphic -lgpfont -lSDL -lTinyGL -lSDL -lgpstdlib -lm -lgpstdio

DEPENDFILE	=	Makedepend
MAPFILE	=	texobj.map
TARGET_ELF	=	texobj.elf
TARGET_BIN	=	texobj.gxb
TARGET_FXE	=	texobj.fxe
LDSCRIPT	=	lnkscript


$(TARGET_FXE): $(TARGET_BIN)
	b2fxec $< $@

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_ELF): $(.OFILES) $(DEPENDFILE)
	$(LD) -o $@ $(.OFILES) $(LDFLAGS)

.PHONY: all clean depend

all:    clean depend $(TARGET_BIN)

tags:	$(DEPENDFILE)
	ctags -e *.c *.s *.h *.S

clean:
	-rm -f $(.OFILES) $(DEPENDFILE) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN) TAGS

send: $(TARGET_FXE)
	gplink -c -x put $(TARGET_FXE) /GPMM

run: $(TARGET_FXE)
	cd ../../../emu && ./geepee32 /FXE=../TinyGL/examples/gp32-texobj/texobj.fxe /RUN

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE):
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)
