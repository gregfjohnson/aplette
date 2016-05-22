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

#define C_LEFTTACK	(char)128	/* Ä */
#define C_RIGHTTACK	(char)129	/* Å */
#define C_LEFTSHOE	(char)130	/* Ç */
#define C_RIGHTSHOE	(char)131	/* É */
#define C_IBEAM		(char)132	/* Ñ */
#define C_RIGHTARROW	(char)133	/* Ö */
#define S_RIGHTARROW	"Ö"
#define C_NOTEQUAL	(char)134	/* Ü */
#define C_CIRCLESTAR	(char)137	/* â */
#define C_DOWNARROW	(char)139	/* ã */
#define C_UPARROW	(char)140	/* å */
#define C_UPSTILE	(char)141	/* ç */
#define C_DOWNSTILE	(char)143	/* è */
#define C_LEFTARROW	(char)144	/* ê */
#define S_LEFTARROW	"ê"
#define C_DELTA		(char)145	/* ë */
#define C_MULTIPLY	(char)146	/* í */
#define C_DELTASTILE	(char)147	/* ì */
#define	C_QUAD		(char)149	/* ï */
#define S_QUAD		"ï"
#define C_DELTILDE	(char)150	/* ñ */
#define C_QUOTEQUAD	(char)151	/* ó */
#define S_QUOTEQUAD	"ó"
#define C_QUADDIVIDE	(char)152	/* ò */
#define C_DIERESIS	(char)154	/* ö */
#define C_CENT		(char)155	/* õ the console treats this as ESC */
#define C_DELSTILE	(char)157	/* ù */
#define C_COMMABAR	(char)158	/* û */
#define C_DIERESISTILDE	(char)159	/* ü */
#define C_UPSHOEJOT	(char)166	/* ¶ */
#define C_SLOPEBAR	(char)167	/* ß */
#define C_DIAMOND	(char)168	/* ® */
#define C_ALPHA		(char)224	/* ‡ */
#define C_BETA		(char)225	/* · */
#define C_IOTA		(char)226	/* ‚ */
#define C_NOR		(char)229	/* Â */
#define C_UPTACK	(char)230	/* Ê */
#define C_DOWNTACK	(char)231	/* Á */
#define C_CIRCLESTILE	(char)232	/* Ë */
#define C_CIRCLEBAR	(char)233	/* È */
#define C_NAND		(char)234	/* Í */
#define C_SLASHBAR	(char)235	/* Î */
#define C_DEL		(char)236	/* Ï */
#define C_CIRCLESLOPE	(char)237	/* Ì */
#define C_EPSILON	(char)238	/* Ó */
#define C_UPSHOE	(char)239	/* Ô */
#define C_EQUALUNDERBAR	(char)240	/*  */
#define C_DELTAUNDERBAR	(char)241	/* Ò */
#define C_GRATOREQUAL	(char)242	/* Ú */
#define C_LESSOREQUAL	(char)243	/* Û */
#define C_DOWNTACKJOT	(char)244	/* Ù */
#define C_UPTACKJOT	(char)245	/* ı */
#define C_DIVIDE	(char)246	/* ˆ */
#define C_OMEGA		(char)247	/* ˜ */
#define C_JOT		(char)248	/* ¯ */
#define C_CIRCLE	(char)249	/* ˘ */
#define C_OR		(char)250	/* ˙ */
#define C_RHO		(char)251	/* ˚ */
#define S_RHO		"˚"
#define C_DOWNSHOE	(char)252	/* ¸ */
#define C_OVERBAR	(char)253	/* ˝ */
#define C_STILE		(char)254	/* ˛ */
