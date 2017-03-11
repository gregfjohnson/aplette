/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "apl.h"
#include "utility.h"

static int openOrCreateFile(char* fileName, int mode)
{
    int fd;

    if (mode != O_RDONLY && mode != O_WRONLY && mode != O_RDWR) {
        fd = creat(fileName, mode);
    }
    else {
        fd = open(fileName, mode);
    }

    return fd;
}

int opn(char file[], int rw)
{
    int fd;
    char f2[100];

    if ((fd = openOrCreateFile(file, rw)) < 0) {
        strcpy(f2, "/usr/lib/apl/");
        strncat(f2, file, sizeof(f2) - 1);

        if ((fd = openOrCreateFile(f2, rw)) >= 0) {
            printf("[using %s]\n", f2);
        }
        else {
            printf("can't open file %s\n", file);
            error(ERR, "");
        }
    }
    return (fd);
}

int empty(int fd)
{
    struct stat sbuf;

    /* Simulate the Rand Corp.'s "empty" system call on a
    * V7 system by seeing if the given fd is a pipe, and if
    * so, whether or not it is empty.
    */

    if (fstat(fd, &sbuf) < 0)
        return (-1); /* Can't "stat" it */
    return (sbuf.st_size == 0);
}
