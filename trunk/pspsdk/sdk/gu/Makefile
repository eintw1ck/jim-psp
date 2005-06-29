SRCDIR=src

all:
	$(MAKE) -C $(SRCDIR) all

install:
	$(MAKE) -C $(SRCDIR) install

clean:
	$(MAKE) -C $(SRCDIR) clean

dos2unix:
	find | while read f ; do dos2unix "$$f" ; done
