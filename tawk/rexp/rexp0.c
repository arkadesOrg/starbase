
/********************************************
rexp0.c
copyright 1991, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/

/*$Log: rexp0.c,v $
/*Revision 1.3  2006/05/26 14:28:01  john
/*
/*coproctable.c cprodtable.c edittable.c extracttable.c CVS:    filebytes.c
/*fixtotable.c histtable.c index.c report.l CVS:	  resampletable.c
/*sorttable.c statstable.c tabletofits.c CVS:    teeproc.c xinc CVS:
/*----------------------------------------------------------------------
/*
/*Revision 1.2  2002/11/19 23:53:44  john
/**** empty log message ***
/*
 *Revision 1.5  1996/11/08 15:39:27  mike
 *While cleaning up block_on, I introduced a bug. Now fixed.
 *
 *Revision 1.4  1996/09/02 18:47:09  mike
 *Allow []...] and [^]...] to put ] in a class.
 *Make ^* and ^+ syntax errors.
 *
 * Revision 1.3  1994/12/26  16:37:52  mike
 * 1.1.2 fix to do_str was incomplete -- fix it
 *
 * Revision 1.2  1993/07/23  13:21:38  mike
 * cleanup rexp code
 *
 * Revision 1.1.1.1  1993/07/03	 18:58:27  mike
 * move source to cvs
 *
 * Revision 3.8	 1992/04/21  20:22:38  brennan
 * 1.1 patch2
 * [c1-c2] now works if c2 is an escaped character
 *
 * Revision 3.7	 1992/03/24  09:33:12  brennan
 * 1.1 patch2
 * When backing up in do_str, check if last character was escaped
 *
 * Revision 3.6	 92/01/21  17:32:51  brennan
 * added some casts so that character classes work with signed chars
 *
 * Revision 3.5	 91/10/29  10:53:57  brennan
 * SIZE_T
 *
 * Revision 3.4	 91/08/13  09:10:05  brennan
 * VERSION .9994
 *
 * Revision 3.3	 91/07/19  07:29:24  brennan
 * backslash at end of regular expression now stands for backslash
 *
 * Revision 3.2	 91/07/19  06:58:23  brennan
 * removed small bozo in processing of escape characters
 *
 * Revision 3.1	 91/06/07  10:33:20  brennan
 * VERSION 0.995
 *
 * Revision 1.2	 91/06/05  08:59:36  brennan
 * changed RE_free to free
 *
 * Revision 1.1	 91/06/03  07:10:15  brennan
 * Initial revision
 *
*/

/*  lexical scanner  */

#include  "rexp.h"

/* static functions */
static int PROTO(do_str, (int, char **, MACHINE *)) ;
static int PROTO(do_class, (char **, MACHINE *)) ;
static int PROTO(escape, (char **)) ;
static BV *PROTO(store_bvp, (BV *)) ;
static int PROTO(ctohex, (int)) ;


#ifndef	 EG	
/* make next array visible */
static
#endif
char  RE_char2token[ '|' + 1 ] = {
0,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,13,13,13,
6,7,3,4,13,13,10,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,11,12,13,8,13,13,13,13,13,13,
13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
13,13,13,13,1} ;

#define	 char2token(x) \
( (unsigned char)(x) > '|' ? T_CHAR : RE_char2token[x] )

#define NOT_STARTED    (-1)

static int prev ;
static char *lp ;		 /*  ptr to reg exp string  */
static unsigned re_len ;


void
RE_lex_init(re)
   char *re ;
{
   lp = re ;
   re_len = strlen(re) + 1 ;
   prev = NOT_STARTED ;
   RE_run_stack_init() ;
}


int
RE_lex(mp)
   MACHINE *mp ;
{
   register int c ;

reswitch:
   switch (c = char2token(*lp))
   {
      case T_PLUS:
      case T_STAR:
	 if (prev == T_START) RE_error_trap(6) ;
	 /* fall thru */

      case T_OR:
      case T_Q:
      case T_RP:
	 lp++ ;	 return	 prev = c ;

      case T_SLASH:
	 break ;

      case 0:
	 return 0 ;

      case T_LP:
	 switch (prev)
	 {
	    case T_CHAR:
	    case T_STR:
	    case T_ANY:
	    case T_CLASS:
	    case T_START:
	    case T_RP:
	    case T_PLUS:
	    case T_STAR:
	    case T_Q:
	    case T_U:
	       return prev = T_CAT ;

	    default:
	       lp++ ;
	       return prev = T_LP ;
	 }
   }

   /*  *lp  is	an operand, but implicit cat op is possible   */
   switch (prev)
   {
      case NOT_STARTED:
      case T_OR:
      case T_LP:
      case T_CAT:

	 switch (c)
	 {
	    case T_ANY:
	       {
		  static int plus_is_star_flag = 0 ;

		  if (*++lp == '*')
		  {
		     lp++ ;
		     *mp = RE_u() ;
		     return prev = T_U ;
		  }
		  else if (*lp == '+')
		  {
		     if (plus_is_star_flag)
		     {
			lp++ ;
			*mp = RE_u() ;
			plus_is_star_flag = 0 ;
			return prev = T_U ;
		     }
		     else
		     {
			plus_is_star_flag = 1 ;
			lp-- ;
			*mp = RE_any() ;
			return prev = T_ANY ;
		     }
		  }
		  else
		  {
		     *mp = RE_any() ;
		     prev = T_ANY ;
		  }
	       }
	       break ;

	    case T_SLASH:
	       lp++ ;
	       c = escape(&lp) ;
	       prev = do_str(c, &lp, mp) ;
	       break ;

	    case T_CHAR:
	       c = *lp++ ;
	       prev = do_str(c, &lp, mp) ;
	       break ;

	    case T_CLASS:
	       prev = do_class(&lp, mp) ;
	       break ;

	    case T_START:
	       *mp = RE_start() ;
	       lp++ ;
	       prev = T_START ;
	       break ;

	    case T_END:
	       lp++ ;
	       *mp = RE_end() ;
	       return prev = T_END ;

	    default:
	       RE_panic("bad switch in RE_lex") ;
	 }
	 break ;

      default:
	 /* don't advance the pointer */
	 return prev = T_CAT ;
   }

   /* check for end character */
   if (*lp == '$')
   {
      mp->start->type += END_ON ;
      lp++ ;
   }

   return prev ;
}

