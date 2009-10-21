#!/bin/sh
# pspirkeyb.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "pspirkeyb"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/pspirkeyb
 else
  svn update pspirkeyb
 fi

 ## Enter the source directory.
 cd pspirkeyb

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
