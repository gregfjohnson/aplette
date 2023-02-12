/* Copyright U S WEST Advanced Technologies, Inc. (AT&T)
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#ifndef LOCAL_PARSER_H
#define LOCAL_PARSER_H

#include <stdbool.h>
#include "../include/apl.h"

extern int vcount;
extern int scount;
extern int litflag;
extern int exprOrNullFlag;
extern int nlexsym;
extern int context;
extern char* iline;
extern char *ccharp, *ccharp2;
extern data lnumb;   /* current label number */
extern char* labcpp; /* label prologue */
extern char* labcpe; /* label epilogue */
extern int immedcmd; /* immediate command number */
extern char oline[OBJS];

int yylex();

char* name(char* np, char c);
bool alpha(char s);
int digit(char s);
int isodigit(char c);
int getquad();
void yyerror(char* error);
void genlab(SymTabEntry* np);
void invert(char* a, char* b);
int getnum(char ic);
int getnam(char ic);
int lastCode(char* s);

struct OPER {
    int input;
    int lexval;
    int retval;
};

struct COMM {
    char* ct_name; /* command name string */
    int ct_ytype;  /* command type */
    int ct_ylval;  /* "yylval" value */
};

struct QUOD {
    char* qname;
    int qtype;
    int rtype;
};

#endif