/*
  Collect a run of characters into a string machine.
  If the run ends at *,+, or ?, then don't take the last
  character unless the string has length one.
*/

static int
do_str(c, pp, mp)
   int c ;			 /* the first character */
   char **pp ;			 /* where to put the re_char pointer on exit */
   MACHINE *mp ;		 /* where to put the string machine */
{
   register char *p ;		 /* runs thru the input */
   char *pt ;			 /* trails p by one */
   char *str ;			 /* collect it here */
   register char *s ;		 /* runs thru the output */
   unsigned len ;		 /* length collected */


   p = *pp ;
   s = str = RE_malloc(re_len) ;
   *s++ = c ;  len = 1 ;

   while (1)
   {
      char *save ;   

      switch (char2token(*p))
      {
	 case T_CHAR:
	    pt = p ;
	    *s++ = *p++ ;
	    break ;

	 case T_SLASH:
	    pt = p ;
	    save = p+1 ;   /* keep p in a register */
	    *s++ = escape(&save) ;
	    p = save ;
	    break ;

	 default:
	    goto out ;
      }
      len++ ;
   }

out:
   /* if len > 1 and we stopped on a ? + or * , need to back up */
   if (len > 1 && (*p == '*' || *p == '+' || *p == '?'))
   {
      len-- ; 
      p = pt ;
      s-- ;
   }

   *s = 0 ;
   *pp = p ;
   *mp = RE_str((char *) RE_realloc(str, len + 1), len) ;
   return T_STR ;
}


/*--------------------------------------------
  BUILD A CHARACTER CLASS
 *---------------------------*/

#define	 on( b, x)  ((b)[(x)>>3] |= ( 1 << ((x)&7) ))

static void PROTO(block_on, (BV, int, int)) ;

static void
block_on(b, x, y)
   BV b ;
   int x, y ;
   /* caller makes sure x<=y and x>0 y>0 */
{
   int lo = x >> 3 ;
   int hi = y >> 3 ;
   int r_lo = x&7 ;
   int r_hi = y&7 ;

   if (lo == hi)
   {
      b[lo] |= (1<<(r_hi+1)) - (1<<r_lo) ;
   }
   else
   {
      int i ;
      for (i = lo + 1; i <  hi ; i++)  b[i] = 0xff ;
      b[lo] |= (0xff << r_lo) ;
      b[hi] |= ~(0xff << (r_hi+1)) ;
   }
}

/* build a BV for a character class.
   *start points at the '['
   on exit:   *start points at the character after ']'
	      mp points at a machine that recognizes the class
*/

