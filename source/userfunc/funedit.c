/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "apl.h"
#include "utility.h"
#include "work_space.h"
#include "userfunc.h"

/*
 * funedit -- edit a file and read it in.
 *
 * If the arg to funedit is non-zero, it is used as a 
 * pointer to the file name to be used.  If it is zero,
 * the namep of the function is used for the file name.
 */

static char* bad_fn = "apl.badfn";
static int badfnsv(char* fname);

void funedit(char* fname) {
    SymTabEntry* p;
    char *c;
    #define CMD_LEN 256
    char cmd[CMD_LEN];

    p = (SymTabEntry *) expr_stack_ptr[-1];
    if (p->itemType != LV)
        error(ERR_value, "function name not found");
    sichk(p);
    if (fname == 0)
        fname = p->namep;
    c = getenv("EDITOR");
    if (c == 0) {
        c = "vi";
    }
    if (strlen(c) + 1 + strlen(fname) >= CMD_LEN) {
        error(ERR, "editor command line too long");
    }

    strncpy(cmd, c, CMD_LEN-1);
    strncat(cmd, " ", CMD_LEN-1);
    strncat(cmd, fname, CMD_LEN-1);

    if (system(cmd) < 0) {
        error(ERR, "could not start editor");
    }

    /* Read function into workspace.  If "funread" (which calls
    * "fundef") returns 0, an error occurred in processing the
    * header (line 0).  If this happened with "editf" or "del",
    * save the bad function in the file "bad_fn".
    */

    if (funread(fname) == 0 && fname == scr_file) {
        unlink(bad_fn);
        if (badfnsv(fname))
            printf("function saved in %s\n", bad_fn);
    }
}

/* This routine saves the contents of "fname" in the file
* named in "bad_fn".  It is called by "funedit" if the
* header of a function just read in is messed up (thus,
* the entire file is not lost).  Returns 1 if successful,
* 0 if not.
*/
static int badfnsv(char* fname)
{
    int fd1, fd2, len;
    char buf[512];

    if ((fd1 = open(fname, 0)) < 0 || (fd2 = creat(bad_fn, 0644)) < 0)
        return (0);
    while ((len = read(fd1, buf, 512)) > 0)
        writeErrorOnFailure(fd2, buf, len);
    close(fd1);
    close(fd2);
    return (1);
}
