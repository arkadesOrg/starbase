
/********************************************
da.c
copyright 1991, Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 2, 1991.
********************************************/


/*  da.c  */
/*  disassemble code */



#include  "mawk.h"


#include  "code.h"
#include  "bi_funct.h"
#include  "repl.h"
#include  "field.h"

static char *PROTO(find_bi_name, (PF_CP)) ;

static struct sc
{
   char op ; 
   char *name ;
} simple_code[] =

{
   _STOP, "stop",
   FE_PUSHA, "fe_pusha",
   FE_PUSHI, "fe_pushi",
   A_TEST, "a_test",
   A_DEL, "a_del",
   DEL_A, "del_a",
   POP_AL, "pop_al",
   _POP, "pop",
   _ADD, "add",
   _SUB, "sub",
   _MUL, "mul",
   _DIV, "div",
   _MOD, "mod",
   _POW, "pow",
   _NOT, "not",
   _UMINUS, "uminus",
   _UPLUS, "uplus",
   _TEST, "test",
   _CAT, "cat",
   _ASSIGN, "assign",
   _ASSIGN2, "assign2",
   _ADD_ASG, "add_asg",
   _SUB_ASG, "sub_asg",
   _MUL_ASG, "mul_asg",
   _DIV_ASG, "div_asg",
   _MOD_ASG, "mod_asg",
   _POW_ASG, "pow_asg",
   NF_PUSHI, "nf_pushi",
   F_ASSIGN, "f_assign",
   F_ADD_ASG, "f_add_asg",
   F_SUB_ASG, "f_sub_asg",
   F_MUL_ASG, "f_mul_asg",
   F_DIV_ASG, "f_div_asg",
   F_MOD_ASG, "f_mod_asg",
   F_POW_ASG, "f_pow_asg",
   _POST_INC, "post_inc",
   _POST_DEC, "post_dec",
   _PRE_INC, "pre_inc",
   _PRE_DEC, "pre_dec",
   F_POST_INC, "f_post_inc",
   F_POST_DEC, "f_post_dec",
   F_PRE_INC, "f_pre_inc",
   F_PRE_DEC, "f_pre_dec",
   _EQ, "eq",
   _NEQ, "neq",
   _LT, "lt",
   _LTE, "lte",
   _GT, "gt",
   _GTE, "gte",
   _MATCH2, "match2",
   _EXIT, "exit",
   _EXIT0, "exit0",
   _NEXT, "next",
   _RET, "ret",
   _RET0, "ret0",
   _OMAIN, "omain",
   _JMAIN, "jmain",
   OL_GL, "ol_gl",
   OL_GL_NR, "ol_gl_nr",
   _HALT, (char *) 0
} ;

static char *jfmt = "%s%s%03d\n" ; 
   /* format to print jumps */
static char *tab2 = "\t\t" ;