static int
do_class(start, mp)  char **start ;
   MACHINE *mp ;
{
   register char *p ;
   register BV *bvp ;
   int prev ;
   char *q, *t ;
   int cnt ;
   int comp_flag ;

   p = t = (*start) + 1 ;

   /* []...]  puts ] in a class
      [^]..]  negates a class with ]
   */
   if (*p == ']') p++ ;
   else if (*p == '^' && *(p + 1) == ']')  p += 2 ;

   while (1)			/* find the back of the class */
   {
      if (!(q = strchr(p, ']')))
      {
	 /* no closing bracket */
	 RE_error_trap(-E3) ;
      }
      p = q - 1 ;
      cnt = 0 ;
      while (*p == '\\')
      {
	 cnt++ ; p-- ; 
      }
      if ((cnt & 1) == 0)
      {
	 /* even number of \ */
	 break ;
      }
      p = q + 1 ;
   }

   /*  q  now  pts at the back of the class   */
   p = t ;
   *start = q + 1 ;

   bvp = (BV *) RE_malloc(sizeof(BV)) ;
   memset(bvp, 0, sizeof(BV)) ;

   if (*p == '^')
   {
      comp_flag = 1 ; p++ ; 
   }
   else	 comp_flag = 0 ;

   prev = -1 ;			 /* indicates  -  cannot be part of a range  */

   while (p < q)
   {
      switch (*p)
      {
	 case '\\':

	    t = p + 1 ;
	    prev = escape(&t) ;
	    on(*bvp, prev) ;
	    p = t ;
	    break ;

	 case '-':

	    if (prev == -1 || p + 1 == q)
	    {
	       prev = '-' ;
	       on(*bvp, '-') ;
	       p++ ;
	    }
	    else
	    {
	       int c ;
	       char *mark = ++p ;

	       if (*p != '\\')	c = *(unsigned char *) p++ ;
	       else
	       {
		  t = p + 1 ;
		  c = escape(&t) ;
		  p = t ;
	       }

	       if (prev <= c)
	       {
		  block_on(*bvp, prev, c) ;
		  prev = -1 ;
	       }
	       else  /* back up */
	       {
		  p = mark ;
		  prev = '-' ;
		  on(*bvp, '-') ;
	       }
	    }
	    break ;

	 default:
	    prev = *(unsigned char *) p++ ;
	    on(*bvp, prev) ;
	    break ;
      }
   }

   if (comp_flag)
   {
      for (p = (char *) bvp; p < (char *) bvp + sizeof(BV); p++)
      {
	 *p = ~*p ;
      }
   }

   /* make sure zero is off */
   (*bvp)[0] &= ~1 ;

   *mp = RE_class(store_bvp(bvp)) ;
   return T_CLASS ;
}


/* storage for bit vectors so they can be reused ,
   stored in an unsorted linear array
   the array grows as needed
*/

#define		BV_GROWTH	6

static BV *
store_bvp(bvp)
   BV *bvp ;
{
   static BV **bv_base, **bv_limit ;
   static BV **bv_next ;	 /* next empty slot in the array */

   register BV **p ;
   unsigned t ;


   if (bv_next == bv_limit)
   {
      /* need to grow */
      if (!bv_base)
      {
	 /* first growth */
	 t = 0 ;
	 bv_base = (BV **) RE_malloc(BV_GROWTH * sizeof(BV *)) ;
      }
      else
      {
	 t = bv_next - bv_base ;
	 bv_base = (BV **) RE_realloc(bv_base, (t + BV_GROWTH) * sizeof(BV *)) ;
      }

      bv_next = bv_base + t ;
      bv_limit = bv_next + BV_GROWTH ;
   }

   /* put bvp in bv_next as a sentinal */
   *bv_next = bvp ;
   p = bv_base ;
   while (memcmp(*p, bvp, sizeof(BV)))	p++ ;

   if (p == bv_next)
   {
      /* it is new */
      bv_next++ ;
   }
   else
   {
      /* we already have it */
      free(bvp) ;
   }

   return *p ;
}


/* ----------	convert escape sequences  -------------*/

#define isoctal(x)  ((x)>='0'&&(x)<='7')

#define	 NOT_HEX	16
static char hex_val['f' - 'A' + 1] =
{
   10, 11, 12, 13, 14, 15, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   10, 11, 12, 13, 14, 15} ;

/* interpret 1 character as hex */
static int
ctohex(c)
   register int c ;
{
   int t ;

   if (c >= '0' && c <= '9')  return c - '0' ;
   if (c >= 'A' && c <= 'f' && (t = hex_val[c - 'A']))	return t ;
   return NOT_HEX ;
}

#define	 ET_END	    7

static struct
{
   char in, out ;
}
escape_test[ET_END + 1] =
{
   'n', '\n',
   't', '\t',
   'f', '\f',
   'b', '\b',
   'r', '\r',
   'a', '\07',
   'v', '\013',
   0, 0
} ;


/*-----------------
  return the char
  and move the pointer forward
  on entry *s -> at the character after the slash
 *-------------------*/

static int
escape(start_p)
   char **start_p ;
{
   register char *p = *start_p ;
   register unsigned x ;
   unsigned xx ;
   int i ;


   escape_test[ET_END].in = *p ;
   i = 0 ;
   while (escape_test[i].in != *p)  i++ ;
   if (i != ET_END)
   {
      /* in escape_test table */
      *start_p = p + 1 ;
      return escape_test[i].out ;
   }

   if (isoctal(*p))
   {
      x = *p++ - '0' ;
      if (isoctal(*p))
      {
	 x = (x << 3) + *p++ - '0' ;
	 if (isoctal(*p))  x = (x << 3) + *p++ - '0' ;
      }
      *start_p = p ;
      return x & 0xff ;
   }

   if (*p == 0)	 return '\\' ;

   if (*p++ == 'x')
   {
      if ((x = ctohex(*p)) == NOT_HEX)
      {
	 *start_p  = p ;  return 'x' ; 
      }

      /* look for another hex digit */
      if ((xx = ctohex(*++p)) != NOT_HEX)
      {
	 x = (x<<4) + xx ; p++ ; 
      }

      *start_p = p ; return x ;
   }

   /* anything else \c -> c */
   *start_p = p ;
   return *(unsigned char *) (p - 1) ;
}

