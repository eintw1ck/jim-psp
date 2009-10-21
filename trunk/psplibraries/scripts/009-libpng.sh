#!/bin/sh
# libpng.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "libpng"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/libpng
 else
  svn update libpng
 fi

 ## Enter the source directory.
 cd libpng

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
