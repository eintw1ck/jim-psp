dnl
dnl AC_PSPDEV_PATH()
dnl
dnl Check for a valid pspdev installation.

AC_DEFUN(AC_PSPDEV_PATH,
[
  AC_ARG_WITH(pspdev,
              [  --with-pspdev=DIR       Path where the pspdev toolchain is installed (default is $PSPDEV)],
              pspdev="$withval", pspdev="$PSPDEV")

  AC_MSG_CHECKING(for pspdev)
  if test x$pspdev = x ; then
     # If there's no $PSPDEV environment variable, find out where psp-gcc lives (it should be on the $PATH).
     psp_gcc_path=`which psp-gcc`
     if test x$psp_gcc_path = x ; then
        AC_MSG_ERROR(can't find the pspdev toolchain.  Use --with-pspdev or set PSPDEV)
     fi
     # Strip both the /psp-gcc and /bin portions from the path.
     pspdev=`echo $psp_gcc_path | sed 's/\/psp-gcc//' | sed 's/\/bin//'`
  fi
  AC_MSG_RESULT($pspdev)

  PSPDEV="$pspdev"
  AC_SUBST(PSPDEV)
])
