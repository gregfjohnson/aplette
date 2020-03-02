/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */


/******************* C declarations ************************/
%{
#include "memory.h"
#include "debug.h"
#include "local_parser.h"
#include "opt_codes.h"
#include "data.h"
%}

/***************** YACC declarations **********************/
%union {
    char   *charptr;
    char   charval;
}
/* terminal tokens */

/* fake tokens that are created by compile_new() to
 * guide the parser; in some cases different behaviors
 * are required for the same input string for different
 * contexts.
 */
%term compile_immed
%term compile_quad_input
%term compile_function_defn
%term compile_function_prolog
%term compile_function_epilog
%term compile_function_body

%term lpar rpar lbkt rbkt eol unk dell
%term null dot colon semi comnt tran
%term <charptr> strng nam numb nfun mfun dfun
%term <charval> com com0 q_var asg
%term <charval> comnam comnull comlist comExpr comExprOrNull
%term <charval> dscal mdscal
%term <charval> m d md msub mdsub

/* non terminal tokens */
%type <charptr> func header args autos labels label
%type <charptr> fstat fstat0 stat statement output expr
%type <charptr> e1 e2 number subs sub monadic
%type <charptr> dyadic subr anyname hprint
%type <charval> command lsub monad smonad sdyad
%type <charval> comp dyad mdcom mondya scalar

/******************** grammar specification *****************/
/***************** line-at-a-time APL compiler **************/
/*
 * first lexical character is a fake character created by
 * callers of compile_{old,new}.c to give context.
 * (compile executable expression, function header, function
 * body expression, etc.)
 */

%%

line:
    /* The top level definition of a line:
     * if its not an assignment, a comment or already printed
     * then print it.
     */
    compile_immed stat
    {
        *ccharp = END;
        integ = lastCode(oline);
        if (integ != ASGN && integ != PRINT && integ != COMNT) *ccharp++ = PRINT;
        *ccharp++ = EOL;
    } |

    /* normally blank lines are not sent to the parser
     * but a line containing only a comment looks like
     * a blank line because lex discards all its contents
     */
    compile_immed eol
    {
        *ccharp++ = COMNT;
        *ccharp++ = EOL;
    } |
   
    /* system commands are unlike ordinary expressions */
    compile_immed bcommand command eol
    {
        *ccharp++ = IMMED;
        *ccharp++ = $3;
    } | 

    /* invoking the function editor is treated like 
    * a system command using the execute-immediate token.
    */
    compile_immed dell func
    {
        *ccharp++ = IMMED;
        /* *ccharp++ = EDITF; */
        *ccharp++ = DELL;
    } |

    /* immediate mode state indicator stuff */
    compile_immed tran eol
    {
        *ccharp++ = SICLR0;
    } |
    compile_immed tran expr eol
    {
        *ccharp++ = SICLR;
    } |

    /* quad input */
    compile_quad_input stat |

    /* function definition */
    compile_function_defn dell func |

    /* function prolog */
    compile_function_prolog dell func |

    /* function epilog */
    compile_function_epilog dell func |

    /* function body */
    compile_function_body fstat ;

/* function header */
func:
    anyname asg header
    {
        switch(context) {

        case compile_function_prolog:
            name($$, AUTO);
            /* see comments in funcomp() concerning
             * label processing.
             */
            *ccharp++ = ELID;
            break;

        case compile_function_epilog:
            ccharp2 = ccharp;
            *ccharp++ = EOL;
            name($$, RVAL);
            name($$, REST);
            invert($3, ccharp2);
        }
    } |

    header
    {
        if(context == compile_function_prolog) *ccharp++ = ELID;

        if(context == compile_function_epilog){
            *ccharp++ = EOL;      /* pop previous result */
            *ccharp++ = NILRET;   /* return empty result */
        }
    } ;

header:
    args autos
    {
        if (context == compile_function_epilog) invert($$, $2);
    } ;

args:
    anyname anyname anyname
    {
        switch(context) {

        case compile_immed:
            name($2, NAME);
            break;

        case compile_function_defn:
            $$ = ccharp;
            name($2, DF);
            break;

        case compile_function_prolog:
            $$ = ccharp;
            name($3, ARG2);
            name($1, ARG1);
            break;

        case compile_function_epilog:
            $$ = ccharp;
            name($1, REST);
            name($3, REST);
        }
    } |

    anyname anyname
    {
        switch(context) {

        case compile_immed:
            name($1, NAME);
            break;

        case compile_function_defn:
            $$ = ccharp;
            name($1, MF);
            break;

        case compile_function_prolog:
            $$ = ccharp;
            name($2, ARG1);
            break;

        case compile_function_epilog:
            $$ = ccharp;
            name($2, REST);
        }
    } |

    anyname
    {
        switch(context) {

        case compile_immed:
            name($$, NAME);
            break;

        case compile_function_defn:
            name($$, NF);
            /* no break, fall through to compile_function_prolog/epilog4 */

        case compile_function_prolog:
        case compile_function_epilog:
            $$ = ccharp;
            break;
        }
    } ;

autos:
    semi nam autos
    {
        $$ = $3;

        switch(context) {
            case compile_function_prolog:
                name($2, AUTO);
                break;

            case compile_function_epilog:
                ccharp2 = name($2, REST);
                invert($$, ccharp2);
        }
    } |

    eol
    {
        $$ = ccharp;
    } ;

