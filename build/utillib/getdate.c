/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "../../utillib/getdate.y"

/* $Revision: 1.3 $
**
**  Originally written by Steven M. Bellovin <smb@research.att.com> while
**  at the University of North Carolina at Chapel Hill.  Later tweaked by
**  a couple of people on Usenet.  Completely overhauled by Rich $alz
**  <rsalz@bbn.com> and Jim Berets <jberets@bbn.com> in August, 1990;
**  send any email to Rich.
**
**  This grammar has eight shift/reduce conflicts.
**
**  This code is in the public domain and has no copyright.
*/
/* SUPPRESS 287 on yaccpar_sccsid *//* Unusd static variable */
/* SUPPRESS 288 on yyerrlab *//* Label unused */


struct tm *breakmjd();

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __GNUC__
#define alloca __builtin_alloca
#else
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else
#ifdef _AIX /* for Bison */
 #pragma alloca
#else
#define yyoverflow	dateoverflow

static int dateoverflow() {
	return 1;
}

char *alloca ();
#endif
#endif
#endif


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void   caldate();
double juldate();

/* The code at the top of get_date which figures out the offset of the
   current time zone checks various CPP symbols to see if special
   tricks are need, but defaults to using the gettimeofday system call.
   Include <sys/time.h> if that will be used.  */

#if !defined (USG) && !defined (sgi) && !defined (__FreeBSD__)
#include <sys/time.h>
#endif

#if	defined(vms)

#include <types.h>
#include <time.h>

#else

#include <sys/types.h>

#if	defined(BSD4_2) || defined(BSD4_1C) || (defined (hp9000) && !defined (hpux))
#include <sys/time.h>
#else
#if defined(_AIX)
#include <sys/time.h>
#endif
#include <time.h>
#endif	/* defined(BSD4_2) */
#endif	/* defined(vms) */

#if defined (STDC_HEADERS) || defined (USG)
#include <string.h>
#endif

#if sgi
#undef timezone
#endif

#define yyparse getdate_yyparse
#define yylex   getdate_yylex
#define yyerror getdate_yyerror
#define yylval  getdate_yylval

#define HOUR(x)		((int)(x) * 60)
#define SECSPERDAY	(24L * 60L * 60L)

#define MJD1970			  40587
#define MJD2038			  65424

#define MJDtoUNIXTIME(mjd)	((int   ) (((mjd - MJD1970) * SECSPERDAY)))
#define UNIXTIMEtoMJD(unx)	((double)unx/SECSPERDAY + MJD1970)


/*
**  An entry in the lexical lookup table.
*/
typedef struct _TABLE {
    char	*name;
    int		type;
    time_t	value;
} TABLE;


/*
**  Daylight-savings mode:  on, off, or not yet known.
*/
typedef enum _DSTMODE {
    DSTon, DSToff, DSTmaybe
} DSTMODE;

/*
**  Meridian:  am, pm, or 24-hour style.
*/
typedef enum _MERIDIAN {
    MERam, MERpm, MER24
} MERIDIAN;


/*
**  Global variables.  We could get rid of most of these by using a good
**  union as the yacc stack.  (This routine was originally written before
**  yacc had the %union construct.)  Maybe someday; right now we only use
**  the %union very rarely.
*/
static char	*yyInput;
static DSTMODE	yyDSTmode;
static time_t	yyDayOrdinal;
static time_t	yyDayNumber;
static int	yyHaveDate;
static int	yyHaveMJD;
static int	yyHaveDay;
static int	yyHaveRel;
static int	yyHaveTime;
static int	yyHaveZone;
static double	yyMJD;
static int	yyNow;
static time_t	yyTimezone;
static time_t	yyDay;
static time_t	yyHour;
static time_t	yyMinutes;
static time_t	yyMonth;
static double	yySeconds;
static time_t	yyYear;
static MERIDIAN	yyMeridian;
static time_t	yyRelMonth;
static time_t	yyRelSeconds;

static int FitsDate = 1;

static int getdate_yyerror();
static int getdate_yylex();

