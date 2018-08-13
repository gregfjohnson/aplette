/* font_map.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdio.h>
#include <string.h>

static char *font_map[][2] = {
    { "1 2.3 4e5", "numbers" },
    { "`1 `2.3 `4e`5", "negative numbers" },
    { "+", "add", },
    { "-", "subtract", },
    { "X", "multiply", },
    { "%", "divide", },
    { "*", "power", },
    { "*@O", "log", },
    { "{", "assign", },
    { "I", "index (iota)", },
    { "R", "dimension (rho)", },
    { "|", "absolute value", },
    { ",", "concatenate", },
    { "/", "reduce", },
    { "-@/", "reduce on first axis", },
    { "\\", "scan", },
    { "-@\\", "scan on first axis", },
    { "O@|", "rotate", },
    { "O@-", "rotate on first axis", },
    { "O@\\", "transpose", },
    { "%@L", "invert (regress)", },
    { "J", "outer product", },
    { ".", "inner product", },
    { "|@H", "grade up", },
    { "|@G", "grade down", },
    { "J@N", "format", },
    { "J@B", "execute", },
    { "'", "quote", },
    { "<", "less than", },
    { "<@= or $", "less than or equal", },
    { "=", "equal", },
    { ">@= or &", "greater than or equal", },
    { ">", "greater than", },
    { "/@= or #", "not equal", },
    { "L", "quad", },
    { "}", "right arrow", },
    { "V", "or", },
    { "^", "and", },
    { "D", "minimum", },
    { "S", "maximum", },
    { "O", "circle", },
    { "!", "factorial", },
    { "N", "encode", },
    { "B", "decode", },
    { "Y", "take", },
    { "U", "drop", },
    { "E", "element of", },
    { "?", "deal", },
    { "~", "not", },
    { "~@V", "nor", },
    { "~@^", "nand", },
    { "B@N", "I-beam", },
    { "G", "del", },
    { "\'@L", "quote quad", },
    { "J@C", "comment", },
    { "(", "left paren", },
    { ")", "right paren", },
    { "[", "left bracket", },
    { "]", "right bracket", },
    { ";", "semicolon", },
    { ":", "colon", },
};

static int font_map_len = sizeof(font_map) / sizeof(font_map[0]);

void font_map_print() {
    int i;
    int left_max_font_len  = 0, left_max_desc_len  = 0;
    int right_max_font_len = 0, right_max_desc_len = 0;
    int right_start = (font_map_len+1) / 2;
    int two_col_len = font_map_len / 2;
    char format[64];

    for (i = 0; i < right_start; ++i) {
        if (left_max_font_len < strlen(font_map[i][0])) {
            left_max_font_len = strlen(font_map[i][0]);
        }
        if (left_max_desc_len < strlen(font_map[i][1])) {
            left_max_desc_len = strlen(font_map[i][1]);
        }
    }

    for (i = right_start; i < font_map_len; ++i) {
        if (right_max_font_len < strlen(font_map[i][0])) {
            right_max_font_len = strlen(font_map[i][0]);
        }
        if (right_max_desc_len < strlen(font_map[i][1])) {
            right_max_desc_len = strlen(font_map[i][1]);
        }
    }
    sprintf(format, "%c%ds : %c%ds || %c%ds %cc %c%ds\n",
                    '%', left_max_font_len,  '%', left_max_desc_len,
                    '%', right_max_font_len, '%', '%', right_max_desc_len);

    for (i = 0; i < two_col_len; ++i) {
        printf(format, font_map[i][0], font_map[i][1],
                       font_map[i+right_start][0], ':', font_map[i+right_start][1]);
    }

    if (font_map_len % 2 == 1) {
        printf(format, font_map[right_start-1][0], font_map[right_start-1][1],
                       "", ' ', "");
    }
}
