#!/bin/sh
# gcc-4.1.0-stage2.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 if test ! -f "gcc-4.1.0.tar.bz2"; then
  wget ftp://ftp.gnu.org/pub/gnu/gcc/gcc-4.1.0/gcc-4.1.0.tar.bz2 || { exit 1; }
 fi

 ## Unpack the source code.
 rm -Rf gcc-4.1.0 && tar xfvj gcc-4.1.0.tar.bz2 || { exit 1; }

 ## Enter the source directory and patch the source code.
 cd gcc-4.1.0 && cat ../../patches/gcc-4.1.0-PSP.patch | patch -p1 || { exit 1; }

 ## Create and enter the build directory.
 mkdir build-psp && cd build-psp || { exit 1; }

 ## Configure the build.
 ../configure --prefix="$PSPDEV" --target="psp" --enable-languages="c,c++" --with-newlib --enable-cxx-flags="-G0" || { exit 1; }

 ## Compile and install.
 make clean && CFLAGS_FOR_TARGET="-G0" make -j 2 && make install && make clean || { exit 1; }
