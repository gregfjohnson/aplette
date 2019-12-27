/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 8 "apl.y" /* yacc.c:339  */

#include "memory.h"
#include "debug.h"
#include "local_parser.h"
#include "opt_codes.h"
#include "data.h"

#line 74 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
    lex0 = 258,
    lex1 = 259,
    lex2 = 260,
    lex3 = 261,
    lex4 = 262,
    lex5 = 263,
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
#define lex0 258
#define lex1 259
#define lex2 260
#define lex3 261
#define lex4 262
#define lex5 263
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
#line 17 "apl.y" /* yacc.c:355  */

    char   *charptr;
    char   charval;

#line 205 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 222 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    64,    71,    80,    88,    92,    98,   101,
     104,   107,   110,   114,   135,   146,   152,   178,   202,   222,
     237,   244,   250,   251,   252,   256,   257,   260,   264,   270,
     276,   289,   293,   297,   301,   302,   305,   306,   309,   315,
     321,   326,   333,   336,   337,   340,   343,   347,   350,   356,
     357,   361,   367,   368,   377,   381,   385,   464,   470,   474,
     481,   485,   491,   502,   509,   510,   517,   518,   525,   530,
     535,   539,   545,   553,   554,   555,   561,   562,   569,   574,
     579,   583,   589,   598,   607,   614,   614,   617,   617,   617,
     617,   617,   617,   620,   620,   623,   623,   623,   626,   626,
     629,   629,   629,   629
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "lex0", "lex1", "lex2", "lex3", "lex4",
  "lex5", "lpar", "rpar", "lbkt", "rbkt", "eol", "unk", "dell", "null",
  "dot", "colon", "semi", "comnt", "tran", "strng", "nam", "numb", "nfun",
  "mfun", "dfun", "com", "com0", "q_var", "asg", "comnam", "comnull",
  "comlist", "comExpr", "comExprOrNull", "dscal", "mdscal", "m", "d", "md",
  "msub", "mdsub", "$accept", "line", "func", "header", "args", "autos",
  "bcomand", "comand", "exprOrNull", "anylist", "fstat", "labels", "label",
  "fstat0", "stat", "statement", "hprint", "output", "hsemi", "expr", "e1",
  "e2", "vector", "number", "lsub", "subs", "sub", "monadic", "monad",
  "smonad", "dyadic", "sdyad", "subr", "comp", "dyad", "mdcom", "mondya",
  "scalar", "anyname", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF -81

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-81)))

