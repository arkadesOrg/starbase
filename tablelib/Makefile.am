# Makefile.am
#
# Starbase Data Tables	- An Ascii Database for UNIX
# 
#   copyright 1991, 1993, 1995, 1999 John B. Roll jr.
#
#  Starbase Data Tables is distributed without warranty under the terms of
#   the GNU General Public License, version 2, 1991.
#

# Define the static library
lib_LTLIBRARIES = libtable.la

# List the object files that will go into the library
libtable_la_SOURCES = \
	coladd.c	\
	colarg.c	\
	colpat.c	\
	colfmt.c	\
	colnum.c	\
	colpad.c	\
	colset.c	\
	colval.c	\
	enum.c		\
	extract.c	\
	hdrfix.c	\
	hdrfree.c	\
	hdrval.c	\
	header.c	\
	load.c		\
	rowfree.c	\
	rowfmt.c	\
	rowget.c	\
	rowbuf.c	\
	rowput.c	\
	rowtrim.c	\
	tabrange.c	\
	xsearch.c	\
	table.c		\
	hash.c		\
	slafit_c.c	\
	slafit.c	\
	xyfit.c

libtable_la_LIBADD = -lgfortran

AM_CPPFLAGS = -I$(top_builddir)/include
	
slafit.o : f2c.h