#line 233 "getdate.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tAGO = 258,                    /* tAGO  */
    tDAY = 259,                    /* tDAY  */
    tDAYZONE = 260,                /* tDAYZONE  */
    tID = 261,                     /* tID  */
    tMERIDIAN = 262,               /* tMERIDIAN  */
    tMINUTE_UNIT = 263,            /* tMINUTE_UNIT  */
    tMONTH = 264,                  /* tMONTH  */
    tMONTH_UNIT = 265,             /* tMONTH_UNIT  */
    tSEC_UNIT = 266,               /* tSEC_UNIT  */
    tSNUMBER = 267,                /* tSNUMBER  */
    tUNUMBER = 268,                /* tUNUMBER  */
    tFNUMBER = 269,                /* tFNUMBER  */
    tZONE = 270,                   /* tZONE  */
    tDST = 271,                    /* tDST  */
    tT = 272                       /* tT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tAGO 258
#define tDAY 259
#define tDAYZONE 260
#define tID 261
#define tMERIDIAN 262
#define tMINUTE_UNIT 263
#define tMONTH 264
#define tMONTH_UNIT 265
#define tSEC_UNIT 266
#define tSNUMBER 267
#define tUNUMBER 268
#define tFNUMBER 269
#define tZONE 270
#define tDST 271
#define tT 272

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 163 "../../utillib/getdate.y"

    double		Number;
    enum _MERIDIAN	Meridian;

#line 322 "getdate.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tAGO = 3,                       /* tAGO  */
  YYSYMBOL_tDAY = 4,                       /* tDAY  */
  YYSYMBOL_tDAYZONE = 5,                   /* tDAYZONE  */
  YYSYMBOL_tID = 6,                        /* tID  */
  YYSYMBOL_tMERIDIAN = 7,                  /* tMERIDIAN  */
  YYSYMBOL_tMINUTE_UNIT = 8,               /* tMINUTE_UNIT  */
  YYSYMBOL_tMONTH = 9,                     /* tMONTH  */
  YYSYMBOL_tMONTH_UNIT = 10,               /* tMONTH_UNIT  */
  YYSYMBOL_tSEC_UNIT = 11,                 /* tSEC_UNIT  */
  YYSYMBOL_tSNUMBER = 12,                  /* tSNUMBER  */
  YYSYMBOL_tUNUMBER = 13,                  /* tUNUMBER  */
  YYSYMBOL_tFNUMBER = 14,                  /* tFNUMBER  */
  YYSYMBOL_tZONE = 15,                     /* tZONE  */
  YYSYMBOL_tDST = 16,                      /* tDST  */
  YYSYMBOL_tT = 17,                        /* tT  */
  YYSYMBOL_18_ = 18,                       /* ':'  */
  YYSYMBOL_19_ = 19,                       /* ','  */
  YYSYMBOL_20_ = 20,                       /* '/'  */
  YYSYMBOL_21_ = 21,                       /* '-'  */
  YYSYMBOL_YYACCEPT = 22,                  /* $accept  */
  YYSYMBOL_spec = 23,                      /* spec  */
  YYSYMBOL_item = 24,                      /* item  */
  YYSYMBOL_time = 25,                      /* time  */
  YYSYMBOL_UorFNumber = 26,                /* UorFNumber  */
  YYSYMBOL_mjd = 27,                       /* mjd  */
  YYSYMBOL_zone = 28,                      /* zone  */
  YYSYMBOL_day = 29,                       /* day  */
  YYSYMBOL_date = 30,                      /* date  */
  YYSYMBOL_rel = 31,                       /* rel  */
  YYSYMBOL_relunit = 32,                   /* relunit  */
  YYSYMBOL_number = 33,                    /* number  */
  YYSYMBOL_o_merid = 34                    /* o_merid  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   60

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  66

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   272


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    19,    21,     2,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    18,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   177,   177,   178,   182,   183,   190,   191,   192,   193,
     194,   195,   196,   199,   205,   211,   219,   227,   239,   242,
     248,   255,   259,   264,   270,   274,   278,   284,   288,   298,
     304,   308,   313,   318,   323,   328,   332,   339,   343,   346,
     349,   352,   355,   358,   361,   364,   367,   370,   375,   409,
     412
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "tAGO", "tDAY",
  "tDAYZONE", "tID", "tMERIDIAN", "tMINUTE_UNIT", "tMONTH", "tMONTH_UNIT",
  "tSEC_UNIT", "tSNUMBER", "tUNUMBER", "tFNUMBER", "tZONE", "tDST", "tT",
  "':'", "','", "'/'", "'-'", "$accept", "spec", "item", "time",
  "UorFNumber", "mjd", "zone", "day", "date", "rel", "relunit", "number",
  "o_merid", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-19)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -19,    15,   -19,   -18,   -19,   -19,     9,   -19,   -19,     1,
      -4,   -19,    21,   -19,   -19,   -19,   -19,   -19,    -7,   -19,
      32,   -19,   -19,    28,    19,   -19,   -19,   -19,   -19,   -19,
     -19,    33,   -19,   -19,    29,    34,    35,    36,   -19,    37,
     -19,   -19,    -5,    38,    39,   -19,   -19,    24,    40,    41,
      -5,   -19,   -19,   -19,   -19,   -19,    30,   -19,    42,   -19,
     -19,   -19,    27,   -19,   -19,   -19
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    24,    22,    41,     0,    47,    44,     0,
      48,    20,    21,     3,     7,     8,     9,    10,     6,    11,
      38,    12,    25,     0,    30,    40,    45,    42,    26,    13,
      39,    35,    46,    43,     0,     0,     0,     0,    23,     0,
      37,    32,    34,     0,     0,    36,    29,    49,    27,     0,
       0,     4,    33,     5,    50,    15,     0,    14,     0,    31,
      18,    19,    49,    28,    17,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -19,   -19,   -19,    -6,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    13,    14,    62,    15,    16,    17,    18,    19,
      20,    21,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      28,    22,    29,    29,    30,    31,    32,    33,    34,    25,
      39,    26,    27,    35,    35,     2,    36,    37,    44,     3,
       4,    23,    24,     5,     6,     7,     8,     9,    10,    11,
      12,    54,    42,    51,    54,    40,    55,    38,    43,    64,
      41,    46,    56,    60,    61,    49,    45,    47,    48,    65,
      50,    52,    53,    59,     0,    63,     0,     0,     0,     0,
      58
};

static const yytype_int8 yycheck[] =
{
       4,    19,     7,     7,     8,     9,    10,    11,    12,     8,
      17,    10,    11,    18,    18,     0,    20,    21,    24,     4,
       5,    12,    13,     8,     9,    10,    11,    12,    13,    14,
      15,     7,    13,    39,     7,     3,    12,    16,    19,    12,
      12,    12,    18,    13,    14,     9,    13,    13,    13,    62,
      13,    13,    13,    12,    -1,    13,    -1,    -1,    -1,    -1,
      20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    23,     0,     4,     5,     8,     9,    10,    11,    12,
      13,    14,    15,    24,    25,    27,    28,    29,    30,    31,
      32,    33,    19,    12,    13,     8,    10,    11,     4,     7,
       8,     9,    10,    11,    12,    18,    20,    21,    16,    17,
       3,    12,    13,    19,    25,    13,    12,    13,    13,     9,
      13,    25,    13,    13,     7,    12,    18,    34,    20,    12,
      13,    14,    26,    13,    12,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    22,    23,    23,    24,    24,    24,    24,    24,    24,
      24,    24,    24,    25,    25,    25,    25,    25,    26,    26,
      27,    28,    28,    28,    29,    29,    29,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    31,    31,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    33,    34,
      34
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     4,     6,     6,     1,     1,
       1,     1,     1,     2,     1,     2,     2,     3,     5,     3,
       2,     4,     3,     4,     3,     2,     3,     2,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     1,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* item: date tT time  */
#line 182 "../../utillib/getdate.y"
                       { yyHaveDate++; yyHaveTime++; }
#line 1374 "getdate.c"
    break;

  case 5: /* item: tMONTH tUNUMBER time tUNUMBER  */
#line 183 "../../utillib/getdate.y"
                                        {
	    yyHaveDate++; yyHaveTime++;

	    yyMonth = (yyvsp[-3].Number);
	    yyDay   = (yyvsp[-2].Number);
	    yyYear  = (yyvsp[0].Number);
	}
#line 1386 "getdate.c"
    break;

  case 6: /* item: date  */
#line 190 "../../utillib/getdate.y"
               { yyHaveDate++;	}
#line 1392 "getdate.c"
    break;

  case 7: /* item: time  */
#line 191 "../../utillib/getdate.y"
               { yyHaveTime++;	}
#line 1398 "getdate.c"
    break;

  case 8: /* item: mjd  */
#line 192 "../../utillib/getdate.y"
               { yyHaveMJD++;	}
