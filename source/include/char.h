/* This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 dated June, 1991.
 */

/* Table of special APL characters 
 * This one file is used to define the character mapping.
 *
 * All characters have a character constant C_XXX
 * used by parser/table_oper.c
 * Some characters also have a string constant S_XXX
 * because the functions that use them need string expressions
 *
 * In order to see the characters within the comment fields
 * set the console to apl character mode and use an 8 bit editor.
 */

#define C_LEFTTACK ((char)128)   /* � */
#define C_RIGHTTACK ((char)129)  /* � */
#define C_LEFTSHOE ((char)130)   /* � */
#define C_RIGHTSHOE ((char)131)  /* � */
#define C_IBEAM ((char)132)      /* � */
#define C_RIGHTARROW ((char)133) /* � */
#define S_RIGHTARROW "�"
#define C_NOTEQUAL ((char)134) /* � */
/*                  ((char) 135)            */
/*                  ((char) 136)            */
#define C_CIRCLESTAR ((char)137) /* � */
/*                  ((char) 138)            */
#define C_DOWNARROW ((char)139) /* � */
#define C_UPARROW ((char)140)   /* � */
#define C_UPSTILE ((char)141)   /* � */
/*                  ((char) 142)            */
#define C_DOWNSTILE ((char)143) /* � */
#define C_LEFTARROW ((char)144) /* � */
#define S_LEFTARROW "�"
#define C_DELTA ((char)145)      /* � */
#define C_MULTIPLY ((char)146)   /* � */
#define C_DELTASTILE ((char)147) /* � */
/*                  ((char) 148)            */
#define C_QUAD ((char)149) /* � */
#define S_QUAD "�"
#define C_DELTILDE ((char)150)  /* � */
#define C_QUOTEQUAD ((char)151) /* � */
#define S_QUOTEQUAD "�"
#define C_QUADDIVIDE ((char)152) /* � */
/*                  ((char) 153)            */
#define C_DIERESIS ((char)154) /* � */
#define C_CENT ((char)155)     /* � the console treats this as ESC */
/*                  ((char) 156) reserved - sterling */
#define C_DELSTILE ((char)157)      /* � */
#define C_COMMABAR ((char)158)      /* � */
#define C_DIERESISTILDE ((char)159) /* � */
/*                  ((char) 160)
                            ((char) 161)
                            ((char) 162)
                            ((char) 163)
                            ((char) 164)
                            ((char) 165)            */
#define C_UPSHOEJOT ((char)166) /* � */
#define C_SLOPEBAR ((char)167)  /* � */
#define C_DIAMOND ((char)168)   /* � */
/*                  ((char) 169)
         * to               ((char) 175)            */
/*                  ((char) 176)
         * to               ((char) 178) grey scales */
/*                  ((char) 179)
         * to               ((char) 223) line draw  */
#define C_ALPHA ((char)224) /* � */
#define C_BETA ((char)225)  /* � */
#define C_IOTA ((char)226)  /* � */
/*                  ((char) 227)            */
/*                  ((char) 228)            */
#define C_NOR ((char)229)           /* � */
#define C_UPTACK ((char)230)        /* � */
#define C_DOWNTACK ((char)231)      /* � */
#define C_CIRCLESTILE ((char)232)   /* � */
#define C_CIRCLEBAR ((char)233)     /* � */
#define C_NAND ((char)234)          /* � */
#define C_SLASHBAR ((char)235)      /* � */
#define C_DEL ((char)236)           /* � */
#define C_CIRCLESLOPE ((char)237)   /* � */
#define C_EPSILON ((char)238)       /* � */
#define C_UPSHOE ((char)239)        /* � */
#define C_EQUALUNDERBAR ((char)240) /* � */
#define C_DELTAUNDERBAR ((char)241) /* � */
#define C_GRATOREQUAL ((char)242)   /* � */
#define C_LESSOREQUAL ((char)243)   /* � */
#define C_DOWNTACKJOT ((char)244)   /* � */
#define C_UPTACKJOT ((char)245)     /* � */
#define C_DIVIDE ((char)246)        /* � */
#define C_OMEGA ((char)247)         /* � */
#define C_JOT ((char)248)           /* � */
#define C_CIRCLE ((char)249)        /* � */
#define C_OR ((char)250)            /* � */
#define C_RHO ((char)251)           /* � */
#define S_RHO "�"
#define C_DOWNSHOE ((char)252) /* � */
#define C_OVERBAR ((char)253)  /* � */
#define C_STILE ((char)254)    /* � */
