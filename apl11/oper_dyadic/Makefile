# Makefile for oper_dyadic (dyadic operators)

include ../include/makefile.common

OBJECTS = ex_iprod.o ex_oprod.o ex_asgn.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	apl.h

ex_asgn.o:	char.h

.c.o:
	$(CC) $(CFLAGS) -c $<

