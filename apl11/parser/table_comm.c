/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "char.h"
#include "parser.h"
#include "y.tab.h"
#include "opt_codes.h"

struct COMM comtab[] = 
{
   "clear",	comnull,	CLEAR,
   "continue",	comnull,	CONTIN,
   "copy",	comnam,		COPY,
   "debug",	comnull,	DEBUG,
   "drop",	comlist,	DROPC,
   "license",	comnull,	LICENSE,
   "edit",	comnam,		EDIT,
   "write",	comnam,		WRITE,
   "trace",	comnull,	TRACE,
   "untrace",	comnull,	UNTRACE,
   "erase",	comlist,	ERASE,
   "fns",	comnull,	FNS,
   "lib",	comnull,	LIB,
   "load",	comnam,		LOAD,
   "off",	comnull,	OFF,
   "read",	comnam,		READ,
   "save",	comnam,		SAVE,
   "vars",	comnull,	VARS,
   "script",	comnam,		SCRIPT,
   "si",	comnull,	SICOM,
   "sic",	comnull,	SICLEAR,
   "code",	comnam,		CODE,
   "shell",	comnull,	SHELL,
   "list",	comnam,		LIST,
   "prws",	comnull,	PRWS,
   "memory",	comnull,	MEMORY,
   0,		unk
};

