dnl Autoconf macros that Google doesn't seem to ship with.

AC_DEFUN([AX_C___ATTRIBUTE__], [
  AC_MSG_CHECKING(for __attribute__)
  AC_CACHE_VAL(ac_cv___attribute__, [
    AC_TRY_COMPILE(
      [#include <stdlib.h>],
      [static void foo(void) __attribute__ ((unused));
      static void
      foo(void) {
          exit(1);
      }],
      ac_cv___attribute__=yes,
      ac_cv___attribute__=no
    )])
  if test "$ac_cv___attribute__" = "yes"; then
    AC_DEFINE(HAVE___ATTRIBUTE__, 1, [define if your compiler has __attribute__])
  fi
  AC_MSG_RESULT($ac_cv___attribute__)
])

# Check compiler characteristics (e.g. type sizes, PRIxx macros, ...)

# If types $1 and $2 are compatible, perform action $3
AC_DEFUN([AC_TYPES_COMPATIBLE],
  [AC_TRY_COMPILE([#include <stddef.h>], [$1 v1 = 0; $2 v2 = 0; return (&v1 - &v2)], $3)])

define(AC_PRIUS_COMMENT, [printf format code for printing a size_t])

AC_DEFUN([AC_COMPILER_CHARACTERISTICS],
  [AC_CACHE_CHECK(AC_PRIUS_COMMENT, ac_cv_formatting_prius,
    [AC_TYPES_COMPATIBLE(unsigned int, size_t, ac_cv_formatting_prius=u)
     AC_TYPES_COMPATIBLE(unsigned long, size_t, ac_cv_formatting_prius=lu)
     AC_TYPES_COMPATIBLE(unsigned long long, size_t, ac_cv_formatting_prius=llu)])
   if test -z "$ac_cv_formatting_prius"; then 
      ac_cv_formatting_prius=zu;
   fi
   AC_DEFINE_UNQUOTED(PRIuS, "$ac_cv_formatting_prius", AC_PRIUS_COMMENT)
])
	

# This was retrieved from
#    http://www.gnu.org/software/ac-archive/htmldoc/acx_pthread.html

AC_DEFUN([ACX_PTHREAD], [
AC_REQUIRE([AC_CANONICAL_HOST])
AC_LANG_SAVE
AC_LANG_C
acx_pthread_ok=no

# We used to check for pthread.h first, but this fails if pthread.h
# requires special compiler flags (e.g. on True64 or Sequent).
# It gets checked for in the link test anyway.

# First of all, check if the user has set any of the PTHREAD_LIBS,
# etcetera environment variables, and if threads linking works using
# them:
if test x"$PTHREAD_LIBS$PTHREAD_CFLAGS" != x; then
        save_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
        save_LIBS="$LIBS"
        LIBS="$PTHREAD_LIBS $LIBS"
        AC_MSG_CHECKING([for pthread_join in LIBS=$PTHREAD_LIBS with CFLAGS=$PTHREAD_CFLAGS])
        AC_TRY_LINK_FUNC(pthread_join, acx_pthread_ok=yes)
        AC_MSG_RESULT($acx_pthread_ok)
        if test x"$acx_pthread_ok" = xno; then
                PTHREAD_LIBS=""
                PTHREAD_CFLAGS=""
        fi
        LIBS="$save_LIBS"
        CFLAGS="$save_CFLAGS"
fi

# We must check for the threads library under a number of different
# names; the ordering is very important because some systems
# (e.g. DEC) have both -lpthread and -lpthreads, where one of the
# libraries is broken (non-POSIX).

# Create a list of thread flags to try.  Items starting with a "-" are
# C compiler flags, and other items are library names, except for "none"
# which indicates that we try without any flags at all, and "pthread-config"
# which is a program returning the flags for the Pth emulation library.

acx_pthread_flags="pthreads none -Kthread -kthread lthread -pthread -pthreads -mthreads pthread --thread-safe -mt pthread-config"

# The ordering *is* (sometimes) important.  Some notes on the
# individual items follow:

# pthreads: AIX (must check this before -lpthread)
# none: in case threads are in libc; should be tried before -Kthread and
#       other compiler flags to prevent continual compiler warnings
# -Kthread: Sequent (threads in libc, but -Kthread needed for pthread.h)
# -kthread: FreeBSD kernel threads (preferred to -pthread since SMP-able)
# lthread: LinuxThreads port on FreeBSD (also preferred to -pthread)
# -pthread: Linux/gcc (kernel threads), BSD/gcc (userland threads)
# -pthreads: Solaris/gcc
# -mthreads: Mingw32/gcc, Lynx/gcc
# -mt: Sun Workshop C (may only link SunOS threads [-lthread], but it
#      doesn't hurt to check since this sometimes defines pthreads too;
#      also defines -D_REENTRANT)
# pthread: Linux, etcetera
# --thread-safe: KAI C++
# pthread-config: use pthread-config program (for GNU Pth library)

case "${host_cpu}-${host_os}" in
        *solaris*)

        # On Solaris (at least, for some versions), libc contains stubbed
        # (non-functional) versions of the pthreads routines, so link-based
        # tests will erroneously succeed.  (We need to link with -pthread or
        # -lpthread.)  (The stubs are missing pthread_cleanup_push, or rather
        # a function called by this macro, so we could check for that, but
        # who knows whether they'll stub that too in a future libc.)  So,
        # we'll just look for -pthreads and -lpthread first:

        acx_pthread_flags="-pthread -pthreads pthread -mt $acx_pthread_flags"
        ;;
esac

if test x"$acx_pthread_ok" = xno; then
for flag in $acx_pthread_flags; do

        case $flag in
                none)
                AC_MSG_CHECKING([whether pthreads work without any flags])
                ;;

                -*)
                AC_MSG_CHECKING([whether pthreads work with $flag])
                PTHREAD_CFLAGS="$flag"
                ;;

                pthread-config)
                AC_CHECK_PROG(acx_pthread_config, pthread-config, yes, no)
                if test x"$acx_pthread_config" = xno; then continue; fi
                PTHREAD_CFLAGS="`pthread-config --cflags`"
                PTHREAD_LIBS="`pthread-config --ldflags` `pthread-config --libs`"
                ;;

                *)
                AC_MSG_CHECKING([for the pthreads library -l$flag])
                PTHREAD_LIBS="-l$flag"
                ;;
        esac

        save_LIBS="$LIBS"
        save_CFLAGS="$CFLAGS"
        LIBS="$PTHREAD_LIBS $LIBS"
        CFLAGS="$CFLAGS $PTHREAD_CFLAGS"

        # Check for various functions.  We must include pthread.h,
        # since some functions may be macros.  (On the Sequent, we
        # need a special flag -Kthread to make this header compile.)
        # We check for pthread_join because it is in -lpthread on IRIX
        # while pthread_create is in libc.  We check for pthread_attr_init
        # due to DEC craziness with -lpthreads.  We check for
        # pthread_cleanup_push because it is one of the few pthread
        # functions on Solaris that doesn't have a non-functional libc stub.
        # We try pthread_create on general principles.
        AC_TRY_LINK([#include <pthread.h>],
                    [pthread_t th; pthread_join(th, 0);
                     pthread_attr_init(0); pthread_cleanup_push(0, 0);
                     pthread_create(0,0,0,0); pthread_cleanup_pop(0); ],
                    [acx_pthread_ok=yes])

        LIBS="$save_LIBS"
        CFLAGS="$save_CFLAGS"

        AC_MSG_RESULT($acx_pthread_ok)
        if test "x$acx_pthread_ok" = xyes; then
                break;
        fi

        PTHREAD_LIBS=""
        PTHREAD_CFLAGS=""
done
fi

# Various other checks:
if test "x$acx_pthread_ok" = xyes; then
        save_LIBS="$LIBS"
        LIBS="$PTHREAD_LIBS $LIBS"
        save_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS $PTHREAD_CFLAGS"

        # Detect AIX lossage: JOINABLE attribute is called UNDETACHED.
        AC_MSG_CHECKING([for joinable pthread attribute])
        attr_name=unknown
        for attr in PTHREAD_CREATE_JOINABLE PTHREAD_CREATE_UNDETACHED; do
            AC_TRY_LINK([#include <pthread.h>], [int attr=$attr;],
                        [attr_name=$attr; break])
        done
        AC_MSG_RESULT($attr_name)
        if test "$attr_name" != PTHREAD_CREATE_JOINABLE; then
            AC_DEFINE_UNQUOTED(PTHREAD_CREATE_JOINABLE, $attr_name,
                               [Define to necessary symbol if this constant
                                uses a non-standard name on your system.])
        fi

        AC_MSG_CHECKING([if more special flags are required for pthreads])
        flag=no
        case "${host_cpu}-${host_os}" in
            *-aix* | *-freebsd* | *-darwin*) flag="-D_THREAD_SAFE";;
            *solaris* | *-osf* | *-hpux*) flag="-D_REENTRANT";;
        esac
        AC_MSG_RESULT(${flag})
        if test "x$flag" != xno; then
            PTHREAD_CFLAGS="$flag $PTHREAD_CFLAGS"
        fi

        LIBS="$save_LIBS"
        CFLAGS="$save_CFLAGS"

        # More AIX lossage: must compile with cc_r
        AC_CHECK_PROG(PTHREAD_CC, cc_r, cc_r, ${CC})
else
        PTHREAD_CC="$CC"
fi

AC_SUBST(PTHREAD_LIBS)
AC_SUBST(PTHREAD_CFLAGS)
AC_SUBST(PTHREAD_CC)

# Finally, execute ACTION-IF-FOUND/ACTION-IF-NOT-FOUND:
if test x"$acx_pthread_ok" = xyes; then
        ifelse([$1],,AC_DEFINE(HAVE_PTHREAD,1,[Define if you have POSIX threads libraries and header files.]),[$1])
        :
else
        acx_pthread_ok=no
        $2
fi
AC_LANG_RESTORE
])dnl ACX_PTHREAD

