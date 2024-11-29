# Makefile.am
#
# Starbase Data Tables	- An Ascii Database for UNIX
# 
#   copyright 1991, 1993, 1995, 1999 John B. Roll jr.
#
#  Starbase Data Tables is distributed without warranty under the terms of
#   the GNU General Public License, version 2, 1991.
#

lib_LTLIBRARIES = libutil.la

C_PFLAGS = $(C_PIC)

include_HEADERS = xos.h xfile.h xlist.h except.h cache.h filelist.h range.h

libutil_la_SOURCES = bsearch.c	\
	cache.c		\
	caldate.c	\
	coproc.c	\
	except.c	\
	f77.c		\
	f77handle.c	\
	getdate.y	\
	saotng.c	\
	filelist.c	\
	muxio.c		\
	poll.c		\
	range.c		\
	readfile.c	\
	shm.c		\
	sleep.c		\
	slurpline.c	\
	sokfile.c	\
	sokmult.c	\
	strtod.c	\
	strupr.c	\
	termcap.c	\
	tmatch.c	\
	xfile.c		\
	xpipe.c		\
	xlist.c	

libutil_la_LIBADD = -lgfortran