void
da(start, fp)
   INST *start ;
   FILE *fp ;
{
   CELL *cp ;
   register INST *p = start ;
   char *name ;

   while (p->op != _HALT)
   {
      /* print the relative code address (label) */
      fprintf(fp, "%03ld ", (long)(p - start)) ;

      switch (p++->op)
      {

	 case _PUSHC:
	    cp = (CELL *) p++->ptr ;
	    switch (cp->type)
	    {
	       case C_RE:
		  fprintf(fp, "pushc\t0x%lx\t/%s/\n", (long) cp->ptr,
			  re_uncompile(cp->ptr)) ;
		  break ;

	       case C_SPACE:
		  fprintf(fp, "pushc\tspace split\n") ;
		  break ;

	       case C_SNULL:
		  fprintf(fp, "pushc\tnull split\n") ;
		  break ;
	       case C_REPL:
		  fprintf(fp, "pushc\trepl\t%s\n",
			  repl_uncompile(cp)) ;
		  break ;
	       case C_REPLV:
		  fprintf(fp, "pushc\treplv\t%s\n",
			  repl_uncompile(cp)) ;
		  break ;

	       default:
		  fprintf(fp,"pushc\tWEIRD\n") ;  ;
		  break ;
	    }
	    break ;
	 case _PUSHD: {
		double *ptr = (double *) p++->ptr;
		int	op  = p++->op;
		fprintf(fp, "pushd\t%.6g %c%c\n",  *ptr, op & 0x80 ? 'U' : ' ', op & ~0x80);
		break;
	 }
	 case _PUSHS:
	    {
	       STRING *sval = (STRING *) p++->ptr ;
	       fprintf(fp, "pushs\t\"%s\"\n", sval->str) ;
	       break ;
	    }

	 case _MATCH0:
	 case _MATCH1:
	    fprintf(fp, "match%d\t0x%lx\t/%s/\n",
		    p[-1].op == _MATCH1, (long) p->ptr,
		    re_uncompile(p->ptr)) ;
	    /* REmprint(p->ptr, fp); */
	    p++ ;
	    break ;

	 case _PUSHA:
	    fprintf(fp, "pusha\t%s\n",
		    reverse_find(ST_VAR, &p++->ptr)) ;
	    break ;

	 case _PUSHI:
	    cp = (CELL *) p++->ptr ;
	    if (cp == field)  fprintf(fp, "pushi\t$0\n") ;
	    else if (cp == &fs_shadow)
	       fprintf(fp, "pushi\t@fs_shadow\n") ;
	    else
	    {
	       if ( cp > NF && cp <= LAST_PFIELD )
		     name = reverse_find(ST_FIELD, &cp) ;
	       else  name = reverse_find(ST_VAR, &cp) ;

	       fprintf(fp, "pushi\t%s\n", name) ;
	    }
	    break ;

	 case L_PUSHA:
	    fprintf(fp, "l_pusha\t%d\n", p++->op) ;
	    break ;

	 case L_PUSHI:
	    fprintf(fp, "l_pushi\t%d\n", p++->op) ;
	    break ;

	 case LAE_PUSHI:
	    fprintf(fp, "lae_pushi\t%d\n", p++->op) ;
	    break ;

	 case LAE_PUSHA:
	    fprintf(fp, "lae_pusha\t%d\n", p++->op) ;
	    break ;

	 case LA_PUSHA:
	    fprintf(fp, "la_pusha\t%d\n", p++->op) ;
	    break ;

	 case F_PUSHA:
	    cp = (CELL *) p++->ptr ;
	    if ( cp >= NF && cp <= LAST_PFIELD )
	       fprintf(fp, "f_pusha\t%s\n",
		       reverse_find(ST_FIELD, &cp)) ;
	    else  fprintf(fp, "f_pusha\t$%d\n",
		       field_addr_to_index(cp)) ;
	    break ;

	 case F_PUSHI:
	    p++ ;
	    fprintf(fp, "f_pushi\t$%d\n", p++->op) ;
	    break ;

	 case AE_PUSHA:
	    fprintf(fp, "ae_pusha\t%s\n",
		    reverse_find(ST_ARRAY, &p++->ptr)) ;
	    break ;

	 case AE_PUSHI:
	    fprintf(fp, "ae_pushi\t%s\n",
		    reverse_find(ST_ARRAY, &p++->ptr)) ;
	    break ;

	 case A_PUSHA:
	    fprintf(fp, "a_pusha\t%s\n",
		    reverse_find(ST_ARRAY, &p++->ptr)) ;
	    break ;

	 case _PUSHINT:
	    fprintf(fp, "pushint\t%d\n", p++->op) ;
	    break ;

	 case _BUILTIN:
	    fprintf(fp, "%s\n",
		    find_bi_name((PF_CP) p++->ptr)) ;
	    break ;

	 case _PRINT:
	    fprintf(fp, "%s\n",
		    (PF_CP) p++->ptr == bi_printf
		    ? "printf" : "print") ;
	    break ;

	 case _JMP:
	    fprintf(fp, jfmt, "jmp", tab2, (p - start) + p->op) ;
	    p++ ;
	    break ;

	 case _JNZ:
	    fprintf(fp, jfmt, "jnz", tab2, (p - start) + p->op) ;
	    p++ ;
	    break ;

	 case _JZ:
	    fprintf(fp, jfmt, "jz", tab2, (p - start) + p->op) ;
	    p++ ;
	    break ;

	 case _LJZ:
	    fprintf(fp, jfmt, "ljz", tab2, (p - start) + p->op) ;
	    p++ ;
	    break ;

	 case _LJNZ:
	    fprintf(fp, jfmt, "ljnz", tab2+1 , (p - start) + p->op) ;
	       p++ ;
	       break ;

	 case SET_ALOOP:
	    fprintf(fp, "set_al\t%03ld\n", (long)(p + p->op - start)) ;
	    p++ ;
	    break ;

	 case ALOOP:
	    fprintf(fp, "aloop\t%03ld\n", (long)(p - start + p->op)) ;
	    p++ ;
	    break ;

	 case  A_CAT :
	    fprintf(fp,"a_cat\t%d\n", p++->op) ;
	    break ;

	 case _CALL:
	    fprintf(fp, "call\t%s\t%d\n",
		    ((FBLOCK *) p->ptr)->name, p[1].op) ;
	    p += 2 ;
	    break ;

	 case _RANGE:
	    fprintf(fp, "range\t%03ld %03ld %03ld\n",
	    /* label for pat2, action, follow */
		    (long)(p - start + p[1].op),
		    (long)(p - start + p[2].op),
		    (long)(p - start + p[3].op)) ;
	    p += 4 ;
	    break ;

	 case _RET2:
	    fprintf(fp, "ret2\n");
	    p++;
	 case _ASSIGNL:
	    fprintf(fp, "assignL\t%d %d\n", p[1].op, p[2].op);
	    p += 2;
	    break;
	 case _ASSIGN2: {
		int nassign = -p++->op ;
		FBLOCK *fbp     = (FBLOCK *) p++->ptr ;

	    fprintf(fp, "assign2\t%d function %s returns %d items\n", 
		    nassign, fbp->name, fbp->nrets);

	    break;
	    }
	 default:
	    {
	       struct sc *q = simple_code ;
	       int k = (p - 1)->op ;

	       while (q->op != _HALT && q->op != k)  q++ ;

	       fprintf(fp, "%s\n",
		       q->op != _HALT ? q->name : "bad instruction") ;
	    }
	    break ;
      }
   }
   fflush(fp) ;
}