# We check what namespace stl code like vector expects to be executed in

AC_DEFUN([AC_CXX_STL_NAMESPACE],
  [AC_CACHE_CHECK(
      what namespace STL code is in,
      ac_cv_cxx_stl_namespace,
      [AC_REQUIRE([AC_CXX_NAMESPACES])
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_COMPILE([#include <vector>],
                     [vector<int> t; return 0;],
                     ac_cv_cxx_stl_namespace=none)
      AC_TRY_COMPILE([#include <vector>],
                     [std::vector<int> t; return 0;],
                     ac_cv_cxx_stl_namespace=std)
      AC_LANG_RESTORE])
   if test "$ac_cv_cxx_stl_namespace" = none; then
      AC_DEFINE(STL_NAMESPACE,,
                [the namespace where STL code like vector<> is defined])
   fi
   if test "$ac_cv_cxx_stl_namespace" = std; then
      AC_DEFINE(STL_NAMESPACE,std,
                [the namespace where STL code like vector<> is defined])
   fi
])

dnl @synopsis AC_CXX_NAMESPACES
dnl
dnl If the compiler can prevent names clashes using namespaces, define
dnl HAVE_NAMESPACES.
dnl
dnl @category Cxx
dnl @author Todd Veldhuizen
dnl @author Luc Maisonobe <luc@spaceroots.org>
dnl @version 2004-02-04
dnl @license AllPermissive

AC_DEFUN([AC_CXX_NAMESPACES],
[AC_CACHE_CHECK(whether the compiler implements namespaces,
ac_cv_cxx_namespaces,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([namespace Outer { namespace Inner { int i = 0; }}],
                [using namespace Outer::Inner; return i;],
 ac_cv_cxx_namespaces=yes, ac_cv_cxx_namespaces=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_namespaces" = yes; then
  AC_DEFINE(HAVE_NAMESPACES,,[define if the compiler implements namespaces])
fi
])

# Figures out where hash_set is defined, and then writes out the
# location to the file specified in $1.  The output file also
# #defines the namespace that hash_set is in HASH_NAMESPACE.
#
# You can use this *instead of* stl_hash.ac.  stl_hash.ac will
# also define HASH_NAMESPACE, and vars indicating where hash_set
# lives, but won't actually make an include file for you.  This
# routine is a higher-level wrapper around hash_set.

AC_DEFUN([AC_CXX_MAKE_HASH_SET_H],
  [AC_REQUIRE([AC_CXX_STL_HASH])
   AC_MSG_CHECKING(writing an include-helper for hash_set)

   AS_MKDIR_P([`AS_DIRNAME([$1])`])
   cat >$1 <<EOF
#include $ac_cv_cxx_hash_set
#ifndef HASH_NAMESPACE
#define HASH_NAMESPACE $ac_cv_cxx_hash_namespace
#endif
EOF

   AC_MSG_RESULT([$1])
])

# We check two things: where the include file is for hash_map, and
# what namespace hash_map lives in within that include file.  We
# include AC_TRY_COMPILE for all the combinations we've seen in the
# wild.  We define one of HAVE_HASH_MAP or HAVE_EXT_HASH_MAP depending
# on location, and HASH_NAMESPACE to be the namespace hash_map is
# defined in.  If we can't find a hash_map that works, we die!

AC_DEFUN([AC_CXX_STL_HASH],
  [AC_CACHE_CHECK(
      location of STL hash_map,
      ac_cv_cxx_stl_hash,
      [AC_REQUIRE([AC_CXX_NAMESPACES])
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_COMPILE([#include <hash_map>],
                     [hash_map<int, int> t; return 0;],
                     ac_cv_cxx_stl_hash=hash_map)
      AC_TRY_COMPILE([#include <ext/hash_map>],
                     [__gnu_cxx::hash_map<int, int> t; return 0;],
                     ac_cv_cxx_stl_hash=ext_hash_map)
      AC_TRY_COMPILE([#include <hash_map>],
                     [std::hash_map<int, int> t; return 0;],
                     ac_cv_cxx_stl_hash=std_hash_map)
      AC_TRY_COMPILE([#include <hash_map>],
                     [stdext::hash_map<int, int> t; return 0;],
                     ac_cv_cxx_stl_hash=stdext_hash_map)

      AC_LANG_RESTORE])
   if test "$ac_cv_cxx_stl_hash" = hash_map; then
      AC_DEFINE(HAVE_HASH_MAP, 1, [define if the compiler has hash_map])
      AC_DEFINE(HAVE_HASH_SET, 1, [define if the compiler has hash_set])
      ac_cv_cxx_hash_map="<hash_map>"
      ac_cv_cxx_hash_set="<hash_set>"
      ac_cv_cxx_hash_namespace=""
   fi
   if test "$ac_cv_cxx_stl_hash" = ext_hash_map; then
      AC_DEFINE(HAVE_EXT_HASH_MAP, 1, [define if the compiler has hash_map])
      AC_DEFINE(HAVE_EXT_HASH_SET, 1, [define if the compiler has hash_set])
      ac_cv_cxx_hash_map="<ext/hash_map>"
      ac_cv_cxx_hash_set="<ext/hash_set>"
      ac_cv_cxx_hash_namespace="__gnu_cxx"
   fi
   if test "$ac_cv_cxx_stl_hash" = std_hash_map; then
      AC_DEFINE(HAVE_HASH_MAP, 1, [define if the compiler has hash_map])
      AC_DEFINE(HAVE_HASH_SET, 1, [define if the compiler has hash_set])
      ac_cv_cxx_hash_map="<hash_map>"
      ac_cv_cxx_hash_set="<hash_set>"
      ac_cv_cxx_hash_namespace="std"
   fi
   if test "$ac_cv_cxx_stl_hash" = stdext_hash_map; then
      AC_DEFINE(HAVE_HASH_MAP, 1, [define if the compiler has hash_map])
      AC_DEFINE(HAVE_HASH_SET, 1, [define if the compiler has hash_set])
      ac_cv_cxx_hash_map="<hash_map>"
      ac_cv_cxx_hash_set="<hash_set>"
      ac_cv_cxx_hash_namespace="stdext"
   fi
   AC_DEFINE_UNQUOTED(HASH_NAMESPACE,$ac_cv_cxx_hash_namespace,
                      [the namespace of hash_map])

   if test x"$ac_cv_cxx_stl_hash" = x; then
      AC_MSG_ERROR(couldn't find an STL hash_map)
   fi
])

AC_DEFUN([AC_PROGRAM_INVOCATION_NAME],
  [AC_CACHE_CHECK(
    for program_invocation_name,
    ac_cv_have_program_invocation_name,
    AC_TRY_LINK([extern char* program_invocation_name;],
	        [char c = *program_invocation_name; return c; ],
	        [ac_cv_have_program_invocation_name=yes],
		[ac_cv_have_program_invocation_name=no])
   )
   if test "$ac_cv_have_program_invocation_name" = "yes"; then
     AC_DEFINE(HAVE_PROGRAM_INVOCATION_NAME, 1,
               [define if libc has program_invocation_name])
   fi
   ])
   

AC_DEFUN([AC_INSTALL_PREFIX],
  [ac_cv_install_prefix="$prefix";
   if test x"$ac_cv_install_prefix" == x"NONE" ; then
     ac_cv_install_prefix="$ac_default_prefix";
   fi
   AC_DEFINE_UNQUOTED(INSTALL_PREFIX, "$ac_cv_install_prefix",
     [prefix where we look for installed files])
   ])

