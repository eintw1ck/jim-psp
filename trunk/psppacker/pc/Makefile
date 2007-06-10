OUTPUT=psp-packer

all: pspstub.h $(OUTPUT)

CFLAGS=-Wall -g

LIBS=-lz

$(OUTPUT): $(OUTPUT).c
	$(LINK.c) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.h: ../pspstub/%.elf
	../bin2c/bin2c $^ $@ pspstub

clean:
	rm -f $(OUTPUT) pspstub.h
