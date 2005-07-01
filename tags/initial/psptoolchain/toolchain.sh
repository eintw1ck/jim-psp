#!/bin/sh
# toolchain.sh - Dan Peori <peori@oopo.net>
# Copy all you want. Please give me some credit.

 ########################
 ## MAIN CONFIGURATION ##
 ########################

  ## Main pspdev settings.
  export PSPDEV="/usr/local/pspdev"
  export PSPSDK="$PSPDEV/pspsdk"
  export CVSROOT=":pserver:anonymous@cvs.ps2dev.org:/home/pspcvs"
  export PATH="$PATH:$PSPDEV/bin:$PSPDEV/psp/bin:$PSPSDK/bin"

  ## Set the directories.
  export SRCDIR="`pwd`"
  export TMPDIR="/tmp/pspdev"

  ## Source code versions.
  export BINUTILS="binutils-2.16"
  export GCC="gcc-4.0.0"
  export NEWLIB="newlib-1.13.0"

  ## CVS configuration.
  # if [ -z "`cat ~/.cvspass | grep $CVSROOT`" ]; then
  #  echo "THE SECRET PASSWORD IS: anonymous"
  #  cvs -d $CVSROOT login
  # fi

 ###########################
 ## SOFTWARE DEPENDENCIES ##
 ###########################

  ## Check for which make to use.
  export MAKE="gmake"; $MAKE -v || { export MAKE="make"; }

  ## Check for make.
  $MAKE -v || { echo "ERROR: Please make sure you have GNU 'make' installed."; exit; }

  ## Check for patch.
  patch -v || { echo "ERROR: Please make sure you have 'patch' installed."; exit; }

  ## Check for wget.
  wget -V || { echo "ERROR: Please make sure you have 'wget' installed."; exit; }

 ################################
 ## DOWNLOAD, UNPACK AND PATCH ##
 ################################

  ## Download the source.
  wget -c ftp://ftp.gnu.org/pub/gnu/binutils/$BINUTILS.tar.gz
  wget -c ftp://ftp.gnu.org/pub/gnu/gcc/$GCC/$GCC.tar.bz2
  wget -c ftp://sources.redhat.com/pub/newlib/$NEWLIB.tar.gz

  ## Create the build directory.
  mkdir -p $TMPDIR; cd $TMPDIR

  ## Unpack the source.
  rm -Rf $BINUTILS; tar xfvz $SRCDIR/$BINUTILS.tar.gz
  rm -Rf $GCC; tar xfvj $SRCDIR/$GCC.tar.bz2
  rm -Rf $NEWLIB; tar xfvz $SRCDIR/$NEWLIB.tar.gz

  ## Patch the source.
  cd $BINUTILS; cat $SRCDIR/$BINUTILS.patch | patch -p1; cd ..
  cd $GCC; cat $SRCDIR/$GCC.patch | patch -p1; cd ..
  cd $NEWLIB; cat $SRCDIR/$NEWLIB.patch | patch -p1; cd ..

 ################################
 ## BUILD AND INSTALL BINUTILS ##
 ################################

  ## Enter the source directory.
  cd $BINUTILS

  ## Build for each target.
  for TARGET in "psp"; do

   ## Create the build directory.
   mkdir build-$TARGET

   ## Enter the build directory.
   cd build-$TARGET

   ## Configure the source.
   ../configure --prefix=$PSPDEV/$TARGET --target=$TARGET || { echo "ERROR CONFIGURING BINUTILS ($BINUTILS $TARGET)"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING BINUTILS ($BINUTILS $TARGET)"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING BINUTILS ($BINUTILS $TARGET)"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build directory.
   cd ..

  ## End of the target build.
  done

  ## Exit the source directory.
  cd ..

 ###########################
 ## BUILD AND INSTALL GCC ##
 ###########################

  ## Enter the source directory.
  cd $GCC

  ## Build for each target.
  for TARGET in "psp"; do

   ## Create the build directory.
   mkdir build-$TARGET

   ## Enter the build directory.
   cd build-$TARGET

   ## Configure the source.
   ../configure --prefix=$PSPDEV/$TARGET --target=$TARGET --enable-languages="c" --with-newlib --without-headers || { echo "ERROR CONFIGURING GCC ($GCC $TARGET)"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING GCC ($GCC $TARGET)"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING GCC ($GCC $TARGET)"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build directory.
   cd ..

  ## End of the target build.
  done

  ## Exit the source directory.
  cd ..

 ##############################
 ## BUILD AND INSTALL NEWLIB ##
 ##############################

  ## Enter the source directory.
  cd $NEWLIB

  ## Build for each target.
  for TARGET in "psp"; do

   ## Create the build directory.
   mkdir build-$TARGET

   ## Enter the build directory.
   cd build-$TARGET

   ## Configure the source.
   ../configure --prefix=$PSPDEV/$TARGET --target=$TARGET || { echo "ERROR CONFIGURING NEWLIB ($NEWLIB $TARGET)"; exit; }

   ## Build the source.
   $MAKE clean; CPPFLAGS="-G0" $MAKE || { echo "ERROR BUILDING NEWLIB ($NEWLIB $TARGET)"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING NEWLIB ($NEWLIB $TARGET)"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build directory.
   cd ..

  ## End of the target build.
  done

  ## Exit the source directory.
  cd ..

 #################################
 ## BUILD AND INSTALL GCC (C++) ##
 #################################

  ## Enter the source directory.
  cd $GCC

  ## Build for each target.
  for TARGET in "psp"; do

   ## Create the build directory.
   mkdir build-$TARGET-c++

   ## Enter the build directory.
   cd build-$TARGET-c++

   ## Configure the source.
   ../configure --prefix=$PSPDEV/$TARGET --target=$TARGET --enable-languages="c,c++" --with-newlib --with-headers=$PSPDEV/$TARGET/$TARGET/include --enable-cxx-flags="-G0" || { echo "ERROR CONFIGURING GCC ($GCC $TARGET C++)"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE CFLAGS_FOR_TARGET="-G0" || { echo "ERROR BUILDING GCC ($GCC $TARGET C++)"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING GCC ($GCC $TARGET C++)"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build directory.
   cd ..

  ## End of the target build.
  done

  ## Exit the source directory.
  cd ..

 ##############################
 ## BUILD AND INSTALL PSPSDK ##
 ##############################

  ## Remove any previous builds.
  # rm -Rf pspsdk

  ## Check out the latest source.
  # cvs -d $CVSROOT checkout pspsdk

  ## Enter the source directory.
  # cd pspsdk

  ## Build the source.
  # $MAKE clean; $MAKE || { echo "ERROR BUILDING PSPSDK"; exit; }

  ## Install the result.
  # $MAKE release || { echo "ERROR INSTALLING PSPSDK"; exit; }
  
  ## Clean up the result.
  # $MAKE clean

  ## Exit the source directory.
  # cd ..

 #########################
 ## CLEAN UP THE RESULT ##
 #########################

  ## Clean up binutils.
  rm -Rf $BINUTILS

  ## Clean up gcc.
  rm -Rf $GCC

  ## Clean up newlib.
  rm -Rf $NEWLIB

  ## Clean up pspsdk.
  # rm -Rf pspsdk
