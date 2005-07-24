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
  GCC="gcc-4.0.1"
  NEWLIB="newlib-1.13.0"

 #########################
 ## PARSE THE ARGUMENTS ##
 #########################

  ## If no arguments are given...
  if test $# -eq 0 ; then

   ## Do everything possible.
   DO_DOWNLOAD=1
   BUILD_BINUTILS=1
   BUILD_GCC=1
   BUILD_NEWLIB=1
   BUILD_PSPSDK=1

  ## Else...
  else

   ## Parse the arguments.
   while test $# -ge 1 ; do
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

  # Newlib depends on PSPSDK headers, so if it's being built
  # then make sure that PSPSDK is being built.
  if test $BUILD_NEWLIB ; then
   BUILD_PSPSDK=1
  fi

 ###########################
 ## SOFTWARE DEPENDENCIES ##
 ###########################

  ## Check for make.
  if test "`gmake -v`" ; then
   MAKE="gmake"
  else
   if test "`make -v`" ; then
    MAKE="make"
   else
    echo "ERROR: Please make sure you have GNU 'make' installed."
    exit
   fi
  fi

  ## Check for patch.
  if test "`gpatch -v`" ; then
   PATCH="gpatch -p1"
  else
   if test "`patch -v`" ; then
    PATCH="patch -p1"
   else
    echo "ERROR: Please make sure you have 'patch' installed."
    exit
   fi
  fi

  ## Check for wget.
  if test "`wget -V`" ; then
   WGET="wget --passive-ftp"
  else
   echo "ERROR: Please make sure you have 'wget' installed."
   exit
  fi

  ## Check for subversion.
  if test "`svn help`" ; then
   SVN="svn"
  else
   echo "ERROR: Please make sure you have 'subversion (svn)' installed."
   exit
  fi

 ################################
 ## DOWNLOAD, UNPACK AND PATCH ##
 ################################

  ## If we've been told to download...
  if test $DO_DOWNLOAD ; then

   ## Download the binutils source.
   if test $BUILD_BINUTILS ; then
    if test ! -f "$BINUTILS.tar.gz" ; then
     $WGET ftp://ftp.gnu.org/pub/gnu/binutils/$BINUTILS.tar.gz || { echo "ERROR DOWNLOADING BINUTILS"; exit; }
    fi
   fi

   ## Download the gcc source.
   if test $BUILD_GCC ; then
    if test ! -f "$GCC.tar.bz2" ; then
     $WGET ftp://ftp.gnu.org/pub/gnu/gcc/$GCC/$GCC.tar.bz2 || { echo "ERROR DOWNLOADING GCC"; exit; }
    fi
   fi

   ## Download the newlib source.
   if test $BUILD_NEWLIB ; then
    if test ! -f "$NEWLIB.tar.gz" ; then
     $WGET ftp://sources.redhat.com/pub/newlib/$NEWLIB.tar.gz || { echo "ERROR DOWNLOADING NEWLIB"; exit; }
    fi
   fi

  fi

  ## Create and enter the temp directory.
  mkdir -p "$TMPDIR"; cd "$TMPDIR"

  ## Unpack and patch the binutils source.
  if test $BUILD_BINUTILS ; then
   rm -Rf $BINUTILS; gzip -cd "$SRCDIR/$BINUTILS.tar.gz" | tar xvf -
   cd $BINUTILS; cat "$SRCDIR/$BINUTILS.patch" | $PATCH || { echo "ERROR PATCHING BINUTILS"; exit; }
   cd ..
  fi

  ## Unpack and patch the gcc source.
  if test $BUILD_GCC ; then
   rm -Rf $GCC; bzip2 -cd "$SRCDIR/$GCC.tar.bz2" | tar xvf -
   cd $GCC; cat "$SRCDIR/$GCC.patch" | $PATCH || { echo "ERROR PATCHING GCC"; exit; }
   cd ..
  fi

  ## Unpack and patch the newlib source.
  if test $BUILD_NEWLIB ; then
   rm -Rf $NEWLIB; gzip -cd "$SRCDIR/$NEWLIB.tar.gz" | tar xvf -
   cd $NEWLIB; cat "$SRCDIR/$NEWLIB.patch" | $PATCH || { echo "ERROR PATCHING NEWLIB"; exit; }
   cd ..
  fi

  ## Grab the latest PSPSDK from Subversion.
  if test $BUILD_PSPSDK ; then
   rm -Rf pspsdk
   $SVN checkout svn://svn.pspdev.org/psp/trunk/pspsdk
  fi

 ################################
 ## BUILD AND INSTALL BINUTILS ##
 ################################

  ## If we've been told to build binutils...
  if test $BUILD_BINUTILS ; then

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

  ## If we've been told to build gcc...
  if test $BUILD_GCC ; then

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

 ############################
 ## INSTALL PSPSDK HEADERS ##
 ############################

  if test $BUILD_PSPSDK ; then

   ## Enter the source directory.
   cd pspsdk

   ## Bootstrap the source.
   ./bootstrap || { echo "ERROR RUNNING PSPSDK BOOSTRAP"; exit; }

   ## Configure the source.
   ./configure || { echo "ERROR RUNNING PSPSDK CONFIGURE"; exit; }

   ## Install the headers that Newlib requires.
   $MAKE clean; $MAKE install-data || { echo "ERROR BUILDING PSPSDK"; exit; }

   ## Exit the source directory.
   cd ..

  fi

 ##############################
 ## BUILD AND INSTALL NEWLIB ##
 ##############################

  ## If we've been told to build newlib...
  if test $BUILD_NEWLIB ; then

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

  ## If we've been told to build gcc...
  if test $BUILD_GCC ; then

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
   cd ..; cd ..

  fi

 ##############################
 ## BUILD AND INSTALL PSPSDK ##
 ##############################

  ## If we've been told to build pspsdk...
  if test $BUILD_PSPSDK ; then

   ## Enter the source directory.
   cd pspsdk

   ## Reconfigure the source (to pick up the C++ compiler).
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

  ## Clean up the binutils source.
  rm -Rf $BINUTILS

  ## Clean up the gcc source.
  rm -Rf $GCC

  ## Clean up the newlib source.
  rm -Rf $NEWLIB

  ## Clean up the pspsdk source.
  rm -Rf pspsdk
