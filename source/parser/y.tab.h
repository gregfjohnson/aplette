/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    compile_immed = 258,
    compile_quad_input = 259,
    compile_function_defn = 260,
    compile_function_prolog = 261,
    compile_function_epilog = 262,
    compile_function_body = 263,
    lpar = 264,
    rpar = 265,
    lbkt = 266,
    rbkt = 267,
    eol = 268,
    unk = 269,
    dell = 270,
    null = 271,
    dot = 272,
    colon = 273,
    semi = 274,
    comnt = 275,
    tran = 276,
    strng = 277,
    nam = 278,
    numb = 279,
    nfun = 280,
    mfun = 281,
    dfun = 282,
    com = 283,
    com0 = 284,
    q_var = 285,
    asg = 286,
    comnam = 287,
    comnull = 288,
    comlist = 289,
    comExpr = 290,
    comExprOrNull = 291,
    dscal = 292,
    mdscal = 293,
    m = 294,
    d = 295,
    md = 296,
    msub = 297,
    mdsub = 298
  };
#endif
/* Tokens.  */
#define compile_immed 258
#define compile_quad_input 259
#define compile_function_defn 260
#define compile_function_prolog 261
#define compile_function_epilog 262
#define compile_function_body 263
#define lpar 264
#define rpar 265
#define lbkt 266
#define rbkt 267
#define eol 268
#define unk 269
#define dell 270
#define null 271
#define dot 272
#define colon 273
#define semi 274
#define comnt 275
#define tran 276
#define strng 277
#define nam 278
#define numb 279
#define nfun 280
#define mfun 281
#define dfun 282
#define com 283
#define com0 284
#define q_var 285
#define asg 286
#define comnam 287
#define comnull 288
#define comlist 289
#define comExpr 290
#define comExprOrNull 291
#define dscal 292
#define mdscal 293
#define m 294
#define d 295
#define md 296
#define msub 297
#define mdsub 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "apl.y" /* yacc.c:1909  */

    char   *charptr;
    char   charval;

#line 145 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
