/* ascii_input.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "apl.h"
#include "ascii_input.h"
#include "char.h"
#include "memory.h"
#include "utility.h"

static void init();
static char* rline(char* source);
static void addChar(char** result, int* len, int* nextIndex, char ch);

static char to_apl_symbol[256];
static bool inited = false;

void dbprint(const char* title, char* p)
{
    int i;
    fprintf(stderr, "%s >>", title);
    for (i = 0; i < strlen((char*)p); ++i) {
        if (p[i] >= 32 && p[i] <= 126)
            fprintf(stderr, "%c", p[i]);
        else
            fprintf(stderr, "<%d>", (int)((unsigned char*)p)[i]);
    }
    fprintf(stderr, "<<\n");
}

char* to_ascii_input(char* input)
{
    if (!inited)
        init();
    char* result;
    int i;
    result = rline(input);
    int len = strlen(result);
    for (i = 0; i < len; ++i) {
        result[i] = to_apl_symbol[(unsigned char)result[i]];
    }

    return result;
}

typedef struct {
    char in;
    char out;
} CharMap;

static CharMap charmap2[] = {
    { 'R', C_RHO },
    { '`', C_OVERBAR },
};

static CharMap charmap[] = {
    { 'R', C_RHO },
    { 'I', C_IOTA },
    { 'J', C_JOT },
    { 'L', C_QUAD },
    { '}', C_RIGHTARROW },
    { '$', C_LESSOREQUAL },
    { '&', C_GRATOREQUAL },
    { '#', C_NOTEQUAL },
    { 'V', C_OR },
    { 'X', C_MULTIPLY },
    { '%', C_DIVIDE },
    { '|', C_STILE },
    { 'D', C_DOWNSTILE },
    { 'S', C_UPSTILE },
    { 'O', C_CIRCLE },
    { 'N', C_DOWNTACK },
    { 'Y', C_UPARROW },
    { 'U', C_DOWNARROW },
    { '{', C_LEFTARROW },
    { 'E', C_EPSILON },
    { 'B', C_UPTACK },
    { 'G', C_DEL },
    { 'H', C_DELTA },
};

static void init()
{
    int i;

    for (i = 0; i < 256; ++i)
        to_apl_symbol[i] = i;

    for (i = 0; i < sizeof(charmap) / sizeof(charmap[0]); ++i) {
        to_apl_symbol[(uint32_t) charmap[i].in] = charmap[i].out;
    }

    inited = true;
}

static struct {
    char in[2];
    char out;
} chartab[] = {
    { "-/", C_SLASHBAR },     /* 0200 compress */
    { "-\\", C_SLOPEBAR },    /* 0201 expand */
    { "\'L", C_QUOTEQUAD },   /* 0202 quote quad */
    { "^~", C_NAND },         /* 0205 nand */
    { "V~", C_NOR },          /* 0206 nor */
    { "*O", C_CIRCLESTAR },   /* 0207 log */
    { "-O", C_CIRCLESTILE },  /* 0211 rotate */
    { "O\\", C_CIRCLESLOPE }, /* 0212 transpose */
    { "BN", C_IBEAM },        /* 0213 i beam */
    { "%L", C_QUADDIVIDE },   /* 0214 domino */
    { "A|", C_DELTASTILE },   /* 0215 grade up */
    { "V|", C_DELSTILE },     /* 0216 grade dn */
    { "O|", C_CIRCLESTILE },  /* 0217 rotate */
    { "<=", C_LESSOREQUAL },  /* 0220 less eq */
    { "=>", C_GRATOREQUAL },  /* 0221 greater eq */
    { "/=", C_NOTEQUAL },     /* 0222 not eq */
    { "^~", C_NAND },         /* 0223 nand */
    { "H|", C_DELTASTILE },   /* 0227 another grade up */
    { "G|", C_DELSTILE },     /* 0230 another grade down */
    { "BJ", C_UPTACKJOT },    /* 0241 standard execute */
    { "JN", C_DOWNTACKJOT },  /* 0242 format */
    { "CJ", C_UPSHOEJOT },    /* 0246 lamp (comment delimiter) */
    { "\0", '\0' }            /* two-characters of null ends list */
};