#line 1404 "getdate.c"
    break;

  case 9: /* item: zone  */
#line 193 "../../utillib/getdate.y"
               { yyHaveZone++;	}
#line 1410 "getdate.c"
    break;

  case 10: /* item: day  */
#line 194 "../../utillib/getdate.y"
               { yyHaveDay++;	}
#line 1416 "getdate.c"
    break;

  case 11: /* item: rel  */
#line 195 "../../utillib/getdate.y"
               { yyHaveRel++;	}
#line 1422 "getdate.c"
    break;

  case 13: /* time: tUNUMBER tMERIDIAN  */
#line 199 "../../utillib/getdate.y"
                             {
	    yyHour = (yyvsp[-1].Number);
	    yyMinutes = 0;
	    yySeconds = 0;
	    yyMeridian = (yyvsp[0].Meridian);
	}
#line 1433 "getdate.c"
    break;

  case 14: /* time: tUNUMBER ':' tUNUMBER o_merid  */
#line 205 "../../utillib/getdate.y"
                                        {
	    yyHour = (yyvsp[-3].Number);
	    yyMinutes = (yyvsp[-1].Number);
	    yySeconds = 0;
	    yyMeridian = (yyvsp[0].Meridian);
	}
#line 1444 "getdate.c"
    break;

  case 15: /* time: tUNUMBER ':' tUNUMBER tSNUMBER  */
#line 211 "../../utillib/getdate.y"
                                         {
	    yyHour = (yyvsp[-3].Number);
	    yyMinutes = (yyvsp[-1].Number);
	    yySeconds = 0;
	    yyMeridian = MER24;
	    yyDSTmode = DSToff;
	    yyTimezone = - ((int)(yyvsp[0].Number) % 100 + ((int)(yyvsp[0].Number) / 100) * 60);
	}
#line 1457 "getdate.c"
    break;

  case 16: /* time: tUNUMBER ':' tUNUMBER ':' UorFNumber o_merid  */
#line 219 "../../utillib/getdate.y"
                                                       {
		double	f;

	    yyHour = (yyvsp[-5].Number);
	    yyMinutes = (yyvsp[-3].Number);
	    yySeconds = (yyvsp[-1].Number);
	    yyMeridian = (yyvsp[0].Meridian);
	}
#line 1470 "getdate.c"
    break;

  case 17: /* time: tUNUMBER ':' tUNUMBER ':' UorFNumber tSNUMBER  */
#line 227 "../../utillib/getdate.y"
                                                        {
		double	f;

	    yyHour = (yyvsp[-5].Number);
	    yyMinutes = (yyvsp[-3].Number);
	    yySeconds = (yyvsp[-1].Number);
	    yyMeridian = MER24;
	    yyDSTmode = DSToff;
	    yyTimezone = - ((int)(yyvsp[0].Number) % 100 + ((int)(yyvsp[0].Number) / 100) * 60);
	}
#line 1485 "getdate.c"
    break;

  case 18: /* UorFNumber: tUNUMBER  */
#line 239 "../../utillib/getdate.y"
                      {
	    (yyval.Number) = (yyvsp[0].Number);
	}
#line 1493 "getdate.c"
    break;

  case 19: /* UorFNumber: tFNUMBER  */
#line 242 "../../utillib/getdate.y"
                   {
	    (yyval.Number) = (yyvsp[0].Number);
	}
#line 1501 "getdate.c"
    break;

  case 20: /* mjd: tFNUMBER  */
#line 248 "../../utillib/getdate.y"
                   {
	    if ( (yyvsp[0].Number) > 5000 && (yyvsp[0].Number) < 100000 ) {
		yyMJD = (yyvsp[0].Number);
	    }
	}
#line 1511 "getdate.c"
    break;

  case 21: /* zone: tZONE  */
#line 255 "../../utillib/getdate.y"
                {
	    yyTimezone = (yyvsp[0].Number);
	    yyDSTmode = DSToff;
	}
#line 1520 "getdate.c"
    break;

  case 22: /* zone: tDAYZONE  */
#line 259 "../../utillib/getdate.y"
                   {
	    yyTimezone = (yyvsp[0].Number);
	    yyDSTmode = DSTon;
	}
#line 1529 "getdate.c"
    break;

  case 23: /* zone: tZONE tDST  */
#line 264 "../../utillib/getdate.y"
                     {
	    yyTimezone = (yyvsp[-1].Number);
	    yyDSTmode = DSTon;
	}
#line 1538 "getdate.c"
    break;

  case 24: /* day: tDAY  */
#line 270 "../../utillib/getdate.y"
               {
	    yyDayOrdinal = 1;
	    yyDayNumber = (yyvsp[0].Number);
	}
#line 1547 "getdate.c"
    break;

  case 25: /* day: tDAY ','  */
#line 274 "../../utillib/getdate.y"
                   {
	    yyDayOrdinal = 1;
	    yyDayNumber = (yyvsp[-1].Number);
	}
#line 1556 "getdate.c"
    break;

  case 26: /* day: tUNUMBER tDAY  */
#line 278 "../../utillib/getdate.y"
                        {
	    yyDayOrdinal = (yyvsp[-1].Number);
	    yyDayNumber = (yyvsp[0].Number);
	}
#line 1565 "getdate.c"
    break;

  case 27: /* date: tUNUMBER '/' tUNUMBER  */
#line 284 "../../utillib/getdate.y"
                                {
	    yyMonth = (yyvsp[-2].Number);
	    yyDay = (yyvsp[0].Number);
	}
#line 1574 "getdate.c"
    break;

  case 28: /* date: tUNUMBER '/' tUNUMBER '/' tUNUMBER  */
#line 288 "../../utillib/getdate.y"
                                             {
	    if ( FitsDate ) {
		    yyDay = (yyvsp[-4].Number);
		    yyMonth = (yyvsp[-2].Number);
	    } else {
		    yyMonth = (yyvsp[-4].Number);
		    yyDay = (yyvsp[-2].Number);
	    }
	    yyYear = (yyvsp[0].Number);
	}
#line 1589 "getdate.c"
    break;

  case 29: /* date: tUNUMBER tSNUMBER tSNUMBER  */
#line 298 "../../utillib/getdate.y"
                                     {
	    /* ISO 8601 format.  yyyy-mm-dd.  */
	    yyYear = (yyvsp[-2].Number);
	    yyMonth = -(yyvsp[-1].Number);
	    yyDay = -(yyvsp[0].Number);
	}
