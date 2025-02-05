
/********************************************
zmalloc.c
copyright 1991, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/


/*  zmalloc.c  */
#include  "mawk.h"
#include  "zmalloc.h"



/*
  zmalloc() gets mem from malloc() in CHUNKS of 2048 bytes
  and cuts these blocks into smaller pieces that are multiples
  of eight bytes.  When a piece is returned via zfree(), it goes
  on a linked linear list indexed by its size.	The lists are
  an array, pool[].

  E.g., if you ask for 22 bytes with p = zmalloc(22), you actually get
  a piece of size 24.  When you free it with zfree(p,22) , it is added
  to the list at pool[2].
*/

#define POOLSZ	    16

#define	 CHUNK		256
 /* number of blocks to get from malloc */

static void PROTO(out_of_mem, (void)) ;


static void
out_of_mem()
{
   static char out[] = "out of memory" ;

   if (mawk_state == EXECUTION)	 rt_error(out) ;
   else
   {
      /* I don't think this will ever happen */
      compile_error(out) ; mawk_exit(2) ; 
   }
}


typedef union zblock
{
   char dummy[ZBLOCKSZ] ;
   union zblock *link ;
} ZBLOCK ;

/* ZBLOCKS of sizes 1, 2, ... 16
   which is bytes of sizes 8, 16, ... , 128
   are stored on the linked linear lists in
   pool[0], pool[1], ... , pool[15]
*/

static ZBLOCK *pool[POOLSZ] ;

/* zmalloc() is a macro in front of bmalloc "BLOCK malloc" */

PTR
bmalloc(blocks)
   register unsigned blocks ;
{
   register ZBLOCK *p ;
   static unsigned amt_avail ;
   static ZBLOCK *avail ;

   if (blocks > POOLSZ)
   {
      p = (ZBLOCK *) malloc(blocks << ZSHIFT) ;
      memset(p, 0, blocks << ZSHIFT);
      if (!p)  out_of_mem() ;
      return (PTR) p ;
   }

   if ( (p = pool[blocks - 1]) )
   {
      pool[blocks - 1] = p->link ;
      return (PTR) p ;
   }

   if (blocks > amt_avail)
   {
      if (amt_avail != 0)	/* free avail */
      {
	 avail->link = pool[--amt_avail] ;
	 pool[amt_avail] = avail ;
      }

      if (!(avail = (ZBLOCK *) malloc(CHUNK * ZBLOCKSZ)))
      {
	 /* if we get here, almost out of memory */
	 amt_avail = 0 ;
	 p = (ZBLOCK *) malloc(blocks << ZSHIFT) ;
         memset(p, 0, blocks << ZSHIFT);
	 if (!p)  out_of_mem() ;
	 return (PTR) p ;
      }
      else  amt_avail = CHUNK ;
      memset(avail, 0, CHUNK * ZBLOCKSZ);
   }

   /* get p from the avail pile */
   p = avail ; avail += blocks ; amt_avail -= blocks ; 
   return (PTR) p ;
}

void
bfree(p, blocks)
   register PTR p ;
   register unsigned blocks ;
{

   if (blocks > POOLSZ)	 free(p) ;
   else
   {
      ((ZBLOCK *) p)->link = pool[--blocks] ;
      pool[blocks] = (ZBLOCK *) p ;
   }
}

PTR
zrealloc(p, old_size, new_size)
   register PTR p ;
   unsigned old_size, new_size ;
{
   register PTR q ;

   if (new_size > (POOLSZ << ZSHIFT) &&
       old_size > (POOLSZ << ZSHIFT))
   {
      if (!(q = realloc(p, new_size)))	out_of_mem() ;
   }
   else
   {
      q = zmalloc(new_size) ;
      memcpy(q, p, old_size < new_size ? old_size : new_size) ;
      zfree(p, old_size) ;
   }
   return q ;
}



#ifndef	 __GNUC__
/* pacifier for Bison , this is really dead code */
PTR
alloca(sz)
   unsigned sz ;
{
   /* hell just froze over */
   exit(100) ;
   return (PTR) 0 ;
}
#endif
