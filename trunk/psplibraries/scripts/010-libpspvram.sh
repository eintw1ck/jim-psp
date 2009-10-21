#!/bin/sh
# libpspvram.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "libpspvram"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/libpspvram
 else
  svn update libpspvram
 fi

 ## Enter the source directory.
 cd libpspvram

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