#line 1600 "getdate.c"
    break;

  case 30: /* date: tMONTH tUNUMBER  */
#line 304 "../../utillib/getdate.y"
                          {
	    yyMonth = (yyvsp[-1].Number);
	    yyDay = (yyvsp[0].Number);
	}
#line 1609 "getdate.c"
    break;

  case 31: /* date: tUNUMBER '-' tMONTH tSNUMBER  */
#line 308 "../../utillib/getdate.y"
                                       {
	    yyDay   =  (yyvsp[-3].Number);
	    yyMonth =  (yyvsp[-1].Number);
	    yyYear  = -(yyvsp[0].Number);
	}
#line 1619 "getdate.c"
    break;

  case 32: /* date: tMONTH tSNUMBER tSNUMBER  */
#line 313 "../../utillib/getdate.y"
                                   {
	    yyMonth =  (yyvsp[-2].Number);
	    yyDay   = -(yyvsp[-1].Number);
	    yyYear  = -(yyvsp[0].Number);
	}
#line 1629 "getdate.c"
    break;

  case 33: /* date: tMONTH tUNUMBER ',' tUNUMBER  */
#line 318 "../../utillib/getdate.y"
                                       {
	    yyMonth = (yyvsp[-3].Number);
	    yyDay = (yyvsp[-2].Number);
	    yyYear = (yyvsp[0].Number);
	}
#line 1639 "getdate.c"
    break;

  case 34: /* date: tMONTH tUNUMBER tUNUMBER  */
#line 323 "../../utillib/getdate.y"
                                   {
	    yyMonth = (yyvsp[-2].Number);
	    yyDay = (yyvsp[-1].Number);
	    yyYear = (yyvsp[0].Number);
	}
#line 1649 "getdate.c"
    break;

  case 35: /* date: tUNUMBER tMONTH  */
#line 328 "../../utillib/getdate.y"
                          {
	    yyMonth = (yyvsp[0].Number);
	    yyDay = (yyvsp[-1].Number);
	}
#line 1658 "getdate.c"
    break;

  case 36: /* date: tUNUMBER tMONTH tUNUMBER  */
#line 332 "../../utillib/getdate.y"
                                   {
	    yyDay = (yyvsp[-2].Number);
	    yyMonth = (yyvsp[-1].Number);
	    yyYear = (yyvsp[0].Number);
	}
#line 1668 "getdate.c"
    break;

  case 37: /* rel: relunit tAGO  */
#line 339 "../../utillib/getdate.y"
                       {
	    yyRelSeconds = -yyRelSeconds;
	    yyRelMonth = -yyRelMonth;
	}
#line 1677 "getdate.c"
    break;

  case 39: /* relunit: tUNUMBER tMINUTE_UNIT  */
#line 346 "../../utillib/getdate.y"
                                {
	    yyRelSeconds += (yyvsp[-1].Number) * (yyvsp[0].Number) * 60L;
	}
#line 1685 "getdate.c"
    break;

  case 40: /* relunit: tSNUMBER tMINUTE_UNIT  */
#line 349 "../../utillib/getdate.y"
                                {
	    yyRelSeconds += (yyvsp[-1].Number) * (yyvsp[0].Number) * 60L;
	}
#line 1693 "getdate.c"
    break;

  case 41: /* relunit: tMINUTE_UNIT  */
#line 352 "../../utillib/getdate.y"
                       {
	    yyRelSeconds += (yyvsp[0].Number) * 60L;
	}
#line 1701 "getdate.c"
    break;

  case 42: /* relunit: tSNUMBER tSEC_UNIT  */
#line 355 "../../utillib/getdate.y"
                             {
	    yyRelSeconds += (yyvsp[-1].Number);
	}
#line 1709 "getdate.c"
    break;

  case 43: /* relunit: tUNUMBER tSEC_UNIT  */
#line 358 "../../utillib/getdate.y"
                             {
	    yyRelSeconds += (yyvsp[-1].Number);
	}
#line 1717 "getdate.c"
    break;

  case 44: /* relunit: tSEC_UNIT  */
#line 361 "../../utillib/getdate.y"
                    {
	    yyRelSeconds++;
	}
#line 1725 "getdate.c"
    break;

  case 45: /* relunit: tSNUMBER tMONTH_UNIT  */
#line 364 "../../utillib/getdate.y"
                               {
	    yyRelMonth += (yyvsp[-1].Number) * (yyvsp[0].Number);
	}
#line 1733 "getdate.c"
    break;

  case 46: /* relunit: tUNUMBER tMONTH_UNIT  */
#line 367 "../../utillib/getdate.y"
                               {
	    yyRelMonth += (yyvsp[-1].Number) * (yyvsp[0].Number);
	}
#line 1741 "getdate.c"
    break;

  case 47: /* relunit: tMONTH_UNIT  */
#line 370 "../../utillib/getdate.y"
                      {
	    yyRelMonth += (yyvsp[0].Number);
	}
#line 1749 "getdate.c"
    break;

  case 48: /* number: tUNUMBER  */
#line 375 "../../utillib/getdate.y"
                   {
	    if (yyHaveTime && yyHaveDate && !yyHaveRel)
		yyYear = (yyvsp[0].Number);
	    else {
		if( (yyvsp[0].Number) > 5000 && (yyvsp[0].Number) < 100000 ) {
		    yyHaveMJD++;
		    yyMJD = (yyvsp[0].Number);
		} else 
		if( (yyvsp[0].Number) > 30000000 ) {
		    yyHaveMJD++;
		    yyMJD = UNIXTIMEtoMJD((yyvsp[0].Number));
		} else 
		if((yyvsp[0].Number)>100000) {
		    yyHaveDate++;
		    yyDay= ((int)(yyvsp[0].Number))%100;
		    yyMonth= ((int)(yyvsp[0].Number)/100)%100;
	    	    yyYear = (yyvsp[0].Number)/10000;
		} else {
		    yyHaveTime++;
		    if ((yyvsp[0].Number) < 100) {
			yyHour = (yyvsp[0].Number);
			yyMinutes = 0;
		    }
		    else {
			yyHour = (yyvsp[0].Number) / 100;
			yyMinutes = (int)(yyvsp[0].Number) % 100;
		    }
		}
		yySeconds = 0;
		yyMeridian = MER24;
	    }
	}
#line 1786 "getdate.c"
    break;

  case 49: /* o_merid: %empty  */
#line 409 "../../utillib/getdate.y"
                     {
	    (yyval.Meridian) = MER24;
	}