#define YYTABLE_NINF -103

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,     8,   169,    -9,    -7,     5,    66,    27,   169,   -81,
     -81,    45,   125,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -15,   -81,   -81,    49,    54,    20,   -81,    56,   -81,    58,
     186,    67,   -81,    60,   169,   -81,    69,   -81,    -4,   -81,
      45,    45,    45,   -81,    81,   147,    64,    77,    80,   -81,
     -81,   103,   -81,   -81,   -81,    83,   -81,    75,   -81,   -81,
     -81,   -81,   -81,     9,   -16,   -81,    86,    45,   -81,    45,
     169,   169,    89,   -81,   -81,   169,    96,   -81,    95,   -81,
     -81,    98,   -81,   106,   169,    69,   -81,   -81,   -81,   101,
     -81,   169,   -81,   -81,   169,   -81,    69,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   107,   -81,   -81,   -81,   -81,   -81,
     -81,    99,   -81,    45,    45,   -81,   -81,    45,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,    58,    -2,   -81,   -81,    -2,
     -81,     0,   -81,   109,   -81,   -81,     9,   -81,    45,   -81,
     -81,   -81,   -81,   -81,   -81,   169,   -81,   -81,   -81
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
       3,     0,     0,    56,    55,    62,    54,    70,    59,    99,
      95,    73,    96,    74,    97,     0,     2,     0,    44,    43,
      49,    52,    57,    61,     0,    68,     0,    75,     0,     8,
       0,     0,     0,    32,     0,     0,    55,    54,    70,   103,
      12,     0,    36,    35,    39,     0,     1,     0,   100,   101,
     102,     5,    14,     0,    18,     6,     0,     0,    26,     0,
       0,    28,     0,    42,    48,     0,     0,    80,    92,    90,
      91,    88,    89,    97,     0,     0,    78,    83,    87,     0,
      63,    67,    60,    50,     0,    69,    85,    86,    71,     9,
      10,    11,    31,    40,     0,    33,    37,    34,    38,    58,
      20,     0,    15,     0,    17,     7,    24,    25,    30,    23,
      22,    27,     4,    47,    45,    46,     0,    51,    79,     0,
      66,     0,    64,     0,    72,    41,     0,    13,    18,    16,
      29,    98,    81,    82,    53,    67,    84,    19,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,    17,     6,   -81,   -13,   -81,   -81,   -81,   -81,
     -81,   -81,    85,    88,    72,   -81,    57,   -81,   -81,    -8,
     -81,   -81,   110,   -81,   -81,   -81,   -14,   -81,   -81,   -81,
     -81,   -81,   -80,   -81,   -81,   -81,   122,   -29,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,    61,    62,    63,   112,    25,    72,   120,   117,
      50,    51,    52,    53,    54,    27,    28,   124,    75,    29,
      30,    31,    32,    33,    91,   131,   132,    34,    35,    36,
      84,    85,    95,    98,    86,    87,    37,    38,    64
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    89,   -98,    55,    66,   128,    40,    58,    41,    59,
      60,    49,   144,   -98,   -98,   113,   134,     8,     9,   145,
      42,    10,   110,    11,    96,    97,    93,    56,   111,    12,
      13,    14,    15,    16,    17,    19,   141,   104,    18,     1,
       2,     3,     4,     5,     6,    19,    20,    21,    55,    22,
      23,    24,    67,    68,    69,    70,    71,    99,   100,   101,
     -76,   114,   119,   121,   116,   -77,   118,   125,    58,    73,
      59,    60,    49,    26,    39,     8,   127,    74,    90,    43,
      94,    44,  -100,   130,    15,   109,   133,    45,    13,    46,
      15,    47,    48,    49,   102,  -101,    18,   142,  -102,   115,
     143,   108,   122,    19,    20,    21,   -94,    22,    23,    24,
     138,   139,     8,   126,   140,   -99,   105,   -93,   129,   137,
     135,   146,   136,   147,    45,    13,    46,    15,    47,    48,
      49,   148,   123,    18,     8,   114,   106,   130,    65,   107,
      19,    20,    21,    92,    22,    23,    24,    13,    14,    15,
      16,    17,    88,     0,     0,    18,     8,     0,     0,     0,
     103,     0,    19,    20,    21,     0,    22,    23,    24,    13,
      14,    15,    16,    17,     0,     0,     0,    18,     8,     0,
       0,     0,     0,     0,    19,    20,    21,     0,    22,    23,
      24,    13,    14,    15,    16,    17,     0,     0,     0,    18,
       0,     0,    76,     0,     0,     0,    19,    20,    21,     0,
      22,    23,    24,    77,    78,    79,     0,    80,     0,     0,
       0,     0,     0,    81,    20,     0,    82,    22,     0,    83
};

