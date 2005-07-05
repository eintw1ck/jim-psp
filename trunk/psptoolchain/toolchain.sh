#!/bin/sh 
# toolchain.sh - Dan Peori <peori@oopo.net>
# Copy all you want. Please give me some credit.

 ########################
 ## MAIN CONFIGURATION ##
 ########################

  ## Main pspdev settings.
  PSPDEV="/usr/local/pspdev"
  PATH="$PATH:$PSPDEV/bin"

  ## Set the directories.
  SRCDIR="`pwd`"
  TMPDIR="/tmp/pspdev"

  ## Source code versions.
  BINUTILS="binutils-2.16"
  GCC="gcc-4.0.0"
  NEWLIB="newlib-1.13.0"

 #########################
 ## PARSE THE ARGUMENTS ##
 #########################

  ## If no arguments are given, do everything.
  if [ $# == 0 ] ; then
   DO_DOWNLOAD=1
   BUILD_BINUTILS=1
   BUILD_GCC=1
   BUILD_NEWLIB=1
   BUILD_PSPSDK=1

  ## Else, parse the arguments.
  else
   while [ $# -ge 1 ] ; do
    case "$1" in
     -d)
      DO_DOWNLOAD=1
      shift;;
     -b)
      BUILD_BINUTILS=1
      shift;;
     -g)
      BUILD_GCC=1
      shift;;
     -n)
      BUILD_NEWLIB=1
      shift;;
     -p)
      BUILD_PSPSDK=1
      shift;;
    esac
   done
  fi

 ###########################
 ## SOFTWARE DEPENDENCIES ##
 ###########################

  ## Check for which make to use.
  MAKE="gmake"; $MAKE -v || { MAKE="make"; }

  ## Check for make.
  $MAKE -v || { echo "ERROR: Please make sure you have GNU 'make' installed."; exit; }

  ## Check for patch.
  patch -v || { echo "ERROR: Please make sure you have 'patch' installed."; exit; }

  ## Check for wget.
  wget -V || { echo "ERROR: Please make sure you have 'wget' installed."; exit; }

  ## Check for subversion.
  svn help || { echo "ERROR: Please make sure you have 'subversion (svn)' installed."; exit; }

 ################################
 ## DOWNLOAD, UNPACK AND PATCH ##
 ################################

  ## Download the source.
  if [ $DO_DOWNLOAD ] ; then
   wget -c --passive-ftp ftp://ftp.gnu.org/pub/gnu/binutils/$BINUTILS.tar.gz
   wget -c --passive-ftp ftp://ftp.gnu.org/pub/gnu/gcc/$GCC/$GCC.tar.bz2
   wget -c --passive-ftp ftp://sources.redhat.com/pub/newlib/$NEWLIB.tar.gz
  fi

  ## Create the temp directory.
  mkdir -p $TMPDIR; cd $TMPDIR

  ## Unpack and patch the binutils source.
  if [ $BUILD_BINUTILS ] ; then
    rm -Rf $BINUTILS; tar xfvz $SRCDIR/$BINUTILS.tar.gz
    cd $BINUTILS; cat $SRCDIR/$BINUTILS.patch | patch -p1; cd ..
  fi

  ## Unpack and patch the gcc source.
  if [ $BUILD_GCC ] ; then
    rm -Rf $GCC; tar xfvj $SRCDIR/$GCC.tar.bz2
    cd $GCC; cat $SRCDIR/$GCC.patch | patch -p1; cd ..
  fi

  ## Unpack and patch the newlib source.
  if [ $BUILD_NEWLIB ] ; then
    rm -Rf $NEWLIB; tar xfvz $SRCDIR/$NEWLIB.tar.gz
    cd $NEWLIB; cat $SRCDIR/$NEWLIB.patch | patch -p1; cd ..
  fi

 ################################
 ## BUILD AND INSTALL BINUTILS ##
 ################################

  if [ $BUILD_BINUTILS ] ; then

   ## Enter the source directory.
   cd $BINUTILS

   ## Create and enter the build directory.
   mkdir build-psp; cd build-psp

   ## Configure the source.
   ../configure --prefix=$PSPDEV --target=psp --enable-install-libbfd || { echo "ERROR CONFIGURING BINUTILS"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING BINUTILS"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING BINUTILS"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build and source directories.
   cd ..; cd ..

  fi

 ###########################
 ## BUILD AND INSTALL GCC ##
 ###########################

  if [ $BUILD_GCC ] ; then

   ## Enter the source directory.
   cd $GCC

   ## Create and enter the build directory.
   mkdir build-psp; cd build-psp

   ## Configure the source.
   ../configure --prefix=$PSPDEV --target=psp --enable-languages="c" --with-newlib --without-headers || { echo "ERROR CONFIGURING GCC"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING GCC"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING GCC"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build and source directories.
   cd ..; cd ..

  fi

 ##############################
 ## BUILD AND INSTALL NEWLIB ##
 ##############################

  if [ $BUILD_NEWLIB ] ; then

   ## Enter the source directory.
   cd $NEWLIB

   ## Create and enter the build directory.
   mkdir build-psp; cd build-psp

   ## Configure the source.
   ../configure --prefix=$PSPDEV --target=psp || { echo "ERROR CONFIGURING NEWLIB"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING NEWLIB"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING NEWLIB"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build and source directories.
   cd ..; cd ..

  fi

 #################################
 ## BUILD AND INSTALL GCC (C++) ##
 #################################

  if [ $BUILD_GCC ] ; then

   ## Enter the source directory.
   cd $GCC

   ## Create and enter the build directory.
   mkdir build-psp-c++; cd build-psp-c++

   ## Configure the source.
   ../configure --prefix=$PSPDEV --target=psp --enable-languages="c,c++" --with-newlib --enable-cxx-flags="-G0" || { echo "ERROR CONFIGURING GCC (C++)"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE CFLAGS_FOR_TARGET="-G0" || { echo "ERROR BUILDING GCC (C++)"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING GCC (C++)"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build and source directories.
   cd ..

  fi

 ##############################
 ## BUILD AND INSTALL PSPSDK ##
 ##############################

  if [ $BUILD_PSPSDK ] ; then

   ## Remove any previous builds.
   rm -Rf pspsdk

   ## Check out the latest source.
   svn checkout svn://svn.pspdev.org/psp/trunk/pspsdk

   ## Enter the source directory.
   cd pspsdk

   ## Bootstrap the source.
   ./bootstrap || { echo "ERROR RUNNING PSPSDK BOOSTRAP"; exit; }

   ## Configure the source.
   ./configure || { echo "ERROR RUNNING PSPSDK CONFIGURE"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING PSPSDK"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING PSPSDK"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the source directory.
   cd ..

  fi

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
  rm -Rf pspsdk
