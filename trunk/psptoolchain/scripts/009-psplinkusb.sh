#!/bin/sh
# psplinkusb.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 if test ! -d "psplinkusb"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/psplinkusb || { exit 1; }
 else
  svn update psplinkusb || { exit 1; }
 fi

 ## Enter the source directory.
 cd psplinkusb && cat ../../patches/psplinkusb.patch | patch -p1 || { exit 1; }|| { exit 1; }

 ## Build and install.
 make -f Makefile.clients clean && make -f Makefile.clients && make -f Makefile.clients install && make -f Makefile.clients clean || { exit 1; }
