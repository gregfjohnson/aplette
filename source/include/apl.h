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
#include <stdio.h>
#include <string.h>

/* Magic Numbers */
#define NFDS 20         /* Number of available file descriptors */
#define MRANK 8         /* maximum rank, ie number of dimensions */
#define STKS 500        /* stack size */
#define SYM_TAB_MAX 200 /* number of local symbols, \
                         * ie varables and user functions, see symbolTable[SYM_TAB_MAX] */
#define NAMS 40         /* maximum size of variable and user function names */
#define OBJS 500        /* space provided for p-code */
#define MAXLAB 100      /* maximum number of labels in one function */
#define LINEMAX 200     /* length of line typed at the keyboard */

/* The basic type of float data in apl11 */
#define data double

/* derived constants */
#define SDAT sizeof(data)
#define SINT sizeof(int)
#define SPTR sizeof(void*)

#ifndef MAXDOUBLE
    #define MAXDOUBLE 1.7976931348623157e+308
#endif

#ifndef MAX_NEGDOUBLE
    #define MAX_NEGDOUBLE (-MAXDOUBLE)
#endif

#ifndef MINFLOAT
    #define MINFLOAT 1.17549435e-38F
#endif

#ifndef MAXFLOAT
    #define MAXFLOAT 3.40282347e+38F
#endif

#define MAXEXP 709 /* the largest value such that exp(MAXEXP) is OK */
#define MINdata MAX_NEGDOUBLE
#define MAXdata MAXDOUBLE

#define INITIAL_tolerance 1.0e-13
extern data tolerance;

#define INITIAL_iorigin 1
extern int iorigin;

#define INITIAL_pagewidth 72
extern int pagewidth;

#define INITIAL_PrintP 9
extern int PrintP;

#define quote_quad_limit 40
extern char quote_quad_prompt[quote_quad_limit + 1];

typedef int (*VoidToIntFn)();
typedef data (*VoidToDataFn)();

struct chrstrct {
    char c[2];
};

/* Global storage for the last reported Error Message */
struct {
    int type;
    int maxlength;
    int caret;
    char diagnostic[80]; /* these oversize fixed length arrays will be */
    char iline[LINEMAX]; /* used to store dynamic strings */
} error_message;

data getdat();

extern data zero;
extern data one;
extern data pi;
extern data datum;
extern int funtrace;         /* function trace enabled */
extern int labgen;           /* label processing being done */
extern jmp_buf cold_restart; /* Used for setexit/reset */

//jmp_buf    gbl_env;                   /* Used for setexit/reset */
//jmp_buf    mainloop_return;
//jmp_buf    reset_env;

/* Error Types
 * Any additions to this list must be dealt with at errors.c
 */
#define ERR 0        /* code 0 for miscellaneous errors */
#define ERR_axis 1   /* codes 1 to 10 are consistent */
#define ERR_domain 2 /* with the standard */
#define ERR_implicit 3
#define ERR_index 4
#define ERR_length 5
#define ERR_limit 6
#define ERR_rank 7
#define ERR_syntax 8
#define ERR_value 9
#define ERR_interrupt 10
#define ERR_botch 11 /* special codes for this implementation */
#define ERR_security 12

/* Quad Variable action codes */
//#define QV_reset           0
#define QV_source 0
#define QV_sink 1
//#define QV_push            3
//#define QV_pop             4

/* Data types
 * Each new type should be accomodated for in several places including:
 * memory/dealloc()
 * save and load
 * print
 */

// newdat() allows only CH, DA, EL, NIL, and QV.
// these values are used in itemp->type.

// copy() mentions DA, IN, PTR, but does not fail if given something else.
//        if not DA, IN, PTR, it assumes 1-byte values (i.e., CH)

typedef enum { 
    UNKNOWN = 0,
    DA = 1,      /* floating point data */
    CH = 2,      /* character data */
    LV = 3,      /* Local Variable */
    IN = 6,      /* used only as first arg of copy(), for "integer type" */
    EL = 7,      /* indexed assignment stack marker */
    NF = 8,      /* niladic function */
    MF = 9,      /* monadic function */
    DF = 10,     /* dyadic function */
    QV = 12,     /* quad variables */
    NIL = 13,    /* Used where a user defined function does */
    QX  = 14,    /* latent expr. quad LX  */
    LBL = 15,    /* locked label value */
    PTR = 16,    /* generic pointer for copy() */
    NTYPES = 17, /* number of defined types */
} ItemType;

typedef enum {
    CompileImmediate,      //   0 compile immediate
    CompileQuadInput,      //   1 compile quad input
    CompileFunctionDefn,   //   2 function definition
    CompileFunctionProlog, //   3 function prolog
    CompileFunctionEpilog, //   4 function epilog
    CompileFunctionBody,   //   5 function body
} CompilePhase;

