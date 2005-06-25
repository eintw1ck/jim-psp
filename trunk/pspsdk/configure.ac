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
AM_PROG_AS
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h malloc.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_CHECK_FUNCS([getcwd strchr])

# Override the default prefix to point to where the pspdev tools should be installed.
# The binaries will end up in $prefix/bin, but pspsdk itself will end up in $prefix/pspsdk.
# TODO: We should see if the user will ever want to override this.
prefix="$pspdev"

# Create the pspsdk installation paths.
pspsdk="$prefix/pspsdk"
pspsdk_includedir="$pspsdk/include"
pspsdk_libdir="$pspsdk/lib"
PSPSDK="$pspsdk"
PSPSDK_INCLUDEDIR="$pspsdk_includedir"
PSPSDK_LIBDIR="$pspsdk_libdir"
AC_SUBST(PSPSDK)
AC_SUBST(PSPSDK_INCLUDEDIR)
AC_SUBST(PSPSDK_LIBDIR)

# CFLAGS used to build pspsdk libraries.
PSPSDK_CFLAGS="$CFLAGS -G0 -Wall"
AC_SUBST(PSPSDK_CFLAGS)

# Turn on all warnings (for host programs).
if test x$ac_compiler_gnu = xyes; then
   CFLAGS="$CFLAGS -Wall"
fi

AC_CONFIG_FILES([Makefile
                 sdk/Makefile
                 sdk/audio/Makefile
                 sdk/base/Makefile
                 sdk/debug/Makefile
                 sdk/kernel/Makefile
                 sdk/libc/Makefile
                 sdk/startup/Makefile
                 tools/Makefile])
AC_OUTPUT
