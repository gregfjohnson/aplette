/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "char.h"
#include "parser.h"
#include "y.tab.h"
#include "opt_codes.h"

/*
 *   qtab -- table of valid quad variables and quad functions
 *   the format of the qtab is the similar to tab, above
 *
 */
struct QUOD qtab[] =
{
   "lx",	QLX,	q_var,
   "av",	QAV,	q_var,
   "ai",	QAI,	q_var,
   "ts",	QTS,	q_var,
   "pp",	QPP,	q_var,
   "pw",	QPW,	q_var,
   "ct",	QCT,	q_var,
   "io",	QIO,	q_var,
   "run",	QRUN,	m,
   "fork",	QFORK,	m,
   "wait",	QWAIT,	m,
   "exec",	QEXEC,	m,
   "cr",	QCRP,	m,
   "fx",	FDEF,	m,
   "exit",	QEXIT,	m,
   "pipe",	QPIPE,	m,
   "chdir",	QCHDIR,	m,
   "open",	QOPEN,	d,
   "close",	QCLOSE,	m,
   "read",	QREAD,	d,
   "write",	QWRITE,	d,
   "creat",	QCREAT,	d,
   "seek",	QSEEK,	m,
   "kill",	QKILL,	d,
   "rd",	QRD,	m,
   "rm",	QUNLNK,	m,
   "dup",	QDUP,	m,
   "ap",	QAP,	d,
   "nc",	QNC,	m,
   "sig",	QSIGNL,	d,
   "float",	QFLOAT,	m,
   "nl",	QNL,	m,
   "ex",	QEX,	m,
   0
};
