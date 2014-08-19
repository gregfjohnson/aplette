/* Copyright U S WEST Advanced Technologies, Inc. (AT&T)
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "../include/apl.h"

int   vcount;
int   scount;
int   litflag;
int   nlexsym;
int   context;
char   *iline;
char   *ccharp, *ccharp2;
data   lnumb;           /* current label number */
char   *labcpp;         /* label prologue */
char   *labcpe;         /* label epilogue */
int   immedcmd;         /* immediate command number */
char	*name();

/*static char oline[OBJS];*/
char oline[OBJS];

struct OPER
{
   int   input;
   int   lexval;
   int   retval;
};

struct COMM
{
   char   *ct_name;      /* command name string */
   int   ct_ytype;      /* command type */
   int   ct_ylval;      /* "yylval" value */
};

struct QUOD
{
   char   *qname;
   int   qtype;
   int   rtype;
};
