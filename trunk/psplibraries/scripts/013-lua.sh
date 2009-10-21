#!/bin/sh
# lua.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "lua"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/lua
 else
  svn update lua
 fi

 ## Enter the source directory.
 cd lua

 ## Compile and install.
 make -f Makefile.psp clean
 make -f Makefile.psp -j2
 make -f Makefile.psp install
 make -f Makefile.psp clean
