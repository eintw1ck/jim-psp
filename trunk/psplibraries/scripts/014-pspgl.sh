#!/bin/sh
# pspgl.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "pspgl"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/pspgl
 else
  svn update pspgl
 fi

 ## Enter the source directory.
 cd pspgl

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
