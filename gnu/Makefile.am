# Makefile for GNU text utilities.
# Copyright (C) 1991, 1992, 1993, 1994 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

PK_LDLIBS	= $(top_builddir)/tablelib/libtable.la $(top_builddir)/utillib/libutil.la -lm
PK_CFLAGS	= -DSAOMOD
AM_CPPFLAGS = -I$(top_builddir)/include $(PK_CFLAGS)

bin_PROGRAMS = %D%/jointable %D%/_sorttable
jointable_SOURCES = $(srcdir)/jointable.c
_sorttable_SOURCES = $(srcdir)/_sorttable.c

jointable_LDADD = $(PK_LDLIBS)
_sorttable_LDADD = $(PK_LDLIBS)

AM_LDFLAGS = -lgfortran
