## TODO: This isn't the best way to handle samples.  Come up with something better.

## XXX: This is severely broken - sdktest is the only sample we can support here.
samplesdir = @PSPSDK@/samples/sdktest

sdktest_files  = $(srcdir)/sdktest/main.c $(srcdir)/sdktest/Makefile.sample

SAMPLES_DIST = $(sdktest_files)

all:

# Copy the samples into the installation samples directory.  Rename any .sample files.
install-data-hook:
	$(mkinstalldirs) $(DESTDIR)$(samplesdir)
	cp -rp $(SAMPLES_DIST) $(DESTDIR)$(samplesdir)
	for f in `find $(DESTDIR)$(samplesdir) -name *.sample -print `; do \
		mv -v $$f `echo $$f | sed -e 's/\.sample$$//'` ; done

uninstall-hook:
	rm -rf $(DESTDIR)$(samplesdir)/*

EXTRA_DIST = $(SAMPLES_DIST)
