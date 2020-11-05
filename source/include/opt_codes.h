/* Interpreter Op Codes */
/* WARNING the following must agree with optcodes.c and code_dump.c */

#define EOL 0
#define END 1
#define ADD 2
#define PLUS 3
#define SUB 4
#define MINUS 5
#define MUL 6
#define SGN 7
#define DIV 8
#define RECIP 9
#define MOD 10
#define ABS 11
#define MIN 12
#define FLOOR 13
#define MAX 14
#define CEIL 15
#define PWR 16
#define EXP 17
#define LOG 18
#define LOGE 19
#define CIR 20
#define PI 21
#define COMB 22
#define FAC 23

#define DEAL 24
#define RAND 25
#define DRHO 26
#define MRHO 27
#define DIOT 28
#define MIOT 29
#define ROT0 30
#define REV0 31
#define DTRN 32
#define MTRN 33
#define DIBM 34
#define MIBM 35

#define GDU 36
#define GDUK 37
#define GDD 38
#define GDDK 39
#define EXD 40
#define SCAN 41
#define EXDK 42
#define SCANK 43
#define IPROD 44
#define OPROD 45
#define QUAD 46
#define QQUAD 47
#define BRAN0 48
#define BRAN 49
#define DDOM 50
#define MDOM 51

#define COM 52
#define RED 53
#define COMK 54
#define REDK 55
#define ROT 56
#define REV 57
#define ROTK 58
#define REVK 59
#define CAT 60
#define RAV 61
#define CATK 62
#define RAVK 63

#define PRINT 64
#define QUOT 65
#define ELID 66
#define CQUAD 67
#define COMNT 68
#define INDEX 69
#define HPRINT 70

#define LT 71
#define LE 72
#define GT 73
#define GE 74
#define EQ 75
#define NE 76
#define AND 77
#define OR 78
#define NAND 79
#define NOR 80
#define NOT 81
#define EPS 82
#define MEPS 83
#define REP 84
#define TAKE 85
#define DROP 86
#define ASGN 88
#define IMMED 89

#define NAME 90
#define CONST 91
#define FUN 92
#define ARG1 93
#define ARG2 94
#define AUTO 95
#define REST 96

#define COM0 97
#define RED0 98
#define EXD0 99
#define SCAN0 100
#define BASE 101
#define MENC 102  /* monadic encode */
#define LABEL 103 /* statement label */

#define QLX 105 /* Quad Latent eXpression */
#define QAV 106 /* Quad Atomic Vector */
#define QTS 107 /* Quad Time Stamp */
#define QPP 108 /* Quad Print Precision */
#define QPW 109 /* Quad Print Width */
#define QCT 110 /* Quad Comparison Tolerance */
#define QIO 111 /* Quad Index Origin */

#define QRUN 112
#define QFORK 113
#define QWAIT 114
#define QEXEC 115
#define FDEF 116
#define QEXIT 117
#define QPIPE 118
#define QCHDIR 119
#define QOPEN 120
#define QCLOSE 121
#define QREAD 122
#define QWRITE 123
#define QCREAT 124
#define QSEEK 125
#define QUNLNK 126
#define QRD 127
#define QDUP 128
#define QAP 129
#define QKILL 130
#define QCRP 131
#define DFMT 132
#define MFMT 133
#define QNC 134
#define NILRET 135

#define SICLR 137
#define SICLR0 138
#define RVAL 139
#define QSIGNL 140
#define QFLOAT 141  /* Float character string to data */
#define QNL 142     /* Produce namelist */
#define QEX 143     /* Expunge added by tyl 13.8.1999 */
#define QAI 144     /* Accinfo added by tyl 13.8.1999 */
#define QARGV 145   /* command-line argument list */
#define OPT_MAX 145 /* largest opt-code */

/* System Command op-codes */
#define CLEAR 1

#define EDIT 3
#define ERASE 4
#define FNS 5

#define READ 7

#define VARS 9

#define DEBUG 11
#define OFF 12
#define LOAD 13
#define SAVE 14
#define COPY 15
#define CONTIN 16
#define LIB 17
#define DROPC 18
#define LICENSE 19
#define SCRIPT 20
#define DELL 21 /* not a system command at all \
                 * but the immediate token for \
                 * function editing */
#define TRACE 22
#define UNTRACE 23
#define WRITE 24
#define SICLEAR 25
#define SICOM 26
#define CODE 27

#define SHELL 29
#define LIST 30
#define PRWS 31
#define MEMORY 32
#define DIGITS 33
#define FONT 34
#define WIDTH 35
