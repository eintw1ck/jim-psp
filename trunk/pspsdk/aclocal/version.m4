AC_DEFUN([PSPSDK_VERSIONING],
m4_define([PSPSDK_VERSION],[1.0]))

AC_DEFUN(AC_PSPSDK_VERSION,
[
AC_REQUIRE([PSPSDK_VERSIONING])
AC_BEFORE([$0], [AM_INIT_AUTOMAKE])

AC_MSG_CHECKING([for pspsdk version])
AS_IF([test -r "${srcdir}/aclocal/version.m4"],
[],
[AC_MSG_ERROR([Unable to find aclocal/version.m4])])
AC_MSG_RESULT([PSPSDK_VERSION])
])
