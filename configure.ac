AC_INIT([cpy], [1.0])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([cpy.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_MODE_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getpagesize mkdir rmdir strerror strrchr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
