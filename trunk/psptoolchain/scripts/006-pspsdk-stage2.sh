#!/bin/sh
# pspsdk-stage2.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 if test ! -d "pspsdk"; then
  svn checkout svn://svn.pspdev.org/psp/trunk/pspsdk || { exit 1; }
 else
  svn update pspsdk || { exit 1; }
 fi

 ## Enter the source directory.
 cd pspsdk || { exit 1; }

 ## Bootstrap the source.
 ./bootstrap || { exit 1; }

 ## Configure the build.
 ./configure --with-pspdev="$PSPDEV" || { exit 1; }

 ## Build and install.
 make clean && make && make install && make clean || { exit 1; }
