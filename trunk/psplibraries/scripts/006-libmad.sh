#!/bin/sh
# libmad.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "libmad"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/libmad
 else
  svn update libmad
 fi

 ## Enter the source directory.
 cd libmad

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
