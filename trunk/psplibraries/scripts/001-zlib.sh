#!/bin/sh
# zlib.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "zlib"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/zlib
 else
  svn update zlib
 fi

 ## Enter the source directory.
 cd zlib

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
