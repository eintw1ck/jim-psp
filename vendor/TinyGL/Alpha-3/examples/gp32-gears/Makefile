CC = arm-thumb-elf-gcc
AS = arm-thumb-elf-as
LD = arm-thumb-elf-gcc
OBJCOPY = arm-thumb-elf-objcopy

.SFILES	=	crt0.s

.CFILES	=	gpstart.c gears.c sdl.c

.OFILES	=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)

CFLAGS	=	-I../../include -Iinclude-gp32 -I. -O2 -mtune=arm920 \
			-DGFXST -DGP32\
			-Wuninitialized -Wno-import -Wchar-subscripts -Wformat -Wimplicit-int \
			-Wimplicit-function-declaration \
			-Wmultichar -Wreturn-type -Wswitch -Wunused -Wuninitialized -Wsign-compare \
			-msoft-float -mthumb-interwork

LDFLAGS	=	-T$(LDSCRIPT) user_init.o -nostartfiles \
			-lgpos -lgpsound -lgpmem -lgpgraphic -lgpfont -lSDL -lTinyGL -lSDL -lgpstdlib -lm -lgpstdio

DEPENDFILE	=	Makedepend
MAPFILE	=	gears.map
TARGET_ELF	=	gears.elf
TARGET_BIN	=	gears.gxb
TARGET_FXE	=	gears.fxe
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

depend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE):
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

include $(DEPENDFILE)
