
samplesdir = @PSPSDK@/samples

SAMPLES = \
	audio/polyphonic \
	audio/wavegen \
	controller/basic \
	debug/exception \
	debug/kprintf \
	debug/prxdecrypt \
	debug/profiler \
	debug/sio \
	debug/gdb \
	gu/blend \
	gu/blit \
	gu/celshading \
	gu/clut \
        gu/common \
	gu/copy \
	gu/cube \
	gu/envmap \
	gu/lights \
	gu/lines \
	gu/logic \
	gu/morph \
	gu/morphskin \
	gu/reflection \
	gu/rendertarget \
	gu/shadowprojection \
	gu/signals \
	gu/skinning \
	gu/speed \
	gu/spharm \
	gu/splinesurface \
	gu/sprite \
	gu/zbufferfog \
	ir/sircs \
	ir/irda \
	kernel/kdumper \
	kernel/loadmodule \
	kernel/threadstatus \
	kernel/cwd \
	kernel/fileio \
	kernel/messagebox \
	nand/dumpipl \
	net/simple \
	net/simple_prx \
	power \
	prx/prx_loader \
	prx/testprx \
	savedata/utility \
	savedata/decrypt \
	savedata/encrypt \
	usb/storage \
	utility/netconf \
	utility/msgdialog \
	utility/systemparam \
	me/basic \
	wlan

all:

dist-hook:
	rm -rf `find $(distdir) -name .svn -o -name CVS`

# Install all of the samples.  Rename any files that end in a .sample extension.
SAMPLES_INSTALL = $(INSTALL_DATA)
install-data-hook:
	$(mkinstalldirs) $(DESTDIR)$(samplesdir)
	@list='$(SAMPLES)'; for s in $$list; do \
	  $(mkinstalldirs) $(DESTDIR)$(samplesdir)/$$s; \
	  for p in $(srcdir)/$$s/*; do \
	    if test -f $$p; then \
	      f="`echo $$p | sed -e 's|^.*/||'`"; \
	      echo " $(SAMPLES_INSTALL) $$p $(DESTDIR)$(samplesdir)/$$s/$$f"; \
	      $(SAMPLES_INSTALL) $$p $(DESTDIR)$(samplesdir)/$$s/$$f; \
	    else :; fi; \
	  done; \
	done
	@for p in `find $(DESTDIR)$(samplesdir) -name *.sample -print `; do \
	  f="`echo $$p | sed -e 's/\.sample$$//'`"; \
	  echo " mv $$p $$f"; \
	  mv $$p $$f;  \
	done

uninstall-hook:
	@list='$(SAMPLES)'; for s in $$list; do \
	  for p in $(DESTDIR)$(samplesdir)/$$s/*; do \
	    if test -f $$p; then \
	      p="`echo $$p | sed -e 's|^.*/||'`"; \
	      echo " rm -f $(DESTDIR)$(samplesdir)/$$s/$$p"; \
	      rm -f $(DESTDIR)$(samplesdir)/$$s/$$p; \
	    else :; fi; \
	  done; \
	done

EXTRA_DIST = $(SAMPLES)
