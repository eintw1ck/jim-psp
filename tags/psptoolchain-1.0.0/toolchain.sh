#!/bin/sh
# toolchain.sh - Dan Peori <peori@oopo.net>
# Copy all you want. Please give me some credit.

 ########################
 ## MAIN CONFIGURATION ##
 ########################

  ## Main pspdev settings.
  PSPDEV="/usr/local/pspdev"

  ## Set the directories.
  SRCDIR="`pwd`"
  BUILDDIR="/tmp/pspdev"

  ## Source code versions.
  BINUTILS="binutils-2.16.1"
  GCC="gcc-4.0.2"
  NEWLIB="newlib-1.13.0"
  GDB="gdb-6.4"
  INSIGHT="insight-6.4"

  ## PSPSDK subversion repository, or path to local working copy
  PSPSDK_SVN="svn://svn.pspdev.org/psp/trunk/pspsdk"

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
   # By default dont add MS Visual Studio support
   MSVS_SUPPORT=0
   # By default dont build GDB
   BUILD_GDB=0
   BUILD_INSIGHT=0

  ## Else...
  else

   ## Parse the arguments.
   while test $# -ge 1 ; do
    case "$1" in
     -d | -download | --download)
      DO_DOWNLOAD=1
      shift;;
     -b | -binutils | --binutils)
      BUILD_BINUTILS=1
      shift;;
     -g | -gcc | --gcc)
      BUILD_GCC=1
      shift;;
     -n | -newlib | --newlib)
      BUILD_NEWLIB=1
      shift;;
     -p | -pspsdk | --pspsdk)
      BUILD_PSPSDK=1
      shift;;
     -m | -msvs | --msvs)
      MSVS_SUPPORT=1
      shift;;
     -e | -gdb | --gdb)
      BUILD_GDB=1
      shift;;
     -i | -insight | --insight)
      BUILD_INSIGHT=1
      shift;;
     -a | -all | --all)
      DO_DOWNLOAD=1
      BUILD_BINUTILS=1
      BUILD_GCC=1
      BUILD_NEWLIB=1
      BUILD_PSPSDK=1
      # By default dont build GDB
      BUILD_GDB=0
	  BUILD_INSIGHT=0
      shift;;
     -P | -pspsdk-src | --pspsdk-src)
      PSPSDK_SVN="$2"
      shift 2;;
     -prefix | --prefix)
      PSPDEV="$2"
      shift 2;;
    esac
   done

  fi

  ## Newlib depends on PSPSDK headers, so if it's being
  ## built then make sure that PSPSDK is being built.
  if test "$BUILD_NEWLIB" = "1" ; then
   BUILD_PSPSDK=1
  fi

  ## Set the path based on the prefix.
  PATH="$PATH:$PSPDEV/bin"

 ###########################
 ## SOFTWARE DEPENDENCIES ##
 ###########################

  ## Check for make.
  if test "`gmake -v 2> /dev/null`" ; then
   MAKE="gmake"
  else
   if test "`make -v 2> /dev/null`" ; then
    MAKE="make"
   else
    echo "ERROR: Please make sure you have GNU 'make' installed."
    exit
   fi
  fi

  ## Check for patch.
  if test "`gpatch -v 2> /dev/null`" ; then
   PATCH="gpatch -p1"
  else
   if test "`patch -v 2> /dev/null`" ; then
    PATCH="patch -p1"
   else
    echo "ERROR: Please make sure you have 'patch' installed."
    exit
   fi
  fi

  ## Check for wget.
  if test "`wget -V 2> /dev/null`" ; then
   WGET="wget -c --passive-ftp"
  else
   echo "ERROR: Please make sure you have 'wget' installed."
   exit
  fi

  ## Check for subversion.
  if test "`svn help 2> /dev/null`" ; then
   SVN="svn"
  else
   echo "ERROR: Please make sure you have 'subversion (svn)' installed."
   exit
  fi

  if test "$BUILD_GDB" = "1" ; then
     if test "`flex --version 2> /dev/null`" ; then
	    FLEX="flex"
     else
        echo "ERROR: To build GDB you need to have 'flex' installed."
		exit
	 fi
  fi

  if test "$BUILD_INSIGHT" = "1" ; then
     if test "`flex --version 2> /dev/null`" ; then
	    FLEX="flex"
     else
        echo "ERROR: To build Insight you need to have 'flex' installed."
		exit
	 fi
     if ! test "`yacc --version 2> /dev/null`" ; then
     echo "ERROR: To build Insight you need to have a yacc parser installed."
     exit
	 fi
  fi

  ## Check for autoconf and automake
  if test "$BUILD_PSPSDK" = "1" ; then
      if ! test "`automake --version 2> /dev/null`" ; then
	  echo "ERROR: Please make sure you have 'automake' installed."
	  exit
      fi
      if ! test "`autoconf --version 2> /dev/null`" ; then
	  echo "ERROR: Please make sure you have 'autoconf' installed."
	  exit
      fi
  fi

 ################################
 ## DOWNLOAD, UNPACK AND PATCH ##
 ################################

  ## If we've been told to download...
  if test "$DO_DOWNLOAD" = "1" ; then

   ## Download the binutils source.
   if test "$BUILD_BINUTILS" = "1" ; then
    if test ! -f "$BINUTILS.tar.gz" ; then
     $WGET ftp://ftp.gnu.org/pub/gnu/binutils/$BINUTILS.tar.gz || { echo "ERROR DOWNLOADING BINUTILS"; exit; }
    fi
    echo -n "Downloading the latest binutils patch... ";
    $SVN cat svn://svn.pspdev.org/psp/trunk/psptoolchain/$BINUTILS.patch > $BINUTILS.patch
    echo "Done!";
   fi

   ## Download the gcc source.
   if test "$BUILD_GCC" = "1" ; then
    if test ! -f "$GCC.tar.bz2" ; then
     $WGET ftp://ftp.gnu.org/pub/gnu/gcc/$GCC/$GCC.tar.bz2 || { echo "ERROR DOWNLOADING GCC"; exit; }
    fi
    echo -n "Downloading the latest gcc patch... ";
    $SVN cat svn://svn.pspdev.org/psp/trunk/psptoolchain/$GCC.patch > $GCC.patch
    echo "Done!";
    ## Download the gcc Visual Studio patch
    if test "$MSVS_SUPPORT" = "1" ; then
     echo -n "Downloading the Visual Studio gcc patch... ";
     $SVN cat svn://svn.pspdev.org/psp/trunk/psptoolchain/$GCC-vs.patch > $GCC-vs.patch
     echo "Done!";
    fi
   fi

   ## Download the newlib source.
   if test "$BUILD_NEWLIB" = "1" ; then
    if test ! -f "$NEWLIB.tar.gz" ; then
     $WGET ftp://sources.redhat.com/pub/newlib/$NEWLIB.tar.gz || { echo "ERROR DOWNLOADING NEWLIB"; exit; }
    fi
    echo -n "Downloading the latest newlib patch... ";
    $SVN cat svn://svn.pspdev.org/psp/trunk/psptoolchain/$NEWLIB.patch > $NEWLIB.patch
    echo "Done!";
   fi

   if test "$BUILD_GDB" = "1" ; then
     if test ! -f "$GDB.tar.gz" ; then
      $WGET ftp://ftp.gnu.org/pub/gnu/gdb/$GDB.tar.gz || { echo "ERROR DOWNLOADING GDB"; exit; }
     fi
     echo -n "Downloading the latest gdb patch... ";
     $SVN cat svn://svn.pspdev.org/psp/trunk/psptoolchain/$GDB.patch > $GDB.patch
     echo "Done!";
   fi

   if test "$BUILD_INSIGHT" = "1" ; then
     if test ! -f "$INSIGHT.tar.bz2" ; then
      $WGET ftp://sourceware.org/pub/insight/releases/$INSIGHT.tar.bz2 || { echo "ERROR DOWNLOADING INSIGHT"; exit; }
     fi
     echo -n "Downloading the latest insight patch... ";
     $SVN cat svn://svn.pspdev.org/psp/trunk/insight-psp/$INSIGHT.patch > $INSIGHT.patch
     echo "Done!";
   fi

  fi

  ## Create and enter the temp directory.
  mkdir -p "$BUILDDIR"; cd "$BUILDDIR"

  ## Unpack and patch the binutils source.
  if test "$BUILD_BINUTILS" = "1" ; then
   rm -Rf $BINUTILS; gzip -cd "$SRCDIR/$BINUTILS.tar.gz" | tar xvf -
   cd $BINUTILS; cat "$SRCDIR/$BINUTILS.patch" | $PATCH || { echo "ERROR PATCHING BINUTILS"; exit; }
   cd ..
  fi

  ## Unpack and patch the gcc source.
  if test "$BUILD_GCC" = "1" ; then
   rm -Rf $GCC; bzip2 -cd "$SRCDIR/$GCC.tar.bz2" | tar xvf -
   cd $GCC; cat "$SRCDIR/$GCC.patch" | $PATCH || { echo "ERROR PATCHING GCC"; exit; }
   
   ## Unpack and patch the gcc source for Visual Studio support.
   if test "$MSVS_SUPPORT" = "1" ; then
    cat "$SRCDIR/$GCC-vs.patch" | $PATCH || { echo "ERROR PATCHING GCC FOR VISUAL STUDIO"; exit; }
   fi
   cd ..
  fi

  ## Unpack and patch the newlib source.
  if test "$BUILD_NEWLIB" = "1" ; then
   rm -Rf $NEWLIB; gzip -cd "$SRCDIR/$NEWLIB.tar.gz" | tar xvf -
   cd $NEWLIB; cat "$SRCDIR/$NEWLIB.patch" | $PATCH || { echo "ERROR PATCHING NEWLIB"; exit; }
   cd ..
  fi

  ## Unpack and patch the gdb source
  if test "$BUILD_GDB" = "1" ; then
   rm -Rf $GDB; gzip -cd "$SRCDIR/$GDB.tar.gz" | tar xvf -
   cd $GDB; cat "$SRCDIR/$GDB.patch" | $PATCH || { echo "ERROR PATCHING GDB"; exit; }
   cd ..
  fi

  ## Unpack and patch the insight source
  if test "$BUILD_INSIGHT" = "1" ; then
   rm -Rf $INSIGHT; bunzip2 -cd "$SRCDIR/$INSIGHT.tar.bz2" | tar xvf -
   cd $INSIGHT; cat "$SRCDIR/$INSIGHT.patch" | $PATCH || { echo "ERROR PATCHING INSIGHT"; exit; }
   cd ..
  fi

  ## Grab the latest PSPSDK from Subversion.
  if test "$BUILD_PSPSDK" = "1" ; then
   rm -Rf pspsdk
   $SVN export "$PSPSDK_SVN" pspsdk
  fi

 ################################
 ## BUILD AND INSTALL BINUTILS ##
 ################################

  ## If we've been told to build binutils...
  if test "$BUILD_BINUTILS" = "1" ; then

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
  if test "$BUILD_GCC" = "1" ; then

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

  if test "$BUILD_PSPSDK" = "1" ; then

   ## Enter the source directory.
   cd pspsdk

   ## Bootstrap the source.
   ./bootstrap || { echo "ERROR RUNNING PSPSDK BOOSTRAP"; exit; }

   ## Configure the source.
   ./configure --with-pspdev=$PSPDEV || { echo "ERROR RUNNING PSPSDK CONFIGURE"; exit; }

   ## Install the headers that Newlib requires.
   $MAKE clean; $MAKE install-data || { echo "ERROR BUILDING PSPSDK"; exit; }

   ## Exit the source directory.
   cd ..

  fi

 ##############################
 ## BUILD AND INSTALL NEWLIB ##
 ##############################

  ## If we've been told to build newlib...
  if test "$BUILD_NEWLIB" = "1" ; then

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
  if test "$BUILD_GCC" = "1" ; then

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

 #################################
 ## BUILD AND INSTALL GDB       ##
 #################################

  if test "$BUILD_GDB" = "1" ; then

   ## Enter the source directory.
   cd $GDB

   ## Create and enter the build directory.
   mkdir build-gdb; cd build-gdb

   ## Configure the source.
   ../configure --prefix=$PSPDEV --target=psp --disable-nls || { echo "ERROR CONFIGURING GDB"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING GDB"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING GDB"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build and source directories.
   cd ..; cd ..

  fi

  if test "$BUILD_INSIGHT" = "1" ; then

   ## Enter the source directory.
   cd $INSIGHT

   ## Create and enter the build directory.
   mkdir build-insight; cd build-insight

   ## Configure the source.
   ../configure --prefix=$PSPDEV --target=psp --disable-nls || { echo "ERROR CONFIGURING INSIGHT"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING INSIGHT"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING INSIGHT"; exit; }

   ## Clean up the result.
   $MAKE clean

   ## Exit the build and source directories.
   cd ..; cd ..

  fi

 ##############################
 ## BUILD AND INSTALL PSPSDK ##
 ##############################

  ## If we've been told to build pspsdk...
  if test "$BUILD_PSPSDK" = "1" ; then

   ## Enter the source directory.
   cd pspsdk

   ## Reconfigure the source (to pick up the C++ compiler).
   ./configure --with-pspdev=$PSPDEV || { echo "ERROR RUNNING PSPSDK CONFIGURE"; exit; }

   ## Build the source.
   $MAKE clean; $MAKE || { echo "ERROR BUILDING PSPSDK"; exit; }

   ## Install the result.
   $MAKE install || { echo "ERROR INSTALLING PSPSDK"; exit; }

   ## Install the pspsdk documentation.

   if $MAKE doxygen-doc ; then
       cp -rf doc $PSPDEV/psp/sdk/
   else
       echo "NON-FATAL ERROR INSTALLING PSPSDK DOCUMENTATION, CONTINUING...";
   fi

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

  ## Clean up the gdb source
  rm -Rf $GDB

  ## Clean up the pspsdk source.
  rm -Rf pspsdk
