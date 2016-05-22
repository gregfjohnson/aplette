#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "apl.h"
#include "ascii_input.h"
#include "../parser/char.h"

void error(int type, char *diagnostic);

static void init();

static char to_apl_symbol[256];
static bool inited = false;

static int length(const char *input) {
}

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
    int i;
    int len = strlen(input);
    char *result = (char *) alloc(len + 2);
    if (!inited) init();
    dbprint("to_ascii_input got", input);
    for (i = 0; i < len; ++i) {
        if (input[i] < 256) {
            result[i] = to_apl_symbol[input[i]];
        } else {
            result[i] = input[i];
        }
    }
    result[i] = '\0';
    dbprint("to_ascii_input returns", result);
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
    {"-/", C_SLASHBAR},        /* 0200 comprs */
    {"-\\", C_SLOPEBAR},        /* 0201 expand */
    {"\'L", C_QUOTEQUAD},        /* 0202 quote quad */
    {"^~", C_NAND},        /* 0205 nand */
    {"V~", C_NOR},        /* 0206 nor */
    {"*O", C_CIRCLESTAR},        /* 0207 log */
    {"-O", C_CIRCLESTILE},        /* 0211 rotate */
    {"O\\", C_CIRCLESLOPE},        /* 0212 transpose */
    {"BN", C_IBEAM},        /* 0213 i beam */
    {"%L", C_QUADDIVIDE},        /* 0214 domino */
    {"A|", C_DELTASTILE},        /* 0215 grade up */
    {"V|", C_DELSTILE},        /* 0216 grade dn */
    {"O|", C_CIRCLESTILE},        /* 0217 rotate */
    {"<=", C_LESSOREQUAL},        /* 0220 less eq */
    {"=>", C_GRATOREQUAL},        /* 0221 greater eq */
    {"/=", C_NOTEQUAL},        /* 0222 not eq */
    {"^~", C_NAND},        /* 0223 nand */
    {"H|", C_DELTASTILE},        /* 0227 another grade up */
    {"G|", C_DELSTILE},        /* 0230 another grade dn */
    {"BJ", C_UPTACKJOT},        /* 0241 standard execute */
    {"JN", C_DOWNTACKJOT},        /* 0242 format */
    {"\0", '\0'}        /* two-characters of null ends list */
};

void addChar(char **result, int *len, int *nextIndex, char ch) {
    if (*result == NULL) {
        *result = (char *) alloc(32);
        *len = 32;
        *nextIndex = 0;

    } else if (*nextIndex == *len) {
        char *current = *result;
        *result = (char *) alloc(*len * 2);
        memcpy(*result, current, *len);
        *len *= 2;
    }

    (*result)[(*nextIndex)++] = ch;
}

int twoCharCmp(const char *a, const char *b) {
    register int c;

    c = (a[0] - b[0]);
    if(c != 0)
        return(c);
    return(a[1] - b[1]);
}

char getTwoferChar(char first, char second) {
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

char *rline(int s) {
    char *result = 0;
    int len = 32;
    int next = 0;
    bool haveFirst = false;
    char first;
    char currentChar = getchar();
    char peekAheadChar;

    // if haveFirst is true, first is that character,
    // we have read '@', and are looking for the second
    // char of the pair.
    // else, currentChar is the most recent char read.
    // the string ends with '\n'.
    do {
        peekAheadChar = getchar();

        // vanilla case..

        if (!haveFirst && peekAheadChar != '@') {
            addChar(&result, &len, &next, currentChar);

            currentChar = peekAheadChar;
        }

        // notice based on peekAheadChar that currentChar
        // is first of a pair..

        else if (!haveFirst && peekAheadChar == '@') {
            haveFirst = true;
            first = currentChar;

        // already have first of a pair...

        } else {
            char second = peekAheadChar;
            char c = getTwoferChar(first, second);
            if (c == '\0') {
                // oops....
                error(ERR_syntax, "");
                break;

            } else {
                addChar(&result, &len, &next, c);
                haveFirst = false;
                // this will give us a char, since the string
                // ends with '\n' and '\n' is not the second
                // char of any twofer character.
                currentChar = getchar();
            }
        }
    } while (peekAheadChar != '\n');

    addChar(&result, &len, &next, '\n');
    addChar(&result, &len, &next, '\0');

    // fprintf(stderr, "rline returns "); dbprint(result);

    return result;
}