static struct
{
   PF_CP action ;
   char *name ;
}
special_cases[] =
{
   bi_split, "split",
   bi_match, "match",
   bi_getline, "getline",
   bi_sub, "sub",
   bi_gsub, "gsub",
   (PF_CP) 0, (char *) 0
} ;

static char *
find_bi_name(p)
   PF_CP p ;
{
   BI_REC *q ;
   int i ;

   for (q = bi_funct; q->name; q++)
   {
      if (q->fp == p)
      {
	 /* found */
	 return q->name ;
      }
   }
   /* next check some special cases */
   for (i = 0; special_cases[i].action; i++)
   {
      if (special_cases[i].action == p)	 return special_cases[i].name ;
   }

   return "unknown builtin" ;
}

static struct fdump
{
   struct fdump *link ;
   FBLOCK *fbp ;
} *fdump_list ;			 /* linked list of all user functions */

void
add_to_fdump_list(fbp)
   FBLOCK *fbp ;
{
   struct fdump *p = ZMALLOC(struct fdump) ;
   p->fbp = fbp ;
   p->link = fdump_list ;  fdump_list = p ;
}

void
fdump()
{
   register struct fdump *p, *q = fdump_list ;

   while (q)
   {
      p = q ;
      q = p->link ;
      fprintf(stdout, "function %s\n", p->fbp->name) ;
      da(p->fbp->code, stdout) ;
      ZFREE(p) ;
   }
}

