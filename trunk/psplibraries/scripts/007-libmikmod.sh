#!/bin/sh
# libmikmod.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "libmikmod"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/libmikmod
 else
  svn update libmikmod
 fi

 ## Enter the source directory.
 cd libmikmod

 ## Compile and install.
 make -f Makefile.psp clean
 make -f Makefile.psp -j2
 make -f Makefile.psp install
 make -f Makefile.psp clean