#line 1794 "getdate.c"
    break;

  case 50: /* o_merid: tMERIDIAN  */
#line 412 "../../utillib/getdate.y"
                    {
	    (yyval.Meridian) = (yyvsp[0].Meridian);
	}
#line 1802 "getdate.c"
    break;


#line 1806 "getdate.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 417 "../../utillib/getdate.y"


/* Month and day table. */
static TABLE const MonthDayTable[] = {
    { "january",	tMONTH,  1 },
    { "february",	tMONTH,  2 },
    { "march",		tMONTH,  3 },
    { "april",		tMONTH,  4 },
    { "may",		tMONTH,  5 },
    { "june",		tMONTH,  6 },
    { "july",		tMONTH,  7 },
    { "august",		tMONTH,  8 },
    { "september",	tMONTH,  9 },
    { "sept",		tMONTH,  9 },
    { "october",	tMONTH, 10 },
    { "november",	tMONTH, 11 },
    { "december",	tMONTH, 12 },
    { "sunday",		tDAY, 0 },
    { "monday",		tDAY, 1 },
    { "tuesday",	tDAY, 2 },
    { "tues",		tDAY, 2 },
    { "wednesday",	tDAY, 3 },
    { "wednes",		tDAY, 3 },
    { "thursday",	tDAY, 4 },
    { "thur",		tDAY, 4 },
    { "thurs",		tDAY, 4 },
    { "friday",		tDAY, 5 },
    { "saturday",	tDAY, 6 },
    { NULL }
};

/* Time units table. */
static TABLE const UnitsTable[] = {
    { "year",		tMONTH_UNIT,	12 },
    { "month",		tMONTH_UNIT,	1 },
    { "fortnight",	tMINUTE_UNIT,	14 * 24 * 60 },
    { "week",		tMINUTE_UNIT,	7 * 24 * 60 },
    { "day",		tMINUTE_UNIT,	1 * 24 * 60 },
    { "hour",		tMINUTE_UNIT,	60 },
    { "minute",		tMINUTE_UNIT,	1 },
    { "min",		tMINUTE_UNIT,	1 },
    { "second",		tSEC_UNIT,	1 },
    { "sec",		tSEC_UNIT,	1 },
    { NULL }
};

/* Assorted relative-time words. */
static TABLE const OtherTable[] = {
    { "tomorrow",	tMINUTE_UNIT,	1 * 24 * 60 },
    { "yesterday",	tMINUTE_UNIT,	-1 * 24 * 60 },
    { "today",		tMINUTE_UNIT,	0 },
    { "now",		tMINUTE_UNIT,	0 },
    { "last",		tUNUMBER,	-1 },
    { "this",		tMINUTE_UNIT,	0 },
    { "next",		tUNUMBER,	2 },
    { "first",		tUNUMBER,	1 },
/*  { "second",		tUNUMBER,	2 }, */
    { "third",		tUNUMBER,	3 },
    { "fourth",		tUNUMBER,	4 },
    { "fifth",		tUNUMBER,	5 },
    { "sixth",		tUNUMBER,	6 },
    { "seventh",	tUNUMBER,	7 },
    { "eighth",		tUNUMBER,	8 },
    { "ninth",		tUNUMBER,	9 },
    { "tenth",		tUNUMBER,	10 },
    { "eleventh",	tUNUMBER,	11 },
    { "twelfth",	tUNUMBER,	12 },
    { "ago",		tAGO,	1 },
    { NULL }
};

/* The timezone table. */
/* Some of these are commented out because a time_t can't store a float. */
static TABLE const TimezoneTable[] = {
    { "gmt",	tZONE,     HOUR( 0) },	/* Greenwich Mean */
    { "ut",	tZONE,     HOUR( 0) },	/* Universal (Coordinated) */
    { "utc",	tZONE,     HOUR( 0) },
    { "wet",	tZONE,     HOUR( 0) },	/* Western European */
    { "bst",	tDAYZONE,  HOUR( 0) },	/* British Summer */
    { "wat",	tZONE,     HOUR( 1) },	/* West Africa */
    { "at",	tZONE,     HOUR( 2) },	/* Azores */
#if	0
    /* For completeness.  BST is also British Summer, and GST is
     * also Guam Standard. */
    { "bst",	tZONE,     HOUR( 3) },	/* Brazil Standard */
    { "gst",	tZONE,     HOUR( 3) },	/* Greenland Standard */
#endif
#if 0
    { "nft",	tZONE,     HOUR(3.5) },	/* Newfoundland */
    { "nst",	tZONE,     HOUR(3.5) },	/* Newfoundland Standard */
    { "ndt",	tDAYZONE,  HOUR(3.5) },	/* Newfoundland Daylight */
#endif
    { "ast",	tZONE,     HOUR( 4) },	/* Atlantic Standard */
    { "adt",	tDAYZONE,  HOUR( 4) },	/* Atlantic Daylight */
    { "est",	tZONE,     HOUR( 5) },	/* Eastern Standard */
    { "edt",	tDAYZONE,  HOUR( 5) },	/* Eastern Daylight */
    { "cst",	tZONE,     HOUR( 6) },	/* Central Standard */
    { "cdt",	tDAYZONE,  HOUR( 6) },	/* Central Daylight */
    { "mst",	tZONE,     HOUR( 7) },	/* Mountain Standard */
    { "mdt",	tDAYZONE,  HOUR( 7) },	/* Mountain Daylight */
    { "pst",	tZONE,     HOUR( 8) },	/* Pacific Standard */
    { "pdt",	tDAYZONE,  HOUR( 8) },	/* Pacific Daylight */
    { "yst",	tZONE,     HOUR( 9) },	/* Yukon Standard */
    { "ydt",	tDAYZONE,  HOUR( 9) },	/* Yukon Daylight */
    { "hst",	tZONE,     HOUR(10) },	/* Hawaii Standard */
    { "hdt",	tDAYZONE,  HOUR(10) },	/* Hawaii Daylight */
    { "cat",	tZONE,     HOUR(10) },	/* Central Alaska */
    { "ahst",	tZONE,     HOUR(10) },	/* Alaska-Hawaii Standard */
    { "nt",	tZONE,     HOUR(11) },	/* Nome */
    { "idlw",	tZONE,     HOUR(12) },	/* International Date Line West */
    { "cet",	tZONE,     -HOUR(1) },	/* Central European */
    { "met",	tZONE,     -HOUR(1) },	/* Middle European */
    { "mewt",	tZONE,     -HOUR(1) },	/* Middle European Winter */
    { "mest",	tDAYZONE,  -HOUR(1) },	/* Middle European Summer */
    { "swt",	tZONE,     -HOUR(1) },	/* Swedish Winter */
    { "sst",	tDAYZONE,  -HOUR(1) },	/* Swedish Summer */
    { "fwt",	tZONE,     -HOUR(1) },	/* French Winter */
    { "fst",	tDAYZONE,  -HOUR(1) },	/* French Summer */
    { "eet",	tZONE,     -HOUR(2) },	/* Eastern Europe, USSR Zone 1 */
    { "bt",	tZONE,     -HOUR(3) },	/* Baghdad, USSR Zone 2 */
#if 0
    { "it",	tZONE,     -HOUR(3.5) },/* Iran */
#endif
    { "zp4",	tZONE,     -HOUR(4) },	/* USSR Zone 3 */
    { "zp5",	tZONE,     -HOUR(5) },	/* USSR Zone 4 */
#if 0
    { "ist",	tZONE,     -HOUR(5.5) },/* Indian Standard */
#endif
    { "zp6",	tZONE,     -HOUR(6) },	/* USSR Zone 5 */
#if	0
    /* For completeness.  NST is also Newfoundland Stanard, and SST is
     * also Swedish Summer. */
    { "nst",	tZONE,     -HOUR(6.5) },/* North Sumatra */
    { "sst",	tZONE,     -HOUR(7) },	/* South Sumatra, USSR Zone 6 */
#endif	/* 0 */
    { "wast",	tZONE,     -HOUR(7) },	/* West Australian Standard */
    { "wadt",	tDAYZONE,  -HOUR(7) },	/* West Australian Daylight */
#if 0
    { "jt",	tZONE,     -HOUR(7.5) },/* Java (3pm in Cronusland!) */
#endif
    { "cct",	tZONE,     -HOUR(8) },	/* China Coast, USSR Zone 7 */
    { "jst",	tZONE,     -HOUR(9) },	/* Japan Standard, USSR Zone 8 */
#if 0
    { "cast",	tZONE,     -HOUR(9.5) },/* Central Australian Standard */
    { "cadt",	tDAYZONE,  -HOUR(9.5) },/* Central Australian Daylight */
#endif
    { "east",	tZONE,     -HOUR(10) },	/* Eastern Australian Standard */
    { "eadt",	tDAYZONE,  -HOUR(10) },	/* Eastern Australian Daylight */
    { "gst",	tZONE,     -HOUR(10) },	/* Guam Standard, USSR Zone 9 */
    { "nzt",	tZONE,     -HOUR(12) },	/* New Zealand */
    { "nzst",	tZONE,     -HOUR(12) },	/* New Zealand Standard */
    { "nzdt",	tDAYZONE,  -HOUR(12) },	/* New Zealand Daylight */
    { "idle",	tZONE,     -HOUR(12) },	/* International Date Line East */
    {  NULL  }
};

