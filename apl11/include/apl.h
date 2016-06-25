/* Copyright U S WEST Advanced Technologies, Inc. (AT&T)
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#ifndef APL_H
#define APL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <setjmp.h>
#include <values.h>
#include <stdio.h>
#include <string.h>

/* Temp file names */
#define WSFILE   ws_file                /* work space file */

/* Magic Numbers */
#define NFDS        20                  /* Number of available file descriptors */
#define MRANK        8                  /* maximum rank, ie number of dimensions */
#define STKS       500                  /* stack size */
#define SYM_TAB_MAX        200                  /* number of local symbols, 
                                         * ie varables and user functions, see symbolTable[SYM_TAB_MAX] */
#define NAMS        40                  /* maximum size of variable and user function names */
#define OBJS       500                  /* space provided for p-code */
#define MAXLAB     100                  /* maximum number of labels in one function */
#define LINEMAX    200                  /* length of line typed at the keyboard */

/* The basic type of float data in apl11 */
#define data   double

/* derived constants */
#define SDAT    sizeof(data)
#define SINT     sizeof(int)
#define MAXEXP           709            /* the largest value such that exp(MAXEXP) is OK */
#define MINdata    MINDOUBLE
#define MAXdata    MAXDOUBLE

#define INITIAL_tolerance    1.0e-13
data tolerance;

#define INITIAL_iorigin      1
int iorigin;

#define INITIAL_pagewidth   72
int pagewidth;

#define INITIAL_PrintP       9
int PrintP;

#define quote_quad_limit    40
char quote_quad_prompt[quote_quad_limit+1];

struct chrstrct {
   char c[2];
};

/* Global storage for the last reported Error Message */
struct {
   int type;
   int maxlength;
   int caret;
   char diagnostic[80];                 /* these oversize fixed length arrays will be */
   char iline[LINEMAX];                 /* used to store dynamic strings */
} error_message;

data      zero;
data      one;
data      pi;
data      datum;
data      getdat();
int       funtrace;                     /* function trace enabled */
int       labgen;                       /* label processing being done */
jmp_buf   cold_restart;                 /* Used for setexit/reset */
jmp_buf   hot_restart;                  /* Used for setexit/reset */

//jmp_buf    gbl_env;                   /* Used for setexit/reset */
//jmp_buf    mainloop_return;
//jmp_buf    reset_env;

/* Error Types
 * Any additions to this list must be dealt with at errors.c
 */
#define    ERR               0          /* code 0 for miscellaneous errors */
#define    ERR_axis          1          /* codes 1 to 10 are consistent */
#define    ERR_domain        2          /* with the standard */
#define    ERR_implicit      3
#define    ERR_index         4
#define    ERR_length        5
#define    ERR_limit         6
#define    ERR_rank          7
#define    ERR_syntax        8
#define    ERR_value         9
#define    ERR_interrupt    10
#define    ERR_botch        11          /* special codes for this implementation */
#define    ERR_security     12

/* Quad Variable action codes */
//#define QV_reset           0
#define QV_source            0
#define QV_sink              1
//#define QV_push            3
//#define QV_pop             4


/* Data types
 * Each new type should be accomodated for in several places including:
 * memory/dealloc()
 * save and load
 * print
 */

#define    DA      1                     /* floating point data */
#define    CH      2                     /* character data */
#define    LV      3                     /* Local Variable */
#define    QD      4
#define    QQ      5
#define    IN      6
#define    EL      7
#define    NF      8                     /* niladic function */
#define    MF      9                     /* monadic function */
#define    DF     10                     /* dyadic function */
#define    QC     11
#define    QV     12                     /* quad variables */
#define    NIL    13                     /* Used where a user defined function does
                                          * not return a value. */
#define    QX     14                     /* latent expr. quad LX  */
#define    LBL    15                     /* locked label value */
#define    NTYPES 16                     /* number of defined types */