extern CompilePhase compilePhase;

/* NOTE:  The expression stack is a stack
 * of pointers.  It is declared to point to
 * "struct item"'s, but via pointer casting it
 * can also point at "SymTabEntry" structs.
 * It would be better to have each stack entry
 * be self-describing, with a field indicating
 * the type of object it describes, and then a
 * union of pointers to different types.
 *
 * I believe the itemType field at the start of
 * each record type unambiguously identifies the type
 * of the struct being pointed at.  itemType is "LV"
 * if and only if the struct is a SymTabEntry
 * struct.  Otherwise it is an item struct.
 */

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
    ItemType itemType;

    int rank;
    int size;
    int index;
    data* datap;
    int dim[MRANK];
};

struct _Context;

/*
 * variable/function (and file name) descriptor block.
 * contains useful information about all LVs.
 * Also kludged up to handle file names (only SymTab.namep 
 * is then used.)
 *
 * For fns, SymbolTable.functionLines[] is an array of pointers to character
 * strings which are the compiled code for lines of the fn.
 * SymTabEntry.functionLineCount == the number of lines in the body of the fn.
 * SymTabEntry.functionLineLength is the length of functionLines[].
 * SymTabEntry.functionLines[0] is the the function startup code, and
 * SymTabEntry.functionLines[1] .. SymTabEntry.functionLines[functionLineCount]
 *     are the lines in the body of the APL function.
 * SymTabEntry.functionLines[functionLineLength-1] is the
 *     "close down shop" epilog code.
 */

typedef struct {
    ItemType itemType;

    ItemType entryUse;
    struct item* itemp;
    char* namep;

    int label;
    int functionLineCount;
    int functionLineLength;
    struct _Context** functionLines;
    int sourceCodeCount;
    char **functionSourceCode;
} SymTabEntry;

struct item *stack[STKS], **sp;

/* The context structure
 * pointed to by the State Indicator
 * Refer to the DESIGN file in apl11/main
 */

typedef struct _Context {
    struct _Context* prev; /* previous */
    int suspended;        /* suspended == 1, otherwise == 0 */

    enum Mode {  /* Mode can only be one of the following: */
        immed,   /*     immediate execution */
        exec,    /*     execute */
        quadinp, /*     quad input */
        deffun   /*     defined function */
    } Mode;

    char* text;                /* input line, plain text */
    char* pcode;               /* pseudo code */
    char* ptr;                 /* pointer to current token in pcode */
    SymTabEntry* np;           /* current fn symbol table entry. */
    SymTabEntry** shadowedIds; /* list of shadowed identifiers */
    int shadowedIdSize;        /* size of the list */
    int shadowedIdCount;       /* length of the list */
    int funlc;                 /* current fn current line number */
    struct item** sp;          /* top of operand stack upon fn entry */
    jmp_buf env;               /* to restore local fn activation record */
} Context;

extern Context *gsip, prime_context;

/* exop[i] is the address of the i'th action routine.
 * Because of a "symbol table overflow" problem with C,
 * the table was moved to utility/optable.c
 */

extern int (*exop[])();

double ltod();
char* compile();
SymTabEntry* nlook();
struct item *fetch(), *fetch1(), *fetch2(), *extend();

extern int integ;
extern int signgamma;
extern int column;
extern int intflg;
extern int echoflg;
extern int sandbox;          /* when set, some functions are barred */
extern int sandboxflg;       /* when set, sandbox cannot be unset */
extern int use_readline;     /* shows that the user has a valid .inputrc */
extern int ascii_characters; /* use 7-bit ascii and map to APL characters */
extern int ifile;
extern int ttystat[3];
extern long startTime;
extern int rowsz;
extern int oldlb[MAXLAB];
extern int pt;
extern int syze;
extern int pas1;
extern int protofile;
extern int lastop;     /* last (current) operator exec'ed */
extern char* scr_file; /* scratch file name */
extern int lineNumber;
extern int normalExit;
extern int mkcore;

/* diagnostics */
extern int code_trace;
extern int mem_trace;
extern int stack_trace;
extern int vars_trace;

typedef struct {
    int rank;
    int type;
    int size;
    int dimk;
    int delk;
    int dim[MRANK];
    int del[MRANK];
    int idx[MRANK];
    char complete;
} DataIterator;

extern DataIterator idx;

#define setexit() setjmp(gbl_env)       /* "setexit" equivalent      */
#define reset() longjmp(gbl_env, 0)     /* "reset" equivalent        */
#define equal(a, b) (0 == strcmp(a, b)) /* character string equality */

#define SECURITY_CHECK \
    if (sandbox)       \
    error(ERR_security, "sand-box")

#endif // APL_H