/* system commands */
bcommand:
    rpar
    {
        litflag = -1;
    } ;

command:
    comExprOrNull exprOrNull |
    comExpr expr |
    comnam anyname
    {
        name($2, NAME);
    } |
    comlist anylist |
    comnull ;

exprOrNull:
    expr
    {
        exprOrNullFlag = 1;
    } |
    {
        exprOrNullFlag = 0;
    }
    ;

anylist:
    anylist anyname
    {
       *ccharp++ = IMMED;
       *ccharp++ = immedcmd;
       name($2, NAME);
    } |
    anyname
    {
       name($1, NAME);
    };

/*
 * statement:
 *   comments
 *   expressions
 *   heterogeneous output
 *   transfers (in functions)
 */
fstat:
    dell eol
    {  
        *ccharp++ = COMNT;
    } |
    eol
    {
        *ccharp++ = COMNT;
    } |
    labels eol
    {
        *ccharp++ = COMNT;
    } |
    labels fstat0 |
    fstat0;

labels:
    label |
    labels label;

label:
    anyname colon
    {
        if(labgen) genlab((SymTabEntry *) $1);
    }  ;

fstat0:
    stat
    {
        *ccharp = END;
        integ = lastCode(oline);
        if (integ != ASGN && integ != PRINT && integ != COMNT) *ccharp++ = PRINT;
    } |
    tran eol
    {
        $$ = ccharp;
        *ccharp++ = BRAN0;
    } |
    tran expr eol
    {
        $$ = $2;
        *ccharp++ = BRAN;
    } ;

stat:
    statement eol ;

statement:
    expr |
    hprint ;

hprint:
    expr hsemi output ;

output:
    expr
    {
        *ccharp++ = PRINT;
    } |
    hprint ;

hsemi:
    semi
    {
        *ccharp++ = HPRINT;
    };

expr:
    e1 |
    monadic expr
    {
        invert($$, $2);
    } |
    e1 dyadic expr
    {
        invert($$, $3);
    } ;

e1:
    e2 |
    e2 lsub subs rbkt
    {
        invert($$, $3);
        *ccharp++ = INDEX;
        *ccharp++ = scount;
        scount = $2;
    } ;

e2:
    nfun
    {
        $$ = name($$, FUN);
    } |
    nam
    {
        $$ = name($$, NAME);
    } |
    strng
    {
        $$ = ccharp;
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
        ((struct chrstrct *)$$)->c[0] = QUOT;
        ((struct chrstrct *)$$)->c[1] = vcount;
    } |
    vector
    {
        *ccharp++ = CONST;
        *ccharp++ = vcount;
        invert($$, ccharp-2);
    } |
    lpar expr rpar
    {
        $$ = $2;
    } |
    q_var
    {
        $$ = ccharp;
        *ccharp++ = $1;
    } ;

vector:
    number vector
    {
        vcount++;
    } |
    number
    {
        vcount = 1;
    } ;

number:
    numb
    {
        $$ = ccharp;
        ccharp += copy(DA, (char *) &datum, (char *) ccharp, 1);
    } ;

/*
 * indexing subscripts
 * optional expressions separated by semi
 */
lsub:
    lbkt
    {
        $$ = scount;
        scount = 1;
    } ;

subs:
    sub |
    subs semi sub
    {
        invert($$, $3);
        scount++;
    } ;

sub:
    expr |
    {
        $$ = ccharp;
        *ccharp++ = ELID;
    } ;

/* return a string of a monadic operator.  */
monadic:
    monad
    {
        $$ = ccharp;
        *ccharp++ = $1;
    } |
    smonad subr
    {
        $$ = $2;
        *ccharp++ = $1+1;
    } |
    mfun
    {
        $$ = name($$, FUN);
    } |
    scalar comp
    {
        $$ = ccharp;
        *ccharp++ = $2+1;
        *ccharp++ = $1;
    } |
    scalar com subr
    {
        $$ = $3;
        *ccharp++ = $2+3;
        *ccharp++ = $1;
    } ;

monad:
    m |
    msub |
    mondya
    {
        $$++;
    } ;

smonad:
    msub |
    mdsub
    {
        $$ += 2;
    } ;

/* return a string of a dyadic operator.  */
dyadic:
    dyad
    {
        $$ = ccharp;
        *ccharp++ = $1;
    } |
    sdyad subr
    {
        $$ = $2;
        *ccharp++ = $1;
    } |
    dfun
    {
        $$ = name($$, FUN);
    } |
    null dot scalar
    {
        $$ = ccharp;
        *ccharp++ = OPROD;
        *ccharp++ = $3;
    } |
    scalar dot scalar
    {
        $$ = ccharp;
        *ccharp++ = IPROD;
        *ccharp++ = $1;
        *ccharp++ = $3;
    } ;

sdyad:
    mdcom
    {
        $$ += 2;
    } ;

/* single expression subscript 
 * as found on operators to select a dimension.
 */
subr:
    lbkt expr rbkt
    {
        $$ = $2;
    } ;

/* various combinations */
comp:
    com | com0 ;

dyad:
    mondya | dscal | d | com0 | asg | com ;

mdcom:
    mdsub | com ;

mondya:
    mdscal | md | mdsub ;

scalar:
    mdscal | dscal ;

anyname:
    nam | nfun | mfun | dfun ;

%%
