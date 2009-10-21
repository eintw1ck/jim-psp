#!/bin/sh
# libbulletml.sh by Dan Peori (danpeori@oopo.net)

 ## Exit on errors
 set -e

 ## Download the latest source code.
 if test ! -d "libbulletml"; then
  svn checkout svn://svn.ps2dev.org/psp/trunk/libbulletml
 else
  svn update libbulletml
 fi

 ## Enter the source directory.
 cd libbulletml/src

 ## Compile and install.
 make clean
 make -j2
 make install
 make clean
