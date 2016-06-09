# Makefile for parser 

include ../include/makefile.common
CFLAGS += -I../include

OBJECTS = alpha.o genlab.o getquad.o name.o \
	compile_old.o compile_new.o getnam.o invert.o yyerror.o \
	digit.o getnum.o yylex.o \
	table_oper.o table_comm.o table_quad.o \
	lastcode.o y.tab.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h local_parser.h

genlab.o compile_old.o compile_new.o yylex.o lastcode.o apl.y \
table_comm.o table_oper.o table_quad.o:	../include/opt_codes.h

y.tab.o: y.tab.c 
	$(CC) $(CFLAGS) -c y.tab.c

y.tab.c y.tab.h: apl.y
	$(YACC) -d apl.y

.c.o:
	$(CC) $(CFLAGS) -c $<

getquad.o compile_old.o compile_new.o getnam.o getnum.o yylex.o \
table_oper.o table_comm.o table_quad.o:	y.tab.h

getnum.o yylex.o table_oper.o:	../include/char.h

clean:
	rm -f $(OBJECTS) core y.tab.c y.tab.h Q.o

