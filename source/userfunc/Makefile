# Makefile for userfunc (user defined functions)

include ../include/makefile.common
CFLAGS += -I../include -I../parser

OBJECTS = ex_auto.o ex_fun.o ex_nilret.o fundef.o \
	csize.o ex_br.o ex_ibr.o ex_rest.o funedit.o sichk.o \
	ex_arg1.o ex_ibr0.o funread.o tback.o \
	ex_arg2.o ex_label.o funcomp.o funwrite.o \
    funstdin.o context.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

# Things that depend on characters
ex_fdef.o ex_ibr.o ex_ibr0.o:	../include/char.h

csize.o funcomp.o:	../include/opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

