INCDIR=../include
OBJDIR=obj
DEPEND=.depend

CC=psp-gcc
AR=psp-ar
RANLIB=psp-ranlib
RMDIR=rmdir

TARGET=libgu.a
CFLAGS:=$(CFLAGS) -Wall -Werror -I$(PSPSDK)/include -G0

SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h) $(wildcard $(INCDIR)/*.h)
OBJECTS=$(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(OBJDIR) $(TARGET)

clean:
	-$(RM) $(OBJECTS) $(TARGET) $(DEPEND) *~
	-$(RMDIR) $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(AR) cru $@ $(OBJECTS)
	$(RANLIB) $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p "$@"

$(DEPEND): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -MM $(SOURCES) | sed "s/\([^:]*\):/$(subst /,\/,$(OBJDIR))\/\1:/" > $(DEPEND)
-include $(DEPEND)
