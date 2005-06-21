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
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h malloc.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MEMCMP

AC_CONFIG_FILES([Makefile
                 tools/Makefile])
AC_OUTPUT
