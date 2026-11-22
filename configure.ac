AC_PREREQ([2.71])
AC_INIT([bonnie], [0.1.0])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_AUX_DIR([build-aux])

# foreign: don't require GNU files (NEWS, AUTHORS, ...).
# subdir-objects: keep object files next to their sources in src/.
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])

# Find a working C++ compiler and tell configure we are compiling C++.
AC_PROG_CXX
AC_LANG([C++])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
