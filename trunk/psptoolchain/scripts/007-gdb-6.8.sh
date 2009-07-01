#!/bin/sh
# gdb-6.8.3.sh by Dan Peori (danpeori@oopo.net)

 ## Download the source code.
 wget --continue ftp://ftp.gnu.org/pub/gnu/gdb/gdb-6.8.tar.bz2 || { exit 1; }

 ## Unpack the source code.
 rm -Rf gdb-6.8 && tar xfvj gdb-6.8.tar.bz2 || { exit 1; }

 ## Enter the source directory and patch the source code.
 cd gdb-6.8 && cat ../../patches/gdb-6.8-PSP.patch | patch -p1 || { exit 1; }

 ## Create and enter the build directory.
 mkdir build-psp && cd build-psp || { exit 1; }

 ## Configure the build.
 ../configure --prefix="$PSPDEV" --target="psp" --disable-werror --disable-nls || { exit 1; }

 ## Compile and install.
 make clean && make -j 2 && make install && make clean || { exit 1; }