/* Military timezone table. */
static TABLE const MilitaryTable[] = {
    { "a",	tZONE,	HOUR(  1) },
    { "b",	tZONE,	HOUR(  2) },
    { "c",	tZONE,	HOUR(  3) },
    { "d",	tZONE,	HOUR(  4) },
    { "e",	tZONE,	HOUR(  5) },
    { "f",	tZONE,	HOUR(  6) },
    { "g",	tZONE,	HOUR(  7) },
    { "h",	tZONE,	HOUR(  8) },
    { "i",	tZONE,	HOUR(  9) },
    { "k",	tZONE,	HOUR( 10) },
    { "l",	tZONE,	HOUR( 11) },
    { "m",	tZONE,	HOUR( 12) },
    { "n",	tZONE,	HOUR(- 1) },
    { "o",	tZONE,	HOUR(- 2) },
    { "p",	tZONE,	HOUR(- 3) },
    { "q",	tZONE,	HOUR(- 4) },
    { "r",	tZONE,	HOUR(- 5) },
    { "s",	tZONE,	HOUR(- 6) },
    { "t",	tZONE,	HOUR(- 7) },
    { "u",	tZONE,	HOUR(- 8) },
    { "v",	tZONE,	HOUR(- 9) },
    { "w",	tZONE,	HOUR(-10) },
    { "x",	tZONE,	HOUR(-11) },
    { "y",	tZONE,	HOUR(-12) },
    { "z",	tZONE,	HOUR(  0) },
    { NULL }
};

/* ARGSUSED */
static int
yyerror(s)
    char	*s;
{
  return 0;
}

#define ToTOD(Hours, Minutes, Seconds, Meridian)	\
     ( ToSeconds(Hours, Minutes, Seconds, Meridian) / SECSPERDAY )

double ToSeconds(Hours, Minutes, Seconds, Meridian)
    int	Hours;
    int	Minutes;
    double	Seconds;
    MERIDIAN	Meridian;
{
    if (Minutes < 0 || Minutes > 59 || Seconds < 0 || Seconds > 60)
	return -1.0;
    switch (Meridian) {
    case MER24:
	if (Hours < 0 
	 || Hours > 24
	 ||(Hours > 23 && Minutes != 0.0 && Seconds != 0.0))
	    return -1.0;
	return (Hours * 60L + Minutes) * 60L + Seconds;
    case MERam:
	if (Hours < 1 || Hours > 12)
	    return -1.0;
	return (Hours * 60L + Minutes) * 60L + Seconds;
    case MERpm:
	if (Hours < 1 || Hours > 12)
	    return -1.0;
	return ((Hours + 12) * 60L + Minutes) * 60L + Seconds;
    }
    /* NOTREACHED */
}


static double
Convert(Month, Day, Year, Hours, Minutes, Seconds, Meridian, DSTmode)
    int	Month;
    int	Day;
    int	Year;
    int	Hours;
    int	Minutes;
    double	Seconds;
    MERIDIAN	Meridian;
    DSTMODE	DSTmode;
{
    double	Julian;
    double	tod;
    int		j;
    time_t	unx;

    if (Year <   0) Year = -Year;
    if (Year <  50) Year += 2000;
    if (Year < 100) Year += 1900;

    Julian = juldate(Year, Month, Day, &j);
    Julian += ((double ) yyTimezone * 60L) / SECSPERDAY;

    if ((tod = ToTOD(Hours, Minutes, Seconds, Meridian)) < 0)
	return -1;
    else
    	Julian += tod;


    if ( Julian >= MJD1970 && Julian <= MJD2038 ) {
	unx = MJDtoUNIXTIME(Julian);

	if (DSTmode == DSTon
	 || (DSTmode == DSTmaybe && localtime(&unx)->tm_isdst))
	    Julian -= ((double) (60 * 60)) / SECSPERDAY;
    }

    return Julian;
}


