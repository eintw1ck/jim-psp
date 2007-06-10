OUTPUT=bin2c

all: $(OUTPUT)

CFLAGS=-Wall

$(OUTPUT): $(OUTPUT).c
	$(LINK.c) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OUTPUT)

