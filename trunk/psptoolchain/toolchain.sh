#!/bin/sh 
# toolchain.sh - Dan Peori <peori@oopo.net>
# Copy all you want. Please give me some credit.

 ########################
 ## MAIN CONFIGURATION ##
 ########################

  ## Main pspdev settings.
  PSPDEV="/usr/local/pspdev"
  PSPSDK="$PSPDEV/pspsdk"
  CVSROOT=":pserver:anonymous@cvs.ps2dev.org:/home/pspcvs"
  PATH="$PATH:$PSPDEV/bin"

  ## Set the directories.
  SRCDIR="`pwd`"
  TMPDIR="/tmp/pspdev"

  ## Source code versions.
  BINUTILS="binutils-2.16"
  GCC="gcc-4.0.0"
  NEWLIB="newlib-1.13.0"


  ## Decide what to build
  args=`getopt gbnx $*`
  set -- $args

  for i
  do
    case "$i"
    in
      -g)
        BUILD_GCC=1
        shift;;
      -b)
        BUILD_BINUTILS=1
        shift;;
      -n)
        BUILD_NEWLIB=1
        shift;;
      -x)
        DO_NOT_DOWNLOAD=1
        shift;;
    esac
  done

  ## Download and build everything if nothing specified
  if [ ! "$1" ]
  then
    BUILD_GCC=1
    BUILD_BINUTILS=1
    BUILD_NEWLIB=1
    DO_NOT_DOWNLOAD=0
  fi

  ## CVS configuration.
  # if [ -z "`cat ~/.cvspass | grep $CVSROOT`" ]; then
  #  echo "THE SECRET PASSWORD IS: anonymous"
  #  cvs -d $CVSROOT login
  # fi

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

 ################################
 ## DOWNLOAD, UNPACK AND PATCH ##
 ################################

  ## Download the source.

  if [ ! $DO_NOT_DOWNLOAD ] ; then
    wget -c --passive-ftp ftp://ftp.gnu.org/pub/gnu/binutils/$BINUTILS.tar.gz
    wget -c --passive-ftp ftp://ftp.gnu.org/pub/gnu/gcc/$GCC/$GCC.tar.bz2
    wget -c --passive-ftp ftp://sources.redhat.com/pub/newlib/$NEWLIB.tar.gz
  fi

  ## Create the build directory.
  mkdir -p $TMPDIR; cd $TMPDIR

  ## Unpack and patch source files.
  if [ $BUILD_BINUTILS ] ; then
    rm -Rf $BINUTILS; tar xfvz $SRCDIR/$BINUTILS.tar.gz
    cd $BINUTILS; cat $SRCDIR/$BINUTILS.patch | patch -p1; cd ..
  fi

  if [ $BUILD_GCC ] ; then
    rm -Rf $GCC; tar xfvj $SRCDIR/$GCC.tar.bz2
    cd $GCC; cat $SRCDIR/$GCC.patch | patch -p1; cd ..
  fi

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
  
    ## Build for each target.
    for TARGET in "psp"; do
  
     ## Create the build directory.
     mkdir build-$TARGET
  
     ## Enter the build directory.
     cd build-$TARGET
  
     ## Configure the source.
     ../configure --prefix=$PSPDEV --target=$TARGET || { echo "ERROR CONFIGURING BINUTILS ($BINUTILS $TARGET)"; exit; }
  
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

  fi
  
 ###########################
 ## BUILD AND INSTALL GCC ##
 ###########################

  if [ $BUILD_GCC ] ; then
  
    ## Enter the source directory.
    cd $GCC
  
    ## Build for each target.
    for TARGET in "psp"; do
  
     ## Create the build directory.
     mkdir build-$TARGET
  
     ## Enter the build directory.
     cd build-$TARGET
  
     ## Configure the source.
     ../configure --prefix=$PSPDEV --target=$TARGET --enable-languages="c" --with-newlib --without-headers || { echo "ERROR CONFIGURING GCC ($GCC $TARGET)"; exit; }
  
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

 fi
  
 ##############################
 ## BUILD AND INSTALL NEWLIB ##
 ##############################

  if [ $BUILD_NEWLIB ] ; then
  
    ## Enter the source directory.
    cd $NEWLIB
  
    ## Build for each target.
    for TARGET in "psp"; do
  
     ## Create the build directory.
     mkdir build-$TARGET
  
     ## Enter the build directory.
     cd build-$TARGET
  
     ## Configure the source.
     ../configure --prefix=$PSPDEV --target=$TARGET || { echo "ERROR CONFIGURING NEWLIB ($NEWLIB $TARGET)"; exit; }
  
     ## Build the source.
     $MAKE clean; $MAKE || { echo "ERROR BUILDING NEWLIB ($NEWLIB $TARGET)"; exit; }
  
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

 fi
  
 #################################
 ## BUILD AND INSTALL GCC (C++) ##
 #################################

  if [ $BUILD_GCC ] ; then
  
    ## Enter the source directory.
    cd $GCC
  
    ## Build for each target.
    for TARGET in "psp"; do
  
     ## Create the build directory.
     mkdir build-$TARGET-c++
  
     ## Enter the build directory.
     cd build-$TARGET-c++
  
     ## Configure the source.
     ../configure --prefix=$PSPDEV --target=$TARGET --enable-languages="c,c++" --with-newlib --enable-cxx-flags="-G0" || { echo "ERROR CONFIGURING GCC ($GCC $TARGET C++)"; exit; }
  
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

 fi
  
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