static time_t
DSTcorrect(Start, Future)
    time_t	Start;
    time_t	Future;
{
    time_t	StartDay;
    time_t	FutureDay;

    StartDay = (localtime(&Start)->tm_hour + 1) % 24;
    FutureDay = (localtime(&Future)->tm_hour + 1) % 24;
    return (Future - Start) + (StartDay - FutureDay) * 60L * 60L;
}


static double
RelativeDate(Start, DayOrdinal, DayNumber)
    double	Start;
    time_t	DayOrdinal;
    time_t	DayNumber;
{
    struct tm	*tm;
    time_t	unx;
    time_t	now;

    if ( Start >= MJD1970 ) {
	unx = MJDtoUNIXTIME(Start);

	tm = localtime(&unx);
	now += SECSPERDAY * ((DayNumber - tm->tm_wday + 7) % 7);
	now += 7 * SECSPERDAY * (DayOrdinal <= 0 ? DayOrdinal : DayOrdinal - 1);
	return ((double) DSTcorrect(unx, now)) / SECSPERDAY;
    }

    return 0.0;
}


static double RelativeMonth(Start, RelMonth)
    double	Start;
    time_t	RelMonth;
{
    struct tm	tm;
    time_t	Month;
    time_t	Year;
    time_t	unx;
    double	mjd;
    time_t	now;

    if (RelMonth == 0 || Start < MJD1970 )
	return 0.0;

    unx = MJDtoUNIXTIME(Start);
    
    breakmjd(Start, &tm);
    Month = 12 * tm.tm_year + tm.tm_mon + RelMonth;
    Year = Month / 12;
    Month = Month % 12 + 1;
    mjd = Convert(Month, (time_t)tm.tm_mday, Year,
	(time_t)tm.tm_hour, (time_t)tm.tm_min, (double) (time_t)tm.tm_sec,
	MER24, DSTmaybe);

    now = MJDtoUNIXTIME(mjd);

    return ((double) DSTcorrect(unx, now)) / SECSPERDAY;
}


static int
LookupWord(buff)
    char		*buff;
{
    register char	*p;
    register char	*q;
    register const TABLE	*tp;
    int			i;
    int			abbrev;

    if (strcmp(buff, "T") == 0) 
	return tT;

    /* Make it lowercase. */
    for (p = buff; *p; p++)
	if (isupper(*p))
	    *p = tolower(*p);

    if (strcmp(buff, "am") == 0 || strcmp(buff, "a.m.") == 0) {
	yylval.Meridian = MERam;
	return tMERIDIAN;
    }
    if (strcmp(buff, "pm") == 0 || strcmp(buff, "p.m.") == 0) {
	yylval.Meridian = MERpm;
	return tMERIDIAN;
    }

    /* See if we have an abbreviation for a month. */
    if (strlen(buff) == 3)
	abbrev = 1;
    else if (strlen(buff) == 4 && buff[3] == '.') {
	abbrev = 1;
	buff[3] = '\0';
    }
    else
	abbrev = 0;

    for (tp = MonthDayTable; tp->name; tp++) {
	if (abbrev) {
	    if (strncmp(buff, tp->name, 3) == 0) {
		yylval.Number = tp->value;
		return tp->type;
	    }
	}
	else if (strcmp(buff, tp->name) == 0) {
	    yylval.Number = tp->value;
	    return tp->type;
	}
    }

    for (tp = TimezoneTable; tp->name; tp++)
	if (strcmp(buff, tp->name) == 0) {
	    yylval.Number = tp->value;
	    return tp->type;
	}

    if (strcmp(buff, "dst") == 0) 
	return tDST;

    for (tp = UnitsTable; tp->name; tp++)
	if (strcmp(buff, tp->name) == 0) {
	    yylval.Number = tp->value;
	    return tp->type;
	}

    /* Strip off any plural and try the units table again. */
    i = strlen(buff) - 1;
    if (buff[i] == 's') {
	buff[i] = '\0';
	for (tp = UnitsTable; tp->name; tp++)
	    if (strcmp(buff, tp->name) == 0) {
		yylval.Number = tp->value;
		return tp->type;
	    }
	buff[i] = 's';		/* Put back for "this" in OtherTable. */
    }

    for ( tp = OtherTable; tp->name; tp++ )
	if ( strcmp(buff, tp->name) == 0 ) {
	    if ( !strcmp(tp->name, "now") ) {
		yyNow = 1;
	    }
	    yylval.Number = tp->value;
	    return tp->type;
	}

    /* Military timezones. */
    if (buff[1] == '\0' && isalpha(*buff)) {
	for (tp = MilitaryTable; tp->name; tp++)
	    if (strcmp(buff, tp->name) == 0) {
		yylval.Number = tp->value;
		return tp->type;
	    }
    }

    /* Drop out any periods and try the timezone table again. */
    for (i = 0, p = q = buff; *q; q++)
	if (*q != '.')
	    *p++ = *q;
	else
	    i++;
    *p = '\0';
    if (i)
	for (tp = TimezoneTable; tp->name; tp++)
	    if (strcmp(buff, tp->name) == 0) {
		yylval.Number = tp->value;
		return tp->type;
	    }

    return tID;
}

int TZX() {
#if HAVE_TM_ZONE
        time_t  unx;
        struct tm *tmx;
        time(&unx);
        tmx = localtime(&unx);
        return tmx->tm_gmtoff;
#else
	return timezone;
#endif
}
	

