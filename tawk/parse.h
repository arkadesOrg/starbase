/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UNEXPECTED = 258,
     BAD_DECIMAL = 259,
     NL = 260,
     SEMI_COLON = 261,
     LBRACE = 262,
     RBRACE = 263,
     LBOX = 264,
     RBOX = 265,
     COMMA = 266,
     IO_OUT = 267,
     POW_ASG = 268,
     MOD_ASG = 269,
     DIV_ASG = 270,
     MUL_ASG = 271,
     SUB_ASG = 272,
     ADD_ASG = 273,
     ASSIGN = 274,
     COLON = 275,
     QMARK = 276,
     OR = 277,
     AND = 278,
     IN = 279,
     MATCH = 280,
     GTE = 281,
     GT = 282,
     LTE = 283,
     LT = 284,
     NEQ = 285,
     EQ = 286,
     CAT = 287,
     GETLINE = 288,
     MINUS = 289,
     PLUS = 290,
     MOD = 291,
     DIV = 292,
     MUL = 293,
     UMINUS = 294,
     NOT = 295,
     PIPE = 296,
     IO_IN = 297,
     POW = 298,
     INC_or_DEC = 299,
     FIELD = 300,
     DOLLAR = 301,
     RPAREN = 302,
     LPAREN = 303,
     DOUBLE = 304,
     STRING_ = 305,
     RE = 306,
     ID = 307,
     D_ID = 308,
     FUNCT_ID = 309,
     BUILTIN = 310,
     LENGTH = 311,
     PRINT = 312,
     PRINTF = 313,
     SPLIT = 314,
     MATCH_FUNC = 315,
     SUB = 316,
     GSUB = 317,
     DO = 318,
     WHILE = 319,
     FOR = 320,
     BREAK = 321,
     CONTINUE = 322,
     IF = 323,
     ELSE = 324,
     DELETE = 325,
     BEGIN = 326,
     END = 327,
     EXIT = 328,
     NEXT = 329,
     RETURN = 330,
     FUNCTION = 331,
     LOAD = 332
   };
#endif
/* Tokens.  */
#define UNEXPECTED 258
#define BAD_DECIMAL 259
#define NL 260
#define SEMI_COLON 261
#define LBRACE 262
#define RBRACE 263
#define LBOX 264
#define RBOX 265
#define COMMA 266
#define IO_OUT 267
#define POW_ASG 268
#define MOD_ASG 269
#define DIV_ASG 270
#define MUL_ASG 271
#define SUB_ASG 272
#define ADD_ASG 273
#define ASSIGN 274
#define COLON 275
#define QMARK 276
#define OR 277
#define AND 278
#define IN 279
#define MATCH 280
#define GTE 281
#define GT 282
#define LTE 283
#define LT 284
#define NEQ 285
#define EQ 286
#define CAT 287
#define GETLINE 288
#define MINUS 289
#define PLUS 290
#define MOD 291
#define DIV 292
#define MUL 293
#define UMINUS 294
#define NOT 295
#define PIPE 296
#define IO_IN 297
#define POW 298
#define INC_or_DEC 299
#define FIELD 300
#define DOLLAR 301
#define RPAREN 302
#define LPAREN 303
#define DOUBLE 304
#define STRING_ 305
#define RE 306
#define ID 307
#define D_ID 308
#define FUNCT_ID 309
#define BUILTIN 310
#define LENGTH 311
#define PRINT 312
#define PRINTF 313
#define SPLIT 314
#define MATCH_FUNC 315
#define SUB 316
#define GSUB 317
#define DO 318
#define WHILE 319
#define FOR 320
#define BREAK 321
#define CONTINUE 322
#define IF 323
#define ELSE 324
#define DELETE 325
#define BEGIN 326
#define END 327
#define EXIT 328
#define NEXT 329
#define RETURN 330
#define FUNCTION 331
#define LOAD 332



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 64 "parse.y"

CELL *cp ;
SYMTAB *stp ;
int  start ; /* code starting address as offset from code_base */
PF_CP  fp ;  /* ptr to a (print/printf) or (sub/gsub) function */
BI_REC *bip ; /* ptr to info about a builtin */
FBLOCK  *fbp  ; /* ptr to a function block */
ARG2_REC *arg2p ;
CA_REC   *ca_p  ;
int   ival ;
PTR   ptr ;


/* Line 2053 of yacc.c  */
#line 225 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
