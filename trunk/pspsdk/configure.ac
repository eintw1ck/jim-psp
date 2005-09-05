#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([pspsdk], [PSPSDK_VERSION], [])
AC_CONFIG_SRCDIR([tools/bin2c.c])
AC_CONFIG_HEADER([config.h])
AC_PSPSDK_VERSION
AC_PSPDEV_PATH

AM_INIT_AUTOMAKE([pspsdk], [PSPSDK_VERSION])

# Checks for programs.
AC_PSPDEV_TOOLCHAIN
AC_PROG_CC
# These will actually be overridden by the psp-specific counterparts.  They are
# here mainly to shut automake up.
AC_PROG_CXX
AM_PROG_AS
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h malloc.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_BIGENDIAN

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_CHECK_FUNCS([getcwd strchr])

# Doxygen.
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN(pspsdk, doxygen.cfg, doc)

# Override the default prefix to point to where the pspdev tools should be installed.
# The binaries will end up in $prefix/bin, but pspsdk itself will end up in $prefix/$target/sdk.
# TODO: We should see if the user will ever want to override this.
prefix="$pspdev"
psp_targetdir="psp"

# Create the pspsdk installation paths.
pspsdk_topdir="$psp_targetdir/sdk"
pspsdk="$prefix/$pspsdk_topdir"
pspsdk_includedir="$pspsdk/include"
pspsdk_libdir="$pspsdk/lib"
PSPSDK="$pspsdk"
PSPSDK_INCLUDEDIR="$pspsdk_includedir"
PSPSDK_LIBDIR="$pspsdk_libdir"
AC_DEFINE_UNQUOTED(PSPSDK_TOPDIR, ["$pspsdk_topdir"],
          [Toplevel directory where PSPSDK will be installed, relative to $prefix])
AC_SUBST(PSPSDK)
AC_SUBST(PSPSDK_INCLUDEDIR)
AC_SUBST(PSPSDK_LIBDIR)

# CFLAGS and CXXFLAGS used to build pspsdk libraries.
PSPSDK_CFLAGS="$CFLAGS -G0 -Wall"
PSPSDK_CXXFLAGS="$PSPSDK_CFLAGS -fno-exceptions -fno-rtti"
AC_SUBST(PSPSDK_CFLAGS)
AC_SUBST(PSPSDK_CXXFLAGS)

# Turn on all warnings (for host programs).
if test x$ac_compiler_gnu = xyes; then
   CFLAGS="$CFLAGS -Wall"
fi

AC_CONFIG_FILES([Makefile
                 sdk/Makefile
                 sdk/audio/Makefile
                 sdk/base/Makefile
                 sdk/ctrl/Makefile
                 sdk/debug/Makefile
                 sdk/display/Makefile
                 sdk/ge/Makefile
                 sdk/gu/Makefile
                 sdk/gum/Makefile
                 sdk/hprm/Makefile
                 sdk/kernel/Makefile
                 sdk/libc/Makefile
                 sdk/power/Makefile
                 sdk/rtc/Makefile
                 sdk/sircs/Makefile
                 sdk/sdk/Makefile
                 sdk/startup/Makefile
		 sdk/user/Makefile
                 sdk/umd/Makefile
                 sdk/usb/Makefile
                 sdk/usbstor/Makefile
                 sdk/utility/Makefile
                 sdk/wlan/Makefile
                 sdk/samples/Makefile
                 tools/Makefile])
AC_OUTPUT
