/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "apl.h"
#include "config.h"
#include "utility.h"
#include "main.h"
#include "data.h"
#include "work_space.h"
#include "quad_func.h"

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#endif

char headline[] = "aplette "
                  "Version 0"
#include "version.h"
                  "\n";

data tolerance;
int iorigin;
int pagewidth;
int PrintP;
char quote_quad_prompt[quote_quad_limit + 1];
data zero;
data one;
data pi;
data datum;
int funtrace;         /* function trace enabled */
int labgen;           /* label processing being done */
jmp_buf cold_restart; /* Used for setexit/reset */
jmp_buf hot_restart;  /* Used for setexit/reset */

int (*exop[])();
int integ;
int signgam;
int column;
int intflg;
int echoflg;
int sandbox;          /* when set, some functions are barred */
int sandboxflg;       /* when set, sandbox cannot be unset */
int use_readline;     /* shows that the user has a valid .inputrc */
int ascii_characters; /* use 7-bit ascii and map to APL characters */
int ifile;
int ttystat[3];
long startTime;
int rowsz;
int oldlb[MAXLAB];
int pt;
int syze;
int pas1;
int protofile;
int lastop;     /* last (current) operator exec'ed */
char* scr_file; /* scratch file name */
int lineNumber;
int normalExit;
int mkcore;
int code_trace;
int mem_trace;
int stack_trace;
int vars_trace;
DataIterator idx;
Context *gsip, prime_context;

CompilePhase compilePhase;

int main(int argc, char** argp)
{
    int pid, sigs, file_id;
    static int fflag;

#ifdef HAVE_LIBREADLINE
    /* Allow conditional parsing of the ~/.inputrc file. */
    rl_readline_name = "aplette";
#endif

    mkcore = 0;           /* if "1", produce core image upon fatal error */
    normalExit = 0;       /* set to true when doing a normal exit */
    sandboxflg = 0;       /* initial security value, changed by command line */
    sandbox = sandboxflg; /* sandbox is set whenever Quad-LX is run,
   				 * upon return it is set to sandboxflg */
    time(&startTime);

    /* setup scratch files */
    pid = getpid();
    scr_file = malloc(32);
    snprintf(scr_file, 32, "/tmp/apled.%d", pid);

    symtab_init();

    sigs = 1;

    /* other flags... */
    echoflg = !isatty(0);
    use_readline = 1;
    ascii_characters = 1;

    /* diagnostics */
    mem_trace = 0;   /* dynamic memory allocation */
    code_trace = 0;  /* pseudo code */
    stack_trace = 0; /* local stack */
    funtrace = 0;

    while (argc > 1 && argp[1][0] == '-') {
        argc--;
        argp++;
        while (*++*argp)
            switch (**argp) {
            case 'e':
                echoflg = 1;
                break;
            case 'q':
                echoflg = 0;
                break;
            case 'd':
            case 'D':
                sigs = 0;
                break;
            case 'c':
            case 'C':
                mkcore = 1;
                break;
            case 'a':
                ascii_characters = 0;
                break;
            case 'A':
                ascii_characters = 0;
                break;
            case 'r':
                use_readline = 1;
                break;
            case 'R':
                use_readline = 1;
                break;
            case 't':
                scr_file += 5;
                break;
            case 's':
                sandbox = sandboxflg = 1;
                break;
            }
    }

    /* initialisation */
    iorigin = INITIAL_iorigin;
    pagewidth = INITIAL_pagewidth;
    PrintP = INITIAL_PrintP;
    tolerance = INITIAL_tolerance;
    quote_quad_prompt[0] = '\0';

    zero = 0;
    one = 1;
    pi = 3.141592653589793238462643383;

    if (sigs)
        catchsigs(); /*   Catch signals  */
    fppinit(0);

    /*
    * open ws file
    */

    sp = stack;
    fflag = 1;
    ifile = 0;
    if (signal(SIGINT, intr) == SIG_ERR)
        signal(SIGINT, SIG_IGN);
    printf("%s", headline);
    //setexit();
    if (fflag) {
        fflag = 0;
        if (argc > 1 && (file_id = opn(argp[1], O_RDONLY)) > 0) {
            wsload(file_id);
            printf(" %s\n", argp[1]);
            close(file_id);
        }
        else {
            if ((file_id = open("continue", 0)) < 0)
                printf("clear ws\n");
            else {
                wsload(file_id);
                printf(" continue\n");
                close(file_id);
            }
        }
        eval_qlx(); /* eval latent expr, if any */
    }
    //setjmp(reset_env);
    /* return to this point to reset the state and context to original */
    setjmp(cold_restart);

    gsip = &prime_context; /* global state indicator */
    gsip->Mode = immed;
    gsip->suspended = 0;
    gsip->prev = (Context*)NULL;
    gsip->sp = 0;
    gsip->ptr = 0;
    gsip->text = (char*)NULL;
    gsip->pcode = (char*)NULL;
    //gsip->xref=(char *)NULL;
    //setjmp(gsip->env);	/* come back here after longjmp() */

    mainloop();
}