static const yytype_int16 yycheck[] =
{
       8,    30,    17,     6,    12,    85,    15,    23,    15,    25,
      26,    27,    12,    28,    29,    31,    96,     9,    10,    19,
      15,    13,    13,    15,    28,    29,    34,     0,    19,    21,
      22,    23,    24,    25,    26,    37,    38,    45,    30,     3,
       4,     5,     6,     7,     8,    37,    38,    39,    51,    41,
      42,    43,    32,    33,    34,    35,    36,    40,    41,    42,
      11,    64,    70,    71,    67,    11,    69,    75,    23,    13,
      25,    26,    27,     1,     2,     9,    84,    19,    11,    13,
      11,    15,    18,    91,    24,    10,    94,    21,    22,    23,
      24,    25,    26,    27,    13,    18,    30,   126,    18,    13,
     129,    18,    13,    37,    38,    39,    11,    41,    42,    43,
     113,   114,     9,    17,   117,    17,    13,    11,    17,   113,
      13,    12,    23,   136,    21,    22,    23,    24,    25,    26,
      27,   145,    75,    30,     9,   138,    51,   145,    13,    51,
      37,    38,    39,    33,    41,    42,    43,    22,    23,    24,
      25,    26,    30,    -1,    -1,    30,     9,    -1,    -1,    -1,
      13,    -1,    37,    38,    39,    -1,    41,    42,    43,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,     9,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    -1,    41,    42,
      43,    22,    23,    24,    25,    26,    -1,    -1,    -1,    30,
      -1,    -1,    16,    -1,    -1,    -1,    37,    38,    39,    -1,
      41,    42,    43,    27,    28,    29,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    41,    -1,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    45,     9,    10,
      13,    15,    21,    22,    23,    24,    25,    26,    30,    37,
      38,    39,    41,    42,    43,    50,    58,    59,    60,    63,
      64,    65,    66,    67,    71,    72,    73,    80,    81,    58,
      15,    15,    15,    13,    15,    21,    23,    25,    26,    27,
      54,    55,    56,    57,    58,    82,     0,    63,    23,    25,
      26,    46,    47,    48,    82,    13,    63,    32,    33,    34,
      35,    36,    51,    13,    19,    62,    16,    27,    28,    29,
      31,    37,    40,    43,    74,    75,    78,    79,    80,    81,
      11,    68,    66,    63,    11,    76,    28,    29,    77,    46,
      46,    46,    13,    13,    63,    13,    56,    57,    18,    10,
      13,    19,    49,    31,    82,    13,    82,    53,    82,    63,
      52,    63,    13,    60,    61,    63,    17,    63,    76,    17,
      63,    69,    70,    63,    76,    13,    23,    47,    82,    82,
      82,    38,    81,    81,    12,    19,    12,    49,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    46,    46,    47,    48,    48,    48,    49,
      49,    50,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    54,    54,    55,    55,    56,    57,
      57,    57,    58,    59,    59,    60,    61,    61,    62,    63,
      63,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    68,    69,    69,    70,    70,    71,    71,
      71,    71,    71,    72,    72,    72,    73,    73,    74,    74,
      74,    74,    74,    75,    76,    77,    77,    78,    78,    78,
      78,    78,    78,    79,    79,    80,    80,    80,    81,    81,
      82,    82,    82,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     4,     3,     3,     4,     2,     3,
       3,     3,     2,     3,     1,     2,     3,     2,     1,     3,
       1,     1,     2,     2,     2,     2,     1,     1,     0,     2,
       1,     2,     1,     2,     2,     1,     1,     2,     2,     1,
       2,     3,     2,     1,     1,     3,     1,     1,     1,     1,
       2,     3,     1,     4,     1,     1,     1,     1,     3,     1,
       2,     1,     1,     1,     1,     3,     1,     0,     1,     2,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 53 "apl.y" /* yacc.c:1646  */
    {
        *ccharp = END;
        integ = lastCode(oline);
        if (integ != ASGN && integ != PRINT && integ != COMNT) *ccharp++ = PRINT;
        *ccharp++ = EOL;
    }
#line 1431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 65 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = COMNT;
        *ccharp++ = EOL;
    }
#line 1440 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 72 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = IMMED;
        *ccharp++ = (yyvsp[-1].charval);
    }
#line 1449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 81 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = IMMED;
        /* *ccharp++ = EDITF; */
        *ccharp++ = DELL;
    }
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 89 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = SICLR0;
    }
#line 1467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = SICLR;
    }
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 115 "apl.y" /* yacc.c:1646  */
    {
        switch(context) {

        case lex3:
            name((yyval.charptr), AUTO);
            /* see comments in funcomp() concerning
             * label processing.
             */
            *ccharp++ = ELID;
            break;

        case lex4:
            ccharp2 = ccharp;
            *ccharp++ = EOL;
            name((yyval.charptr), RVAL);
            name((yyval.charptr), REST);
            invert((yyvsp[0].charptr), ccharp2);
        }
    }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 136 "apl.y" /* yacc.c:1646  */
    {
        if(context == lex3) *ccharp++ = ELID;

        if(context == lex4){
            *ccharp++ = EOL;      /* pop previous result */
            *ccharp++ = NILRET;   /* return empty result */
        }
    }
