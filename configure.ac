#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([2048], [0.1], [aiden.woodruff@gmail.com])
AC_CONFIG_SRCDIR([src/grid.h])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AX_CHECK_COMPILE_FLAG([-std=c++17], [AC_DEFINE([HAVE_CXX17], [1], [If C++17 support is enabled])], [AC_DEFINE([HAVE_CXX17], [0], [If C++17 support is enabled])], [-std=c++17])

# Checks for libraries.
AC_CHECK_LIB([ncurses], [newwin])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([alloc_pair reset_color_pairs use_default_colors])

AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AM_INIT_AUTOMAKE
AC_OUTPUT
