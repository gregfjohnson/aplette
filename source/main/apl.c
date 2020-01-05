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
                  "; \")font\" for APL touchtype font"
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

int integ;
int signgamma;
int column;
int intflg;
int echoflg = 0;
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

static void usage() {
    printf("usage:\n");
    printf("    apl\n");
    printf("        -a            # use native APL instead of default ascii touchtype font\n");
    printf("        -c            # create core file on fatal error\n");
    printf("        -d            # do not catch signals\n");
    printf("        -e            # echo input lines\n");
    printf("        -f script     # execute script\n");
    printf("        -h            # this help message\n");
    printf("        -r            # force readline use even with scripts\n");
    printf("        -s            # execute in secure sandbox\n");
    printf("        -t            # create temporary files in current directory instead of /tmp\n");
    printf("        -w workspace  # load workspace\n");
        
    exit(1);
}

int main(int argc, char** argv)
{
    int pid, sigs, file_id, use_readline_arg;
    char *ws_filename = NULL;
    char *script_filename = NULL;
    int opt;
    int help = 0;

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
    use_readline_arg = -1;

    ascii_characters = 1;

    /* diagnostics */
    mem_trace   = 0;   /* dynamic memory allocation */
    code_trace  = 0;   /* pseudo code */
    stack_trace = 0;   /* local stack */
    funtrace    = 0;   /* function execution trace */

    while ((opt = getopt(argc, argv, "acdef:hrstw:")) != -1) {
        switch (opt) {
            case 'a':
                ascii_characters = 0;
                break;
            case 'c':
                mkcore = 1;
                break;
            case 'd':
                sigs = 0;
                break;
            case 'e':
                echoflg = 1;
                break;
            case 'f':
                script_filename = optarg;
                break;
            case 'h':
                help = 1;
                break;
            case 'r':
                use_readline_arg = 1;
                break;
            case 's':
                sandbox = sandboxflg = 1;
                break;
            case 't':
                snprintf(scr_file, 32, "apled.%d", pid);
                break;
            case 'w':
                ws_filename = optarg;
                break;
        }
    }

    if (help) {
        usage();
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

    sp = stack;
    ifile = 0;
    if (signal(SIGINT, intr) == SIG_ERR) {
        signal(SIGINT, SIG_IGN);
    }

    /* script files that start with '#!apl' on first line are invoked as
     * "apl name_of_script_file" by the shell.
     * we want to get rid of that first line and not feed it to the apl
     * interpreter in that case.
     * However, unlike in other scripting languages, '#!' is a perfectly
     * legal start of an apl expression.  SOOOO.  you will inexplicably
     * have the first line of your script file 
     */
    if (script_filename != NULL) {
        if (freopen(script_filename, "r", stdin) == NULL) {
            fprintf(stderr, "could not open file '%s'\n", script_filename);
            exit(1);
        }
    }

    /* 'apl filename' is not supposed to be done directly from the command line
     * by users.  it is only intended to be done implicitly for scripts with
     * the first line '#! (apl_binary)'.  the shell translates such scripts to
     * 'apl_binary script_filename'.  in that case, we need to remove the first
     * line of the file here, since the apl interpreter will try to parse lines
     * starting '#! ..'
     */
    if (optind < argc) {
        int c;

        if (script_filename != NULL) {
            fprintf(stderr, "cannot have '-f %s' in this context.\n", script_filename);
            exit(1);
        }

        if (freopen(argv[optind], "r", stdin) == NULL) {
            fprintf(stderr, "could not open file '%s'\n", argv[optind]);
            exit(1);
        }

        while ((c = getchar() != '\n') && c != EOF);
    }

    if (isatty(0)) {
        printf("%s", headline);
    }

    if (use_readline_arg == 0 || use_readline_arg == 1) {
        use_readline = use_readline_arg;

    } else {
        use_readline = isatty(0);
    }

    if (ws_filename != NULL) {
        file_id = open(ws_filename, O_RDONLY);

        if (file_id < 0) {
            fprintf(stderr, "could not open file '%s'\n", ws_filename);
            exit(1);
        }

        wsload(file_id);
        close(file_id);

        if (isatty(0)) {
            printf(" %s\n", ws_filename);
        }

        eval_qlx(); /* eval latent expr, if any */

    } else if ((file_id = open("continue", O_RDONLY)) >= 0) {
        wsload(file_id);
        close(file_id);

        if (isatty(0)) {
            printf(" continue\n");
        }

        eval_qlx(); /* eval latent expr, if any */

    } else {
        if (isatty(0)) {
            printf("clear ws\n");
        }
    }

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