void putAplTouchtypeChar(char c) {
    int i;
    int done = 0;
    for (i = 0; chartab[i].out != '\0'; ++i) {
        if (c == chartab[i].out) {
            printf("%c@%c", chartab[i].in[0], chartab[i].in[1]);
            done = 1;
            break;
        }
    }

    if (!done) {
        for (i = 0; i < sizeof(charmap) / sizeof(charmap[0]); ++i) {
            if (c == charmap[i].out) {
                printf("%c", charmap[i].in);
                done = 1;
                break;
            }
        }
    }

    if (!done) {
        for (i = 0; i < sizeof(charmap2) / sizeof(charmap2[0]); ++i) {
            if (c == charmap2[i].out) {
                printf("%c", charmap2[i].in);
                done = 1;
                break;
            }
        }
    }

    if (!done) {
        printf("%c", c);
    }
}

void toAplTouchtypeChar(char output[3], char inChar) {
    int i;
    int done = 0;
    memset(output, 0, /*output length*/ 3);

    for (i = 0; chartab[i].out != '\0'; ++i) {
        if (inChar == chartab[i].out) {
            output[0] = chartab[i].in[0];
            output[1] = chartab[i].in[1];
            done = 1;
            break;
        }
    }

    if (!done) {
        for (i = 0; i < sizeof(charmap) / sizeof(charmap[0]); ++i) {
            if (inChar == charmap[i].out) {
                output[0] = charmap[i].in;
                done = 1;
                break;
            }
        }
    }

    if (!done) {
        for (i = 0; i < sizeof(charmap2) / sizeof(charmap2[0]); ++i) {
            if (inChar == charmap2[i].out) {
                output[0] = charmap2[i].in;
                done = 1;
                break;
            }
        }
    }

    if (!done) {
        output[0] = inChar;
    }
}

char *toAplTouchtypeLine(char *inLine) {
    char buf[3];
    char *output = NULL;
    int len = 32;
    int next = 0;
    char *q;
    int i;
    int inLen = strlen(inLine);
    int tailLfCount = 0;

    for (q = &inLine[inLen-1]; q >= inLine; --q) {
        if (*q == '\n') {
            ++tailLfCount;
        } else {
            break;
        }
    }

    if (tailLfCount > 1)
        inLen -= tailLfCount-1;

    for (i = 0; i < inLen; ++i) {
        toAplTouchtypeChar(buf, inLine[i]);
        for (q = buf; *q != '\0'; ++q) {
            addChar(&output, &len, &next, *q);
        }
    }
    addChar(&output, &len, &next, '\0');

    return output;
}

static void addChar(char** result, int* len, int* nextIndex, char ch)
{
    if (*result == NULL) {
        *result = (char*)alloc(32);
        *len = 32;
        *nextIndex = 0;
    }
    else if (*nextIndex == *len) {
        char* current = *result;
        *result = (char*)alloc(*len * 2);
        memcpy(*result, current, *len);
        aplfree((int*)current);
        *len *= 2;
    }

    (*result)[(*nextIndex)++] = ch;
}

static int twoCharCmp(const char* a, const char* b)
{
    register int c;

    c = (a[0] - b[0]);
    if (c != 0)
        return (c);
    return (a[1] - b[1]);
}

static char getTwoferChar(char first, char second)
{
    int i;
    char pair[2];
    pair[0] = (first <= second ? first : second);
    pair[1] = (first <= second ? second : first);

    for (i = 0; twoCharCmp(chartab[i].in, "\0\0") != 0; ++i) {
        if (twoCharCmp(chartab[i].in, pair) == 0) {
            return chartab[i].out;
        }
    }
    return 0;
}

// Translate a string from apl touchtype to internal representation.
// Multiple-character strings such as "L@%" or "O@*" map to single
// characters.
//
// And, upper-case characters such as "R" map to internal Greek letters.
// Could imagine getting around to not doing the latter eventually..
//
// Assume source is a null-terminated string.
//
// Returns a newly malloc'd string that someone else should free.
//
static char* rline(char* source)
{
    char* result = 0;
    int len = 32;
    int next = 0;
    int i;

    for (i = 0; source[i] != '\0'; ++i) {
        if (source[i + 1] != '@') {
            addChar(&result, &len, &next, source[i]);
        }
        else {
            // source[i+1] is '@'; source[i+2] may be null
            char c = getTwoferChar(source[i], source[i + 2]);
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
