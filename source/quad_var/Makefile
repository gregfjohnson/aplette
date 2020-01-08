# Makefile for quad_var (quad variables) 

include ../include/makefile.common
CFLAGS += -I../include -I../main

OBJECTS = ex_quad.o ex_qquad.o \
	ex_qav.o ex_qct.o ex_qio.o ex_qlx.o ex_qpp.o ex_qpw.o \
	ex_qts.o ex_qai.o ex_qargv.o

all: Q.o

Q.o:	$(OBJECTS)
	$(LD) -r -o Q.o $(OBJECTS)

$(OBJECTS):	../include/apl.h

# Things that depend on characters
ex_qav.o ex_qlx.o ex_qpp.o ex_qpw.o ex_quad.o :	../include/char.h

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) core

