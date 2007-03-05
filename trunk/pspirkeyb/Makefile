all:
	$(MAKE) -C libpspirkeyb all
	$(MAKE) -C irkeybtest all
	$(MAKE) -C asciidemo all
	$(MAKE) -C pspirkeybprx exp_symbols
	$(MAKE) -C libpspirkeybprx all
	$(MAKE) -C asciidemoprx all

clean:
	$(MAKE) -C libpspirkeyb clean	
	$(MAKE) -C irkeybtest clean
	$(MAKE) -C asciidemo clean
	$(MAKE) -C pspirkeybprx clean	
	$(MAKE) -C libpspirkeybprx clean	
	$(MAKE) -C asciidemoprx clean
	rm -rf release

release: all
	mkdir -p release
	mkdir -p release/seplugins
	mkdir -p release/psp/game150/asciidemo
	mkdir -p release/psp/game150/asciidemoprx
	cp pspirkeybprx/irkeyb.prx release/seplugins
	cp -ar libpspirkeyb/keymap release/seplugins
	cp libpspirkeyb/config/pspirkeyb.ini release/seplugins
	cp asciidemo/EBOOT.PBP release/psp/game150/asciidemo
	cp asciidemoprx/EBOOT.PBP release/psp/game150/asciidemoprx

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
