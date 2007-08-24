#!/bin/sh
# psplink.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 if test ! -d "psplink"; then
  svn checkout svn://svn.pspdev.org/psp/trunk/psplink || { exit 1; }
 else
  svn update psplink || { exit 1; }
 fi

 ## Enter the source directory.
 cd psplink || { exit 1; }

 ## Build and install.
 make clean-clients && make all-clients && make install-clients && make clean-clients || { exit 1; }
