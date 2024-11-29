# Process this file with autoconf to produce a configure script.

# Copyright (C) 2015-2020 Dominik Kummer <admin@arkades.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Arkades.org; either version 1, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

## ---------------------- ##
##  Autoconf Initiazion.  ##
## ---------------------- ##

AC_PREREQ([2.72])
AC_INIT([starbase],[3.4.5],[admin@arkades.org],[arkades],[www.arkades.org])
AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT

# Set the includedir to install headers under include/mypackage/
AC_ARG_VAR([includedir], [directory for installing header files])
includedir='${prefix}/include/${PACKAGE}'

# Create the config.h file with the results of the checks
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIRS([m4])


AC_CHECK_FUNCS([dirent dup2 floor gethostbyaddr gethostbyname gethostname gettimeofday memchr memmove memset pow select socket sqrt strcasecmp strchr strcspn strdup strerror strpbrk strrchr strstr strtol tzset])

# Checks for header files.
AC_CHECK_HEADERS([dirent.h fcntl.h inttypes.h libintl.h malloc.h netdb.h netinet/in.h stdint.h strings.h sys/file.h sys/param.h sys/socket.h sys/time.h unistd.h values.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_FSEEKO
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD

# Checks for programs.
AC_PROG_CXX
AC_PROG_AR
AC_PROG_AWK
AC_PROG_YACC
AC_PROG_CC
AC_PROG_CPP
AC_PROG_LEX([noyywrap])
AC_PROG_FC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_MKDIR_P

AC_CHECK_PROG([DOXYGEN], [doxygen], [doxygen], [no])
if test "$DOXYGEN" = "no"; then
  AC_MSG_WARN([Doxygen not found - documentation will not be built])
fi

AM_CONDITIONAL([DOXYGEN], [test "$DOXYGEN" != "no"])
AC_CONFIG_FILES([doc/Doxyfile])

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lgfortran':
AC_CHECK_LIB([gfortran], [main])
# FIXME: Replace 'main' with a function in '-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace 'main' with a function in '-lmpfit':
AC_CHECK_LIB([mpfit], [main])
# FIXME: Replace 'main' with a function in '-lradar':
AC_CHECK_LIB([radar], [main])

AC_CONFIG_FILES([Makefile
                 bsd/Makefile
                 doc/Makefile
                 gnu/Makefile
                 iraf/Makefile
                 nlfit/Makefile
                 nlfit/cmpfit-1.2/Makefile
                 python/Makefile
                 slalink/Makefile
                 tablefun/Makefile
                 tablelib/Makefile
                 tablesrc/Makefile
                 utillib/Makefile])
AC_CONFIG_SUBDIRS([tawk])

AC_OUTPUT