/*
 * This is a descriptor for apl data, 
 * allocated by newdat(), destroyed by pop()
 * The actual data is not part of this descriptor
 * not all types have an associated data space
 * See the comment in data/newdat() about "dim".
 *
 * A null item is a vector(!), and is rank==1, size==0.
 *
 * the stack is the operand stack, and sp is the pointer to the
 * top of the stack.
 */

struct item {
   int    rank;
   int    type;
   int    size;
   int    index;
   data*  datap;
   int    dim[MRANK];
} *stack[STKS], **sp;

/*
 * variable/fn (and file name) descriptor block.
 * contains useful information about all LVs.
 * Also kludged up to handle file names (only symbolTable.namep 
 * is then used.)
 *
 * For fns, symbolTable.itemp is an array of pointers to character
 * strings which are the compiled code for a line of the fn.
 * (Itemp == 0) means that the fn has not yet been compiled .
 * symbolTable.itemp[0] == the number of lines in the fn, and
 * symbolTable.itemp[1] == the function startup code, and
 * symbolTable.itemp[max] == the close down shop code.
 */

typedef struct {
   int          use;
   int          type;
   struct item* itemp;
   char*        namep;
   int          label;
} SymTabEntry;

SymTabEntry symbolTable[SYM_TAB_MAX];

/* The context structure
 * pointed to by the State Indicator
 * Refer to the DESIGN file in apl11/main
 */

struct Context {
    struct Context* prev;               /* previous */
    int             suspended;          /* suspended == 1, otherwise == 0 */

    enum Mode {                         /* Mode can only be one of the following: */
        immed,                          /*     immediate execution */
        exec,                           /*     execute */
        quadinp,                        /*     quad input */
        deffun                          /*     defined function */
    } Mode;

    char*           text;               /* input line, plain text */
    char*           pcode;              /* pseudo code */
    char*           xref;               /* cross reference text vs pcode */
    char*           ptr;                /* pointer to current token in pcode */
    SymTabEntry*    np;                 /* current fn vital stats. */
    int             funlc;              /* current fn current line number */
    struct item**   sp;                 /* top of operand stack upon fn entry */
    jmp_buf         env;                /* for restoration of local fn activation record */
} *gsip, prime_context;

/*
 * exop[i] is the address of the i'th action routine.
 * Because of a "symbol table overflow" problem with C,
 * the table was moved to utility/optable.c
 */

extern int (*exop[])();

double ltod();
char   *compile();
SymTabEntry *nlook();
struct item *fetch(), *fetch1(), *fetch2(), *extend();
struct item *newdat(), *dupdat();

int    integ;
int    signgam;
int    column;
int    intflg;
int    echoflg;
int    sandbox;                         /* when set, some functions are barred */
int    sandboxflg;                      /* when set, sandbox cannot be unset */
int    use_readline;                    /* shows that the user has a valid .inputrc */
int    ascii_characters;                /* use 7-bit ascii and map to APL characters */
int    ifile;
int    wfile;
int    ttystat[3];
long   startTime;
int    rowsz;
int    oldlb[MAXLAB];
int    pt;
int    syze;
int    pas1;
int    protofile;
int    lastop;                          /* last (current) operator exec'ed */
char   *scr_file;                       /* scratch file name */
char   *ws_file;                        /* apl workspace file */
int    lineNumber;
int    normalExit;
int    mkcore;

/* diagnostics */
int    code_trace;
int    mem_trace;
int    stack_trace;
int    vars_trace;

typedef struct {
   int    rank;
   int    type;
   int    size;
   int    dimk;
   int    delk;
   int    dim[MRANK];
   int    del[MRANK];
   int    idx[MRANK];
   char   complete;
} DataIterator;

DataIterator idx;

#define setexit()      setjmp(gbl_env)        /* "setexit" equivalent      */
#define reset()        longjmp(gbl_env, 0)    /* "reset" equivalent        */
#define equal(a,b)     (0 == strcmp(a,b))     /* character string equality */

#define SECURITY_CHECK if ( sandbox ) error(ERR_security,"sand-box")

#endif   // APL_H