#line 1512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 147 "apl.y" /* yacc.c:1646  */
    {
        if (context == lex4) invert((yyval.charptr), (yyvsp[0].charptr));
    }
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 153 "apl.y" /* yacc.c:1646  */
    {
        switch(context) {

        case lex0:
            name((yyvsp[-1].charptr), NAME);
            break;

        case lex2:
            (yyval.charptr) = ccharp;
            name((yyvsp[-1].charptr), DF);
            break;

        case lex3:
            (yyval.charptr) = ccharp;
            name((yyvsp[0].charptr), ARG2);
            name((yyvsp[-2].charptr), ARG1);
            break;

        case lex4:
            (yyval.charptr) = ccharp;
            name((yyvsp[-2].charptr), REST);
            name((yyvsp[0].charptr), REST);
        }
    }
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 179 "apl.y" /* yacc.c:1646  */
    {
        switch(context) {

        case lex0:
            name((yyvsp[-1].charptr), NAME);
            break;

        case lex2:
            (yyval.charptr) = ccharp;
            name((yyvsp[-1].charptr), MF);
            break;

        case lex3:
            (yyval.charptr) = ccharp;
            name((yyvsp[0].charptr), ARG1);
            break;

        case lex4:
            (yyval.charptr) = ccharp;
            name((yyvsp[0].charptr), REST);
        }
    }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 203 "apl.y" /* yacc.c:1646  */
    {
        switch(context) {

        case lex0:
            name((yyval.charptr), NAME);
            break;

        case lex2:
            name((yyval.charptr), NF);
            /* no break, fall through to lex3/4 */

        case lex3:
        case lex4:
            (yyval.charptr) = ccharp;
            break;
        }
    }
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 223 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[0].charptr);

        switch(context) {
            case lex3:
                name((yyvsp[-1].charptr), AUTO);
                break;

            case lex4:
                ccharp2 = name((yyvsp[-1].charptr), REST);
                invert((yyval.charptr), ccharp2);
        }
    }
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 238 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
    }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 245 "apl.y" /* yacc.c:1646  */
    {
        litflag = -1;
    }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 253 "apl.y" /* yacc.c:1646  */
    {
        name((yyvsp[0].charptr), NAME);
    }
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 261 "apl.y" /* yacc.c:1646  */
    {
        exprOrNullFlag = 1;
    }
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 264 "apl.y" /* yacc.c:1646  */
    {
        exprOrNullFlag = 0;
    }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 271 "apl.y" /* yacc.c:1646  */
    {
       *ccharp++ = IMMED;
       *ccharp++ = immedcmd;
       name((yyvsp[0].charptr), NAME);
    }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 277 "apl.y" /* yacc.c:1646  */
    {
       name((yyvsp[0].charptr), NAME);
    }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 290 "apl.y" /* yacc.c:1646  */
    {  
        *ccharp++ = COMNT;
    }
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 294 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = COMNT;
    }
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 298 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = COMNT;
    }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 310 "apl.y" /* yacc.c:1646  */
    {
        if(labgen) genlab((SymTabEntry *) (yyvsp[-1].charptr));
    }
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 316 "apl.y" /* yacc.c:1646  */
    {
        *ccharp = END;
        integ = lastCode(oline);
        if (integ != ASGN && integ != PRINT && integ != COMNT) *ccharp++ = PRINT;
    }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 322 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = BRAN0;
    }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 327 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[-1].charptr);
        *ccharp++ = BRAN;
    }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 344 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = PRINT;
    }
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 351 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = HPRINT;
    }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 358 "apl.y" /* yacc.c:1646  */
    {
        invert((yyval.charptr), (yyvsp[0].charptr));
    }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 362 "apl.y" /* yacc.c:1646  */
    {
        invert((yyval.charptr), (yyvsp[0].charptr));
    }
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 369 "apl.y" /* yacc.c:1646  */
    {
        invert((yyval.charptr), (yyvsp[-1].charptr));
        *ccharp++ = INDEX;
        *ccharp++ = scount;
        scount = (yyvsp[-2].charval);
    }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 378 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = name((yyval.charptr), FUN);
    }
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 382 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = name((yyval.charptr), NAME);
    }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 386 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        ccharp += 2;
        integ = iline[-1];
        vcount = 0;
        for(;;) {
            if (*iline == '\n') {
                nlexsym = unk;
                break;
            }
            if (*iline == '\\') {
                char temp, sum;
                int dcount;
                iline++;
                switch (*iline) {
                    case 'b':
                    temp = '\b';
                    break;

                    case 't':
                    temp = '\t';
                    break;

                    case 'n':
                    temp = '\n';
                    break;

                    case 'e':
                    temp = '\033';
                    break;

                    case 'f':
                    temp = '\014';
                    break;

                    case 'r':
                    temp = '\r';
                    break;

                    default:
                    temp = *iline;
                    if (temp == '\n') continue;
                    if (isodigit(temp)) {
                        dcount = 0;
                        sum = 0;
                        while (isodigit(temp) && dcount < 3) {
                            sum = 8 * sum + (temp - '0');
                            dcount++;
                            iline++;
                            temp = *iline;
                        }
                        if (temp == '\n') continue;
                        temp = sum;
                        iline--;
                    }
                    break;
                }
                *ccharp++ = temp;
                iline++;
                vcount++;
                continue;
            }
            if( *iline == integ) {
                iline++;
                if(*iline != integ) break;
            }
            *ccharp++ = *iline++;
            vcount++;
        }
        *ccharp++ = (char)0;    /* null termination */
        vcount++;
        /* if you can figure out some way to do this without
       * vcount, please do so!
       * then fix execute() and code_dump()
       */
        ((struct chrstrct *)(yyval.charptr))->c[0] = QUOT;
        ((struct chrstrct *)(yyval.charptr))->c[1] = vcount;
    }
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 465 "apl.y" /* yacc.c:1646  */
    {
        *ccharp++ = CONST;
        *ccharp++ = vcount;
        invert((yyval.charptr), ccharp-2);
    }
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 471 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[-1].charptr);
    }
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 475 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = (yyvsp[0].charval);
    }
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 482 "apl.y" /* yacc.c:1646  */
    {
        vcount++;
    }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 486 "apl.y" /* yacc.c:1646  */
    {
        vcount = 1;
    }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 492 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        ccharp += copy(DA, (char *) &datum, (char *) ccharp, 1);
    }
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 503 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charval) = scount;
        scount = 1;
    }
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 511 "apl.y" /* yacc.c:1646  */
    {
        invert((yyval.charptr), (yyvsp[0].charptr));
        scount++;
    }
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 518 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = ELID;
    }
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 526 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = (yyvsp[0].charval);
    }
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 531 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[0].charptr);
        *ccharp++ = (yyvsp[-1].charval)+1;
    }
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 536 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = name((yyval.charptr), FUN);
    }
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 540 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = (yyvsp[0].charval)+1;
        *ccharp++ = (yyvsp[-1].charval);
    }
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 546 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[0].charptr);
        *ccharp++ = (yyvsp[-1].charval)+3;
        *ccharp++ = (yyvsp[-2].charval);
    }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 556 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charval)++;
    }
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 563 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charval) += 2;
    }
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 570 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = (yyvsp[0].charval);
    }
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 575 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[0].charptr);
        *ccharp++ = (yyvsp[-1].charval);
    }
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 580 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = name((yyval.charptr), FUN);
    }
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 584 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = OPROD;
        *ccharp++ = (yyvsp[0].charval);
    }
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 590 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = ccharp;
        *ccharp++ = IPROD;
        *ccharp++ = (yyvsp[-2].charval);
        *ccharp++ = (yyvsp[0].charval);
    }
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 599 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charval) += 2;
    }
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 608 "apl.y" /* yacc.c:1646  */
    {
        (yyval.charptr) = (yyvsp[-1].charptr);
    }
#line 2080 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2084 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 631 "apl.y" /* yacc.c:1906  */

