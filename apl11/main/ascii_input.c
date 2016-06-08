/* ascii_input.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "apl.h"
#include "ascii_input.h"
#include "char.h"
#include "memory.h"
#include "utility.h"

static void init();
static char *rline(char *source);

static char to_apl_symbol[256];
static bool inited = false;

void dbprint(const char *title, char *p) {
    int i;
    fprintf(stderr, "%s >>", title);
    for (i = 0; i < strlen((char *) p); ++i) {
        if (p[i] >= 32 && p[i] <= 126)
            fprintf(stderr, "%c", p[i]);
        else
            fprintf(stderr, "<%d>", (int) ((unsigned char *) p)[i]);
    }
    fprintf(stderr, "<<\n");
}

char *to_ascii_input(char *input) {
    if (!inited) init();
    char *result;
    int i;
    result = rline(input);
    int len = strlen(result);
    for (i = 0; i < len; ++i) {
        result[i] = to_apl_symbol[(unsigned char) result[i]];
    }

    return result;
}

static struct {
    char in;
    char out;
} charmap[] = {
    {'R', C_RHO},
    {'I', C_IOTA},
    {'J', C_JOT},
    {'L', C_QUAD},
    {'}', C_RIGHTARROW},
    {'$', C_LESSOREQUAL},
    {'&', C_GRATOREQUAL},
    {'#', C_NOTEQUAL},
    {'V', C_OR},
    {'X', C_MULTIPLY},
    {'%', C_DIVIDE},
    {'|', C_STILE},
    {'D', C_DOWNSTILE},
    {'S', C_UPSTILE},
    {'O', C_CIRCLE},
    {'N', C_DOWNTACK},
    {'Y', C_UPARROW},
    {'U', C_DOWNARROW},
    {'{', C_LEFTARROW},
    {'E', C_EPSILON},
    {'B', C_UPTACK},
};

static void init() {
    int i;
    for (i = 0; i < 256; ++i) to_apl_symbol[i] = i;
    for (i = 0; i < sizeof(charmap) / sizeof(charmap[0]); ++i) {
        to_apl_symbol[charmap[i].in] = charmap[i].out;
    }
    inited = true;
}

static struct {
    char in[2];
    char out;
} chartab[] =
{
    {"-/", C_SLASHBAR},                 /* 0200 comprs */
    {"-\\", C_SLOPEBAR},                /* 0201 expand */
    {"\'L", C_QUOTEQUAD},               /* 0202 quote quad */
    {"^~", C_NAND},                     /* 0205 nand */
    {"V~", C_NOR},                      /* 0206 nor */
    {"*O", C_CIRCLESTAR},               /* 0207 log */
    {"-O", C_CIRCLESTILE},              /* 0211 rotate */
    {"O\\", C_CIRCLESLOPE},             /* 0212 transpose */
    {"BN", C_IBEAM},                    /* 0213 i beam */
    {"%L", C_QUADDIVIDE},               /* 0214 domino */
    {"A|", C_DELTASTILE},               /* 0215 grade up */
    {"V|", C_DELSTILE},                 /* 0216 grade dn */
    {"O|", C_CIRCLESTILE},              /* 0217 rotate */
    {"<=", C_LESSOREQUAL},              /* 0220 less eq */
    {"=>", C_GRATOREQUAL},              /* 0221 greater eq */
    {"/=", C_NOTEQUAL},                 /* 0222 not eq */
    {"^~", C_NAND},                     /* 0223 nand */
    {"H|", C_DELTASTILE},               /* 0227 another grade up */
    {"G|", C_DELSTILE},                 /* 0230 another grade dn */
    {"BJ", C_UPTACKJOT},                /* 0241 standard execute */
    {"JN", C_DOWNTACKJOT},              /* 0242 format */
    {"\0", '\0'}                        /* two-characters of null ends list */
};

static void addChar(char **result, int *len, int *nextIndex, char ch) {
    if (*result == NULL) {
        *result = (char *) alloc(32);
        *len = 32;
        *nextIndex = 0;

    } else if (*nextIndex == *len) {
        char *current = *result;
        *result = (char *) alloc(*len * 2);
        memcpy(*result, current, *len);
        aplfree((int *) current);
        *len *= 2;
    }

    (*result)[(*nextIndex)++] = ch;
}

static int twoCharCmp(const char *a, const char *b) {
    register int c;

    c = (a[0] - b[0]);
    if(c != 0)
        return(c);
    return(a[1] - b[1]);
}

static char getTwoferChar(char first, char second) {
    int i;
    char pair[2];
    pair[0] = (first <= second ? first  : second);
    pair[1] = (first <= second ? second : first);

    for (i = 0; twoCharCmp(chartab[i].in, "\0\0") != 0; ++i) {
        if (twoCharCmp(chartab[i].in, pair) == 0) {
            return chartab[i].out;
        }
    }
    return 0;
}

static char *rline(char *source) {
    char *result = 0;
    int len = 32;
    int next = 0;
    int i;

    for (i = 0; source[i] != '\0'; ++i) {
        if (source[i+1] != '@') {
            addChar(&result, &len, &next, source[i]);

        } else {
            char c = getTwoferChar(source[i], source[i+2]);
            if (c == '\0') {
                error(ERR_syntax, "");
                break;
            }
            addChar(&result, &len, &next, c);
            i += 2;
        }
    }

    addChar(&result, &len, &next, '\n');
    addChar(&result, &len, &next, '\0');

    // dbprint("rline returns", result);

    return result;
}
