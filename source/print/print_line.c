#include <string.h>
#include "main.h"

void printLine(char *line) {
    int i;
    int len = strlen(line);

    for (i = 0; i < len; ++i) {
        putAplTouchtypeChar(line[i]);
    }
}