static int
yylex()
{
    register char	c;
    register char	*p;
    char		buff[20];
    int			Count;
    int			sign;
    int			floa = 0;

    if ( FitsDate == 1 ) 
	if ( getenv("STARBASE_CALDATE") ) FitsDate = 0;
	else				  FitsDate = 2;

    for ( ; ; ) {
	while (isspace(*yyInput))
	    yyInput++;

	if (isdigit(c = *yyInput) || c == '-' || c == '+') {
	    if (c == '-' || c == '+') {
		sign = c == '-' ? -1 : 1;
		if (!isdigit(*++yyInput))
		    /* skip the '-' sign */
		    return '-';
	    }
	    else
		sign = 0;
	    for (yylval.Number = 0; isdigit(c = *yyInput++); )
		yylval.Number = 10 * yylval.Number + (c - '0');
	    yyInput--;

	    if ( *yyInput == '.' ) {
		double div = 10 * (sign < 0 ? -1 : 1);

		floa = 1;

		yyInput++;
		for ( ; isdigit(c = *yyInput++); ) {
		    yylval.Number += (c - '0') / div;
		    div *= 10;
		}
		yyInput--;
	    }

	    if (sign < 0)
		yylval.Number = -yylval.Number;

	    if ( floa ) { return tFNUMBER; }

	    return sign ? tSNUMBER : tUNUMBER;
	}
	if (isalpha(c)) {
	    for (p = buff; isalpha(c = *yyInput++) || c == '.'; )
		if (p < &buff[sizeof buff - 1])
		    *p++ = c;
	    *p = '\0';
	    yyInput--;
	    return LookupWord(buff);
	}
	if (c != '(')
	    return *yyInput++;
	Count = 0;
	do {
	    c = *yyInput++;
	    if (c == '\0')
		return c;
	    if (c == '(')
		Count++;
	    else if (c == ')')
		Count--;
	} while (Count > 0);
    }
}


double juldate();

/* Return the MJD as a double.
 */
double mjd(p, now, gmt)
    char		*p;
    double		 now;
    int			 gmt;
{
    double		Start;

    int	day, month, year, hour, min, sec;
    time_t unx;

    localtime(&unx);

    yyInput = p;

    yyMJD	= 0;
    yyNow	= 0;
    yyYear 	= 0;
    yyMonth 	= 0;
    yyDay 	= 0;
    yyTimezone 	= gmt ? 0 : TZX() / 60L;	/* In minutes	*/
    yyDSTmode  	= gmt ? DSToff : DSTmaybe;
    yyHour 	= 0;
    yyMinutes 	= 0;
    yySeconds 	= 0;
    yyMeridian 	= MER24;


    yyRelSeconds = 0;
    yyRelMonth 	= 0;

    yyHaveMJD	= 0;
    yyHaveDate 	= 0;
    yyHaveDay 	= 0;
    yyHaveRel 	= 0;
    yyHaveTime 	= 0;
    yyHaveZone 	= 0;

    if (yyparse()
     || yyHaveMJD > 1 || yyHaveTime > 1 || yyHaveZone > 1 || yyHaveDate > 1 || yyHaveDay > 1) {
	return -1;
    }

    if ( yyHaveMJD ) {
	return yyMJD;
    }

    if ( yyMonth > 12 ) {
	return -1;
    }

    if ( now == -1 ) {
	struct timeval date;
	struct timezone tz;

	gettimeofday(&date, &tz);

	now = date.tv_sec + date.tv_usec / 1000000.0;
	now = UNIXTIMEtoMJD(now);
    }

    if ( yyHaveDate ) {
	Start = Convert(yyMonth, yyDay, yyYear, yyHour, yyMinutes, yySeconds,
		    yyMeridian, yyDSTmode);
    } else {
	if ( yyNow ) {
	    Start = now;
	} else {
	    Start = (int) now;

	    if ( yyHaveTime || yyHaveDay ) {
		Start += ToTOD(yyHour, yyMinutes, yySeconds, yyMeridian);
	    }
	}
    }


    if ( Start < 0 ) return -1;

    Start += ((double) yyRelSeconds) / SECSPERDAY;

    if ( yyRelMonth ) 
	if ( Start < MJD1970 || Start > MJD2038 ) return -1;
    	else
	    Start += RelativeMonth(Start, yyRelMonth);

    if (yyHaveDay && !yyHaveDate) {
	if ( Start < MJD1970 || Start > MJD2038 ) return -1;
	else
	    Start += RelativeDate(Start, yyDayOrdinal, yyDayNumber);
    }

    return Start;
}

struct tm *breakmjd(mjd, tm)
    double	mjd;
    struct tm	*tm;
{
    double	hour;
    double	min;
    int		yjd;
    int		j;

    /* MJD % 7 tells the day of the week
       (4=Sunday, 5=Monday, 6=Tuesday, 0=Wednesday, ...)  */

    caldate(mjd, &tm->tm_year, &tm->tm_mon, &tm->tm_mday, &hour);
    yjd = juldate(tm->tm_year, 1, 1);

    tm->tm_year -= 1900;
    tm->tm_mon--;

    tm->tm_hour = (int) hour + 0.5;
           min  =       (hour - tm->tm_hour) * 60;
    tm->tm_min  = (int)  min + 0.5;
    tm->tm_sec  =      ((min  - tm->tm_min)  * 60) + 0.5;
    tm->tm_wday = ((int) (mjd + 3) % 7) - 1;
    tm->tm_yday = (int)  (mjd - yjd)    - 1;  
    tm->tm_isdst = 0; 

    if ( tm->tm_sec >= 60 ) { tm->tm_sec = 0; tm->tm_min++;  }
    if ( tm->tm_min >= 60 ) { tm->tm_min = 0; tm->tm_hour++; }

    return tm;
}


char *cal(buffer, max, mjd, format)
	char	*buffer;
	int	 max;
	double	 mjd;
	char	*format;
{
	struct   tm tstc;
	struct   tm*tstp = &tstc;

	if ( !format ) format = "%b %e %T %Y";

	{
		int	 iy, im, id, j;
		double	 fd;

	    tstc.tm_mday = -1;
	    tstc.tm_wday = -1;
	    tstc.tm_yday = -1;

	    caldate(mjd, &iy, &im, &id, &fd);

	    tstc.tm_year = iy - 1900;
	    tstc.tm_mon  = im - 1;
	    tstc.tm_mday = id;
	    tstc.tm_hour =  ((int) fd / 24) * 24;
	    tstc.tm_min  = (((int) ((fd - tstc.tm_hour) / 60) * 60) + .5);
	    tstc.tm_sec  = ((int) (((fd - (tstc.tm_hour + tstc.tm_min))
			    / 60 * 60 ) * 60 * 60) + .5);
	    if ( tstc.tm_sec >= 60 ) { tstc.tm_sec = 0; tstc.tm_min++;  }
	    if ( tstc.tm_min >= 60 ) { tstc.tm_min = 0; tstc.tm_hour++; }

	    tstc.tm_isdst = 0;

	    breakmjd(mjd, &tstc);
	}

	strftime(buffer, max, format, tstp);

	return buffer;
}
