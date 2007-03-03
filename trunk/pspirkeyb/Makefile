all:
	$(MAKE) -C libpspirkeyb all
	$(MAKE) -C irkeybtest all
	$(MAKE) -C asciidemo all

clean:
	$(MAKE) -C libpspirkeyb clean	
	$(MAKE) -C irkeybtest clean
	$(MAKE) -C asciidemo clean
	rm -rf release

release: all
	mkdir -p release
	mkdir -p release/seplugins
	mkdir -p release/psp/game150/asciidemo
	cp -ar libpspirkeyb/keymap release/seplugins
	cp libpspirkeyb/config/pspirkeyb.ini release/seplugins
	cp asciidemo/EBOOT.PBP release/psp/game150/asciidemo

PSPSDK=$(shell psp-config --pspsdk-path)

install: all
	$(MAKE) -C libpspirkeyb install
	mkdir -p $(PSPSDK)/samples/irkeyb
	cp -r libpspirkeyb/keymap $(PSPSDK)/samples/irkeyb
	cp libpspirkeyb/config/pspirkeyb.ini $(PSPSDK)/samples/irkeyb
	cp asciidemo/main.c $(PSPSDK)/samples/irkeyb
	cp asciidemo/Makefile.sdk $(PSPSDK)/samples/irkeyb/Makefile

uninstall:
	$(MAKE) -C libpspirkeyb install
	rm -rf $(PSPSDK)/samples/irkeyb
