# Makefile for userfunc (user defined functions)

include ../include/makefile.common

OBJECTS = badfnsv.o ex_auto.o ex_fun.o ex_nilret.o fundef.o reverse.o \
	csize.o catcode.o ex_br.o ex_ibr.o ex_rest.o funedit.o sichk.o \
	ex_arg1.o ex_br0.o ex_ibr0.o funread.o tback.o \
	ex_arg2.o ex_label.o funcomp.o funwrite.o 


Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

# Things that depend on characters
ex_fdef.o ex_ibr.o ex_ibr0.o:	char.h

csize.o funcomp.o:	opt_codes.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

