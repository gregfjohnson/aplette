#include "local_parser.h"

int vcount;
int scount;
int litflag;
int exprOrNullFlag;
int nlexsym;
int context;
char* iline;
char *ccharp, *ccharp2;
data lnumb;   /* current label number */
char* labcpp; /* label prologue */
char* labcpe; /* label epilogue */
int immedcmd; /* immediate command number */
char oline[OBJS];
