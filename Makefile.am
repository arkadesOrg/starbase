# Makefile for Starbase Data Tables
#

Package = starbase

MAKEDEFS = bindir=$(bindir) libdir=$(libdir) incdir=$(incdir) $(flags)

CC = @CC@
CFLAGS = @CFLAGS@
LDFLAGS = @LDFLAGS@

AM_CPPFLAGS = -I$(top_builddir)/include

SUBDIRS = bsd iraf nlfit nlfit/cmpfit-1.2 python slalink utillib tablefun tablelib tablesrc gnu doc

all-init:
	mkdir -p bin
	mkdir -p lib
	mkdir -p include
	cp $(srcdir)/utillib/*.h  include
	cp $(srcdir)/tablelib/*.h include
	cp $(srcdir)/tawk/xawk*.h include
	if [ ! -f touched -a -f     $(srcdir)/tawk/parse.c ]      ; then touch     $(srcdir)/tawk/parse.c; 	    fi
	if [ ! -f touched -a -f     $(srcdir)/tawk/getdate.c ]    ; then touch     $(srcdir)/tawk/getdate.c;    fi
	if [ ! -f touched -a -f     $(srcdir)/tawk/array.c ]      ; then touch     $(srcdir)/tawk/array.c;      fi
	if [ ! -f touched -a -f $(srcdir)/tablesrc/table_lex.c ]  ; then touch $(srcdir)/tablesrc/table_lex.c;  fi
	if [ ! -f touched -a -f $(srcdir)/tablesrc/report_lex.c ] ; then touch $(srcdir)/tablesrc/report_lex.c; fi
	if [ ! -f touched -a -f  $(srcdir)/utillib/getdate.c ]    ; then touch  $(srcdir)/utillib/getdate.c;    fi
	touch touched

all: all-init

afl: 
	$(MAKE) CC=afl-gcc C_DFLAGS=-g all

debug:
	$(MAKE) flags=C_DLFLAGS=-g all

parser:
	-rm -f tawk/parse.c
	-rm -f utillib/getdate.c
	-rm -f tablesrc/table_lex.c
	-rm -f tablesrc/report_lex.c
	$(MAKE) $(MAKEDEFS) all

install::
	rm -f Commands
	test -d $(bindir) || mkdir -p $(bindir)
	test -d $(libdir) || mkdir -p $(libdir)
	test -d $(incdir) || mkdir -p $(incdir)

distclean :: clean
	rm -rf bin lib include
	rm -f make.log Makefile
	rm -f Commands .config

install distclean clean ::
	for dir in $(SUBDIRS); do 			\
          if [ -d $$dir ]; then  			\
	    echo $(MAKE) $@ $(MAKEDEFS) in $$dir ; 	\
	    (cd $$dir; $(MAKE) $(MAKEDEFS) $@ ) ; 	\
          fi; 						\
	done

clean ::
	rm -f touched

html:
	-rm -f tawk/parse.c
	-rm -f utillib/getdate.c
	-rm -f tablesrc/table_lex.c
	-rm -f tablesrc/report_lex.c
	gtags
	htags
	rm GPATH    GRTAGS   GSYMS    GTAGS
	rm -r $MMTIHTML/starbase/SRC
	mv HTML $MMTIHTML/starbase/SRC

CONFIGARGS=`cat .save`

release:
	cp .config .save
	./configure
	make source
	./configure
	make binary
	./configure $(CONFIGARGS)
	rm .save


rebuild:
	make distclean
	./configure --arch=$(MMTIOS)
	make
	make install

