/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "apl.h"
#include "utility.h"
#include "main.h"
#include "work_space.h"

void intr(int s)
{
    intflg = 1;
    /* legacy code: what is the following line supposed to do? */
    /* lseek(0, 0L, 2); */
    error(ERR_interrupt, "");
}

void catchsigs()
{
    extern void panic();

#ifdef SIGINT
    signal(SIGINT, intr);
#endif
#ifdef SIGINT
    signal(SIGHUP, panic);
#endif
#ifdef SIGQUIT
    signal(SIGQUIT, panic);
#endif
#ifdef SIGILL
    signal(SIGILL, panic);
#endif
#ifdef SIGTRAP
    signal(SIGTRAP, panic);
#endif
#ifdef SIGEMT
    signal(SIGEMT, panic);
#endif
#ifdef SIGBUS
    signal(SIGBUS, panic);
#endif
    signal(SIGSEGV, panic);
#ifdef SIGSYS
    signal(SIGSYS, panic);
#endif
#ifdef SIGPIPE
    signal(SIGPIPE, panic);
#endif
#ifdef SIGTERM
    signal(SIGTERM, panic);
#endif
#ifdef SIGABRT
    signal(SIGABRT, panic);
#endif
}

void panic(int signum)
{

    int fd;
    static int insane = 0; /* if != 0, die */
    static char* abt_file = "aplws.abort";
    static char* errtbl[] = {
        "excessive eofs",
        "hangup",
        "interrupt",
        "quit",
        "illegal instruction",
        "trace trap",
        "i/o trap instruction",
        "emt trap",
        "floating exception",
        "kill",
        "bus error",
        "segmentation violation",
        "bad system call",
        "write no pipe",
        "alarm clock",
        "software termination"
    };

    if (normalExit)
        exit(0);

    /* Attempt to save workspace.  A signal out of here always
    * causes immediate death.
    */

    printf("\nfatal signal: %s\n", errtbl[(signum < NSIG) ? signum : 0]);

    /* enable some or all of the following whilst debugging */
    /* mem_dump(); */
    /* stack_dump(); */
    /* code_dump(TBA!!!) */
    if (mkcore)
        abort();

    if (!insane++) {
        if ((fd = creat(abt_file, 0644)) >= 0) {
            printf("[attempting ws dump]\n");
            wssave(fd);
            printf(" workspace saved in %s\n", abt_file);
            close(fd);
        }
        else
            printf("workspace lost -- sorry\n");
    }
    else
        printf("recursive errors: unrecoverable\n");

    Exit(0);
}
