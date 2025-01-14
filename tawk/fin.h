
/********************************************
fin.h
copyright 1991, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/


/* fin.h */

#ifndef  FIN_H
#define  FIN_H
/* structure to control input files */

typedef struct {
int  fd ;
FILE *fp ;   /* NULL unless interactive */
char *buff ;
char *buffp ;
unsigned nbuffs ; /* sizeof *buff in BUFFSZs */
int  flags ;
}  FIN ;

#define  MAIN_FLAG    1   /* part of main input stream if on */
#define  EOF_FLAG     2
#define  START_FLAG   4   /* used when RS == "" */

FIN *  PROTO (FINdopen, (int, int) );
FIN *  PROTO (FINopen, (char *, int) );
void   PROTO (FINclose, (FIN *) ) ;
void   PROTO (FINsemi_close, (FIN *)) ;
char*  PROTO (FINgets, (FIN *, unsigned *) ) ;
unsigned PROTO ( fillbuff, (int, char *, unsigned) ) ;


extern  FIN  *main_fin ;  /* for the main input stream */
void   PROTO( open_main, (void) ) ;

#if HAVE_TEXTMODE
void  PROTO(setmode, (int,int)) ;
#endif
#endif  /* FIN_H */
