#!/bin/sh
# jpeg.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "jpeg"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/jpeg
 else
  svn update jpeg
 fi

 ## Enter the source directory.
 cd jpeg

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
