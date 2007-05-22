#!/bin/sh
# insight-6.4.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 if test ! -f "insight-6.4.tar.bz2"; then
  wget ftp://sourceware.org/pub/insight/releases/insight-6.4.tar.bz2 || { exit 1; }
 fi

 ## Unpack the source code.
 rm -Rf insight-6.4 && tar xfvj insight-6.4.tar.bz2 || { exit 1; }

 ## Enter the source directory and patch the source code.
 cd insight-6.4 && cat ../../patches/insight-6.4-PSP.patch | patch -p1 || { exit 1; }

 ## Create and enter the build directory.
 mkdir build-psp && cd build-psp || { exit 1; }

 ## Configure the build.
 ../configure --prefix="$PSPDEV" --target="psp" --disable-nls || { exit 1; }

 ## Compile and install.
 make clean && make -j 2 && make install || { exit 1; }
